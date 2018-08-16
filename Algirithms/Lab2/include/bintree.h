/*Файл хранит информацию о структуре, которая представляет список инцидентности графа.
Каждая структура - информация об одной вершине. Список таких структур - это список вершин инцидентной веришне, которая
идет первой в списке. Массив таких сруктур - список инцидентности.*/

#ifndef BINTREE_H
#define BINTREE_H
#include <QChar>
#include "node.h"

typedef QString elem;

//Непосредственно структура
typedef struct INCTR
{
    struct INCTR* prev=NULL; //Указаетль на предыдущий элемент списка инцидентности
    elem name;               //Название вершине - отображаемый при выводе графа на экран текст
    int deg=0;               //Степень вершины (Разность числа выходящих и входящих ребер)
    int intdeg=0;            //Число входящих ребер
    int outdeg=0;            //Число выходящих ребер
    int turn = 0;            //Номер вершины в списке инцидентности. Присваивается во время интерпритации входных данных
    bool label = false;      // Метка, необходимая для поиска стягивающего дерева. Используется в алгоритме
    struct INCTR* next=NULL; //Указатель на следующий элемент списка инцидентности
    Node* node;              //Указатель на стуктуру типа "Node", необходимую для рисования вершины и ребер
}INCTR;


//Дальнейший код - структура бинарного дерева и методы работы с ним. Для данной программы не нужны, но оставлены на будущее
typedef struct BT
{
    struct BT* Root;
    struct BT* Left;
    struct BT* Right;
    elem info;
    int key;
    int size;
    Node* node;
}BT;

BT* RootBT(BT* tree);
BT* LeftBT(BT* tree);
BT* RightBT(BT* tree);
bool NullBT(BT* tree);
BT* ConsBT(elem info, BT* Left, BT* Right, BT* Root);
int getsize(BT* tree);
int fixsize(BT* tree);
BT* rotateright(BT* tree);
BT* rotateleft(BT* tree);
BT* insertroot(BT* tree, BT* root, int key, QString key_ch);
BT* insertrand(BT* tree, BT* root, int key, QString key_ch);
BT* Find(BT* tree, int key);
BT *delete_tree(BT* tree);
void fixRoots(BT* tree, BT* past);
BT* merge(BT* tree1, BT* tree2);
BT* remove(BT* tree, int key);
#endif // BINTREE_H
