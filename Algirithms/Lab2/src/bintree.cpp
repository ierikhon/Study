/*Файл реализует некоторые методы работы с бинарными деревьями. В данной программе не нужен*/

#include "bintree.h"

BT* RootBT(BT* tree){
    return tree->Root;
}

BT* LeftBT(BT* tree){
    return tree->Left;
}

BT* RightBT(BT* tree){
    return tree->Right;
}

bool NullBT(BT* tree){
    if (tree == NULL){
        return 1;
    }
    return 0;
}

void fixRoots(BT* tree, BT* past)
{
    if(NullBT(tree))
        return;
    if (!NullBT(past)){
        tree->Root=past;
    }
    if (!NullBT(LeftBT(tree))){
        fixRoots(LeftBT(tree), tree);
    }
    if (!NullBT(RightBT(tree))){
        fixRoots(RightBT(tree), tree);
    }
}

BT* delete_tree(BT* tree)
{
    if(!tree)
        return tree;
    if(tree->Left)
        delete_tree(tree->Left);
    if(tree->Right)
        delete_tree(tree->Right);
    tree=NULL;
    delete tree;
    return tree;
}

BT* ConsBT(elem info, BT* Left, BT* Right, BT* Root)
{
    BT* tree= new BT;
    tree->info = info;
    tree->Root = Root;
    tree->Right = Right;
    tree->Left = Left;
    return tree;
}

