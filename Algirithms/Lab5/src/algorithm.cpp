#include "algorithm.h"

vector<int> KMP(const string &P, const string &T)
{
    vector<int> result;
    vector<int> pf = prefixFunction(P);
    size_t i;
    size_t cur = 0;
    for (i=0; i<T.size(); i++)
    {
        while ((cur>0)&&(T[i] != P[cur]))
            cur = pf[cur-1];
        if (T[i] == P[cur])
            cur++;
        if (cur == P.size())
            result.push_back(i-cur+1);
    }
    return result;
}

vector<int> prefixFunction (const string &S)
{
    int size = S.length();
    vector<int> pf(size);
    for (int i=1; i<size; i++)
    {
        int cur = pf[i-1];
        while ((cur>0)&&(S[i] != S[cur]))
            cur = pf[cur-1];
        if (S[cur] == S[i])
            cur++;
        pf[i] = cur;
    }

    return pf;
}

vector<int> KMP_UPGR(const string &P, const string &T)
{
    vector<int> result;
    vector<int> pf = prefixFunction(P);
    size_t i;
    size_t size = T.size();
    size_t cur = 0;
    for (i=0; i<2*size; i++)
    {
        while ((cur>0)&&(T[i%size] != P[cur]))
            cur = pf[cur-1];
        if (T[i%size] == P[cur])
            cur++;
        if (cur == P.size())
            result.push_back(i-cur+1);
    }
    return result;
}

bool compare(const char& a, const char& b, long int* operations)
{
    (*(operations))++;
    return a == b;
}

vector<int> prefixFunctionVS (const string &S, long int* operations)
{
    int size = S.length();
    vector<int> pf(size);
    for (int i=1; i<size; i++)
    {
        int cur = pf[i-1];
        while ((cur>0)&&(!compare(S[i], S[cur], operations)))
            cur = pf[cur-1];
        if (compare(S[i], S[cur], operations))
            cur++;
        pf[i] = cur;
    }

    return pf;
}

vector<int> KMPvsN(const string &P, const string &T, long int* operations)
{
    vector<int> result;
    vector<int> pf = prefixFunctionVS(P, operations);
    size_t i;
    size_t cur = 0;
    for (i=0; i<T.size(); i++)
    {
        while ((cur>0)&&(!compare(T[i], P[cur], operations)))
            cur = pf[cur-1];
        if (compare(T[i], P[cur], operations))
            cur++;
        if (cur == P.size())
            result.push_back(i-cur+1);
    }
    return result;
}

char randChar ()
{
    return (rand() % 26 + 'a');
}

vector<int> Naive(const string &P, const string &T, long int* operations)
{
    vector<int> result;
    size_t j=0;
    size_t k=0;
    for (size_t i=0; i<=(T.size() - P.size()); i++)
    {
        k=0;
        while (compare(T[i+k], P[j+k], operations) && (k < P.size()))
            k++;

        if (k == P.size())
            result.push_back(i);
    }
    return result;
}