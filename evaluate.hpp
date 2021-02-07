#include <bits/stdc++.h>
using namespace std;
 
#define PI 3.14159265

int precedence(string op){
    if(op == "+" || op == "-")
        return 1;
    if(op == "*" || op == "/")
        return 2;
    if(op == "^") 
        return 3;

    return 0;
}
 
double applyOp(double a, double b, string op){

    if(op == "+") return a + b;
    if(op == "-") return a - b;
    if(op == "*") return a * b;
    if(op == "/") return a / b;
    if(op == "^") return pow(a,b);

    return 0;
}

float cbl(float base, float arg){
    return (float)log10(arg)/(float)log10(base);
}

double applyOpF(double a, string op){

    if(op == "sin") return sin(a*(PI/180));
    if(op == "cos") return cos(a*(PI/180));
    if(op == "tan") return tan(a*(PI/180));
    if(op == "cotan") return 1/tan(a*(PI/180));
    if(op == "arcsin") return asin(a);
    if(op == "arccos") return acos(a);
    if(op == "arctan") return atan(a);
    if(op == "arccotan") return PI/2 - atan(a);
    if(op == "sqrt") return sqrt(a);
    if(op == "log_2") return log2(a);
    if(op == "ln") return log(a);
    if(op == "log_3") return cbl(3,a);
    if(op == "log_4") return cbl(4,a);
    if(op == "log_5") return cbl(5,a);
    if(op == "log_6") return cbl(6,a);
    if(op == "log_7") return cbl(7,a);
    if(op == "log_8") return cbl(8,a);
    if(op == "log_9") return cbl(9,a);
    if(op == "log") return log10(a);

    return 0;
}

bool isOperand(char ch){
    switch(ch){
        case '+': return true;
        case '-': return true;
        case '*': return true;
        case '/': return true;
        case '^': return true;
    }

    return false;
}

bool isF(string op){

    if(op == "sin") return true;
    if(op == "cos") return true;
    if(op == "tan") return true;
    if(op == "cotan") return true;
    if(op == "arcsin") return true;
    if(op == "arccos") return true;
    if(op == "arctan") return true;
    if(op == "arccotan") return true;
    if(op == "sqrt") return true;
    if(op == "log_2") return true;
    if(op == "ln") return true;
    if(op == "log_3") return true;
    if(op == "log_4") return true;
    if(op == "log_5") return true;
    if(op == "log_6") return true;
    if(op == "log_7") return true;
    if(op == "log_8") return true;
    if(op == "log_9") return true;
    if(op == "log") return true;

    return false;
}

vector<string> tokenization(string token){
    string tmp = "";
    vector<string> ret;
    
    for(auto x : token){
        if(x != ' ')  
            if(isOperand(x) || x == '(' || x == ')' ){
                    ret.push_back(tmp);
                    tmp = x;
                    ret.push_back(tmp);
                    tmp = "";
            }
            else
                tmp += x;
        else
            continue;
    }

    if(tmp.size() > 0)
        ret.push_back(tmp);

    vector<string> retret;
    for(auto x : ret)
        if(x != "")
            retret.push_back(x);

    return retret;
}

bool is_number(string s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
 
void update(stack<double> &values, stack<string> &_operators){
    double value1, value2;
    string _operator;

    value2 = values.top(); //Prendo il valore in cima allo stack (Primo numero)
    values.pop(); // Lo rimuovo
    
    value1 = values.top(); //Prendo il valore in cima allo stack (Secondo numero)
    values.pop(); //Lo rimuovo
    
    _operator = _operators.top(); //Prendo l'operatore in cima allo stack
    _operators.pop(); //Lo rimuovo
    
    values.push(applyOp(value1, value2, _operator));
}

void updateFunction(stack<double> &values, stack<string> &_operators){
    double value;
    string _operator;

    value = values.top(); //Prendo il valore in cima allo stack (Numero interno alla funzione)
    values.pop(); // Lo rimuovo
    
    _operator = _operators.top(); //Prendo l'operatore in cima allo stack
    _operators.pop(); //Lo rimuovo
    
    values.push(applyOpF(value, _operator));
}

double evaluate(string tokens){
    vector<string> tk = tokenization(tokens);
    double value;
    char _operator;
    stack <double> values;
     
    stack <string> ops;
    char x;
    for(int i = 0; i < tk.size(); i++){

        if(tk[i] == "(")
            ops.push(tk[i]);
        else 
            if(is_number(tk[i])){
                int val = stoi(tk[i]);
                values.push(val);
            }
            else 
                if(tk[i] == ")")
                {
                    while(!ops.empty() && ops.top() != "("){
                        if(isF(ops.top()))
                            updateFunction(values, ops);
                        else
                            if(precedence(ops.top())>= precedence(tk[i]))
                                update(values, ops);
                    }

                    if(!ops.empty())
                        ops.pop();
                }
                else
                {
                    while(!ops.empty() && ops.top() != "("){
                        if(isF(ops.top()))
                            updateFunction(values, ops);
                        else{
                            if(precedence(ops.top())>= precedence(tk[i]))
                                update(values, ops);
                        }

                    }
                
                    ops.push(tk[i]);
                }
        }

        while(!ops.empty())
            if(isF(ops.top()))
                updateFunction(values, ops);
            else
                update(values, ops);
     
    return values.top();
}