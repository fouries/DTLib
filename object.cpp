#include "Object.h"
#include <cstdlib>


// 顶层父类的创建
// Object类用于统一动态内存申请的行为
// 在堆空间创建 Object子类的对象，失败时返回NULL值
// Object类为纯虚父类（抽象类），所有子类都能进行动态类型识别
using namespace std;

namespace DTLib
{

// new失败时返回空值，而不是异常
void* Object::operator new(unsigned int size) throw()
{
    //cout << "Object::operator new: " << size <<endl;
    return malloc(size);
}
void Object::operator delete(void* p)
{
    //cout << "Object::operator delete: " << p << endl;
    free(p);
}

void* Object::operator new[] (unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete[] (void* p)
{
    free(p);
}

bool Object::operator == (const Object& obj)
{
    return (this == &obj);
}

bool Object::operator != (const Object& obj)
{
    return (this != &obj);
}


Object::~Object()
{

}

}

