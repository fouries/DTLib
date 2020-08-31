#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "SmartPointer.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        SmartPointer<Node> next;
    };

    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        SmartPointer<Node> next;
    } m_header;  // 头结点

    int m_length;
    int m_step;
    SmartPointer<Node> m_current;

    Node* position(int i) const     // O(n)
    {
        //Node* ret = reinterpret_cast<Node*>(&m_header);
        SmartPointer<Node> ret = reinterpret_cast<Node*>(&m_header);

        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }

        return ret.get();
    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
    }

public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }

    bool insert(const T& e)     // O(n)
    {
        return insert(m_length, e);
    }

    bool insert(int i, const T& e)      // O(n)
    {
        bool ret = ((0 <= i)&&(i <= m_length));

        if( ret )
        {
            Node* node = create();

            if( node != NULL )
            {
                Node* current = position(i);

                node->value = e;
                node->next = current->next;
                current->next = node;

                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
            }
        }

        return ret;
    }

    bool remove(int i)      // O(n)  0 1 2
    {
        bool ret = ((0 <= i) && (i <= m_length));

        if( ret )
        {
            SmartPointer<Node> current = position(i); // current指向第 i个结点
            SmartPointer<Node> toDel = current->next;

            if( m_current == toDel) // 游标是否指向已经删除的数据元素
            {
                // 游标指向即将被删除的元素的下一个元素
                m_current = toDel->next;
            }

            current->next = toDel->next; // current的指针域保存

            m_length--;

            //destroy(toDel.get());

        }

        return ret;
    }

    bool set(int i, const T& e)     // O(n)
    {
        bool ret = ((0 <= i) && (i <= m_length));

        if( ret )
        {

            position(i)->next->value = e;
        }

        return ret;
    }

    T get(int i) const
    {
        T ret;

        if(get(i, ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invaid parameter i to get element ...");
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = ((0 <= i) && (i <= m_length));

        if( ret )
        {

            e = position(i)->next->value;
        }

        return ret;
    }

    int find(const T& e) const      // O(n)
    {
        int ret = -1;
        int i = 0;
        SmartPointer<Node> node = m_header.next;

        // while( node )
        while( node.isNull() )
        {
            if( node->value == e )
            {
                ret = i;
                break;
            }
            else
            {
                node = node->next;
                i++;
            }
        }

        return ret;
    }

    int length() const      // O(1)
    {
        return m_length;
    }

    void clear()        // O(n)
    {
        // while( m_header.next )
        while( m_header.next.isNull() )
        {
            // Node* toDel = m_header.next;
            SmartPointer<Node> toDel = m_header.next;
            m_header.next = toDel->next;

            m_length--;

            //destroy(toDel.get());
        }

    }

    int move(int i, int step = 1)
    {
        bool ret = (0 <= i) && (i < m_length) && (step > 0);

        if( ret )
        {
            m_current = position(i)->next;
            m_step = step;
        }

        return ret;
    }

    bool end()
    {
        //return (m_current == NULL);
        return m_current.isNull();
    }

    T current()
    {
        if( !end() )
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    bool next()
    {
        int i = 0;

        while( (i < m_step) && !end() )
        {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);
    }

    ~LinkList()     // O(n)
    {
        clear();
    }
};

}

#endif // LINKLIST_H
