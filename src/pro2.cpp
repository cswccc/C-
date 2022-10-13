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
int cnt_for_input;

void Input()
{
    string input_now = "";

    while(true)
    {
        input_now = "";

        getline(cin,input_now);
        
        if(input_now == "") break;

        input_Main.push(input_now); cnt_for_input++;
    }
}

int CaseFor_P_Or_A(stack<string> input)
{
    if(cnt_for_input == 1) return 1;
    else return 2;
}

void Dialog()
{
    int x = CaseFor_P_Or_A(input_Main);
    switch(x)
    {
        case 1: PolynomialWork(input_Main.top()); break;
        // case 2: AlgebraicExpreWork(input_Main); break;
        default: break;
    }
}

int main()
{
    Input();
    Dialog();

    return 0;
}