#include "algorithm.h"

vector<Bor> bor;
vector<string> patterns;

int main()
{
    bor.push_back(makeBor(0, '$'));
    string T, temp;
    char joker;
    cin >> T;
    cin >> temp;
    cin >> joker;

    stringstream str_pat(temp);
    vector<size_t> count(T.size(),0);

    vector<int> lenght;
    int len=0;
    string tmp;
    while(getline(str_pat, tmp, joker))
    {
        if(tmp.size()>0)
        {
            len+=tmp.size();
            lenght.push_back(len);
            addtoBor(tmp);
        }
        len++;
    }

    AC_UPGR(T, count, lenght);

    for(size_t i=0; i<T.size(); i++)
        if(count[i] == patterns.size())
            cout << i+1 << endl;

    return 0;
}