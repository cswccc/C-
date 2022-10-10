#include "add.hpp"
#include <cmath>
#define ll long long
using namespace std;

const ll mod = 1e8;

void add(ll a[], ll b[], ll ans[], int lena, int lenb, int &len_ans)
{
    len_ans = max(lena,lenb);

    for(int i = len_ans; i >= 1; i--)
    {
        if(i <= lena) ans[i] += a[i];
        if(i <= lenb) ans[i] += b[i];

        if(ans[i] >= mod)
        {
            ans[i-1] += ans[i]/mod;
            ans[i] %= mod;
        }
    }
}