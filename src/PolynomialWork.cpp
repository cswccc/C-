#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <stack>
#include "mul.hpp"
#include "add.hpp"
#include "StringToNum.hpp"
#include "NumToString.hpp"
#include "PolynomialWork.hpp"
#include "WrongDialog.hpp"
#define ll long long
using namespace std;

const int maxn = 10000000+5;

string input_Po;
string postfix_expression;
stack<string> work;
int cnt_for_work;
bool symbol[maxn];
ll a[maxn],b[maxn],c[maxn];

void PreWork()
{
    memset(a,0,sizeof(a)); memset(b,0,sizeof(b)); memset(c,0,sizeof(c));
    memset(symbol,false,sizeof(symbol));
    
    input_Po = "";
    postfix_expression = "";

    cnt_for_work = 0;
    while(!work.empty()) work.pop();
}

void GetInput()
{
    getline(cin,input_Po);
    printf("Please input the polynomial you want to solve:");
    getline(cin,input_Po);

    // cout << input_Po << endl;
}

void HandleFormula()
{
    int len = input_Po.length();

    string now_get = "";
    string Stack = "";

    for(int i = 0; i < len; i++)
    {
        if(input_Po[i] >= '0' && input_Po [i] <= '9') now_get += input_Po[i];
        else
        {
            if(now_get != "")
            {
                postfix_expression += now_get;
                postfix_expression += ' ';
                now_get = "";
            }

            if(input_Po[i] == ' ') continue;
            else if(input_Po[i] == '(') Stack += '(';
            else if(input_Po[i] == '+' || input_Po[i] == '-')
            {
                int len_Sta = Stack.length();
                while(len_Sta != 0 && Stack[len_Sta-1] != '(')
                {
                    postfix_expression += Stack[len_Sta-1];
                    Stack.pop_back();
                    len_Sta--;
                }
                Stack += input_Po[i];
            }
            else if(input_Po[i] == '*')
            {
                int len_Sta = Stack.length();
                while(len_Sta != 0 && Stack[len_Sta-1] != '(' && Stack[len_Sta-1] != '-' && Stack[len_Sta-1] != '+')
                {
                    postfix_expression += Stack[len_Sta-1];
                    Stack.pop_back();
                    len_Sta--;
                }
                Stack += input_Po[i];
            }
            else if(input_Po[i] == ')')
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
        postfix_expression += ' ';
        now_get = "";
    }
    
    for(int i = Stack.length(); i >= 0; i--) 
    {
        if(Stack[i] == '(') WrongDialog;

        postfix_expression += Stack[i];
    }
    // cout << postfix_expression << endl;
}

void HandlePostfix()
{
    int len = postfix_expression.length();
    string now_get = "";
    
    for(int i = 0; i < len; i++)
    {
        if(postfix_expression[i] <= '9' && postfix_expression[i] >= '0')
            now_get += postfix_expression[i];
        else
        {
            if(postfix_expression[i] == ' ')
            {
                work.push(now_get); cnt_for_work++;
                now_get = "";
            }
            else if(postfix_expression[i] == '+' || postfix_expression[i] == '-' || postfix_expression[i] == '*')
            {
                if(cnt_for_work < 2) WrongDialog();

                string b_st = work.top(); work.pop();
                string a_st = work.top(); work.pop();
                bool symbol_b = symbol[cnt_for_work], symbol_a = symbol[cnt_for_work-1];
                symbol[cnt_for_work] = false; symbol[cnt_for_work-1] = false;
                cnt_for_work -= 2;

                memset(a,0,sizeof(a)); memset(b,0,sizeof(b)); memset(c,0,sizeof(c));
                int len1 = a_st.length(), len2 = b_st.length();
                int lena = ceil(len1/8.0), lenb = ceil(len2/8.0);
                int lenc = 0;

                StringToNum(a,len1,lena,a_st);
                StringToNum(b,len2,lenb,b_st);

                // cout << symbol_a << ' ' << a_st << endl;
                // cout << symbol_b << ' ' << b_st << endl;

                if(postfix_expression[i] == '+')
                    add(a,b,c,lena,lenb,lenc,symbol_a,symbol_b,symbol[cnt_for_work+1]);
                else if(postfix_expression[i] == '-')
                    add(a,b,c,lena,lenb,lenc,symbol_a,!symbol_b,symbol[cnt_for_work+1]);
                else
                    mul(a,b,c,lena,lenb,lenc,symbol_a,symbol_b,symbol[cnt_for_work+1]);
                
                string c_st = ChangeNumToString(c,lenc);
                // cout <<symbol[cnt_for_work+1] << ' ' << c_st << endl;

                work.push(c_st); cnt_for_work++;
            }
        }
    }
}

void Print()
{
    if(symbol[1]) cout << '-';
    cout << work.top() << endl;
}

void PolynomialWork()
{
    PreWork();

    GetInput();

    HandleFormula();

    HandlePostfix();

    Print();
}

void InputFormula(string formula)
{
    PreWork();

    input_Po = formula;

    HandleFormula();

    HandlePostfix();

    Print();
}