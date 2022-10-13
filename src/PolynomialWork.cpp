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
#include "MathematicalWork.hpp"
#include "WrongDialog.hpp"
#define ll long long
using namespace std;

struct EachNum
{
    string integer;
    string decimal;
    bool decimal_point;
    bool symbol;
};

const int maxn = 10000000+5;

string input_Po;
string postfix_expression;
stack<EachNum> work;
int cnt_for_work;
ll a_int[maxn],b_int[maxn],c_int[maxn];
ll a_dec[maxn], b_dec[maxn], c_dec[maxn];

void PreWork()
{
    input_Po = "";
    postfix_expression = "";

    cnt_for_work = 0;
    while(!work.empty()) work.pop();
}

string PreHandleFormula(string formula)
{
    string ret = "";
    int len = formula.length();

    // cout << "len = " << len << endl;

    for(int i = 0; i < len; i++)
    {
        // cout << "formula[i] = " << formula[i] << endl;

        if(formula[i] == ' ') continue;

        if((formula[i] >= '0' && formula[i] <= '9')
            || (formula[i] == '.' || formula[i] == '+' || formula[i] == '-' || formula[i] == '*')
            || (formula[i] == '(' || (formula[i] == ')')))
        {
            ret += formula[i];
        }

        else if(formula[i] >= 'a' && formula[i] <= 'z')
        {
            string function_name = "";
            while(i < len && (formula[i] >= 'a' && formula[i] <= 'z'))
            {
                function_name += formula[i];
                i++;
            }

            int type = Function_Type(function_name);

            cout << "type = " << type << endl;

            if(type == -1) WrongDialog();

            string num1_part = "", num2_part = "";
            bool front_bra = false, back_bra = false;
            bool num1_finished = false;
            bool num1_point = false, num2_point = false;
            bool num1_minus = false, num2_minus = false;

            while(i < len)
            {
                // cout << "i = " << i << endl;
                if(formula[i] == ' ') continue;
                if(formula[i] == '(' && !front_bra) front_bra = true;
                else if(front_bra)
                {
                    if(i == len-1 && formula[i] != ')') WrongDialog();

                    if((formula[i] >= '0' && formula[i] <= '9'))
                    {
                        if(!num1_finished) num1_part += formula[i];
                        else num2_part += formula[i];
                    }
                    else if(formula[i] == '.')
                    {
                        if(!num1_finished)
                        {
                            if(!num1_point && (formula[i-1] >= '0' && formula[i-1] <= '9') && (formula[i+1] >= '0' && formula[i+1] <= '9')) num1_point = true, num1_part += formula[i];
                            else WrongDialog();
                        }
                        else
                        {
                            if(!num2_point && (formula[i-1] >= '0' && formula[i-1] <= '9') && (formula[i+1] >= '0' && formula[i+1] <= '9')) num2_point = true, num2_part += formula[i];
                            else WrongDialog();
                        }
                    }
                    else if(formula[i] == '-')
                    {
                        if(!num1_finished)
                        {
                            if(!num2_minus && (formula[i+1] >= '0' && formula[i+1] <= '9') && (formula[i-1] < '0' || formula[i-1] > '9')) num2_minus = true, num2_part += formula[i];
                            else WrongDialog();
                        }
                        else
                        {
                            if(!num2_minus && (formula[i+1] >= '0' && formula[i+1] <= '9') && (formula[i-1] < '0' || formula[i-1] > '9')) num2_minus = true, num2_part += formula[i];
                            else WrongDialog();
                        }
                    }
                    else if(formula[i] == ',')
                    {
                        if(!num1_finished) num1_finished = true;
                        else WrongDialog();
                    }
                    else if(formula[i] == ')')
                    {
                        back_bra = true;
                        break;
                    }
                    else WrongDialog();
                }
                else WrongDialog();

                i++;
            }

            if(!back_bra) WrongDialog();

            switch(type)
            {
                case 0: ret += pow(num1_part,num2_part); break;
                case 1: ret+= abs(num1_part); break;
                case 2: ret+= sqrt(num1_part); break;
            }
        }
        else WrongDialog();
    }

    cout << "ret = " << ret << endl;

    return ret;
}

void FormulaToPostfix()
{
    int len = input_Po.length();

    string now_get = "";
    string Stack = "";

    for(int i = 0; i < len; i++)
    {
        if(input_Po[i] >= '0' && input_Po [i] <= '9' || input_Po[i] == '.') now_get += input_Po[i];
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
        if(Stack[i] == '(') WrongDialog();

        postfix_expression += Stack[i];
    }
    cout << postfix_expression << endl;
}

void HandlePostfix()
{
    int len = postfix_expression.length();
    EachNum now_get;
    
    for(int i = 0; i < len; i++)
    {
        if(postfix_expression[i] <= '9' && postfix_expression[i] >= '0')
        {
            if(now_get.decimal_point) now_get.decimal += postfix_expression[i];
            else now_get.integer += postfix_expression[i];
        }
        else if(postfix_expression[i] == '.')
            now_get.decimal_point = true;
        else
        {
            if(postfix_expression[i] == ' ')
            {
                work.push(now_get); cnt_for_work++;

                now_get.decimal = "";
                now_get.integer = "";
                now_get.decimal_point = false;
            }
            else if(postfix_expression[i] == '+' || postfix_expression[i] == '-' || postfix_expression[i] == '*')
            {
                if(cnt_for_work < 2) WrongDialog();

                EachNum b_st = work.top(); work.pop();
                EachNum a_st = work.top(); work.pop();
                EachNum c_st;
                bool symbol_b = b_st.symbol, symbol_a = a_st.symbol;
                cnt_for_work -= 2;

                memset(a_int,0,sizeof(a_int)); memset(b_int,0,sizeof(b_int)); memset(c_int,0,sizeof(c_int));
                memset(a_dec,0,sizeof(a_dec)); memset(b_dec,0,sizeof(b_dec)); memset(c_dec,0,sizeof(c_dec));

                int lena_int = 0, lena_dec = 0;
                int lenb_int = 0, lenb_dec = 0;
                int lenc_int = 0, lenc_dec = 0;

                StringToNum(a_int, a_dec, lena_int, lena_dec, a_st.integer, a_st.decimal);
                StringToNum(b_int, b_dec, lenb_int, lenb_dec, b_st.integer, b_st.decimal);

                // cout << symbol_a << ' ' << a_st << endl;
                // cout << symbol_b << ' ' << b_st << endl;

                if(postfix_expression[i] == '+');
                    // add(a,b,c,lena,lenb,lenc,symbol_a,symbol_b,symbol[cnt_for_work+1]);
                else if(postfix_expression[i] == '-');
                    // add(a,b,c,lena,lenb,lenc,symbol_a,!symbol_b,symbol[cnt_for_work+1]);
                else;
                    // mul(a,b,c,lena,lenb,lenc,symbol_a,symbol_b,symbol[cnt_for_work+1]);
                
                // string c_st = ChangeNumToString(c,lenc);
                c_st.integer = ChangeIntegerPartNumToString(c_int,lenc_int);
                c_st.decimal = ChangeDecimalPartNumToString(c_dec,lenc_dec);
                // cout <<symbol[cnt_for_work+1] << ' ' << c_st << endl;

                // work.push(c_st); cnt_for_work++;
            }
        }
    }
}

void Print()
{
    // if(symbol[1]) cout << '-';
    // if(!work.empty()) cout << work.top() << endl;
    // else WrongDialog();
}

void PolynomialWork(string formula)
{
    PreWork();
    // cout << formula << endl;

    input_Po = PreHandleFormula(formula);
    
    FormulaToPostfix();

    HandlePostfix();

    Print();
}