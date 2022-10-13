#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "mul.hpp"
#include "add.hpp"
#include "StringToNum.hpp"
#include "WrongDialog.hpp"
using namespace std;

string input_Ma;

void pow(string input, string power)
{

}

void abs(string input)
{

}

void sqrt(string input)
{

}

int Check(string input)
{
    int len = input.length();

    string function_name = "";
    for(int i = 0; i < len; i++)
    {
        if(input[i] == ' ') continue;
        else if(input[i] >= 'a' && input[i] <= 'z') function_name += input[i];
        else break;
    }

    if(function_name == "pow") return 1;
    if(function_name == "abs") return 2;
    if(function_name == "sqrt") return 3;

    return 0;
}

void PreForPow(string input)
{
    bool flag_Pow = false;

    int len = input.length();

    for(int i = 0; i < len; i++)
    {
        if(input[i] == '(') flag_Pow = true;
        if(!flag_Pow) continue;
    }
}

void PreForAbs(string input)
{
    bool flag_Abs = false;

    int len = input.length();

    for(int i = 0; i < len; i++)
    {
        if(input[i] == '(') flag_Abs = true;
        if(!flag_Abs) continue;
    }
}

void PreForSqrt(string input)
{
    bool flag_Sqrt = false;

    int len = input.length();

    for(int i = 0; i < len; i++)
    {
        if(input[i] == '(') flag_Sqrt = true;
        if(!flag_Sqrt) continue;
    }
}

void MathematicalWork()
{
    getline(cin,input_Ma);
    printf("Please input the mathematical function you want to solve:");
    getline(cin,input_Ma);

    switch(Check(input_Ma))
    {
        case 1: PreForPow(input_Ma); break;
        case 2: PreForAbs(input_Ma); break;
        case 3: PreForSqrt(input_Ma); break;
        default: WrongDialog(); break;
    }
}