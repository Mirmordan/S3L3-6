#ifndef MYONEWAYLIST_H_
#define MYONEWAYLIST_H_
using namespace std;
template <typename Type>
class ForwardList{
    struct Node{
        Node * _next;
        Type _value;
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
    ForwardList();
    ~ForwardList();
    void push_front(Type value);
    void push_back(Type value);
    void pop_front();
    void pop_back();
    iterator begin();
    iterator end();
    unsigned size();
    private:
    Node*_head;
    Node*_tail;
    unsigned _size;
};
#include "flist.tpp"

#endif // MYONEWAYLIST_H_