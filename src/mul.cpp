#include "mul.hpp"
#include <cstring>
#include <string>
#include <iostream>
#define ll long long
using namespace std;

const int maxn = 1000000+5;

const ll mod = 10;

ll a[maxn],b[maxn],c[maxn];

void mul(ll a_int[], ll b_int[], ll ans_int[], ll a_dec[], ll b_dec[], ll ans_dec[], int lena_int, int lenb_int, int &len_ans_int, int lena_dec, int lenb_dec, int &len_ans_dec, bool symbol1, bool symbol2, bool &sy_ans)
{
    memset(c,0,sizeof(c));

    if(symbol1 == symbol2) sy_ans = false;
    else sy_ans = true;
    
    for(int i = 0; i <= lena_int; i++) a[i] = a_int[i];
    for(int j = 1; j <= lena_dec; j++) a[j+lena_int] = a_dec[j];

    for(int i = 0; i <= lenb_int; i++) b[i] = b_int[i];
    for(int j = 1; j <= lenb_dec; j++) b[j+lenb_int] = b_dec[j];

    // for(int i = 1; i <= lena_int+lena_dec; i++) cout << a[i] << ' ';
    // puts("");
    // for(int i = 1; i <= lenb_int+lenb_dec; i++) cout << b[i] << ' ';
    // puts("");

    for(int i = lena_int+lena_dec; i >= 1; i--)
    for(int j = lenb_int+lenb_dec; j >= 1; j--)
    {
        c[i+j] += a[i]*b[j];

        c[i+j-1] += c[i+j]/mod;
        c[i+j] %= mod;
    }

    for(int i = 1; i <= lenb_dec+lena_dec; i++) ans_dec[i] = c[lena_int + lenb_int + i];

    for(int i = 0; i <= lena_int+lenb_int; i++) ans_int[i] = c[i];

    len_ans_int = lena_int+lenb_int; len_ans_dec = lena_dec+lenb_dec;
}