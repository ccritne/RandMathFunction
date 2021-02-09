#include "evaluate.hpp"
#include <bits/stdc++.h>
using namespace std;

string generatefunction(int);
string generateFunction();
string generatenumber();
string generatespecialnumber(int,int,int);
string generatefraction();
string generatespecialfraction(double);
string generateExp();
string generateDecimal();
string generateInt(string);
string deleteLastZeros(string);
string change(string, double);
char generateOperator();

int levelOfDifficult, numberOfInnerCompositions = 2;
string f;
bool debug = false;
bool flag = false;
char ope;


#define all(x) (x).begin(), (x).end()

vector<string> functions = {
    "sin", "cos", "tan", "cotan",
    "arcsin", "arccos", "arctan", "arccotan",
    "sqrt", "x", "2.718", "number", "3.141",
    "log", "ln", "log_",
    "x", "x", "x", "x",
    "x", "x", "x", "x",
    };

vector<char> op = {'+', '-', '*', '/', '^'};


string generatefunction(int numberOfCompositions){
    
    int openBrackets = 0;
    int closeBrackets = 0;
    string function = "";
    for(int i = 0; i < numberOfCompositions; i++){
        ope = generateOperator();
        int random = rand()%numberOfInnerCompositions;
        f = generateFunction();
        flag = false;
                if(f == "x" || f == "2.718" || f == "3.141")
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

    if(count(function.begin(), function.end(), 'x') == 0 && count(function.begin(), function.end(), 'e') == 0){
        double nret = evaluate(function);
        if(!isnan(nret))
            return to_string(nret);
    }

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

string generatespecialnumber(int diverse, int max, int min){
    
    double n = rand()%max + min;

    while(n == diverse)
        n = rand()%max + min;

    return deleteLastZeros(to_string(n));
}

string generatespecialfraction(double diverse){
    
    int num, den, mcd, fraction;
    do{
    num = rand()%10;
    den = rand()%10 + 1;
    mcd = MCD(num, den);

    num /= mcd;
    den /= mcd;

    double fraction = (double)num/(double)den;
    }while(fraction != diverse);

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
    res = (res == "number")? ((rand()%100)%2 == 0)? generatespecialfraction(0) : generatespecialnumber(0, 10, 0.1) : res; 
    return res;
}

string generateDecimal(){
    double n = rand()%32000 + 1;
    double divisor = pow(10, 5);
    double nn = n/divisor;
    return deleteLastZeros(to_string(nn));
}

string deleteLastZeros(string str){

    int i;
    for(i = str.size() - 1; i > -1; i--)
        if(str[i] != '0' && str[i] != '.')
            break;
    

    return str.substr(0, i+1);
}

string generateInt(string f){
    int n;
    if(f == "tan")
        n = rand()%89999;
    if(f == "cotan")
        n = rand()%90000 + 1;

    int nn = n/(pow(10, 5));
    return to_string(nn);
    
}

string change(string newstr, double value){
    string str = newstr;
    string nstr = to_string(value);
    while(count(all(str), 'x') > 0){
        string left = str.substr(0, str.find('x'));
        string right = str.substr(str.find('x') + 1);
        str = left + "("+ nstr + ")" + right;
    }
    return str;
}