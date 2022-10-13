#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "mul.hpp"
#include "add.hpp"
#include "Get_Num.hpp"
#include "numToString.hpp"
#include "Polynomial_work.hpp"
#define ll long long
using namespace std;

string input;
string postfix_expression;

void GetInput()
{
    getline(cin,input);
    printf("Please input the polynomial you want to solve:");
    getline(cin,input);

    // cout << input << endl;
}

string Stack;

void HandleFormula()
{
    int len = input.length();

    string now_get = "";
    for(int i = 0; i < len; i++)
    {
        if(input[i] >= '0' && input [i] <= '9') now_get += input[i];
        else
        {
            if(now_get != "")
            {
                postfix_expression += now_get;
                now_get = "";
            }

            if(input[i] == ' ') continue;
            else if(input[i] == '+' || input[i] == '-')
            {
                int len_Sta = Stack.length();
                while(len_Sta != 0 && Stack[len_Sta-1] != '(')
                {
                    postfix_expression += Stack[len_Sta-1];
                    Stack.pop_back();
                    len_Sta--;
                }
                Stack += input[i];
            }
            else if(input[i] == '*')
            {
                int len_Sta = Stack.length();
                while(len_Sta != 0 && Stack[len_Sta-1] != '(' && Stack[len_Sta-1] != '-' && Stack[len_Sta-1] != '+')
                {
                    postfix_expression += Stack[len_Sta-1];
                    Stack.pop_back();
                    len_Sta--;
                }
                Stack += input[i];
            }
        }
    }
}

void PolynomialWork()
{
    GetInput();

    HandleFormula();
}