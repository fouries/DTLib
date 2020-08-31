#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;             // 顺序存储空间的大小
public:
    DynamicList(int capacity)  // 申请空间
    {
        this->m_array = new T[capacity];  // new int(10)和 new int[10]的区别

        if( this->m_array != NULL )
        {
            this->m_length = 0;
            this->m_capacity = capacity;  // 当前对象的容量
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object ...");
        }
    }

    int capacity() const
    {
        return m_capacity;
    }

    /* 重新设置顺序存储空间的大小, 保存原顺序表数据 */
    void resize(int capacity)
    {
        if( capacity != m_capacity )
        {
            T* array = new T[capacity];

            if( array != NULL)
            {
                int length = (this->m_length < capacity ? this->m_length : capacity);

                for(int i=0; i<length; i++)
                {
                    array[i] = this->m_array[i];  // 保存原顺序表示数据
                }

                T* temp = this->m_array;   // delete[] this->m_array;

                this->m_array = array;
                this->m_length = length;
                this->m_capacity = capacity;

                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynamicList object ...");
            }
        }
    }

    ~DynamicList()   // 归还空间
    {
        delete[] this->m_array;
    }
};

}


#endif // DYNAMICLIST_H
