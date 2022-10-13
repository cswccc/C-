#include "StringToNum.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

const int maxn = 1000000+5;
const ll mod = 10;

void StringToNum(ll a_int[], ll a_dec[], int &lena_int, int &lena_dec, string input_int, string input_dec)
{
    int len = input_int.length();
    int len_dec = input_dec.length();

    lena_int = len;
    lena_dec = len_dec;

    for(int i = 0; i < len; i++)
        a_int[i+1] = input_int[i]-'0';

    for(int i = 0 ; i < len_dec; i++)
        a_dec[i+1] = input_dec[i]-'0';
}