#include "algorithm.h"

int main()
{
    string T, P;
    cin >> P;
    cin >> T;
    vector<int> result = KMP_UPGR(T, P);
    if (result.size() != 0)
        cout << result[0];

    else
        cout << "-1";
    cout << endl;

    return 0;
}