/*
* @Author CristianCin
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
#include "evaluate.hpp"
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
string generateFunction();
string generatenumber();
string generatefraction();
string generateExp();
string generateDecimal();
string generateInt(string);
string deleteLastZeros(string);
char generateOperator();
int find(string, char);

int main(){

    string fun;
    bool dbg = false;
    if(dbg){
    cout<<"Insert complexity: "
        <<"\nvery easy \t1"
        <<"\neasy \t\t2"
        <<"\nmedium \t\t3"
        <<"\nhard \t\t4"
        <<"\nvery hard \t>=5\n";
    cin>>levelOfDifficult;
    }else
        levelOfDifficult = 2;
    srand(time(NULL));
    fun = generatefunction(levelOfDifficult);
    cout<<"f(x) = " <<fun<<endl;
    return 0;
}

string generatefunction(int numberOfCompositions){
    
    bool condPI = false;
    int openBrackets = 0;
    int closeBrackets = 0;
    string function = "";
    for(int i = 0; i < numberOfCompositions; i++){
        ope = generateOperator();
        int random = rand()%numberOfInnerCompositions;
        f = generateFunction();
        flag = false;
            if(f == "pi"){
                function += "\u03C0"; 
                condPI = true;
            }
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
                                function += "(", openBrackets++;
                            else{
                                flag = true;
                                function += "((";
                                openBrackets += 2;
                            }
                            if(f == "arccos" || f == "arcsin" || f == "arctan" || f == "arccotan")
                                function += generateDecimal();
                            else{
                                if(f == "cotan" || f == "tan")
                                    function += generateInt(f);
                                else
                                    function += (!random)? generateExp() : generatefunction(random);
                            }
    
                            function += ")";
                            closeBrackets++;
                        }
                    
            if(ope == '^'){
                function += "^(";
                openBrackets++;
                function += (!random)? generateExp() : generatefunction(random);
                function += ")";
                closeBrackets++;
                if(flag)
                    function += ")", closeBrackets++;

                while(ope != '^')
                    ope = generateOperator();

                if(i + 1 < numberOfCompositions)
                    function += ope;
            }else
                if(i + 1 < numberOfCompositions)
                    function += ope;
    }

    while(openBrackets > closeBrackets){
        function += ")";
        closeBrackets++;
    }

    if(condPI == false && count(function.begin(), function.end(), 'x') == 0 && count(function.begin(), function.end(), 'e') == 0)
        return to_string(evaluate(function)); 

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

    int mcd = MCD(num, den);
    num /= mcd;
    den /= mcd;

    if(num == 0)
        return "0";
    if(num == den)
        return "1";
    if(den == 1)
        return to_string(num);
                
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

int find(string a, char ch){
    for(int i = 0; i < a.size(); i++)
        if(a[i] == ch)
            return i;

    return -1;
}

string generateDecimal(){
    double n = rand()%32000 + 1;
    double divisor = pow(10, 5);
    double nn = n/divisor;
    return deleteLastZeros(to_string(nn));
}

string deleteLastZeros(string str){
    string newStr = "";

    for(int i = str.size() - 1; i > -1; i--)
        if(str[i] == '0')
            newStr = str + newStr;
        else
            break;

    return newStr;
}

string generateInt(string f){
    double n;
    if(f == "tan")
        n = rand()%89999;
    if(f == "cotan")
        n = rand()%90000 + 1;

    double nn = n/(pow(10, 5));
    return deleteLastZeros(to_string(nn));
    
}