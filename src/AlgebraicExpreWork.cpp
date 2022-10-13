#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <stack>
#include <algorithm>
#include "mul.hpp"
#include "add.hpp"
#include "StringToNum.hpp"
#include "NumToString.hpp"
#include "PolynomialWork.hpp"
#include "AlgebraicExpreWork.hpp"
#define ll long long
using namespace std;

struct Vari
{
    string name;
    string value;
};

const int maxn = 1000+5;
const int maxm = 100000+5;

string input_formula, output_formula;

Vari V[maxn];
int cnt;

string FindValueOf(string name)
{
    for(int i = 1; i <= cnt; i++)
        if(name == V[i].name) return V[i].value;

    return name;
}

bool IsNotOperator(char c)
{
    return c != '*' && c != '+' && c != '-' && c != '(' && c != ')';
}

void HnadleInputFormula()
{
    int len = input_formula.length();

    string get_now = "";

    for(int i = 0; i < len; i++)
    {
        char c = input_formula[i];

        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            while(i < len && IsNotOperator(input_formula[i])) get_now += input_formula[i], i++;

            output_formula += FindValueOf(get_now);

            get_now = "";
        }
        
        if(i < len) output_formula += input_formula[i];
    }
}

void AlgebraicExpreWork(stack<string> input)
{
    input_formula = input.top(); input.pop();

    while(!input.empty())
    {
        string name = "", value = "";

        string handle_now = input.top(); input.pop();

        int len = handle_now.length();

        bool flag_equalSymbol = false;

        for(int i = 0; i < len; i++)
        {
            if(!flag_equalSymbol)
            {
                if(handle_now[i] != '=') name += handle_now[i];
                else flag_equalSymbol = true;
            }
            else
                value += handle_now[i];
        }
        Vari now;
        now.name = name; now.value = value;

        V[++cnt] = now;
    }

    HnadleInputFormula();

    PolynomialWork(output_formula);
}