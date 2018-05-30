#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;

struct Bor
{
    map<char, int> next;
    vector<int> patternNumber;
    int suffixL;
    map<char, int> auto_move;
    int parent;
    int CompressedSuffixL;
    bool isStr;
    char symbol;
};

Bor makeBor(int parentN, char sym);
void addtoBor(const string &s);
int getLink(int node);
int getAM(int node, char sym);
int getCompressedLink(int node);

vector<int> KMP (const string &T, const string &P);
vector<int> KMP_UPGR (const string &P, const string &pattern, char joker);
void AC(const string &s);
void AC_UPGR(const string& s,vector<size_t>& count, const vector<int>& lngth);

#endif