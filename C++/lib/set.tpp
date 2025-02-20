#include "set.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


template <typename Type>
Set<Type>::Node::Node(){
    _next_node=nullptr;
}

template <typename Type>
Set<Type>::Set(){
    _bucket_ammount=8;
    _size=0;
    _buckets=new Node*[_bucket_ammount];
    for(int i=0;i<_bucket_ammount;i++){
        _buckets[i]=new Node;
    }
}

template <typename Type>
Set<Type>::~Set(){
    for(size_t i=0;i<_bucket_ammount;i++){
        Node *delete_node=_buckets[i];
        while (delete_node!=nullptr){
            Node *next_node=delete_node->_next_node;
            delete delete_node;
            delete_node=next_node;
        }
    }
}

template <typename Type>
void Set<Type>::insert (Type value){
    Node *set_node=_buckets[Hash_function(value)];
    while(set_node->_next_node!=nullptr and set_node->_value!=value) 
        set_node=set_node->_next_node;
    set_node->_value=value;
    if(set_node->_next_node==nullptr)
        set_node->_next_node=new Node;
}



template <typename Type>
void Set<Type>::erase(Type key){
    Node **search_node=&_buckets[Hash_function(key)]; 
    while((*search_node)->_next_node!=nullptr and (*search_node)->_value!=key){
        search_node=&((*search_node)->_next_node);
    }
    if((*search_node)->_next_node!=nullptr){
        Node *delete_node=*search_node;
        *search_node=delete_node->_next_node;
        delete delete_node;
    }
}

template <typename Type>
bool Set<Type>::contains(Type key){
    Node* get_node=_buckets[Hash_function(key)];
    while(get_node->_next_node!=nullptr and get_node->_value!=key ) 
        get_node=get_node->_next_node;
    if (get_node->_value==key) 
        return true;
    else
        return false;
}

template <typename Type>
void Set<Type>::print(){
    for(auto i=0;i<_bucket_ammount;i++){
        Node *print_node=_buckets[i];
        while(print_node->_next_node!=nullptr){
            cout<<print_node->_value<<" ";
            print_node=print_node->_next_node;
        }
    }
    cout<<endl;
}

template <typename KeyType>
size_t Set<KeyType>::Hash_function(KeyType key){
    if(is_same <KeyType,string>::value or is_same <KeyType,int>::value){
        hash<KeyType> h;
        size_t index = h(key);
        return index%_bucket_ammount;
    }
}

template <typename Type>
void Set<Type>::open(string file){
    ifstream input_file(file);
    int number;
    while(input_file>>number)
        insert(number);
    input_file.close();
}

template <typename Type>
void Set<Type>::close(string file){
    ofstream output_file(file);
    for(auto i=0;i<_bucket_ammount;i++){
        Node *print_node=_buckets[i];
        while(print_node->_next_node!=nullptr){
            output_file<<print_node->_value<<" ";
            print_node=print_node->_next_node;
        }
    }
    output_file.close();
}