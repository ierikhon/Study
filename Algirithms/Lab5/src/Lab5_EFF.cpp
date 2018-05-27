#include "algorithm.h"
#include <fstream>

int main()
{
    ofstream fout("EffTest.txt", ios_base::trunc);
    string P;
    string T;
    vector<size_t> TextSizes = {15001, 20000, 30000, 50000, 100000, 1000000, 5000000};
    vector<size_t> PatternSizes = {1, 50, 100, 1000, 5000, 10000, 15000};
    for (int i=0; i<6; i++)
    {
        fout << "Text length - " << TextSizes[i] << endl;
        for (size_t j=0; j<7; j++)
        {
            T.resize(TextSizes[i]);
            P.resize(PatternSizes[j]);

            for (size_t k=0; k<T.length(); k++)
                T[k] = randChar();
            for (size_t k=0; k<P.length(); k++)
                P[k] = randChar();

            long int operationsKMP = 0;
            long int operationsN = 0;
            vector<int> result = Naive(P, T, &operationsKMP);
            result = KMPvsN (P, T, &operationsN);

            fout << "Pattern length - " << P.length() << ", KMP - " << operationsKMP << ", Naive - " << operationsN << endl;
        }
    }

    return 0;
}