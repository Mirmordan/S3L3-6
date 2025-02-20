#include <thread>
#include <atomic>
#include <mutex>
#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
struct Student{
    static unsigned student_number;
    Student(){
        Name+=vector<string>{"Mark","Daniil","Ivan","Petya","Sereja","Vitya","Oleg","Sasha"}[rand()%8];
        Name+=" ";
        Name+=vector<string>{"Ivanov","Morozov","Petrov","Fedorov","Nikitich","Harkonin","Stark","Jevovich"}[rand()%8];
        Group="AB";
        unsigned group_number=100+(student_number++)/30;
        Group+=to_string(group_number);
        for(int i=1;i<=8;i++){
            Results.emplace_back(i,"Programming",rand()%3+3);
            Results.emplace_back(i,"Physics",rand()%3+3);
            Results.emplace_back(i,"Phylosophy",rand()%3+3);
            Results.emplace_back(i,"Electrycity",rand()%3+3);
            Results.emplace_back(i,"OIB",rand()%3+3);
            Results.emplace_back(i,"PE",rand()%3+3);
        }
    }
    
    struct Result{
        short Mark:8;
        short Term:8;
        string Subject;
        Result(short term,string subject,short mark):Mark(mark),Subject(subject),Term(term){}
    };
    
    string Name;
    string Group;
    vector <Result> Results;
};
unsigned Student::student_number=0;

int main()
{ 
    short term;                         //Стартовые условия
    string group;
    unsigned data_amount=60000; 
    unsigned thread_amount=8;
    cout<<"Введите объём выборки"<<endl;
    cin>>data_amount;
    cout<<"Введите число потоков"<<endl;
    cin>>thread_amount;
    cout<<"Введите семестр (1-8)"<<endl;
    cin>>term;
    cout<<"Введите название группы (ABXXX, начиная с AB100)"<<endl;
    cin>>group;
    
    vector<Student> data(data_amount);       //Ресурс и счётчики
    unsigned normal_count(0);
    unsigned multi_count(0);
    
    std::chrono::time_point<std::chrono::system_clock> start,multi; ////////Замеры
    std::chrono::duration<double> multithreading,normal;
    cout<<"Sequentional"<<endl;
    start=chrono::system_clock::now();
    /////////////////////////////////////////////Обычная обработка
    for(auto &stud:data){
        if(stud.Group!=group)
            continue;
        bool is_good_student=true;
        for(auto result:stud.Results){
            if(result.Term!=term)
                    continue;
                if(result.Mark<4){
                    is_good_student=false;
                    break;
                }
        }
        if(is_good_student){
            cout<<stud.Name<<" "<<stud.Group<<endl;
            normal_count++;
        }
    } 
    ///////////////////////////////////
    normal=chrono::system_clock::now()-start;
    cout<<"Multithread"<<endl;
    multi=chrono::system_clock::now();
    ///////////////////////////////////Многопоточная обработка
    mutex m;
    
    
    auto process=[&](unsigned left,unsigned right){
        for(unsigned current_index=left;current_index<right;current_index++){
            bool is_good_student=true;
            if(data[current_index].Group!=group){
                continue;
            }
            for(auto &result:data[current_index].Results){
                if(result.Term!=term)
                    continue;
                if(result.Mark<4){
                    is_good_student=false;
                    break;
                }
            }
            if(is_good_student){
                cout<<data[current_index].Name<<" "<<data[current_index].Group<<endl;
                multi_count++;
            }
        }
    };
    
    vector<thread> thread_pool;
    unsigned low=0,app=data_amount/thread_amount;
    if(thread_amount<data_amount)
        thread_amount=1;
    for(int i=0;i<thread_amount-1;i++){
        thread_pool.emplace_back(process,low,low+app);
        low+=app;
    }
    thread_pool.emplace_back(process,low,data_amount);
    for(auto &i:thread_pool)
        i.join();
    ///////////////////////////////////
    multithreading=chrono::system_clock::now()-multi;
    
    cout<<"Multithreading time:"<<multithreading.count()<<endl;
    cout<<"Multithreading result:"<<multi_count<<endl;
    cout<<"Sequentional time:"<<normal.count()<<endl;
    cout<<"Sequentional result:"<<normal_count<<endl;

    return 0;
}