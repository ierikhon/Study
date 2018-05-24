#ifndef MALGORITHM_H
#define MALGORITHM_H
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

struct Bor
{
    int next[52];
    vector<int> patternNumber;
    int suffixL;
    int auto_move[52];
    int parent;
    int CompressedSuffixL;
    bool isStr;
    char symbol;
};

Bor makeBor(int parentN, char sym);
void addtoBor(string s);
int getLink(int node);
int getAM(int node, char sym);
int getCompressedLink(int node);

vector<int> KMP (string P, string patterns, char joker);
void AC(const string& s,vector<int>& count, const vector<int>& lenght);
#endif