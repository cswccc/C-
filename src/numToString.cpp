#include <string>
#include "numToString.hpp"
#define ll long long
using namespace std;

const ll mod = 1e8;

void Change_Each_Num(ll x, string &ret)
{
    if(x >= 10) Change_Each_Num(x/10,ret);

    ret += char(x%10 + '0');
}

string Change_Num_To_String(ll a[], int lena)
{
    string ret = "";

    int i = 0;
    while(a[i] == 0 && i <= lena) i++;

    Change_Each_Num(a[i],ret);
    for(i++; i <= lena; i++)
    {
        ll x = a[i];
        while(x * 10 < mod) ret += '0', x *= 10;

        Change_Each_Num(a[i],ret);
    }

    return ret;
}