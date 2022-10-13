#include <string>
#include "NumToString.hpp"
#define ll long long
using namespace std;

const ll mod = 1e8;

void ChangeEachNum(ll x, string &ret)
{
    if(x >= 10) ChangeEachNum(x/10,ret);

    ret += char(x%10 + '0');
}

string ChangeIntegerPartNumToString(ll a[], int len)
{
    string ret = "";

    int i = 0;
    while(a[i] == 0 && i <= len) i++;

    if(i <= len) ChangeEachNum(a[i],ret);
    for(i++; i <= len; i++)
    {
        ll x = a[i];
        while(x * 10 < mod) ret += '0', x *= 10;

        ChangeEachNum(a[i],ret);
    }

    return ret;
}

string ChangeDecimalPartNumToString(ll a[], int len)
{
    string ret = "";

    int i = 0;
    while(a[i] == 0 && i <= len) i++;
    while(len >= 0 && a[len] == 0) len--;

    if(i <= len) ChangeEachNum(a[i],ret);
    for(i++; i <= len; i++)
    {
        ll x = a[i];
        while(x * 10 < mod) ret += '0', x *= 10;

        if(i == len)
        {
            
        }
        ChangeEachNum(a[i],ret);
    }

    return ret;
}