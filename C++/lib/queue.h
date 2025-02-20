#ifndef MY_QUEUE_H_
#define MY_QUEUE_H_
#include "serialization.hpp"
template <typename Type>
class Queue:public Serializable{
    class Node{
        friend class Queue;
        Type value;
        Node* next;
        Node();
        Node(Type value);
    };
    class iterator{
        friend class Queue;
        Node* pointer;
        iterator();
        iterator(Node* node);
        public:
        iterator& operator++();
        Type& operator*();
        bool operator!=(const iterator& other);
    };
    public:
    Queue();
    ~Queue();

    void serialize_to(ostream& output)override;
    void deserialize_from(istream& input)override;
    void binserialize_to(ostream& output)override;
    void bindeserialize_from(istream& input)override;

    iterator begin();
    iterator end();

    void push(Type value);
    void pop();
    std::size_t size();
    Type& front();
    Type& back();
    
    private:
    Node * _tail;
    Node * _head;
    unsigned _size;
};
#include "queue.tpp"



#endif //MY_STACK_H_