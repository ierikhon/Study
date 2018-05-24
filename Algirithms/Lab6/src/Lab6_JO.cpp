#include "AC_joker.h"

int main()
{
    vector<Bor> bor;
    vector<string> patterns;
    bor.push_back(makeBor(0,255));
    string T, temp;
    char joker;
    cin >> T;
    cin >> temp;
    cin >> joker;

    stringstream str_pat(temp);
    vector<int> count(T.size(),0);

    vector<int> lenght;
    int len=0;
    string tmp;
    while(getline(str_pat, tmp, joker))
    {
        if(tmp.size()>0)
        {
            len+=tmp.size();
            lenght.push_back(len);
            addtoBor(tmp, bor, patterns);
        }
        len++;
    }

    AC(T, count, lenght, bor, patterns);

    for(int i=0; i<T.size(); i++)
        if(count[i] == patterns.size())
            cout << i+1 << endl;

    return 0;
}