#include <iostream>
#include "add.hpp"
#include <cmath>
#define ll long long
using namespace std;

const ll mod = 10;

int ComForInt(ll a[], ll b[], int lena, int lenb)
{
    if(lena > lenb) return 1;
    if(lena < lenb) return -1;

    for(int i = 0; i <= lena; i++)
        if(a[i] > b[i]) return 1;
        else if(a[i] < b[i]) return -1;
    
    return 0;
}

int ComForDec(ll a[], ll b[], int len)
{
    for(int i = 1; i <= len; i++)
        if(a[i] > b[i]) return 1;
        else if(a[i] < b[i]) return -1;
    
    return 0;
}

void AddForInt(ll a[], ll b[], ll ans[], int lena, int lenb, int &len_ans, bool sya, bool syb, bool &sy_ans)
{
    if(sya == syb)
    {
        len_ans = max(lena,lenb);

        for(int i = 1; i <= len_ans; i++)
        {
            if(i <= lena) ans[len_ans-i+1] += a[lena-i+1];
            if(i <= lenb) ans[len_ans-i+1] += b[lenb-i+1];

            if(ans[len_ans-i+1] >= mod)
            {
                ans[len_ans-i] += ans[len_ans-i+1]/mod;
                ans[len_ans-i+1] %= mod;
            }
        }
        sy_ans = sya;
    }
    
    else
    {
        int x = ComForInt(a,b,lena,lenb);
        if(x == 1)
        {
            len_ans = lena;

            for(int i = 1; i <= len_ans; i++)
            {
                if(i <= lena) ans[len_ans-i+1] += a[lena-i+1];
                if(i <= lenb) ans[len_ans-i+1] -= b[lenb-i+1];

                if(ans[len_ans-i+1] >= mod)
                {
                    ans[len_ans-i] += ans[len_ans-i+1]/mod; ans[len_ans-i+1] %= mod;
                }
                else if(ans[len_ans-i+1] < 0)
                {
                    ans[len_ans-i] -= 1; ans[len_ans-i+1] += mod;
                }
            }
            sy_ans = sya;
        }
        else if(x == -1)
        {
            len_ans = lenb;

            for(int i = 1; i <= len_ans; i++)
            {
                if(i <= lena) ans[len_ans-i+1] -= a[lena-i+1];
                if(i <= lenb) ans[len_ans-i+1] += b[lenb-i+1];

                if(ans[len_ans-i+1] >= mod)
                {
                    ans[len_ans-i] += ans[len_ans-i+1]/mod; ans[len_ans-i+1] %= mod;
                }
                else if(ans[len_ans-i+1] < 0)
                {
                    ans[len_ans-i] -= 1; ans[len_ans-i+1] += mod;
                }
            }
            sy_ans = syb;
        }
        else
        {
            len_ans = 1; sy_ans = false;
        }
    }

    for(int i = len_ans; i >= 1; i--)
    {
        if(ans[i] >= mod)
        {
            ans[i-1] += 1;
            ans[i] %= mod;
        }
        else if(ans[i] < 0)
        {
            ans[i-1] -= 1;
            ans[i] += mod;
        }
    }

    if(ans[0] < 0) sy_ans = true, ans[0] = abs(ans[0]);
}

void AddForDec(ll a[], ll b[], ll ans[], int lena, int lenb, int &len_ans, bool sya, bool syb, bool &sy_ans)
{
    len_ans = max(lena,lenb);

    if(sya == syb)
    {
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
        sy_ans = sya;
    }
    
    else
    {
        int x = ComForDec(a,b,max(lena,lenb));
        if(x != 0)
        {
            a[1] += 10;
            ans[0] -= 1;
            for(int i = len_ans; i >= 1; i--)
            {
                if(i <= lena) ans[i] += a[i];
                if(i <= lenb) ans[i] -= b[i];

                if(ans[i] >= mod)
                {
                    ans[i-1] += ans[i]/mod;
                    ans[i] %= mod;
                }
                else if(ans[i] < 0)
                {
                    ans[i-1] -= 1;
                    ans[i] += mod;
                }
            }
            sy_ans = sya;
        }
        else
        {
            len_ans = 1; sy_ans = false;
        }
    }

    for(int i = len_ans; i >= 1; i--)
    {
        if(ans[i] >= mod)
        {
            ans[i-1] += 1;
            ans[i] %= mod;
        }
        else if(ans[i] < 0)
        {
            ans[i-1] -= 1;
            ans[i] += mod;
        }
    }
}