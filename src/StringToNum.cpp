#include "StringToNum.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

const int maxn = 1000000+5;
const ll mod = 1e8;

void StringToNum(ll a_int[], ll a_dec[], int &lena_int, int &lena_dec, string input_int, string input_dec)
{
    int len = input_int.length();
    int len_dec = input_dec.length();

    lena_int = (int)ceil(len/8.0);
    lena_dec = (int)ceil(len_dec/8.0);

    int ci = 0;
    for(int i = len-1; i >= 0; i--)
    {
        if(ci == 8) lena_int--, ci = 0;

        a_int[lena_int] = (input_int[i]-'0')*pow(10,ci)+a_int[lena_int];
        
        ci++;
    }

    ci = 0;

    for(int i = len_dec-1; i >= 0; i--)
    {
        if(ci == 8) lena_dec--, ci = 0;

        a_dec[lena_dec] = (input_dec[i]-'0')*pow(10,ci)+a_dec[lena_dec];

        ci++;
    }

    lena_int = (int)ceil(len/8.0);
    lena_dec = (int)ceil(len_dec/8.0);
}