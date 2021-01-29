/*
* @Author CristianCin
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

int levelOfDifficult, numberOfInnerCompositions = 2;
string f;
bool debug = false;
bool flag = false;
char ope;
vector<string> functions = {
    "sin", "cos", "tan", "cotan",
    "arcsin", "arccos", "arctan", "arccotan",
    "sqrt", "x", "e", "number", "pi",
    "log", "ln", "log_",
    "x", "x", "x", "x",
    "x", "x", "x", "x",
    };

vector<char> op = {'+', '-', '*', '/', '^'};

string generatefunction(int);
string generateInnerfunction(int);
string generateFunction();
string generatenumber();
string generatefraction();
string generateExp();
char generateOperator();

int main(){

    string fun;
    cout<<"Insert complexity: \nvery easy \t1\neasy \t\t2\nmedium \t\t3 \nhard \t\t4\nvery hard \t>=5\n";
    cin>>levelOfDifficult;
    srand(time(NULL));
    fun = generatefunction(levelOfDifficult);
    cout<<"f(x) = " <<fun<<endl;
    return 0;
}

string generateInnerfunction(int numberOfCompositions){
    string function = "";

    for(int i = 0; i < numberOfCompositions; i++){
        int random = rand()%numberOfInnerCompositions;
        ope = generateOperator();
        flag = false;
        f = generateFunction();
                if(f == "pi")
                    function += "\u03C0";
                else
                    if(f == "x" || f == "e")
                        function += f;
                    else{        
                            if(f == "number")
                                function += ((rand()%100)%2 == 0)? generatefraction() : generatenumber();
                            else{
                                if(f != "log_")
                                    function += f;
                                else
                                    function += f + to_string(rand()%8 + 2);

                                if(ope != '^')
                                    function += "(";
                                else{
                                        flag = true;
                                        function += "((";
                                }

                                function += (!random)? generateExp() : generateInnerfunction(random);
                                function += ")";
                            }
                        }
                        if(ope == '^'){
                            function += "^(";
                            function += (!random)? generateExp() : generateInnerfunction(random);
                            function += ")";
                            if(flag)
                                function += ")";

                            while(ope != '^')
                                ope = generateOperator();

                            if(i + 1 < numberOfCompositions)
                                function += ope;
                        }else
                            if(i + 1 < numberOfCompositions)
                                function += ope;

    }

    return function;
}

string generatefunction(int numberOfCompositions){

    string function = "";
    for(int i = 0; i < numberOfCompositions; i++){
        ope = generateOperator();
        int random = rand()%numberOfInnerCompositions;
        f = generateFunction();
        flag = false;
            if(f == "pi")
                function += "\u03C0";
            else
                if(f == "x" || f == "e")
                    function += f;
                else        
                        if(f == "number")
                            function += ((rand()%100)%2 == 0)? generatefraction() : generatenumber();
                        else{
                            if(f != "log_")
                                function += f;
                            else
                                function += f + to_string(rand()%8 + 2);
                            if(ope != '^')
                                function += "(";
                            else{
                                flag = true;
                                function += "((";
                            }
                                
                            function += (!random)? generateExp() : generateInnerfunction(random);
                            function += ")";
                        }
                    
            if(ope == '^'){
                function += "^(";
                function += (!random)? generateExp() : generateInnerfunction(random);
                function += ")";
                if(flag)
                    function += ")";

                while(ope != '^')
                    ope = generateOperator();

                if(i + 1 < numberOfCompositions)
                    function += ope;
            }else
                if(i + 1 < numberOfCompositions)
                    function += ope;
    }
    if(count(function.begin(), function.end(), '(') == count(function.begin(), function.end(), ')') + 1)
        function += ")";
    return function;
}

char generateOperator(){
    return op[rand()%(op.size())];
}

string generatenumber(){
    return to_string(rand()%100 + 1);
}

int MCD(int a, int b)
{
    int r;
    r = a % b;
    while (r>0){
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

string generatefraction(){
    int num = rand()%10;
    int den = rand()%10 + 1;

    if(num == 0)
        return "0";
    if(num == den)
        return "1";
    if(den == 1)
        return to_string(num);

    int mcd = MCD(num, den);
    num /= mcd;
    den /= mcd;
    
    return "("+to_string(num)+"/"+to_string(den)+")";
}

string generateFunction(){
    return functions[rand()%(functions.size())];
}

string generateExp(){
    string res = functions[rand()%4 + 9];
    res = (res == "number")? ((rand()%100)%2 == 0)? generatefraction() : generatenumber() : res; 
    res = (res == "pi")? "\u03C0" : res;
    return res;
}