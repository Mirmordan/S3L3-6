#include "queue.h"
using namespace std;

template <typename Type>
Queue<Type>::Node::Node(){
    next=nullptr;
};

template <typename Type>
Queue<Type>::Node::Node(Type start_value){ //Инициализатор подкласса
    value=start_value;
    next=nullptr;
};

template <typename Type>
Queue<Type>::Queue(){  //Инициализатор класса
    _size=0;
    _head=_tail=nullptr;
};

template <typename Type>
Queue<Type>::~Queue(){  //Инициализатор класса
    while (_head!=nullptr){
        Node * delete_node=_head;
        _head=_head->next;
        delete delete_node;
    }
};

template <typename Type>
void Queue<Type>::serialize_to(ostream& output){
    output<<_size;
    for(auto &i:*this){
        serialize(' ',output);
        serialize(i,output);
    }
};

template <typename Type>
void Queue<Type>::deserialize_from(istream& input){
    unsigned add_size;
    input>>add_size;
    for(unsigned i=0;i<add_size;i++){
        Type value;
        deserialize(value,input);
        push(value);
    }
};

template <typename Type>
void Queue<Type>::binserialize_to(ostream& output){
    binserialize(_size,output);
    for(auto &i:*this){
        binserialize(i,output);
    }
};



template <typename Type>
void Queue<Type>::bindeserialize_from(istream& input){
    unsigned add_size;
    bindeserialize(add_size,input);
    for(unsigned i=0;i<add_size;i++){
        Type value;
        bindeserialize(value,input);
        push(value);
    }
};


template <typename Type>
void Queue<Type>::push(Type value){      //Добавление в хвост
    if(_size==0){
        _head=new Node(value);
        _tail=_head;
    }
    else{
        _tail->next=new Node(value);
        _tail=_tail->next;
    }
    _size++;
};

template <typename Type>
void Queue<Type>::pop(){      //Удаление первого с головы
    if (_size==0) return;
    Node *delete_node=_head;
    _head=_head->next;
    delete delete_node;
    _size--;
};

template <typename Type>
size_t Queue<Type>::size(){
    return _size;
}

template <typename Type>
Type& Queue<Type>::front(){
    return _head->value;
}

template <typename Type>
Type& Queue<Type>::back(){
    return _tail->value;
}

template <typename Type>              
Queue <Type>::iterator::iterator(Node* node){
    pointer=node;
};

template <typename Type>                       //Начало списка
typename Queue <Type>::iterator Queue <Type>::begin(){
    return iterator(_head);
};

template <typename Type>                      //Конец
typename Queue <Type>::iterator Queue <Type>::end(){
    return iterator(nullptr);
};

template <typename Type>                //Операторы итератора
typename Queue <Type>::iterator& Queue <Type>::iterator::operator++(){
    pointer=pointer->next;
    return *this;
};

template <typename Type>
Type& Queue <Type>::iterator::operator*(){
    return pointer->value;
};

template <typename Type>
bool Queue <Type>::iterator::operator!=(const iterator& other){
    if(pointer!=other.pointer)
        return true;
    return false;
};