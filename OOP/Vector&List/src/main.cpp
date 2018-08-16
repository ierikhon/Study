#include <iostream>
#include "vector.hpp"
#include "list.hpp"

using namespace std;

int main()
{
    cout << "------Explicit------" << endl;
    stepik::vector<int> a(10);

    for (size_t i = 0; i < a.size(); i++)
        a.operator[](i) = 10;

    a.out();
    cout << endl << endl  << endl;

    cout << "-------Diapason------" << endl;
    stepik::vector<int> b(a.begin(), a.end());
    a.out();
    b.out();
    cout << endl << endl  << endl;

    cout << "--------InitList-------" << endl;
    stepik::vector<int> c{ 1, 2, 3, 4, 5 };
    c.out();

    cout << "-------Copy-------" << endl;
    stepik::vector<int> d(c);
    c.out();
    d.out();
    cout << endl << endl  << endl;

    cout << "-------Move-------" << endl;
    stepik::vector<int> e(std::move(d));
    d.out();
    e.out();
    cout << endl << endl  << endl;



    cout << "-------Resize-------" << endl;
    a.out();
    a.resize(8);
    a.out();
    a.resize(10);
    a.out();
    cout << endl << endl  << endl;

    cout << "-------Erase-------" << endl;
    stepik::vector<int> i(10);

    for (size_t j=0; j<i.size(); j++)
       i[j] = j;

    i.out();
    i.erase(&i[6]);
    i.out();
    cout << endl << endl  << endl;

    cout << "-------Erase2-------" << endl;
    i.erase(&i[3], &i[5]);
    i.out();
    cout << endl << endl  << endl;

    cout << "-------Insert-------" << endl;
    stepik::vector<int> j(1);
    j[0] = 10;
    j.out();
    j.insert(j.begin(), 9);
    j.insert(&j[1], 10);
    j.insert(j.end(), 20);
    j.out();
    cout << endl << endl  << endl;

    cout << "-------Insert2-------" << endl;
    j.insert(&j[2], i.begin(), i.end());
    j.out();
    stepik::vector<int> k;
    k.insert(k.begin(), j.begin(), j.end());
    k.out();
    cout << endl << endl  << endl;

    cout << "-------PushBack-------" << endl;
    j.push_back(6);
    j.push_back(0);
    j.out();
    cout << "============================" << endl << endl << endl;

    return 0;
}
