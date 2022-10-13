#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <stack>
#include "mul.hpp"
#include "add.hpp"
#include "Get_Num.hpp"
#include "numToString.hpp"
#include "Polynomial_work.hpp"
#include "WrongDialog.hpp"
#define ll long long
using namespace std;

const int maxn = 100000+5;

string input;
string postfix_expression;
stack<string> work;
bool symbol[maxn];

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
                postfix_expression += ' ';
                now_get = "";
            }

            if(input[i] == ' ') continue;
            else if(input[i] == '(') Stack += '(';
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
            else if(input[i] == ')')
            {
                int len_Sta = Stack.length();
                while(len_Sta != 0 && Stack[len_Sta-1] != '(')
                {
                    postfix_expression += Stack[len_Sta-1];
                    Stack.pop_back();
                    len_Sta--;
                }
                if(len_Sta == 0) WrongDialog();
                else Stack.pop_back();
            }
        }
    }

    if(now_get != "")
    {
        postfix_expression += now_get;
        now_get = "";
    }
    
    for(int i = Stack.length(); i >= 0; i--) postfix_expression += Stack[i];

    // cout << postfix_expression << endl;
}

void HandlePostfix()
{
    int len = postfix_expression.length();
    string now_get = "";
    
    for(int i = 0; i < len; i++)
    {
        if(postfix_expression[i] <= '9' && postfix_expression >= '0')
            now_get += postfix_expression[i];
        else
        {
            if(postfix_expression[i] == '+') 
        }
    }
}

void PolynomialWork()
{
    GetInput();

    HandleFormula();

    HandlePostfix();
}