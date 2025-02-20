#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <set>
using namespace std;

class Decorator{
    ostream *output;
    bool is_green;
    public:
    Decorator (ostream& ost){
        output=&ost;
        *output<<"<html>"<<endl;
        is_green=false;
    }
    ~Decorator(){
        *output<<"</html>";
    }
    template<typename T>
    Decorator& operator<<(const T& value){
        stringstream input_stream(value);
        string token;
        while (input_stream>>token){
            
            while (token.find('<') != std::string::npos) 
                token.replace(token.find('<'), 1, "&lt;");
            while (token.find('>') != std::string::npos) 
                token.replace(token.find('>'), 1, "&gt;");
            unsigned pos=0;
            while (token.find('\"',pos) != std::string::npos){
                pos=token.find('\"',pos);
                if (pos>0 and token[pos-1]=='\\'){
                    token.replace(pos-1,2,"<blu style=\"color: blue;\">\\\" </blu>");
                    pos+=34;
                }
                else
                if (is_green){
                    token.replace(pos, 1, "\"</green>");
                    pos+=8;
                    is_green=false;
                }
                else {
                    token.replace(pos, 1, "<green style=\"color: green;\">\"" );
                    pos+=30;
                    is_green=true;
                }
            }
            if (is_green){
                (*output)<<token<<" ";
                continue ;
            }
            if (blue_replace.count(token))
                (*output)<<"<span style=\"color: blue;\">"<<token<<" </span>";
            else if (orange_replace.count(token))
                (*output)<<"<span style=\"color: orange;\"> "<<token<<" </span>";
            else
                (*output)<<token<<" ";
        }
        return *this;
    }
    Decorator& operator<<(ostream& (*manip)(std::ostream&)){
        if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl))
            *output<<"<br>";
        manip(*output);
        return *this;
    }
    const static set<string> blue_replace;
    const static set<string> orange_replace;
};
const set<string> Decorator::blue_replace={
        "char","short","int","long","unsigned","string","bool",
        "class","true","false"
};
const set<string> Decorator::orange_replace={
        "or","and",
        "#include","using","namespace",
        "if","while","return","break","continue",
        "const","static"
};

int main(){
    ofstream output_f("o.html");
    ifstream input_f("13.cpp");

    Decorator decor(output_f);
    string input;
    while (getline(input_f,input))
        decor<<input<<endl;

    Decorator console(cout);
    console << "string a=\"Hello world\""<<endl;
}