#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <vector>
#include <iostream>

using namespace std;

vector<int> KMP(const string &P, const string &T);
vector<int> prefixFunction (const string &S);
vector<int> KMP_UPGR(const string &P, const string &T);

#endif // ALGORITHM_H
