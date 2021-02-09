/*
* @Author CristianCin
*/

#include "function.hpp"
using namespace std;

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
        levelOfDifficult = 3;
    srand(time(NULL));
    fun = generatefunction(levelOfDifficult);
    cout<<"f(x) = " <<fun<<endl;
    cout<<"Graph: (y/n) ";
    char choice;
    cin>>choice;
    if(choice == 'y'){
        vector<double> x, y;
        for(double i = 0; i <= 15; i = i + 0.5){
            string newstr = change(fun, i);
            double num;
            num = evaluate(newstr);
            if(!isnan(num))
                x.push_back(i),y.push_back(num); 
            newstr = change(fun, -i);
            num = evaluate(newstr);
            if(!isnan(num))
                x.push_back(-i),y.push_back(num); 
        }

        for(int i = 0; i < x.size(); i= i + 2)
            cout<<"("<<x[i]<<", "<<y[i]<<") ("<<x[i+1]<<", "<<y[i+1]<<")\n";
    }
    return 0;
}
