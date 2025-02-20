#ifndef CUSTOM_SER_HPP_
#define CUSTOM_SER_HPP_
#include <iostream>
#include <type_traits>

using namespace std;

class Serializable{ //Интерфейс для специфически сериализуемых объектов (queue stack tree hash), очередь потому что стек (перевороты) и у них обоих методы push вместо push_back
    protected:
    void virtual serialize_to(ostream& output)=0;
    void virtual deserialize_from(istream& input)=0;
    void virtual binserialize_to(ostream& output)=0;
    void virtual bindeserialize_from(istream& input)=0;
    virtual ~Serializable(){};
};
////////////////////////////////////////////////////////////////////////////////////Сериализация
// Шаблон для базовых типов аля int char double
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
serialize(const T& value,ostream& output) {
    output << value;
}

// Шаблон для контейнеров 
template <typename T>
typename std::enable_if<!std::is_base_of<Serializable, T>::value &&
    std::is_same<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>::value>::type
serialize(T& value,ostream& output) {
    serialize(value.size(),output);
    for(auto &i:value){
        serialize(' ',output);
        serialize(i,output);
    }
}

//Шаблон для моих сериализуемых типов
template<typename T>
typename std::enable_if<std::is_base_of<Serializable, T>::value>::type
serialize(T& serializable,ostream& output) {
    serializable.serialize_to(output);
}
//////////////////////////////////////////////////////////////////////////////////////Десюреализация
// Шаблон для базовых типов аля int char double
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
deserialize(T& value,istream& output) {
    output >> value;
}

// Шаблон для контейнеров
template <template <typename> typename Container, typename T>
typename std::enable_if<!std::is_base_of<Serializable, Container<T>>::value>::type
deserialize(Container<T>& container,istream& output) {
    unsigned size;
    deserialize(size,output);
    for(unsigned i=0;i<size;i++){
        T value;
        deserialize(value,output);
        container.push_back(value);
    }
        
}

//Шаблон для моих сериализуемых типов
template<typename T>
typename std::enable_if<std::is_base_of<Serializable, T>::value>::type
deserialize(T& serializable,istream& input) {
    serializable.deserialize_from(input);
}

////////////////////////////////////////////////////////////////////////////////////Бинарная сериализация
// Шаблон для базовых типов аля int char double
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
binserialize(T& value,ostream& output) {
    output.write(reinterpret_cast<char*>(&value),sizeof(value));
}

template <typename T>
typename std::enable_if<!std::is_base_of<Serializable, T>::value &&
    std::is_same<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>::value>::type
binserialize(T& container,ostream& output) {
    unsigned size=container.size();
    binserialize(size,output);
    for(auto &i:container)
        binserialize(i,output);
}


//Шаблон для моих сериализуемых типов
template<typename T>
typename std::enable_if<std::is_base_of<Serializable, T>::value>::type
binserialize(T& serializable,ostream& output) {
    serializable.binserialize_to(output);
}
//////////////////////////////////////////////////////////////////////////////Десериализация бинарная
// Шаблон для базовых типов аля int char double
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
bindeserialize(T& value,istream& output) {
    output.read(reinterpret_cast<char*>(&value),sizeof(value));
}

template <template <typename> typename Container, typename T>
typename std::enable_if<!std::is_base_of<Serializable, Container<T>>::value>::type
bindeserialize(Container<T>& container,istream& output) {
    unsigned size;
    bindeserialize(size,output);
    for(unsigned i=0;i<size;i++){
        T value;
        bindeserialize(value,output);
        container.push_back(value);
    }
        
}


//Шаблон для моих сериализуемых типов
template<typename T>
typename std::enable_if<std::is_base_of<Serializable, T>::value>::type
bindeserialize(T& serializable,istream& input) {
    serializable.bindeserialize_from(input);
}
#endif