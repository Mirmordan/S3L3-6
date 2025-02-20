#ifndef MY_HASH_H_
#define MY_HASH_H_
#include <iostream>
#include "serialization.hpp"
using namespace std;

template <typename KeyType, typename ValueType>
class Hash:public Serializable{
    public:
    struct Node{                         //Элементы помимо ключ-значение обладают состоянием
        KeyType key;
        ValueType value;
        Node* next;
        Node(KeyType key,ValueType value):key(key),value(value),next(nullptr){};
    };
    
    Hash();
    ~Hash();

    void serialize_to(ostream& output)override;
    void deserialize_from(istream& input)override;
    void binserialize_to(ostream& output)override;
    void bindeserialize_from(istream& input)override;

    void insert (KeyType key,ValueType value);
    void erase (KeyType key);
    size_t size();
    bool contains(KeyType value);
    ValueType& operator[](KeyType key);
    
    private:
    void resize();
    unsigned Hash_function(KeyType key);
    size_t _table_size;
    size_t _size;
    Node ** _table;
};
#include "mhash.tpp"
#endif //MY_HASH_H_