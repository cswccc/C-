#include <string>
#include "NumToString.hpp"
#define ll long long
using namespace std;

const ll mod = 10;


string ChangePartNumToString(ll a[], int len, bool isDecimal)
{
    string ret = "";
    int i;

    if(isDecimal)//decimal part doesn't need the 0s at the end
    {
        i = 1;
        while(a[len] == 0) len--;
    }
        
    else//integer part doesn't need the os at the beginning
    {
        i = 0;
        while(a[i] == 0 && i <= len) i++;  
    }
        

    for(; i <= len; i++) ret += (char)(a[i] + '0');

    return ret;
}