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

void StringToNum(ll a[], ll a_dec[], int &lena, int &lena_dec, lenaEachNum a_st)
{
    int len = a_st.integer.length();
    int len_dec = a_st.decimal.length();

    lena = ceil(len/8.0);
    lena_dec = ceil(len_dec/8.0);

    int ci = 0;
    for(int i = len-1; i >= 0; i--)
    {
        if(ci == 8) lena--,ci = 0;

        a[lena] = (S[i]-'0')*pow(10,ci)+a[lena];
        ci++;
    }


    lena = ceil(len/8.0);
    lena_dec = ceil(len_dec/8.0);
}