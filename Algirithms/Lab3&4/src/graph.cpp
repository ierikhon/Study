#include "graph.h"
#include <cstdio>
#include <QQueue>


Graph::Graph()
{
    gr = nullptr;
    ResetIts();
}

Graph::~Graph()
{
    Clear();
}

void Graph::Clear()
{
    Clear(gr);
    gr = nullptr;
    marked = nullptr;
    stupidnames = 0;
}

void Graph::Clear(List *ls, Elem* el)
{
    if (ls != nullptr) {
        if (ls->next != nullptr)
            Clear(ls->next, el);
        RemoveEdge(el, ls->node);
    }
}

void Graph::Clear(Elem *gr)
{
    if (gr){
        if (gr->next != nullptr) {
            Clear(gr->next);
        }
        Clear(gr->childs, gr);
        RemoveElem(gr->name);
    }
}

Elem *Graph::it()
{
    if (pos == nullptr)
        pos = gr;
    else
    {
        if (gr)
            pos = pos->next;
    }
    return pos;
}

List *Graph::it(Elem *el, bool marked)
{
    if (el == nullptr)
        lpos = nullptr;
    else{
        if (lpos == nullptr){
            lpos = el->childs;
            if (!marked){
                while ((lpos!=nullptr) && (lpos->mark))
                    lpos = lpos->next;
            }
        }
        else{
            lpos = lpos->next;
            if (!marked){
                while ((lpos!=nullptr) && (lpos->mark))
                    lpos = lpos->next;
            }
        }
    }
    return lpos;
}

List *Graph::itin(Elem *el)
{
    SAVEITS;
    int k = CountElems();
    List* res = nullptr;
    if (linpos == k){
        linpos = 0;
        return nullptr;
    }
    else{
        while ((res == nullptr) && (linpos < k)){
            res = GetEdge(this->operator [](linpos++), el);
        }
    }
    return res;
    RESTOREITS;
}

void Graph::ResetIts()
{
    lpos = nullptr;
    pos = nullptr;
    linpos = 0;
}

void Graph::ReadFile(QString fileName)
{
    SAVEITS;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream file1s(&file);
    QString str;
    int i; int k = 0;
    int weight = 1; double x = -100; double y = -100;
    weights = file1s.readLine().toInt();
    bool pos = file1s.readLine().toInt();
    while (!file1s.atEnd()){
        str = file1s.readLine();
        QStringList strl = str.split(' ');
        QByteArray arr;
        arr = strl.at(0).toLocal8Bit();
        char* name = arr.data();
        if (pos){
            x = strl.at(1).toDouble();
            y = strl.at(2).toDouble();
        }
        AddElem(name, x, y);
        if (!weights){
            for (i = 1 + pos*2; i < strl.size(); i++){
                arr = strl.at(i).toLocal8Bit();
                name = arr.data();
                AddEdge(this->operator [](k), name);
            }
        }
        else{
            for (i = 1 + pos*2; i<strl.size() - 1; i = i + 2){
                arr = strl.at(i).toLocal8Bit();
                name= arr.data();
                weight = strl.at(i+1).toInt();
                AddEdge(this->operator [](k), name, weight);
            }
        }
        k++;
    }
    Solve();
    file.close();
    RESTOREITS;
}

void Graph::SaveFile(QString fileName, bool pos)
{
    SAVEITS;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream files(&file);
    Elem* el;
    List* ls;
    files << weights << "\r\n";
    files << pos << "\r\n";
    while ((el = it())!=nullptr){
        files << el->name << " ";
        if (pos){
            files << el->node->scenePos().x() << " " << el->node->scenePos().y() << " ";
        }
        while ((ls = it(el))!=nullptr){
            files << ls->node->name << " ";
            if (weights){
                files << ls->weight << " ";
            }
        }
        files << "\r\n";
    }
    file.close();
    RESTOREITS;
}

char *Graph::GetMinStupidName()
{
    char* name = new char[80];
    sprintf(name, "%d", stupidnames);
    while (FindElem(name)){
        stupidnames++;
        sprintf(name, "%d", stupidnames);
    }
    return name;
}

char *Graph::GetLastStupidName()
{
    char* name = new char[80];
    sprintf(name, "%d", stupidnames);
    return name;
}

void Graph::AddElem(char *name, double X, double Y)
{
    SAVEITS;
    if (X == -100)
        X = rand()%Wid - Wid/2;
    if (Y == -100)
        Y = rand()%Hei - Hei/2;
    Elem* el;
    if (!gr){ //Если добавляется первый элемент
        gr = new Elem;
        strcpy_s(gr->name, Numb, name);
        gr->node = new Node(widget);
        gr->node->name = (gr->name);
        widget->centerNode = gr->node;
        widget->scene()->addItem(widget->centerNode);
        widget->centerNode->setPos(X, Y);

    }
    else{
        while ((el = it())->next!=nullptr);
        el->next = new Elem;
        el = el->next;
        strcpy_s(el->name, Numb, name);
        el->node = new Node(widget);
        el->node->name = el->name;
        el->node->setPos(X, Y);
        widget->scene()->addItem(el->node);

    }
    RESTOREITS;
}

Elem *Graph::FindElem(List *ls)
{
    SAVEITS;
    Elem* el;
    List* ls2;
    while ((el = it())!=nullptr){
        while ((ls2 = it(el))!=nullptr){
            if (ls == ls2){
                RESTOREITS;
                return el;
            }
        }
    }
    RESTOREITS;
    return el;
}

Elem *Graph::FindElem(char *name)
{
    SAVEITS;
    Elem* el;
    bool res = 0;
    while ((el = it())!=nullptr){
        res = (strncmp(name, el->name, Numb))==0;
        if (res)
            break;
    }
    RESTOREITS;
    return el;
}

void Graph::AddEdge(Elem *el1, Elem *el2, int weight)
{
    SAVEITS;
    List* ls;
    if (Is_Egde(el1, el2)){
        return;
    }
    int ow;
    if (abs(ow = Is_Egde(el2, el1, 1)))
        weight = ow;
    if (el1 && el2){
        if (!el1->childs){
            el1->childs = new List;
            strcpy_s(el1->childs->name, el2->name);
            el1->childs->weight = weight;
            el1->childs->node = el2;
            el1->childs->edge = new Edge(el1->node, el2->node, el1->childs);
            el1->childs->next = nullptr;
            widget->scene()->addItem(el1->childs->edge);
        }
        else{
            while ((ls = it(el1))->next!=nullptr);
            ls->next = new List;
            ls = ls->next;
            strcpy_s(ls->name, el2->name);
            ls->weight = weight;
            ls->node = el2;
            ls->edge = new Edge(el1->node, el2->node, ls);
            ls->next = nullptr;
            widget->scene()->addItem(ls->edge);
        }
    }
    RESTOREITS;
}

void Graph::AddEdge(Elem *el1, char *name, int weight)
{
    SAVEITS;
    List* ls;
    if (el1 && (strlen(name)!=0)){
        if (!el1->childs){
            el1->childs = new List;
            strcpy_s(el1->childs->name, name);
            el1->childs->weight = weight;
        }
        else{
            while ((ls = it(el1))->next!=nullptr);
            ls->next = new List;
            ls = ls->next;
            strcpy_s(ls->name, name);
            ls->weight = weight;
        }
    }
    RESTOREITS;
}

bool Graph::Solve()
{
    SAVEITS;
    bool res = 1;
    Elem* el;
    List* ls;
    Elem* el2;
    while ((el = it())!=nullptr){
        while ((ls = it(el))!=nullptr){
            if (ls->node == nullptr){
                el2 = FindElem(ls->name);
                if (el2){
                    ls->node = el2;
                    ls->edge = new Edge(el->node, el2->node, ls);
                    widget->scene()->addItem(ls->edge);
                }
                else
                    res = 0;
            }
        }
    }
    RESTOREITS;
    return res;
}

void Graph::RemoveElem(char *name)
{
    SAVEITS;
    if (gr){
        Elem* el = gr;
        bool res = strncmp(name, el->name, Numb) == 0;
        if (!res){
            while (((el = it())->next)!=nullptr){
                res = strncmp(el->next->name, name, Numb) == 0;
                if (res)
                    break;
            }
            if (res){
                RemoveEdges(el->next);
                widget->scene()->removeItem(el->next->node);
                delete el->next->node;
                Elem* el2 = el->next->next;
                delete el->next;
                el->next = el2;
            }
        }
        else{
            RemoveEdges(gr);
            widget->scene()->removeItem(gr->node);
            delete gr->node;
            Elem* el2 = gr->next;
            delete gr;
            gr = el2;
        }
    }
    RESTOREITS;
}

void Graph::RemoveEdge(Elem *el1, Elem *el2)
{
    SAVEITS;
    if (el1 && el2){
        bool res = (el1->childs->node == el2);
        if (!res){
            List* ls;
            while ((ls = it(el1))->next != nullptr){
                res = (ls->next->node == el2);
                if (res)
                    break;
            }
            List* ls2 = ls->next->next;
            ls->next->edge->clear();
            widget->scene()->removeItem(ls->next->edge);
            delete ls->next->edge;
            delete ls->next;
            ls->next = ls2;
        }
        else{
            List* ls2 = el1->childs->next;
            el1->childs->edge->clear();
            widget->scene()->removeItem(el1->childs->edge);
            delete el1->childs->edge;
            delete el1->childs;
            el1->childs = ls2;
        }
    }
    RESTOREITS;
}

void Graph::RenameElem(char *oldname, char *newname)
{
    Elem* el = FindElem(oldname);
    if ((!FindElem(newname)) && strlen(newname)!=0){
        strcpy_s(el->name, newname);
        List* ls;
        while ((ls = itin(el))!=nullptr){
            strcpy_s(ls->name, newname);
        }
    }
}

void Graph::Desorientate()
{
    SAVEITS;
    Elem* el;
    List* ls;
    while ((el = it())!=nullptr){
        while ((ls = it(el))!=nullptr){
            if (!Is_Egde(ls->node, el))
                AddEdge(ls->node, el);
        }
    }
    RESTOREITS;
}

int Graph::CountChildren(Elem *el, bool marked)
{
    SAVEITS;
    int i = 0;
    List* ls;
    while ((ls = it(el))!=nullptr){
        if ((marked) || !(ls->mark))
            i++;
    }
    return i;
    RESTOREITS;
}

int Graph::CountElems()
{
    SAVEITS;
    int i = 0;
    while (it()!=nullptr)
        i++;
    RESTOREITS;
    return i;
}

int Graph::Is_Egde(Elem *el1, Elem *el2, bool noabs)
{
    List* t_lpos = KeepItL();
    List* curr;
    int res = 0;
    while ((curr = it(el1))!=nullptr){
        if (curr->node == el2){
            res = curr->weight;
            break;
        }
    }
    RestoreItL(t_lpos);
    if (!noabs)
        res = abs(res);
    return res;
}

List *Graph::GetEdge(Elem *el1, Elem *el2)
{
    if (Is_Egde(el1, el2)){
        SAVEITS;
        List* curr;
        while ((curr = it(el1))!=nullptr){
            if (curr->node == el2){
                break;
            }
        }
        RESTOREITS;
        return curr;
    }
    return nullptr;
}



int Graph::Max_Width()
{
    SAVEITS;
    int i = 0;
    int l;
    Elem* el;
    List* ls;
    while ((el = it())!=nullptr){
        if ((l=strlen(el->name)) > i)
            i = l;
        while ((ls = it(el))!=nullptr){
            l = log10(abs(ls->weight)) + 1;
            if (ls->weight < 0)
                l++;
            if (l > i)
                i = l;
        }
    }
    RESTOREITS;
    return i;
}

void Graph::Inc_Matr(QTextStream &os)
{
    SAVEITS;
    int len = Max_Width();
    Elem* el;
    int z = CountElems();
    int i; int k;
    os.setFieldWidth(len + 1);
    os << " ";
    while ((el = it())!=nullptr){
        os << el->name;
    }
    os << endl;
    for (i=0; i<z; i++){
        os << this->operator [](i)->name;
        for (k=0; k<z; k++)
            os << Is_Egde(this->operator [](i), this->operator [](k), 1);
        os << endl;
    }
    RESTOREITS;
}

void Graph::Mark(List *ls, int mark)
{
    SAVEITS;
    if (mark!=0){
        ls->mark = mark;
        RESTOREITS;
        return;
    }
    if (itermarks){
        ls->mark = ib + 1;
    }
    else{
        int maxmark = 0;
        List* ls1;
        while ((ls1=itin(ls->node))!=nullptr){
            if (ls1->mark > maxmark)
                maxmark = ls1->mark;
        }
        ls->mark = maxmark + 1;
    }
    RESTOREITS;
}

void Graph::ClearMarks()
{
    SAVEITS;
    marked = nullptr;
    Elem* el;
    List* ls;
    while ((el = it())!=nullptr){
        el->node->update();
        while ((ls = it(el))!=nullptr){
            ls->mark = 0;
            ls->edge->update();
        }
    }
    RESTOREITS;

}

QQueue<List*> Graph::MakeQueue(Elem** previous)
{
    SAVEITS;
    QQueue<List*> result;
    List* temp = it(v0);
    while (temp)
    {
        result.enqueue(temp);
        previous[number(FindElem(temp->name))] = v0;
        arr[number(FindElem(temp->name))] = temp->weight;
        temp = it(v0);
    }
    RESTOREITS;

    return result;

}

Elem* Graph::FindMinimal(QQueue<List*> *H)
{

    QQueue<List*> temporary;
    List* temp = H->dequeue();
    temporary.enqueue(temp);

    while (!H->isEmpty())
    {
        List* temp2 = H->dequeue();
        temporary.enqueue(temp2);
        if (temp->weight > temp2->weight)
            temp = temp2;
    }

    List* temp3 = temporary.dequeue();
    while (temp3->name != temp->name)
    {
        H->enqueue(temp3);
        temp3 = temporary.dequeue();
    }

    while(!temporary.isEmpty())
        H->enqueue(temporary.dequeue());

    return FindElem(temp->name);
}

void Graph::DeicstraAlgorithm()
{
    SAVEITS;
    int ammount = this->CountElems();
    arr[number(this->FindElem(v0->name))] = 0;

    Elem** previous = new Elem*[ammount];
    for (int i=0; i<ammount; i++)
        previous[i] = nullptr;

    QQueue<List*> H = MakeQueue(previous);
    while (!H.isEmpty())
    {
        Elem* v = FindMinimal(&H);
        List* u_temp = it(v);
        while (u_temp)
        {
            Elem* u = this->FindElem(u_temp->name);
            if (arr[number(u)] > (arr[number(v)] + (GetEdge(v, u))->weight))
            {
                arr[number(u)] = arr[number(v)] + (GetEdge(v, u))->weight;
                previous[number(u)] = v;

                //Update Priorities
                H.enqueue(u_temp);
            }
            u_temp = it(v);
        }
    }
    RESTOREITS;
}

bool Graph::DeicstraInit(Elem* v0i)
{
    if (v0i!=nullptr)
        v0 = v0i;
    else{
        bool ok;
        QString namev0 = QInputDialog::getText(widget, "Deicstra's Algorithm", "Please Enter Name of the First Element", QLineEdit::Normal, "", &ok);
        QByteArray arr = namev0.toLocal8Bit();
        char* cnamev0 = arr.data();
        v0 = FindElem(cnamev0);
    }
    if (v0 == nullptr){
        QMessageBox msg;
        msg.setText("Error 404: First Element not in Graph!");
        msg.exec();
        return 1;
    }
    if (arr!=nullptr){
        delete[] arr;
        arr = nullptr;
    }
    vm = CountElems();
    if (vm == 0)
        return 1;
    arr = new int[vm];
    for (int i =0; i<vm; i++){
        arr[i] = INT_MAX/2;
    }
    arr[number(v0)] = 0;
    ib = 0;
    ResetIts();
    return 0;
}

Elem *Graph::FindPath()
{
    SAVEITS;
    QQueue<Elem*> queue;
    queue.enqueue(source);
    source->searched = 1;
    List* ls;
    while(!queue.isEmpty()){
        Elem* el2 = queue.dequeue();
        if (el2 == sink){
            RESTOREITS;
            return el2;
        }
        while (ls = it(el2)){
            if ((!ls->node->searched) && ((ls->weight - ls->flow) != 0)){
                ls->node->searched = 1;
                ls->mark2 = 1;
                queue.enqueue(ls->node);
            }
        }
    }
    RESTOREITS;
    return nullptr;
}

void Graph::RestorePath(Elem* el)
{
    SAVEITS;
    List* ls;
    path.way_el.push_front(el);
    if (el!=source){
        linpos = 0;
        while (ls = itin(el)){
            if (ls->mark2){
                path.way.push_front(ls);
                ls->mark = it_num;
                ls->edge->update();
                RestorePath(FindElem(ls));
                RESTOREITS;
                return;
            }
        }
    }
    else{
        Elem* el2;
        while ((el2 = it())!=nullptr){
            while ((ls = it(el2))!=nullptr){
                ls->mark2 = 0;
            }
        }
    }
    RESTOREITS;
}

void Graph::ResetFindPath()
{
    SAVEITS;
    Elem* el;
    path.way.clear();
    path.way_el.clear();
    path.min_flow = INT_MAX/2;
    while ((el = it())!=nullptr){
        el->searched = 0;
    }
    RESTOREITS;
}

void Graph::SetMinPath()
{
    int res = INT_MAX / 2;
    for (auto it : path.way){
        if ((it->weight - it->flow) < res)
            res = it->weight - it->flow;
    }
    path.min_flow = res;
}


void Graph::FordInit()
{
    if (!sink || !source)
    {
        QMessageBox box;
        box.setText("No source or sink marked");
        box.exec();
        return;
    }
    if (!weights)
    {
        QMessageBox box;
        box.setText("No weights");
        box.exec();
        return;
    }
    max_iter = 10;
}

bool Graph::FordAlgorithm()
{
    if (max_iter == 0)
        FordInit();

    if (max_iter == 0)
        return false;

    it_num++;
    ResetFindPath();
    FindPath();
    RestorePath(sink);
    SetMinPath();    
    if (path.way.size() == 0)
        return false;
    int i = 0;
    for (auto current : path.way)
    {
        current->flow = current->flow + path.min_flow;
        Elem* temp = path.way_el.at(i++);
        List* templist = GetEdge(current->node, temp);
        if (templist)
            templist->flow = current->flow;
    }


    return true;
}

void Graph::WeightsOn(bool state)
{
    if (state!=weights){
        weights = state;
        widget->updateEdges();
        if (state == 0)
            ClearWeights();
    }
}

void Graph::ChangeWeight(Elem *el1, Elem *el2, int weight)
{
    SAVEITS;
    if (!Is_Egde(el1, el2))
        return;
    if (el1 && el2){
        List* ls = GetEdge(el1, el2);
        ls->weight = weight;
        if (ls = GetEdge(el2, el1)){
            ls->weight = weight;
        }
    }
    RESTOREITS;
}

double Graph::AverageWeight()
{
    SAVEITS;
    Elem* el;
    List* ls;
    double w = 0; int k = 0;
    while ((el = it())!=nullptr){
        while ((ls = it(el))!=nullptr){
            w = w + ls->weight;
            k++;
        }
    }
    if (k!=0)
        w = w / k;
    return w;
    RESTOREITS;
}

void Graph::ClearWeights()
{
    SAVEITS;
    Elem* el;
    List* ls;
    while ((el = it())!=nullptr){
        el->node->update();
        while ((ls = it(el))!=nullptr){
            ls->weight = 1;
            ls->edge->update();
        }
    }
    RESTOREITS;
}

Elem *Graph::operator[](int i)
{
    SAVEITS;
    int k=0;
    Elem* el = nullptr;
    while (k<=i){
        el = it();
        if (el!=nullptr)
            k++;
        else
            break;
    }
    RESTOREITS;
    return el;
}

int Graph::number(Elem *el)
{
    SAVEITS;
    int k = CountElems();
    int i;
    for (i = 0; i < k; i++){
        Elem* t = this->operator [](i);
        if (t == el)
            break;
    }
    RESTOREITS;
    if (i == k)
        i = 0;
    return i;
}


Elem *Graph::KeepItE()
{
    Elem* t_pos = pos;
    pos = nullptr;
    return t_pos;
}

List *Graph::KeepItL()
{
    List* t_lpos = lpos;
    lpos = nullptr;
    return t_lpos;
}

void Graph::RestoreItE(Elem *t_pos)
{
    pos = t_pos;
}

void Graph::RestoreItL(List *t_lpos)
{
    lpos = t_lpos;
}

void Graph::RemoveEdges(Elem *el)
{
    SAVEITS;
    Elem* el1;
    while ((el1 = it())!=nullptr){
        if (Is_Egde(el1, el))
            RemoveEdge(el1, el);
        if (Is_Egde(el, el1))
            RemoveEdge(el, el1);
    }
    RESTOREITS;
}
