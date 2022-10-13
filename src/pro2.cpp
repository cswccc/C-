#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <cstring>
#include <algorithm>
#include "mul.hpp"
#include "add.hpp"
#include "StringToNum.hpp"
#include "PolynomialWork.hpp"
#include "MathematicalWork.hpp"
#include "AlgebraicExpreWork.hpp"
#define ll long long
using namespace std;

stack<string> input_Main;

void Input()
{
    string input_now = "";

    while(true)
    {
        input_now = "";

        getline(cin,input_now);
        
        if(input_now == "") break;
    }
}

void Dialog()
{
    
    // switch(x)
    // {
    //     case 0: exit(0); break;
    //     case 1: PolynomialWork(); break;
    //     case 2: MathematicalWork(); break;
    //     case 3: AlgebraicExpreWork(); break;
    //     default: break;
    // }
}

int main()
{
    Input();
    Dialog();

    return 0;
}