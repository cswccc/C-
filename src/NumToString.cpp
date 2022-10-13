#include <string>
#include "NumToString.hpp"
#define ll long long
using namespace std;

const ll mod = 10;


string ChangePartNumToString(ll a[], int len, bool isDecimal)
{
    string ret = "";
    int i;

    if(isDecimal)
    {
        i = 1;
        while(a[len] == 0) len--;
    }
        
    else
    {
        i = 0;
        while(a[i] == 0 && i <= len) i++;  
    }
        

    for(; i <= len; i++) ret += (char)(a[i] + '0');

    return ret;
}