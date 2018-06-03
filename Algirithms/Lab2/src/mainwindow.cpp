/*Основной файл программы, отвечающий за реализацию слотов интерфейса.*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <QQueue>
#include <QStack>
#include "graphwidget.h"
#include "bintree.h"
#include "node.h"
#include <QWidget>
#include <cmath>
#include <algorithm>


//Глобальные переменные, без которых не обойтись
INCTR* tree= new INCTR; //Непосредственно массив структур (реализация списка инцидентности)
int peaks_i;            //Переменная, хранящая число вершин графа
bool gravity = false;   //Переменная, необходимая для включения/отключения функции гравитации на отрисовке графа
int** _Gamilton_Path;   //Список всех гамильтоновых путей в графе
int _cycle = 0;         //Количество гамильтоновых путей в графе

INCTR* tTree;           //Переменная, хранящая стягивающее дерево
QString fileName;       //Переменная, хранящая путь к файлу. Теперь она глобальная, так как перепроверять дерево нужно перед каждым действием с ним


//Созданный для удобства работы с пошаговой реализацией алгоритма класс, содержащий очередь.
class PTP
{
public:
    QQueue<int> sequen;
};


QQueue<PTP> steps;      //Очередь еще не отработавших шагов алгоритма
QStack<PTP> complete;   //Стек отработавших шагов алгоритма
PTP current;            //Текущее состояние алгоритма


//Рекурсивная функция факториала
int Factor (int size)
{
    if (size==1)
        return 1;
    size = size*Factor(size-1);
    return size;
}

//Главная функция - рекурсивный поиск гамильтоновых путей
int** MainWindow::FindGamilton (INCTR* grandparent, INCTR* parent, int peaks, int step, int cycle, int** gampath)
{
    bool flag = false;
    INCTR* temp = new INCTR;
    temp = parent;

    while (temp->next!=NULL)
    {
        temp = temp->next;
        flag = false;
        for (int i=0; i<peaks; i++)
        {
            if (step!=peaks)
            {
                if (temp->turn==tree[i].turn)
                {
                    for (int k=0; k<step; k++)
                    {
                        if (gampath[cycle][k]==tree[i].turn)
                        {
                            if (temp->next==NULL)
                            {
                                gampath[0][peaks+1] = cycle;
                                gampath[0][peaks+2] = step-1;
                                return gampath;
                            }
                            else
                            {
                                flag = true;
                            }
                        }
                    }
                    if (!flag)
                    {
                        gampath[cycle][step] = temp->turn;


                        PTP vazn;
                        for (int z=0; z<=step; z++)
                            vazn.sequen.enqueue(gampath[cycle][z]);
                        steps.enqueue(vazn);


                        step++;
                        gampath = FindGamilton(grandparent, &tree[i], peaks, step, cycle, gampath);
                        step = gampath[0][peaks+2];
                        cycle = gampath[0][peaks+1];
                    }
                }

            }
            else
            {
                if (temp->turn==grandparent->turn)
                {
                    cycle++;
                    gampath[cycle] = new int [peaks+10];
                    for (int j=0; j<step-1; j++)
                        gampath[cycle][j]  = gampath [cycle-1][j];


                    step--;
                    gampath[cycle-1][peaks]=-1;
                    gampath[0][peaks+1] = cycle;
                    gampath[0][peaks+2] = step;
                    return gampath;
                }
                else
                {
                   while (temp->next!=NULL)
                   {
                       temp = temp->next;
                       if (temp->turn==grandparent->turn)
                       {
                           cycle++;
                           gampath[cycle] = new int[peaks+10];
                           for (int j=0; j<step-1; j++)
                               gampath[cycle][j]=gampath[cycle-1][j];

                           step--;
                           gampath[cycle-1][peaks] = -1;
                           gampath[0][peaks+1] = cycle;
                           gampath[0][peaks+2] = step;
                           return gampath;
                       }
                   }
                   step--;
                   gampath[0][peaks+1] = cycle;
                   gampath[0][peaks+2] = step;
                   return gampath;
                }
            }
        }
    }
    gampath[0][peaks+2] = step-1;
    return gampath;
}

//Функция-анализатор, которая изучает данные из файла и подсчитывает число вершин графа
int analyser(QString str, int k)
{
    int peaks=0;
    int com=0;
    while(str[k]==' ' || str[k]=='\t' || str[k]=='\r' || str[k]=='\n')
        k++;
    if(str[k]!='\0')
        peaks++;
    while(str[k]!='\0' /*&& com<3*/)
    {
        if(str[k]==',')
            com++;
        if(str[k]=='\n')
        {
            while(str[k+1]==' ' || str[k+1]=='\t' || str[k+1]=='\r')
                k++;
            if(str[k+1]!='\0' && str[k+1]!='\r' && str[k+1]!='\n')
                peaks++;
            com=0;
        }
        k++;
    }
    if(k!=str.size())
        return -1;
    return peaks;
}

//Функция для удаления лишних пробелов и табуляций
QString corrector(QString str)
{
    int k=0, i=0;
    QString new_str;
    bool flag=false;
    if(str[k]!='\t' && str[k]!=' ' && str[k]!='\n' && str[k]!='\r')
        flag=true;
    if(flag==true)
    {
        new_str[i]=str[k];
        i++;
    }
    for(k=1; k<str.size(); k++)
    {
        if(str[k-1]=='\n' || str[k-1]==',' || str[k]=='\n' || str[k]==',')
            flag=false;
        if(str[k]!='\t' && str[k]!=' ' && str[k]!='\n' && str[k]!='\r')
            flag=true;
        if(flag==true)
        {
            new_str[i]=str[k];
            i++;
        }
    }
    return new_str;
}

//Функция непосредственно преобразует текст из файла в массив структур типа INCTR
INCTR* Read(QString str, INCTR* peaks, int size)
{
    int i=0, j=0, k=0;
    while(str[k]!='\0')
    {
        while(str[k]!=',' && str[k]!='\r' && str[k]!='\0')
        {
            peaks[i].name[j]=str[k];
            peaks[i].turn=i+1;
            k++;
            j++;
        }
        j=0;
        if(str[k]!='\0' && str[k]!='\r')
        {
            k++;
            INCTR* temp=new INCTR;
            peaks[i].next=temp;
            peaks[i].outdeg++;
            temp->next=NULL;
            temp->intdeg++;
            temp->prev=&peaks[i];
            while(str[k]!=',' && str[k]!='\r' && str[k]!='\0')
            {
                while(str[k]!=',' && str[k]!='\r' && str[k]!='\0')
                {
                    temp->name[j]=str[k];
                    j++;
                    k++;
                }
                if(str[k]!='\0' && str[k]!='\r')
                {
                    INCTR* temp2=new INCTR;
                    peaks[i].outdeg++;
                    temp->next=temp2;
                    temp2->next=NULL;
                    temp2->intdeg++;
                    temp2->prev=temp;
                    temp=temp2;
                    k++;
                }
                j=0;
            }

        }
        i++;
        k++;
    }
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            if(peaks[j].next)
            {
                INCTR* temp=new INCTR;
                temp=peaks[j].next;
                if(peaks[i].name==temp->name)
                {
                    peaks[i].intdeg+=temp->intdeg;
                    temp->turn=peaks[i].turn;
                }
                while(temp->next)
                {
                    temp=temp->next;
                    if(peaks[i].name==temp->name)
                    {
                        peaks[i].intdeg+=temp->intdeg;
                        temp->turn=peaks[i].turn;
                    }
                }

            }
        }
        peaks[i].deg=peaks[i].intdeg+peaks[i].outdeg;
    }
    return peaks;
}

/*Итерпретатор полученных из файла данных. Запускает ряд вышеописанных функций для составления информации
о списке инцидентности и перевода его в удобную для дальнейшей работы форму*/
INCTR* ReadFile(QString fileName, QTextEdit* te){
    QFile file1(fileName);
    file1.open(QIODevice::ReadOnly);
    if (!file1.isOpen()){
        QMessageBox msg;
        msg.setText("File isn't open!");
        msg.setWindowTitle("ERROR");
        msg.exec();
        return NULL;
    }
    int i = 0;
    QTextStream file1s(&file1);
    QString temp = file1s.readAll();
    te->setPlainText(temp);
    peaks_i=analyser(temp, i);
    if(peaks_i==-1)
        return NULL;
    temp=corrector(temp);
    INCTR* peaks = new INCTR[peaks_i];
    peaks=Read(temp, peaks, peaks_i);

    return peaks;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    globalWidget = nullptr;
 //   ui->graphicsView->setViewport(globalWidget);
    tree = NULL;

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Функция чтения данных из файла
void MainWindow::on_action_5_triggered()
{
   _cycle = 0;
   fileName = QFileDialog::getOpenFileName(this, "Open file");
   tree = ReadFile(fileName, ui->textEdit);
   tTree = new INCTR[peaks_i];
}

/*Управление фукнцией гравитации при отрисовки графа. Активирутеся установкой флажка в соответствующем чекбоксе интерфейса.
может быть изменено  в любой момент работы программы*/
void MainWindow::on_checkBox_clicked()
{
    if (ui->checkBox->checkState()){
        gravity = true;
    }
    else
        gravity = false;
}


//Простой вывод графа без поиска и отрисовки в нем гамильтоновых путей
void MainWindow::on_pushButton_clicked()
{
    if(tree==NULL)
    {
        ui->textEdit_3->setText("Error 404: no info for graph construction!");
        return;
    }
    else
    {
       tree = ReadFile(fileName, ui->textEdit);
       globalWidget = new GraphWidget(this, tree, &gravity, peaks_i, NULL);
       ui->graphicsView->setViewport(globalWidget);
    }
}

//Инициализация поиска гамильтоновых путей по нажатию соответствующей кнопки. Здесь также происходит очистка от предыдущей информации
void MainWindow::on_pushButton_3_clicked()
{
    if (tree!=NULL)
    {
        ui->textEdit_4->clear();
        int step = 1;
        int cycle = 0;
        int i;
        steps.clear();
        complete.clear();


        int** Gamilton_Path = new int*[100];

        for (i = 0; i < log(Factor(peaks_i))+1; i++)
        {
            Gamilton_Path[i] = NULL;
            Gamilton_Path[i] = new int[100];
            for (int o=0; o< log(Factor(peaks_i))+1; o++)
                Gamilton_Path[i][o] = 0;
        }


        for (i = 0; i < peaks_i; i++)
        {
            Gamilton_Path[cycle][0] = tree[i].turn;
            Gamilton_Path = FindGamilton (&tree[i], &tree[i], peaks_i, step, cycle, Gamilton_Path); //Непосредственный запуск поиска путей

            while (Gamilton_Path[cycle] && Gamilton_Path[cycle][peaks_i]==-1)
                cycle++;
        }

        Gamilton_Path[cycle] = NULL;

        //Вывод результатов поиска
        for (i = 0; i<cycle; i++)
        {
            ui->textEdit_4->append(QString::number(i+1)+')');
            for (int j=0; j<peaks_i; j++)
                for (int k=0; k<peaks_i; k++)
                    if (Gamilton_Path[i][j]==tree[k].turn)
                    {
                        ui->textEdit_4->insertPlainText(tree[k].name);
                        ui->textEdit_4->insertPlainText(" ");
                    }
            ui->textEdit_4->append((QString)'\n');
        }
        _cycle = cycle;
        _Gamilton_Path = Gamilton_Path;
    }
    else ui->textEdit_3->append("Error 404: No info for search");


}

//Отрисовка графа с выбранным гамильтоновым путем
void MainWindow::on_pushButton_4_clicked()
{
    if (ui->textEdit_2->toPlainText()!="")
    {
        int chosenCycle = ui->textEdit_2->toPlainText().toInt();
        if (chosenCycle<=_cycle)
        {
           globalWidget = new GraphWidget(this, tree, &gravity, peaks_i, _Gamilton_Path[chosenCycle-1]);
           ui->graphicsView->setViewport(globalWidget);
        }
        else
        {
            ui->textEdit_3->append("Error 404: This cycle was not found");
            return;
        }
    }
}

//Очистка окна вывода сообщений об ошибках
void MainWindow::on_pushButton_5_clicked()
{
    ui->textEdit_3->clear();
}

//Отрисовка текущего шага алгоритма, хранящегося в переменной current, при нажатии соотв. кнопки
void MainWindow::on_pushButton_7_clicked()
{
    if ((!steps.isEmpty())||(!complete.isEmpty()))
    {
        int i = 0;
        int* tempor = new int;
        while (!current.sequen.isEmpty())
            tempor[i++] = current.sequen.dequeue();


        GraphWidget* widget = new GraphWidget(this, tree, &gravity, peaks_i , tempor);
        QMainWindow* temp = new QMainWindow;
        temp->setCentralWidget(widget);
        temp->setWindowTitle("Graph outputer 3000 pro");
        temp->show();
    }
    else ui->textEdit_3->append("Error 404: Full search wasn't complete yet");
}

//Шаг вперед, осуществляющийся по нажатию соответствующей кнопки
void MainWindow::on_pushButton_6_clicked()
{
    if (!steps.isEmpty())
    {
        current = steps.dequeue();
        complete.push(current);
        ui->textEdit_3->append("One more step right");
    }
    else ui->textEdit_3->append("Error 404: All steps proceeded or search wasn't started.");
}

//Шаг назад, осуществляющийся по нажатию соответствующей кнопки
void MainWindow::on_pushButton_2_clicked()
{
    if (!complete.isEmpty())
    {
        current = complete.pop();
        steps.enqueue(current);
        ui->textEdit_3->append("One more step left");
    }
    else ui->textEdit_3->append("Error 404: No steps proceeded or search wasn't started.");
}


//Непосредственно реализация алгоритма поиска в глубину. Создание копии дерева необходимо для сохраниения информации о структуре графа,
//так как во время работы алгоритма переменная tree затрагивается
void dfst (int nodeTurn)
{
    tree[nodeTurn].label = true;
    INCTR* copy = new INCTR[peaks_i];
    for (int i=0; i<peaks_i; i++)
        copy[i] = tree[i];

    INCTR* temp = copy[nodeTurn].next;
    while (temp!=NULL)
    {
        if (tree[(temp->turn)-1].label == false)
        {
            INCTR* moreTemp = tTree[nodeTurn].next;
            if (moreTemp==NULL)
            {
                tTree[nodeTurn].next = new INCTR;
                tTree[nodeTurn].next->name = temp->name;
                tTree[nodeTurn].next->turn = temp->turn;
                tTree[nodeTurn].next->deg = 1;
            }
            else
            {
            while (moreTemp->deg != 1)
                moreTemp = moreTemp->next;
            moreTemp->deg = 0;
            moreTemp->next = new INCTR;
            moreTemp->next->name = temp->name;
            moreTemp->next->turn = temp->turn;
            moreTemp->next->deg = 1;
            }

            dfst((temp->turn)-1);
        }

        //восстановление исходного состояния гафа. Здесь stopName служит индикатором места, куда указывал temp
        for (int i=0; i<peaks_i; i++)
            copy[i] = tree[i];
        QString stopName = temp->name;
        temp = copy[nodeTurn].next;
        while (temp->name!=stopName)
            temp = temp->next;
        temp = temp->next;
    }
}

//Инициализация алгоритма, происодящая по нажатию кнопки Deep Search of Tightening Tree
//Здесь обновляется граф, чтобы исключить ошибки при повторном нажатии на кнопку и выделяется память на список инцидентности стягивающего дерева
void MainWindow::on_pushButton_8_clicked()
{
    tree = ReadFile(fileName, ui->textEdit);
    tTree = new INCTR[peaks_i];
    for (int i=0; i<peaks_i; i++)
    {
        tTree[i] = tree[i];
        tTree[i].deg = 0;
        tTree[i].next = NULL;
    }

    if (tree!=NULL)
    {
        dfst(0);
        globalWidget = new GraphWidget(this, tTree, &gravity, peaks_i, NULL);
        ui->graphicsView->setViewport(globalWidget);
    }
    else ui->textEdit_3->append("Error 404: No info for search!");
}
