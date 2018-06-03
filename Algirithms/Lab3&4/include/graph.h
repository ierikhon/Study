#ifndef GRAPH_H
#define GRAPH_H
#define SAVEITS List* t_lpos = KeepItL(); Elem* t_pos = KeepItE(); int t_linpos = linpos;
#define RESTOREITS RestoreItL(t_lpos); RestoreItE(t_pos); linpos = t_linpos;
#define Numb 80
#define Wid 800
#define Hei 600

#include <iostream>
#include <cstring>
#include <climits>
#include <QTextStream>
#include <QString>
#include <QFile>
#include <QStack>
#include <QMessageBox>
#include <QInputDialog>
#include <QTime>

#include "graphwidget.h"

using namespace std;

typedef struct List List;

typedef struct Elem{ //Элементы графа
    Elem() = default;
    char name[Numb];
    Elem* next=nullptr;
    List* childs=nullptr; //Дети элемента
    Node* node;
    bool searched = false;
}Elem;

typedef struct List{
    List() = default;
    char name[Numb];
    int mark = 0;
    int mark2 = 0;
    int weight = 1;
    int flow = 0;
    Elem* node = nullptr; //Сам элемент
    List* next = nullptr;
    Edge* edge;
}List;

typedef struct Path{
    QList<List*> way;
    QList<Elem*> way_el;
    int min_flow = INT_MAX / 2;
}Path;

class Graph
{
public:
    Graph();
    ~Graph();
    void Clear(); //Очистка

    Elem* it(); //Итератор через вершины
    List* it(Elem* el, bool marked = 1); //Итератор через сыновей
    List* itin(Elem* el); //Итератор через входящие вершины
    void ResetIts();

    void ReadFile(QString fileName); //Считать из файла
    void SaveFile(QString fileName, bool pos = 0); //Сохранить в файл

    char* GetMinStupidName(); //Получение минимального числового имени
    char* GetLastStupidName(); //Получение последнего такого

    void AddElem(char* name, double X = -100, double Y = -100); //Добавить элемент
    void AddEdge(Elem* el1, Elem* el2, int weight = 1); //Добавить линию
    void AddEdge(Elem* el1, char* name, int weight = 1); //Добавить "заготовку" для линии
    bool Solve(); //Разрешить зависимости "заготовок" для линий
    void RemoveElem(char* name); //Удалить элемент
    void RemoveEdge(Elem* el1, Elem* el2); //Удалить линию
    void RemoveEdges(Elem* el); //Удалить связи элемента
    void RenameElem(char* oldname, char* newname); //Переименовать элемент

    void Desorientate(); //Снять ориентацию графа

    Elem* FindElem(char* name); //Найти элемент
    Elem* FindElem(List* ls);

    int CountChildren(Elem* el, bool marked = 1); //Сколько детей
    int CountElems(); //Сколько элементов

    int Is_Egde(Elem* el1, Elem* el2, bool noabs = 0); //Есть ли связь от 1 к 2
    List* GetEdge(Elem* el1, Elem* el2); //Получить связь

    int Max_Width(); //Максимальная длина имени в графе
    void Inc_Matr(QTextStream& os); //Напечатать матрицу инцидентности

    void Mark(List* ls, int mark = 0); //Пометка ребра
    void ClearMarks(); //Очистка меток ребер на графе


    Elem* FindPath();
    void ResetFindPath();
    void SetMinPath();
    void RestorePath(Elem* el);

    bool DeicstraInit(Elem *v0i = nullptr); //Инициализация алгоритма Дейкстры
    void DeicstraAlgorithm(); //Непосредственно алгоритм Дейкстры
    QQueue<List*> MakeQueue(Elem** previous); //Создание очереди приоритетов для алгоритма
    Elem* FindMinimal(QQueue<List *> *H); //Нахождение минимального элемента в очереди

    void FordInit(); //Инициализация алгоритма Форда
    bool FordAlgorithm(); //Непосредственно алгоритм Форда

    void WeightsOn(bool state); //Изменение взвешенности
    void ChangeWeight(Elem* el1, Elem* el2, int weight); //Изменение веса
    double AverageWeight(); //Средний вес
    void ClearWeights();

    Elem* operator[](int i); //Доступ к элементам по индексу
    int number(Elem* el); //Получить номер элемента

    GraphWidget* widget;

    Elem* marked = nullptr; //Выделенная вершина

    bool itermarks = false;
    bool weights = false;
    bool flows = false;

    Elem* source = nullptr;
    Elem* sink = nullptr;
    Path path;

    int max_iter = 0; //Максимальное число итераций

    //Переменные алгоритма Дейкстры
    Elem* v0 = nullptr;
    int* arr = nullptr;
    int ib = 0;
    int vm = 10;
    int changes = 0;
    bool go = 1;

private:
    int it_num = 0;
    int stupidnames = 0;
    Elem* gr;

    Elem* pos; //Iterator
    List* lpos; //Iterator
    int linpos; //Iterator
    void Clear(List* ls, Elem *el);
    void Clear(Elem* gr);
    Elem* KeepItE();
    List* KeepItL();
    void RestoreItE(Elem* t_pos);
    void RestoreItL(List* t_lpos);
};

#endif // GRAPH_H
