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

void add(ll a_int[], ll b_int[], ll ans_int[], ll a_dec[], ll b_dec[], ll ans_dec[], int lena_int, int lenb_int, int &len_ans_int, int lena_dec, int lenb_dec, int &len_ans_dec, bool sya, bool syb, bool &sy_ans)
{
    len_ans_dec = max(lena_dec,lenb_dec);
    len_ans_int = max(lena_int,lenb_int);

    if(sya == syb)//a & b have the same symbol, they add each other and the final symbol is the same with a & b
    {
        sy_ans = sya;

        for(int i = len_ans_dec; i >= 1; i--)//decimal part
        {
            if(i <= lena_dec) ans_dec[i] += a_dec[i];
            if(i <= lenb_dec) ans_dec[i] += b_dec[i];

            if(ans_dec[i] >= mod)
            {
                ans_dec[i-1] += ans_dec[i]/mod;
                ans_dec[i] %= mod;
            }
        }

        ans_int[len_ans_int] += ans_dec[0];

        for(int i = 1; i <= len_ans_int; i++)//integer part
        {
            if(i <= lena_int) ans_int[len_ans_int-i+1] += a_int[lena_int-i+1];
            if(i <= lenb_int) ans_int[len_ans_int-i+1] += b_int[lenb_int-i+1];

            if(ans_int[len_ans_int-i+1] >= mod)
            {
                ans_int[len_ans_int-i] += ans_int[len_ans_int-i+1]/mod;
                ans_int[len_ans_int-i+1] %= mod;
            }
        }
    }
    
    else//for different symbol
    {
        int x = ComForInt(a_int,b_int,lena_int,lenb_int);

        if(x == 1)
        {
            sy_ans = sya;

            for(int i = len_ans_dec; i >= 1; i--)//decimal part
            {
                if(i <= lena_dec) ans_dec[i] += a_dec[i];
                if(i <= lenb_dec) ans_dec[i] -= b_dec[i];

                if(ans_dec[i] >= mod)
                {
                    ans_dec[i-1] += ans_dec[i]/mod;
                    ans_dec[i] %= mod;
                }
                if(ans_dec[i] < 0)
                {
                    ans_dec[i-1] -= 1;
                    ans_dec[i] += 10;
                }
            }

            ans_int[len_ans_int] += ans_dec[0];

            for(int i = 1; i <= len_ans_int; i++)// integer part
            {
                if(i <= lena_int) ans_int[len_ans_int-i+1] += a_int[lena_int-i+1];
                if(i <= lenb_int) ans_int[len_ans_int-i+1] -= b_int[lenb_int-i+1];

                if(ans_int[len_ans_int-i+1] >= mod)
                {
                    ans_int[len_ans_int-i] += ans_int[len_ans_int-i+1]/mod;
                    ans_int[len_ans_int-i+1] %= mod;
                }
                else if(ans_int[len_ans_int-i+1] < 0)
                {
                    ans_int[len_ans_int-i] -= 1;
                    ans_int[len_ans_int-i+1] += mod;
                }
            }
        }

        else if(x == -1)
        {
            sy_ans = syb;

            for(int i = len_ans_dec; i >= 1; i--)
            {
                if(i <= lena_dec) ans_dec[i] -= a_dec[i];
                if(i <= lenb_dec) ans_dec[i] += b_dec[i];

                if(ans_dec[i] >= mod)
                {
                    ans_dec[i-1] += ans_dec[i]/mod;
                    ans_dec[i] %= mod;
                }
                if(ans_dec[i] < 0)
                {
                    ans_dec[i-1] -= 1;
                    ans_dec[i] += 10;
                }
            }

            ans_int[len_ans_int] += ans_dec[0];

            for(int i = 1; i <= len_ans_int; i++)
            {
                if(i <= lena_int) ans_int[len_ans_int-i+1] -= a_int[lena_int-i+1];
                if(i <= lenb_int) ans_int[len_ans_int-i+1] += b_int[lenb_int-i+1];

                if(ans_int[len_ans_int-i+1] >= mod)
                {
                    ans_int[len_ans_int-i] += ans_int[len_ans_int-i+1]/mod;
                    ans_int[len_ans_int-i+1] %= mod;
                }
                else if(ans_int[len_ans_int-i+1] < 0)
                {
                    ans_int[len_ans_int-i] -= 1;
                    ans_int[len_ans_int-i+1] += mod;
                }
            }
        }
        else
        {
            len_ans_int = 1;
            int y = ComForDec(a_dec,b_dec,len_ans_dec);

            if(y == 1)
            {
                sy_ans = sya;

                for(int i = len_ans_dec; i >= 1; i--)
                {
                    if(i <= lena_dec) ans_dec[i] += a_dec[i];
                    if(i <= lenb_dec) ans_dec[i] -= b_dec[i];

                    if(ans_dec[i] >= mod)
                    {
                        ans_dec[i-1] += ans_dec[i]/mod;
                        ans_dec[i] %= mod;
                    }
                    if(ans_dec[i] < 0)
                    {
                        ans_dec[i-1] -= 1;
                        ans_dec[i] += 10;
                    }
                }
                
                ans_int[len_ans_int] += ans_dec[0];
            }
            else if(y == -1)
            {
                sy_ans = syb;

                for(int i = len_ans_dec; i >= 1; i--)
                {
                    if(i <= lena_dec) ans_dec[i] -= a_dec[i];
                    if(i <= lenb_dec) ans_dec[i] += b_dec[i];

                    if(ans_dec[i] >= mod)
                    {
                        ans_dec[i-1] += ans_dec[i]/mod;
                        ans_dec[i] %= mod;
                    }
                    if(ans_dec[i] < 0)
                    {
                        ans_dec[i-1] -= 1;
                        ans_dec[i] += 10;
                    }
                }
                
                ans_int[len_ans_int] += ans_dec[0];
            }
            else
            {
                sy_ans = 0; len_ans_dec = 0;
            }
        }
    }

    if(ans_int[1] < 0) sy_ans = true, ans_int[1] = abs(ans_int[1]);
    // because the decimal part will borrow numbers from the integer part, this part is used to avoid wrong symbol
}