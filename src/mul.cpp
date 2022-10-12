#include "mul.hpp"
#define ll long long

const ll mod = 1e8;

void mul(ll a[],ll b[], ll ans[],int lena, int lenb, int &len_ans, bool symbol1, bool symbol2, bool &sy_ans)
{
    if(symbol1 == symbol2) sy_ans = false;
    else sy_ans = true;
    
    len_ans = lena + lenb;

    for(int i = lena; i >= 1; i--)
    for(int j = lenb; j >= 1; j--) {
        ans[i+j] += a[i]*b[j];
        
        if(ans[i+j] >= mod)
        {
            ans[i+j-1] += ans[i+j]/mod;
            ans[i+j] %= mod;
        }
    }

    for(int i = len_ans; i >= 1; i--) ans[i-1] += ans[i]/mod,ans[i] %= mod;
}