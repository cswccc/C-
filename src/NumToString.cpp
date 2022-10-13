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

string ChangeNumToString(ll a[], int lena)
{
    string ret = "";

    int i = 0;
    while(a[i] == 0 && i <= lena) i++;

    ChangeEachNum(a[i],ret);
    for(i++; i <= lena; i++)
    {
        ll x = a[i];
        while(x * 10 < mod) ret += '0', x *= 10;

        ChangeEachNum(a[i],ret);
    }

    return ret;
}