#ifndef AC_BASE_HPP
#define AC_BASE_HPP
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct Bor
{
    int next[52];
    int patternNumber;
    int suffixL;
    int auto_move[52];
    int parent;
    int CompressedSuffixL;
    bool isStr;
    char symbol;
};

Bor makeBor(int parentN, char sym);
void addtoBor(string s, vector<Bor> bor, vector<string> patterns);
int getLink(int node, vector<Bor> bor);
int getAM(int node, char sym, vector<Bor> bor);
int getCompressedLink(int node, vector<Bor> bor);

void AC(string s, vector<Bor> bor, vector<string> patterns);

#endif

