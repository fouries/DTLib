#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

// 智能指针使用军规：
// 1.只能用来指向堆空间的单个变量（对象）
// 2.不同类型的智能指针对象不能混合使用
// 3.不要使用delete释放智能指针指向的堆空间
namespace DTLib
{

template < typename T >
class Pointer : public Object
{
protected:
    T* m_pointer;

public:
    Pointer(T* p = NULL)
    {
        m_pointer = p;
    }

    T* operator-> ()
    {
        return m_pointer;
    }

    const T& operator* () const
    {
        return *m_pointer;
    }

    const T* operator-> () const
    {
        return m_pointer;
    }

    T& operator* ()
    {
        return *m_pointer;
    }

    bool isNull() const
    {
        return (m_pointer == NULL);
    }

    T* get() const
    {
        return m_pointer;
    }

};

}

#endif // POINTER_H
