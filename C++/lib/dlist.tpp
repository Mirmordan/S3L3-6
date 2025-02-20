#include "dlist.h"
#include <iostream>
using namespace std;

template <typename Type>  //Конструкторы ноды
DoubleList<Type>::Node::Node(){
     _next=nullptr;
     _previous=nullptr;
};

template <typename Type>
DoubleList<Type>::Node::Node(Type value){
    _previous=nullptr;
    _next=nullptr;
    _value=value;
};

template <typename Type> //Конструктор списка
DoubleList <Type>::DoubleList(){
    _size=0;
    _head._next=_head._previous=&_head;
}
template <typename Type> //Конструктор списка
DoubleList <Type>::~DoubleList(){
    Node * delete_pointer=_head._next;
    while(delete_pointer!=&_head){
        Node * next_node=delete_pointer->_next;
        delete delete_pointer;
        delete_pointer=next_node;
    }
}

template <typename Type>    
void DoubleList <Type>::pop_pointer(Node *pointer){
    pointer->_next->_previous=pointer->_previous;
    pointer->_previous->_next=pointer->_next;
    delete pointer;
    _size--;
}

template <typename Type>    
void DoubleList <Type>::pop_front(){
    if (_size==0)
        return;
    pop_pointer(_head._next);
}

template <typename Type>    
void DoubleList <Type>::pop_back(){
    if (_size==0)
        return;
    pop_pointer(_head._previous);
}

template <typename Type>    
void DoubleList <Type>::pop_value(Type value){
    Node * delete_node=_head._next;
    while(delete_node!=&_head and delete_node->_value!=value)
        delete_node=delete_node->_next;
    if(delete_node!=&_head)
        pop_pointer(delete_node);
}

template <typename Type>    
void DoubleList <Type>::push_after(Node * pointer,Type& value){
    Node * new_node=new Node(value); //Новая нода

    new_node->_next=pointer->_next;   //Подвешиваем новую ноду 
    new_node->_previous=pointer;

    pointer->_next->_previous=new_node; //Переподвешиваем ноду до и после
    pointer->_next=new_node;

    _size++; //+ размер
}

template <typename Type>                            //Добавление в начало 
void DoubleList <Type>::push_front(Type value){
    push_after(&_head,value);
}

template <typename Type>                                // Добавление в хвост
void DoubleList <Type>::push_back(Type value){
    push_after(_head._previous,value);
}

template <typename Type>
size_t DoubleList <Type>::size(){
    return _size;
}

template <typename Type>                            //Конструкторы итератора
DoubleList <Type>::iterator::iterator(){
    pointer=nullptr;
};

template <typename Type>              
DoubleList <Type>::iterator::iterator(Node* node){
    pointer=node;
};

template <typename Type>                       //Начало списка
typename DoubleList <Type>::iterator DoubleList <Type>::begin(){
    return iterator(_head._next);
};

template <typename Type>                      //Конец
typename DoubleList <Type>::iterator DoubleList <Type>::end(){
    return iterator(&_head);
};

template <typename Type>                //Операторы итератора
typename DoubleList <Type>::iterator& DoubleList <Type>::iterator::operator++(){
    pointer=pointer->_next;
    return *this;
};

template <typename Type>                //Операторы итератора
typename DoubleList <Type>::iterator& DoubleList <Type>::iterator::operator--(){
    pointer=pointer->_previous;
    return *this;
};

template <typename Type>
Type& DoubleList <Type>::iterator::operator*(){
    return pointer->_value;
};

template <typename Type>
bool DoubleList <Type>::iterator::operator!=(const iterator& other){
    if(pointer!=other.pointer)
        return true;
    return false;
};