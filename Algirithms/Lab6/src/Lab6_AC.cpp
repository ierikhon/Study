#include "algorithm.h"

vector<Bor> bor;
vector<wstring> patterns;
vector<string> patterns_NR;

int main()
{
    bor.push_back(makeBor(0,'$'));
    wstring T, temp;
    int PNum;
    wcin >> T >> PNum;
    for(int i=0; i<PNum; i++)
    {
        wcin >> temp;
        addtoBor(temp);
    }
    AC(T);
    return 0;
}