#include <iostream>
#include "SharePointer.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
public:
    int value;

    Test() : value(0)
    {
        cout << "Test()" << endl;
    }

    ~Test()
    {
        cout << "~Test()" << endl;
    }
};

int main()
{
    const SharePointer<Test> sp0 = new Test();


    return 0;
}
