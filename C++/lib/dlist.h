#ifndef MYDOUBLELIST_H_
#define MYDOUBLELIST_H_
#include <iostream>
using namespace std;
template <typename Type>
class DoubleList{
    struct Node{
        Node * _previous;
        Node * _next;
        Type _value;
        Node();
        Node(Type value);
    };
    class iterator{
        public:
        Node* pointer;
        iterator();
        iterator(Node* node);
        iterator& operator++();
        iterator& operator--();
        Type& operator*();
        bool operator!=(const iterator& other);
    };
    
    public:
    DoubleList();
    ~DoubleList();
    
    void push_front(Type value);
    void push_back(Type value);
    void pop_front();
    void pop_back();
    void pop_value(Type value);
    iterator begin();
    iterator end();
    size_t size();

    private:
    void push_after(Node *pointer,Type&value);
    void pop_pointer(Node *pointer);


    Node _head;
    size_t _size;
};
#include "dlist.tpp"

#endif // MYONEWAYLIST_H_