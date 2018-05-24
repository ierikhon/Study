#ifndef AC_JOKER_HPP
#define AC_JOKER_HPP
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
void addtoBor(string s, vector<Bor> bor, vector<string>& patterns);
int getLink(int node, vector<Bor> bor);
int getAM(int node, char sym, vector<Bor> bor);
int getCompressedLink(int node, vector<Bor> bor);

void AC(const string& s, vector<int>& count,const vector<int>& lenght, vector<Bor> bor, vector<string> patterns);
#endif
