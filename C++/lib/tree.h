#ifndef MYTREE_H_
#define MYTREE_H_
#include <iostream>
#include "serialization.hpp"
using namespace std;
template <typename Type>
class Tree:public Serializable{
    struct Node {
        Node *left;
        Node *right;
        int height;
        Type value;
        Node ();
        Node (Type input);
    };
    public:
    Tree();
    
    void insert(Type value);
    void erase(Type value);
    bool contains(Type value);
    void print(ostream &output);

    void serialize_to(ostream& output)override;
    void deserialize_from(istream& input)override;
    void binserialize_to(ostream& output)override;
    void bindeserialize_from(istream& input)override;

    size_t size();

    private:
    void serialize_recursion(Node* print_node,ostream &output);
    void binserialize_recursion(Node* print_node,ostream &output);

    void insert_recursion(Node *& node,Type new_value);
    void delete_recursion(Node *&node,Type value);
    void print_recursion(Node* print_node,ostream &output);
    
    int get_height(Node* node);        //Балансировка
    void check_height(Node* check_node);
    int get_balance(Node* node);
    void check_balance(Node* check_node);
    void swap_values(Node* first,Node *second);
    void R_ROTATE (Node *rotate_node);
    void L_ROTATE (Node *rotate_node);
    Node * max_ptr();

    size_t _size;
    Node* _root;
};
#include "tree.tpp"
#endif //MYTREE_H_