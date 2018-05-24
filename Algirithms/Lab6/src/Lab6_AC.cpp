#include "AC_base.h"

int main()
{
    vector<Bor> bor;
    vector<string> patterns;
    bor.push_back(makeBor(0,255));
    string T, temp;
    int PNum;
    cin >> T >> PNum;
    for(int i=0; i<PNum; i++)
    {
        cin >> temp;
        addtoBor(temp, bor, patterns);
    }

    AC(T, bor, patterns);
    return 0;
}