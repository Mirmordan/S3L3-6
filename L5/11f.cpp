#include <vector>
#include <map>
#include <set>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class ThroneInheritance{
    public:
    ThroneInheritance(string kingName);
    void birth(string parentName, string childName);
    void death(string name);
    vector<string> getInheritanceOrder();
    
    private:
    
    
    map<string,list<string>> People;
    set<string> Dead_People;
    string kingName;
};



int main()
{
    ifstream input_file("11i.txt");
    ofstream output_file("11o.txt");
    string commands;
    getline(input_file,commands);
    string arguments;
    getline(input_file,arguments);
    list <string> command_list;
    list <string> argument_list;
    output_file<<"[";
    
    stringstream command_stream(commands);
    command_stream.ignore(100,'"');
    while(getline(command_stream,commands,'\"')){
        command_list.push_back(commands);
        command_stream.ignore(100,'"');
    }
    
    stringstream argument_stream(arguments);
    argument_stream.ignore(100,'"');
    while(getline(argument_stream,arguments,'\"')){
        argument_list.push_back(arguments);
        argument_stream.ignore(100,'"');
    }
    
    auto argument_iter=argument_list.begin();
    ThroneInheritance kingdom(*(argument_iter++));
    unsigned command_number=0;
    
    for(string &command:command_list){
        if(command=="birth"){
            string parent,child;
            parent=*(argument_iter++);
            child=*(argument_iter++);
            kingdom.birth(parent,child);
        }
        else
        if(command=="death"){
            string dead=*(argument_iter++);
            kingdom.death(dead);
        }

        if(command_number>0)
            output_file<<",";
        if(command=="getInheritanceOrder"){
            argument_iter++;
            output_file<<"[";
            vector<string> order=kingdom.getInheritanceOrder();
            for(auto &i:order){
                if(i!=order[0])
                    output_file<<",";
                output_file<<"\""<<i<<"\"";
            }
            output_file<<"]";
        }
        else
            output_file<<"null";
        command_number++;
    }
    output_file<<"]";
}

using TI = ThroneInheritance;

TI::ThroneInheritance(string kingName):kingName(kingName){
    People[kingName];
}

void TI::birth(string parentName, string childName){
    if(!People.count(parentName) or Dead_People.count(parentName))
        return;    //Родитель убежал за хлебом или умер
    if(People.count(childName))
        return;       //Такой уже есть в таблице
    People[parentName].push_back(childName);
    People[childName];
}

void TI::death(string name){
    if(Dead_People.count(name) or !People.count(name))
        return; //Уже мертв или не существует
    Dead_People.insert(name);
}

vector<string> TI::getInheritanceOrder(){
    vector<string> order;
    
    auto Successors = [&](const auto& self, string name) ->void {
        if (!Dead_People.count(name)) { // Если человек не умер, он первый правит
            order.push_back(name);
        }

        // Если у человека есть дети, рекурсивно вызываем Successors для каждого ребенка
        for (const auto& child : People[name]) {
            self(self, child); // Передаем саму себя как параметр
        }
    };
    Successors(Successors,kingName);
    return order;
}




