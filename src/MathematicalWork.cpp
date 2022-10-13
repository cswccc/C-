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

string pow(string input, string power)
{
    ll a_int[maxn],b_int[maxn],c_int[maxn];
    ll a_dec[maxn],b_dec[maxn],c_dec[maxn];
    ll x_int[maxn],x_dec[maxn];
    ll ans_int[maxn],ans_dec[maxn];

    int lena_int,lenb_int,lenc_int;
    int lena_dec,lenb_dec,lenc_dec;
    int lenx_int,lenx_dec;
    int len_ans_int,len_ans_dec;

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

    StringToNum(x_int, x_dec, lenx_int, lenx_dec, integer, decimal);
    
    ll p = 0;
    for(int i = 0; i < power.length(); i++) p = p*10 + power[i]-'0';

    ans_int[1] = 1; len_ans_int = 1;
    bool none = false;

    while(p)
    {
        if(p & 1)
        {
            memcpy(a_int,ans_int,sizeof(ans_int)); memcpy(a_dec,ans_dec,sizeof(ans_dec));
            memcpy(b_int,x_int,sizeof(x_int)); memcpy(b_dec,x_dec,sizeof(x_dec));
            lena_int = len_ans_int; lena_dec = len_ans_dec;
            lenb_int = lenx_int; lenb_dec = lenx_dec;

            memset(c_int,0,sizeof(c_int)); memset(c_dec,0,sizeof(c_dec));
            mul(a_int, b_int, c_int, a_dec, b_dec, c_dec, lena_int, lenb_int, lenc_int, lena_dec, lenb_dec, lenc_dec, true, true, none);

            memcpy(ans_int,c_int,sizeof(c_int)); memcpy(ans_dec,c_dec,sizeof(c_dec));
            len_ans_dec = lenc_dec; len_ans_int = lenc_int;
        }

        memset(c_int,0,sizeof(c_int)); memset(c_dec,0,sizeof(c_dec));
        mul(b_int, b_int, c_int, b_dec, b_dec, c_dec, lenb_int, lenb_int, lenc_int, lenb_dec, lenb_dec, lenc_dec, true, true, none);
        memcpy(x_int,c_int,sizeof(c_int)); memcpy(x_dec,c_dec,sizeof(c_dec));
        lenx_dec = lenc_dec; lenx_int = lenc_int;

        p >>= 1;
    }

    string ans = ChangePartNumToString(ans_int,len_ans_int,false)+ChangePartNumToString(ans_int,len_ans_dec,true);

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