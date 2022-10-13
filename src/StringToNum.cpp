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

void StringToNum(ll a[], int len, int lena, string S)
{
    int ci = 0;
    for(int i = len-1; i >= 0; i--)
    {
        if(ci == 8) lena--,ci = 0;

        a[lena] = (S[i]-'0')*pow(10,ci)+a[lena];
        ci++;
    }
}