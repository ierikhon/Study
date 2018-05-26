#include "algorithm.h"

vector<int> KMP(string P, string T)
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

vector<int> prefixFunction (string S)
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

vector<int> KMP_UPGR(string P, string T)
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
