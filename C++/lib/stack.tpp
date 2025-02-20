#include <iostream>
#include "stack.h"
using namespace std;

template <typename Type>
void Stack<Type>::push(Type value){
    Node *new_node=new Node(value);
    new_node->next=_head;
    _head=new_node;
    _size++;
};

template <typename Type>
void Stack<Type>::pop(){
    if(_size==0)
        return;
    Node *delete_node=_head;
    _head=delete_node->next;
    delete delete_node;
    _size--;
};

template <typename Type>
Type Stack<Type>::peek(){
    if(_size==0)
        return Type();
    return _head->value;
    
};

template <typename Type>
void Stack<Type>::inverse(){
    if(_size==0)
        return;
    Node *previous_node=nullptr;
    while(true){
        Node *next_node=_head->next;
        _head->next=previous_node;
        previous_node=_head;
        if(next_node!=nullptr)
            _head=next_node;
        else
            break;
    }
};

template <typename Type>
unsigned Stack<Type>::size(){
    return _size;
};

template <typename Type>
Stack<Type>::Stack(){
    _head=nullptr;
    _size=0;
};

template <typename Type> //Конструктор списка
Stack <Type>::~Stack(){
    Node * delete_pointer=_head;
    while(delete_pointer){
        Node * next_node=delete_pointer->next;
        delete delete_pointer;
        delete_pointer=next_node;
    }
}

template <typename Type>
void Stack<Type>::serialize_to(ostream& output){
    inverse();
    output<<_size;
    for(auto &i:*this){
        serialize(' ',output);
        serialize(i,output);
    }
    inverse();
};

template <typename Type>
void Stack<Type>::deserialize_from(istream& input){
    unsigned add_size;
    input>>add_size;
    for(unsigned i=0;i<add_size;i++){
        Type value;
        deserialize(value,input);
        push(value);
    }
};

template <typename Type>
void Stack<Type>::binserialize_to(ostream& output){
    inverse();
    binserialize(_size,output);
    for(auto &i:*this){
        binserialize(i,output);
    }
    inverse();
};



template <typename Type>
void Stack<Type>::bindeserialize_from(istream& input){
    unsigned add_size;
    bindeserialize(add_size,input);
    for(unsigned i=0;i<add_size;i++){
        Type value;
        bindeserialize(value,input);
        push(value);
    }
};

template <typename Type>
Stack<Type>::Node::Node(){
    next=nullptr;
};

template <typename Type>
Stack<Type>::Node::Node(Type value){
    this->value=value;
    next=nullptr;
};

template <typename Type>              
Stack <Type>::iterator::iterator(Node* node){
    pointer=node;
};

template <typename Type>                       //Начало списка
typename Stack <Type>::iterator Stack <Type>::begin(){
    return iterator(_head);
};

template <typename Type>                      //Конец
typename Stack <Type>::iterator Stack <Type>::end(){
    return iterator(nullptr);
};

template <typename Type>                //Операторы итератора
typename Stack <Type>::iterator& Stack <Type>::iterator::operator++(){
    pointer=pointer->next;
    return *this;
};

template <typename Type>
Type& Stack <Type>::iterator::operator*(){
    return pointer->value;
};

template <typename Type>
bool Stack <Type>::iterator::operator!=(const iterator& other){
    if(pointer!=other.pointer)
        return true;
    return false;
};
