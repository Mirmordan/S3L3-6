#include "flist.h"
#include <iostream>
using namespace std;

template <typename Type>  //Конструкторы ноды
ForwardList<Type>::Node::Node(){
     _next=nullptr;
};

template <typename Type>
ForwardList<Type>::Node::Node(Type value){
    _next=nullptr;
    _value=value;
};

template <typename Type> //Конструктор списка
ForwardList <Type>::ForwardList(){
    _size=0;
    _tail=_head=nullptr;
}
template <typename Type> //Конструктор списка
ForwardList <Type>::~ForwardList(){
    Node * delete_pointer=_head;
    while(delete_pointer){
        Node * next_node=delete_pointer->_next;
        delete delete_pointer;
        delete_pointer=next_node;
    }
}

template <typename Type>    
void ForwardList <Type>::pop_front(){
    if (_size==0)
        return;
    Node * delete_node=_head;
    if(_size==1){
        _head=nullptr;
        _tail=nullptr;
    }
    else
        _head=_head->_next;
    delete delete_node;
    _size--;
}

template <typename Type>    
void ForwardList <Type>::pop_back(){
    if (_size==0)
        return;
    Node * delete_node=_tail;
    if(_size==1){
        _head=nullptr;
        _tail=nullptr;
    }
    else{
        Node* search_pointer=_head;
        while(search_pointer->_next!=_tail)
            search_pointer=search_pointer->_next;
        search_pointer->_next=nullptr;
        _tail=search_pointer;
    }
    delete delete_node;
    _size--;
}

template <typename Type>    
void ForwardList <Type>::push_front(Type value){
    if (_size==0){
        _head=new Node(value);
        _tail=_head;
    }
    else {
        Node *new_node= new Node(value);
        new_node->_next=_head;
        _head=new_node;
    }
    _size++;
}

template <typename Type> // Добавление в хвост
void ForwardList <Type>::push_back(Type value){
    if (_size==0)
        _tail=_head=new Node(value);
    else {
        _tail->_next=new Node(value);
        _tail=_tail->_next;
    }
    _size++;
}

template <typename Type>
unsigned ForwardList <Type>::size(){
    return _size;
}

template <typename Type>        //Конструкторы итератора
ForwardList <Type>::iterator::iterator(){
    pointer=nullptr;
};

template <typename Type>              
ForwardList <Type>::iterator::iterator(Node* node){
    pointer=node;
};

template <typename Type>                       //Начало списка
typename ForwardList <Type>::iterator ForwardList <Type>::begin(){
    return iterator(_head);
};

template <typename Type>                      //Конец
typename ForwardList <Type>::iterator ForwardList <Type>::end(){
    return iterator(nullptr);
};

template <typename Type>                //Операторы итератора
typename ForwardList <Type>::iterator& ForwardList <Type>::iterator::operator++(){
    pointer=pointer->_next;
    return *this;
};

template <typename Type>
Type& ForwardList <Type>::iterator::operator*(){
    return pointer->_value;
};

template <typename Type>
bool ForwardList <Type>::iterator::operator!=(const iterator& other){
    if(pointer!=other.pointer)
        return true;
    return false;
};