#include <iostream>
#include "shared_ptr.hpp"
#include <string>

using namespace std;
using stepik::shared_ptr;

struct testSTR
{
    string name;
    int age;
    testSTR (int a, string names): age(a), name(names)
    {}
    void print ()
    {
        cout << "member has name " << name << " and age " << age << endl;
    }
};

int main()
{
    cout << "Creating Pointers" << endl;
   testSTR* obj = new testSTR(10, "Vasua");
    shared_ptr<testSTR> shp(obj);

    cout << "Getter"<< endl;
    shp.get()->print();

    cout << "Operator *"<< endl;
    (*shp).print();

    cout << "Copy constructor"<< endl;
    shared_ptr<testSTR> shp2(shp);
    shared_ptr<testSTR> shp3(shp2);
    shp->print();
    cout << shp.use_count() << " pointers" << endl;
    shp2->print();
    cout << shp2.use_count() << " pointers" << endl;
    shp3->print();
    cout << shp3.use_count() << " pointers" << endl;

    cout << "Assignment"<< endl;
    testSTR* obj2 = new testSTR(15, "Petya");
    shared_ptr<testSTR> shp4(obj2);
    shp3 = shp4;
    shp3->print();
    shp4->print();

    cout << "Reset"<< endl;
    testSTR* obj3 = new testSTR(20, "Vova");
    shp3.reset(obj3);
    cout << "reset shp3 (obj3)" << endl;
    shp->print();
    cout << shp.use_count() << " pointers" << endl;
    shp2->print();
    cout << shp2.use_count() << " pointers" << endl;
    shp3->print();
    cout << shp3.use_count() << " pointers" << endl;
    shp2.reset();
    cout << "reset shp2 ()" << endl;
    cout << shp.use_count() << " pointers for shp1" << endl;
    cout << shp2.use_count() << " pointers for shp2" << endl;
    cout << shp3.use_count() << " pointers for shp3" << endl;
    cout << "========================"<< endl;
    return 0;
}
