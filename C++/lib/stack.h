#ifndef MY_STACK_H_
#define MY_STACK_H_
#include <iostream>
#include "serialization.hpp"
template <typename Type>
class Stack:public Serializable{
    struct Node{
        Type value;
        Node* next;
        Node();
        Node(Type value);
    };
    class iterator{
        public:
        Node* pointer;
        iterator();
        iterator(Node* node);
        iterator& operator++();
        Type& operator*();
        bool operator!=(const iterator& other);
    };
    public:
    Stack();
    ~Stack();
    void serialize_to(ostream& output)override;
    void deserialize_from(istream& input)override;
    void binserialize_to(ostream& output)override;
    void bindeserialize_from(istream& input)override;
    iterator begin();
    iterator end();
    void push(Type value);
    void pop();
    unsigned size();
    Type peek();
    void inverse();
    private:
    Node * _head;
    unsigned _size;
};
#include "stack.tpp"



#endif //MY_STACK_H_