#ifndef MY_SET_H_
#define MY_SET_H_
#include "serialization.hpp"
#include <iostream>
template <typename Type>
class Set{
    struct Node{
        Type _value;
        Node* _next_node;
        Node();
    };
    public:
    Set();
    ~Set();
    
    void insert(Type input_value);
    void erase(Type key);
    bool contains(Type input_value);
    void resize();
    void print();
    void open(std::string file);
    void close(std::string file);
    private:
    void rehash();
    size_t Hash_function(Type key);
    size_t _bucket_ammount;
    size_t _size;
    Node ** _buckets;
};
#include "set.tpp"

#endif //MY_SET_H_