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

string pow(string input, string power)
{
    string ans = "";

    // cout << input << ' ' << power << endl;

    return ans;
}

string abs(string input)
{
    string ans = "";

    // cout << input << endl;

    int len = input.length();

    for(int i = 0; i < len; i++)
    {
        if(input[i] == '-') continue;
        ans += input[i];
    }

    return ans;
}

string sqrt(string input)
{
    string ans = "";

    // cout << input << endl;

    return ans;
}

int Function_Type(string name)
{
    if(name == "pow") return 0;
    if(name == "abs") return 1;
    if(name == "sqrt") return 2;

    return -1;
}