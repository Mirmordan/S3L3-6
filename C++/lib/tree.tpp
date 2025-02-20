#include <iostream>
#include <math.h>
#include <functional>
#include <string>
#include "tree.h"
using namespace std;

template <typename Type>
Tree<Type>::Node::Node(){
        left=nullptr;
        right=nullptr;
        height=0;
}

template <typename Type>
void Tree<Type>::serialize_to(ostream& output){
    output<<_size;
    if(_size!=0)
        serialize_recursion(_root,output);
};

template <typename Type>
void Tree<Type>::deserialize_from(istream& input){
    unsigned add_size;
    input>>add_size;
    for(unsigned i=0;i<add_size;i++){
        Type value;
        deserialize(value,input);
        insert(value);
    }
};

template <typename Type>
void Tree<Type>::binserialize_to(ostream& output){
    binserialize(_size,output);
    if(_size!=0)
        binserialize_recursion(_root,output);
};

template <typename Type>
void Tree<Type>::bindeserialize_from(istream& input){
    unsigned add_size,lol;
    bindeserialize(add_size,input);
    bindeserialize(lol,input);
    for(unsigned i=0;i<add_size;i++){
        Type value;
        bindeserialize(value,input);
        insert(value);
    }
};

template <typename Type>
void Tree<Type>::serialize_recursion(Node* print_node,ostream &output){
    if(print_node->left!=nullptr)
        serialize_recursion(print_node->left,output);
    serialize(' ',output);
    serialize(print_node->value,output);
    if(print_node->right!=nullptr) 
    serialize_recursion(print_node->right,output);
}

template <typename Type>
void Tree<Type>::binserialize_recursion(Node* print_node,ostream &output){
    if(print_node->left!=nullptr)
        binserialize_recursion(print_node->left,output);
    binserialize(print_node->value,output);
    if(print_node->right!=nullptr) 
        binserialize_recursion(print_node->right,output);
}


template <typename Type>
Tree<Type>::Node::Node (Type input){
    left=nullptr;
    right=nullptr;
    height=0;
    value=input;
}
template <typename Type>
Tree<Type>::Tree(){
    _size=0;
    _root=nullptr;
}

template <typename Type>
size_t Tree<Type>::size(){
    return _size;
}

template <typename Type>
void Tree<Type>::insert (Type value){    //Вставляем рекурсивно от корня
    insert_recursion(_root,value);
    _size++;
}

template <typename Type>
bool Tree<Type>::contains(Type value){        //Поиск через цикл

        Node* search_pointer=_root;   //Идём от корня
        while(true){
        if (search_pointer->value==value) return true;  //Нашли элемент
        if (search_pointer->value>value){  //Сравнение с текущим элементом, выбор ветви
            if(search_pointer->left==nullptr) return false; //Идём налево, некуда - нет элемента
            search_pointer=search_pointer->left;
        }
        else{
            if(search_pointer->right==nullptr) return false; //Идём направо, некуда - нет элемента
            search_pointer=search_pointer->right;
        }
    }
}

template <typename Type>
void Tree<Type>::erase(Type value){
        if(_size!=0)
        delete_recursion(_root,value);
}

template <typename Type>
void Tree<Type>::print(ostream &output){
    print_recursion(_root,output);
}

template <typename Type>
void Tree<Type>::insert_recursion(Node *& node,Type new_value){ //Рекурсивная вставка по предку
        if (node==nullptr){             //Свободно - запихиваем
            node=new Node(new_value);
            return;
        };
        if(node->value<new_value){    //Если не свободно, вызываем вставку от ветви
            insert_recursion(node->right,new_value);
        }
        else{
            insert_recursion(node->left,new_value);
        }
        check_balance(node); //После вставки в обратном порядке проверяем баланс
}

template <typename Type>
void Tree<Type>::delete_recursion(Node *&node,Type value){ //Рекурсивное удаление
        if(node->value==value){
            Node* delete_node=node;
            size_t key=(node->right!=nullptr) + (node->left!=nullptr);
            switch(key){
                case 0:{
                    node=nullptr;
                    delete delete_node;
                    _size--;
                    break;
                }
                case 1:{
                    if(node->right!=nullptr)
                        node=node->right;
                    else
                        node=node->left;
                    delete delete_node;
                    _size--;
                    break;
                }
                case 2:{
                    function<void(Node*&)> find=[&](Node*&node_ptr){
                        if(node_ptr->right!=nullptr){
                            find(node_ptr->right);
                            check_balance(node_ptr);
                        }
                        else{
                            swap_values(node_ptr,delete_node);
                            delete_recursion(node_ptr,value);
                        }
                    };
                    find(node->left);
                }
            }
        }
        else{
            if(node->right!=nullptr) 
                delete_recursion(node->right,value);
            if(node->left!=nullptr) 
                delete_recursion(node->left,value);
            check_balance(node);
        }
}

template <typename Type>
void Tree<Type>::print_recursion(Node* print_node,ostream &output){
    if(print_node->left!=nullptr)
        print_recursion(print_node->left,output);
    output<<(print_node->value)<<" ";
    if(print_node->right!=nullptr) 
    print_recursion(print_node->right,output);
}

template <typename Type>
int Tree<Type>::get_height(Node * node){
    if(node==nullptr) 
        return -1;
    else 
        return node->height;
}

template <typename Type>
void Tree<Type>::check_height(Node* node){
    if(node==nullptr)
        return;
    node->height=max(get_height(node->right),get_height(node->left))+1;
}

template <typename Type>
int Tree<Type>::get_balance(Node *node){ //Проверка баланса (<0 перевес влево, >0 перевес вправо)
        return get_height(node->right)-get_height(node->left); 
}

template <typename Type>
void Tree<Type>::check_balance(Node* check_node){     //Проверка баланса и правка
        int balance=get_balance(check_node);
        if(balance*balance < 4) 
            check_height(check_node); //Если баланс впорядке, обновляем высоту
        else {
            if (balance<0){ //Если баланс страдает, то крутим влево или вправо
                if(get_balance(check_node->left)>0) 
                    L_ROTATE(check_node->left);
                R_ROTATE(check_node);
            }
            else{
                if(get_balance(check_node->right)<0)
                    R_ROTATE(check_node->right);
                L_ROTATE(check_node);
            }
            check_height(check_node);
        }
    }
template <typename Type>
void Tree<Type>::swap_values(Node* first,Node *second){
    Type swap=first->value;
    first->value=second->value;
    second->value=swap;
}

template <typename Type>
void Tree<Type>::R_ROTATE (Node *rotate_node){
    Node *left_node=rotate_node->left;
    swap_values(rotate_node,left_node);
    rotate_node->left=left_node->left;
    left_node->left=left_node->right;
    left_node->right=rotate_node->right;
    rotate_node->right=left_node;

    check_balance(left_node);
    check_balance(rotate_node);
}
template <typename Type>
void Tree<Type>::L_ROTATE (Node *rotate_node){
    Node *right_node=rotate_node->right;
    swap_values(rotate_node,right_node);
    rotate_node->right=right_node->right;
    right_node->right=right_node->left;
    right_node->left=rotate_node->left;
    rotate_node->left=right_node;

    check_balance(right_node);
    check_balance(rotate_node);
}

template <typename Type>
typename Tree<Type>::Node* Tree<Type>::max_ptr(){
    Node* result=_root;
    while(result->right!=nullptr)
        result=result->right;
    return result;
}
