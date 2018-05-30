#include "algorithm.h"

vector<Bor> bor;
vector<string> patterns;

int main()
{
    bor.push_back(makeBor(0,'$'));
    string T, temp;
    int PNum;
    cin >> T >> PNum;
    for(int i=0; i<PNum; i++)
    {
        cin >> temp;
        addtoBor(temp);
    }
    AC(T);
    return 0;
}