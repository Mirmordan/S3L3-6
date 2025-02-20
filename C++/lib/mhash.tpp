#include <iostream>
#include <fstream>
#include <string>
#include "mhash.h"
using namespace std;

template <typename KeyType, typename ValueType>
Hash<KeyType,ValueType>::Hash(){
    _table_size=8;
    _size=0;
    _table=new Node*[_table_size];
    for(int i=0;i<_table_size;i++)
        _table[i]=nullptr;
}

template <typename KeyType, typename ValueType>
Hash<KeyType,ValueType>::~Hash(){
    for(auto i=0;i<_table_size;i++){
        Node* delete_node=_table[i];
        while (delete_node!=nullptr){
            Node *next_node=delete_node->next;
            delete delete_node;
            delete_node=next_node;
        }
    }
    delete[] _table;
}

template <typename KeyType, typename ValueType>
void Hash<KeyType,ValueType>::insert (KeyType key,ValueType value){
    if(_size*1.5>=_table_size)
        resize();
    unsigned bucket=Hash_function(key);
    Node ** insert_pointer=&(_table[bucket]);
    while((*insert_pointer)!=nullptr and (*insert_pointer)->key!=key)
        (*insert_pointer)=(*insert_pointer)->next;
    
    if((*insert_pointer)!=nullptr){
        (*insert_pointer)->value=value;
    }
    else
    {
        (*insert_pointer)=new Node(key,value);
        _size++;
    }
}

template <typename KeyType, typename ValueType>
void Hash<KeyType,ValueType>::erase(KeyType key){
    unsigned bucket=Hash_function(key);
    Node ** delete_pointer=&(_table[bucket]);
    while((*delete_pointer)!=nullptr and (*delete_pointer)->key!=key)
        (*delete_pointer)=(*delete_pointer)->next;
    if((*delete_pointer)!=nullptr)
        {
            Node *delete_node =(*delete_pointer);
            (*delete_pointer)=delete_node->next;
            delete delete_node;
            _size--;
        }
}

template <typename KeyType, typename ValueType>
size_t Hash<KeyType,ValueType>::size(){
    return _size;
}

template <typename KeyType, typename ValueType>
bool Hash<KeyType,ValueType>::contains(KeyType key){
    unsigned bucket=Hash_function(key);
    Node * search_pointer=_table[bucket];
    while(search_pointer!=nullptr and search_pointer->key!=key)
        search_pointer=search_pointer->next;
    if(search_pointer!=nullptr)
        return true;
    else
        return false;
}

template <typename KeyType, typename ValueType>
ValueType& Hash<KeyType,ValueType>::operator[](KeyType key){
    unsigned bucket=Hash_function(key);
    Node * search_pointer=_table[bucket];
    while(search_pointer!=nullptr and search_pointer->key!=key)
        search_pointer=search_pointer->next;
    if(search_pointer!=nullptr)
        return search_pointer->value;
    else{
        insert(key,ValueType());
        return (*this)[key];
    }
};

template <typename KeyType, typename ValueType>
void Hash<KeyType,ValueType>::serialize_to(ostream& output){
    output<<_size;
    for(int i=0;i<_table_size;i++){
        Node * out=_table[i];
        while(out!=nullptr){
            serialize(' ',output);
            serialize(out->key,output);
            serialize(' ',output);
            serialize(out->value,output);
            out=out->next;
        }
    }
};

template <typename KeyType, typename ValueType>
void Hash<KeyType,ValueType>::deserialize_from(istream& input){
    unsigned add_size;
    input>>add_size;
    for(unsigned i=0;i<add_size;i++){
        KeyType key;
        ValueType value;
        deserialize(key,input);
        deserialize(value,input);
        insert(key,value);
    }
};

template <typename KeyType, typename ValueType>
void Hash<KeyType,ValueType>::binserialize_to(ostream& output){
    unsigned size=_size;
    binserialize(size,output);
    for(int i=0;i<_table_size;i++){
        Node * out=_table[i];
        while(out!=nullptr){
            binserialize(out->key,output);
            binserialize(out->value,output);
            out=out->next;
        }
    }
};



template <typename KeyType, typename ValueType>
void Hash<KeyType,ValueType>::bindeserialize_from(istream& input){
    unsigned add_size;
    bindeserialize(add_size,input);
    cout<<add_size<<endl;
    for(unsigned i=0;i<add_size;i++){
        KeyType key;
        ValueType value;
        bindeserialize(key,input);
        bindeserialize(value,input);
        insert(key,value);
    }
};



template <typename KeyType, typename ValueType>
unsigned Hash<KeyType,ValueType>::Hash_function(KeyType key){
    hash<KeyType> h;
    unsigned index = h(key);
    return index%_table_size;
}

template <typename KeyType, typename ValueType>
void Hash<KeyType,ValueType>::resize(){
    _size=0;
    unsigned old_size=_table_size;
    _table_size*=3;
    Node **old_table=_table;
    _table=new Node*[_table_size];
    for(int i=0;i<_table_size;i++)
        _table[i]=nullptr;
    for(unsigned i=0;i<old_size;i++){
        Node *old_node=old_table[i];
        while(old_node!=nullptr){
            insert(old_node->key,old_node->value);
            old_node=old_node->next;
        }
    }
        
}