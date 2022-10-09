#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

const int maxn = 1000000+5;
const ll mod = 1e8;

void Polynomial_work();
void Mathematical_work();
void Algebraic_expre_work();

void Dialog()
{
    puts("0: Exit");
    puts("1: Polynomial Arithmetic");
    puts("2: Mathematical Functions");
    puts("3: Algebraic expression");
    printf("Please type the number before the function you want to do:");

    int x;
    scanf("%d",&x);

    while(x < 0 || x > 3)
    {
        printf("Wrong input! The number needs to be between 0 and 3. Please type the number again:");
        scanf("%d",&x);
    }

    switch(x)
    {
        case 0: exit(0); break;
        case 1: Polynomial_work(); break;
        case 2: Mathematical_work(); break;
        case 3: Algebraic_expre_work(); break;
        default: break;
    }
}

int main()
{
    while(true)
    {
        Dialog();
    }

    return 0;
}

char formula[maxn];
int st[maxn],num;

void mul(ll a[],ll b[], ll ans[],int lena, int lenb, int &len_ans)
{
    len_ans = lena + lenb;

    memset(ans,0,lena+lenb);

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

void add(ll a[], ll b[], ll ans[], int lena, int lenb, int &len_ans)
{
    len_ans = max(lena,lenb);

    memset(ans,0,len_ans);

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

inline void Solve_Brackets(int start, int end)
{
    
}

inline void Handle_Brackets(int start,int len)
{
    if(formula[start] == '(') st[++num] = start;
    for(int i = start; i < len; i++)
    {
        if(formula[i] == '(') Handle_Brackets(i,len);

        if(formula[i] == ')')
        {
            if(num == 0) WrongDialog();
            SolveBrackets(st[num],i);
            num--;
        }
    }
}

void Polynomial_work()
{
    cin.getline(formula,maxn);
    printf("Please input the polynomial you want to solve:");
    cin.getline(formula,maxn);
}

void Mathematical_work()
{
    cin.getline(formula,maxn);
    printf("Please input the mathematical function you want to solve:");
    cin.getline(formula,maxn);

    printf("%s",formula);
}

void Algebraic_expre_work()
{
    cin.getline(formula,maxn);
    printf("Please input the equation you want to solve:");
    cin.getline(formula,maxn);

    printf("%s",formula);
}