#ifndef LIST_H
#define LIST_H

#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

#endif // LIST_H

namespace stepik
{
template <class Type>
struct node
{
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
        : value(value), next(next), prev(prev)
    {
    }
};

template <class Type>
class list; //forward declaration

template <class Type>
class list_iterator
{
public:
    typedef ptrdiff_t difference_type;
    typedef Type value_type;
    typedef Type* pointer;
    typedef Type& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;

    list_iterator()
        : m_node(NULL)
    {
    }

    list_iterator(const list_iterator& other)
        : m_node(other.m_node)
    {
    }

    list_iterator& operator = (const list_iterator& other)
    {
        if (this != &other)
            m_node = other.m_node;

        return *this;
    }

    bool operator == (const list_iterator& other) const
    {
        if (m_node == other.m_node)
            return true;

        return false;
    }

    bool operator != (const list_iterator& other) const
    {
        if (m_node != other.m_node)
            return true;

        return false;
    }

    reference operator * ()
    {
        return m_node->value;
    }

    pointer operator -> ()
    {
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
        m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        list_iterator temp = *this;
        m_node = m_node->next;
        return temp;
    }

private:
    friend class list<Type>;

    list_iterator(node<Type>* p)
        : m_node(p)
    {
    }

    node<Type>* m_node;
};

//------------------------------------------------------

template <class Type>
class list
{
public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_iterator<Type> iterator;

    list()
        : m_head(nullptr), m_tail(nullptr)
    {
    }

    ~list()
    {
        clear();
    }

    void swap(list& first, list& second)
    {
        std::swap(first.m_head, second.m_head);
        std::swap(first.m_tail, second.m_tail);
    }

    list(const list& other) : list()
    {
        node<Type> *temp = other.m_head;
        for (temp; temp; temp = temp->next)
            push_back(temp->value);
    }

    list(list&& other) : list()
    {
        swap(*this, other);
    }

    list& operator= (const list& other)
    {

        if (!empty())
            clear();
        node<Type> *temp = other.m_head;
        for (temp; temp; temp = temp->next)
            push_back(temp->value);

        return *this;
    }


    const_reference front() const
    {
        return m_head->value;
    }


    const_reference back() const
    {
        return m_tail->value;
    }


    size_t size() const
    {
        size_t size = 0;
        node<Type> *temp = m_head;
        while (temp!=NULL)
        {
            size++;
            temp = temp->next;
        }

        return size;
    }

    list::iterator begin()
    {
        return iterator(m_head);
    }

    list::iterator end()
    {
        return iterator();
    }

    void push_back(const value_type& value)
    {

        if (!empty())
        {
            m_tail->next = new node<Type>(value, NULL, m_tail);
            m_tail = m_tail->next;
        }
        else
        {
            m_tail = new node<Type>(value, NULL, NULL);
            m_head = m_tail;
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
        if (pos==begin())
        {
            push_front(value);
            return begin();
        }

        if (pos==end())
        {
            push_back(value);
            return iterator(m_tail);
        }

        node<Type> *temp = new node<Type>(value, pos.m_node, pos.m_node->prev);
        temp->prev->next = temp;
        temp->next->prev = temp;
        return iterator(temp);
    }

    iterator erase(iterator pos)
    {
        if (pos.m_node==NULL)
            return iterator();

        if (pos==begin())
        {
            pop_front();
            return begin();
        }

        if (pos==iterator(m_tail))
        {
            pop_back();
            return end();
        }

        pos.m_node->next->prev = pos.m_node->prev;
        pos.m_node->prev->next = pos.m_node->next;
        list_iterator<Type>  temp(pos.m_node->next);
        delete pos.m_node;
        return temp;
    }

    reference front()
    {
        return m_head->value;
    }

    reference back()
    {
        return m_tail->value;
    }

    void clear()
    {
        node<Type>* temp = m_head;
        while( m_head )
        {
            temp = m_head;
            m_head = m_head->next;
            delete temp;
        }
        m_head = NULL;
        m_tail = NULL;
    }


    bool empty() const
    {
        if ((m_head==NULL)&&(m_tail==NULL))
            return true;
        return false;
    }

    void push_front(const value_type& value)
    {
        if (this->empty() == false)
        {
            m_head->prev = new node<Type>(value, m_head, NULL);
            m_head = m_head->prev;
        }
        else
        {
            m_head = new node<Type>(value, NULL, NULL);
            m_tail = m_head;
        }
    }

    void pop_front()
    {
        if (m_head->next!=NULL)
        {
            m_head = m_head->next;
            delete m_head->prev;
            m_head->prev = NULL;
        }
        else
        {
            m_tail = NULL;
            delete m_head;
            m_head = NULL;
        }
    }

    void pop_back()
    {
        if (m_tail->prev!=NULL)
        {
            m_tail = m_tail->prev;
            delete m_tail->next;
            m_tail->next = NULL;
        }
        else
        {
            m_head = NULL;
            delete m_tail;
            m_tail = NULL;
        }
    }

private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
};

}// namespace stepik
