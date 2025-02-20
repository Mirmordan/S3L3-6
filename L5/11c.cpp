#include <vector>
#include <map>
#include <set>
#include <list>
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
    string king;
    cout<<"Команды"<<endl;
    cout<<"birth <родитель> <ребенок> - добавить наследника"<<endl;
    cout<<"death <умерший> - убить человечка"<<endl;
    cout<<"order - вывод порядка"<<endl;
    cout<<"exit - выход"<<endl;
    cout<<"Введите короля :"<<endl;
    ThroneInheritance kingdom("king");
    while (true){
        string command;
        cin>>command;
        if(command=="order"){
            for(auto &i:kingdom.getInheritanceOrder())
            cout<<i<<" ";
            cout<<endl;
        }
        if(command=="birth"){
            string parent,child;
            cin>>parent>>child;
            kingdom.birth(parent,child);
        }
        if(command=="death"){
            string dead;
            cin>>dead;
            kingdom.death(dead);
        }
        if(command=="exit"){
            break;
        }
    }
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




