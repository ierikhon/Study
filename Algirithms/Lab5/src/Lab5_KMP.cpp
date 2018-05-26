#include "algorithm.h"

int main()
{
    string T, P;
    cin >> P;
    cin >> T;
    size_t i = 0;
    vector<int> result = KMP(P, T);
    if (result.size() != 0)
    {
        for (auto current: result)
        {
            cout << current;
            if ((i++) != result.size()-1)
                cout << ",";
            else
                cout << endl;
        }
    }
    else
        cout << "-1";
    cout << endl;

    return 0;
}