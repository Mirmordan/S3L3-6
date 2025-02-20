#include <string>
#include <iostream>
using namespace std;

template <typename Type>
Array<Type>::Array(){ //Инициализатор
        _size=0;
        capacity=16;
        array=new Type[capacity];
};
template <typename Type>
Array<Type>::Array(size_t start_size){ //Инициализатор
        _size=start_size;
        if(start_size<8) 
            capacity=8;
        else 
            capacity=start_size*1.5;
        array=new Type[capacity];
        for(int i=0;i<_size;i++)
            array[i]=Type();
};

template <typename Type>
std::size_t Array<Type>::size(){ //Функция, выводящая размер
        return _size;
}

template <typename Type>
void Array<Type>::push(int index,Type input){ //Добавление по индексу со сдвигом
    if(_size==capacity)
        resize();
    check_index(index);
    _size++;
    for(auto i=_size-1;i>index;i--){
         array[i]=array[i-1];
    }
    array[index]=input;
}

template <typename Type>
void Array<Type>::push_back(Type input){ //Добавление в конец
    if(_size==capacity)
        resize();
    array[_size]=input;
    _size++;
}

template <typename Type>
void Array<Type>::erase (std::size_t index){  //Удаление по индексу сдвигом
    check_index(index);
    _size--;
    for(auto i=index;i<_size;i++){
        array[i]=array[i+1];
    }
}

template <typename Type>
Type& Array<Type>::operator[](std::size_t index){ //Доступ оп индексу
    return array[index];
}

template <typename Type>
void Array<Type>::resize(){ // Метод реаллокации с увеличением размера
    capacity*=1.5;
    Type *new_array=new Type[capacity];
    for(auto i=0;i<_size;i++){
            new_array[i]=array[i];
    }
    delete[] array;
    array=new_array;
}

template <typename Type>
void Array<Type>::check_index(std::size_t index){ //Проверка индекса
    if (index<0 or index>_size-1){
        throw logic_error("Array out of range");
    }
}

template <typename Type>        //Конструкторы итератора
Type& Array <Type>::back(){
    return array[_size-1];
};

template <typename Type>        //Конструкторы итератора
Array <Type>::iterator::iterator(){
    pointer=nullptr;
};

template <typename Type>              
Array <Type>::iterator::iterator(Type *ptr){
    pointer=ptr;
};

template <typename Type>                       //Начало списка
typename Array <Type>::iterator Array <Type>::begin(){
    return iterator(array);
};

template <typename Type>                      //Конец
typename Array <Type>::iterator Array <Type>::end(){
    return iterator(array+_size);
};

template <typename Type>                //Операторы итератора
typename Array <Type>::iterator& Array <Type>::iterator::operator++(){
    pointer++;
    return *this;
};

template <typename Type>
Type& Array <Type>::iterator::operator*(){
    return *pointer;
};

template <typename Type>
typename Array <Type>::iterator Array <Type>::iterator::operator+(const int other){
    return iterator((this->pointer)+other);
};

template <typename Type>
bool Array <Type>::iterator::operator!=(const iterator& other){
    if(pointer!=other.pointer)
        return true;
    return false;
};

template <typename Type>
ptrdiff_t Array <Type>::iterator::operator-(const iterator& other){
    return this->pointer-other.pointer;
};

