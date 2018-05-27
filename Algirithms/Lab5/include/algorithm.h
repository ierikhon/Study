#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <vector>
#include <iostream>

using namespace std;

vector<int> KMP(const string &P, const string &T);
vector<int> prefixFunction (const string &S);

vector<int> KMP_UPGR(const string &P, const string &T);

vector<int> KMPvsN(const string &P, const string &T, long int* operations);
vector<int> prefixFunctionVS (const string &S, long int* operations);
bool compare(const char& a, const char& b, long int* operations);
vector<int> Naive(const string &P, const string &T, long int* operations);
char randChar();

#endif // ALGORITHM_H
