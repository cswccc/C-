#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "mul.hpp"
#include "add.hpp"
#include "StringToNum.hpp"
#include "NumToString.hpp"
#include "WrongDialog.hpp"
using namespace std;

const int maxn = 1000000+5;

string input_Ma;
ll c_int_M[maxn],c_dec_M[maxn];
ll x_int_M[maxn],x_dec_M[maxn];
ll ans_int_M[maxn],ans_dec_M[maxn];

int lenc_int_M;
int lenc_dec_M;
int lenx_int_M,lenx_dec_M;
int len_ans_int_M,len_ans_dec_M;

string pow(string input, string power)
{
    bool flag_decimal = false;
    string integer = "", decimal = "";

    for(int i = 0; i < input.length(); i++)
    {
        if(!flag_decimal)
        {
            if(input[i] == '.') flag_decimal = true;
            else integer += input[i];
        }
        else decimal += input[i];
    }

    StringToNum(x_int_M, x_dec_M, lenx_int_M, lenx_dec_M, integer, decimal);
    
    ll p = 0;
    for(int i = 0; i < power.length(); i++) p = p*10 + power[i]-'0';

    ans_int_M[1] = 1; len_ans_int_M = 1;
    bool none = false;

    while(p)
    {
        //a b c are used to multiply
        if(p & 1)
        {

            memset(c_int_M,0,sizeof(c_int_M)); memset(c_dec_M,0,sizeof(c_dec_M));
            mul(ans_int_M, x_int_M, c_int_M, ans_dec_M, x_dec_M, c_dec_M, len_ans_int_M, lenx_int_M, lenc_int_M, len_ans_dec_M, lenx_dec_M, lenc_dec_M, true, true, none);

            memcpy(ans_int_M,c_int_M,sizeof(c_int_M)); memcpy(ans_dec_M,c_dec_M,sizeof(c_dec_M));
            len_ans_dec_M = lenc_dec_M; len_ans_int_M = lenc_int_M;

            //these steps stands for ans = ans*x
        }

        memset(c_int_M,0,sizeof(c_int_M)); memset(c_dec_M,0,sizeof(c_dec_M));
        mul(x_int_M, x_int_M, c_int_M, x_dec_M, x_dec_M, c_dec_M, lenx_int_M, lenx_int_M, lenc_int_M, lenx_dec_M, lenx_dec_M, lenc_dec_M, true, true, none);
        memcpy(x_int_M,c_int_M,sizeof(c_int_M)); memcpy(x_dec_M,c_dec_M,sizeof(c_dec_M));
        lenx_dec_M = lenc_dec_M; lenx_int_M = lenc_int_M;

        //these steps stands for x = x*x

        p >>= 1;
    }

    string ans = ChangePartNumToString(ans_int_M,len_ans_int_M,false);

    string dec_part = ChangePartNumToString(ans_dec_M,len_ans_dec_M,true);

    if(dec_part != "")
    {
        ans += '.';
        ans += dec_part;
    }

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

int Function_Type(string name)
{
    if(name == "pow") return 0;
    if(name == "abs") return 1;

    return -1;
}