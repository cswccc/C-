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

    puts("2323232");

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

string Stack[maxn];
char Operator[maxn];
int top,num_operator;
int bracket_place[maxn],num;
ll a[maxn],b[maxn],c[maxn];

inline void Get_Num(ll a[], int len, int lena)
{
    int ci = 0;
    for(int i = lena-1; i >= 0; i--)
    {
        if((Stack[top][i]-'0')*pow(10,ci)+a[lena] >= mod) lena--,ci = 0;

        a[lena] = (Stack[top][i]-'0')*pow(10,ci)+a[lena];
        ci++;
    }

    top--;
}

inline void Prepare_Mul()
{
    memset(a,0,sizeof(a)); memset(b,0,sizeof(b)); memset(c,0,sizeof(c));

    int len1 = Stack[top].length(), len2 = Stack[top-1].length();
    int lena = ceil(len1/8.0), lenb = ceil(len2/8.0);
    
    Get_Num(a,len1,lena);
    Get_Num(b,len2,lenb);

    for(int i = 1; i <= lena; i++) printf("%lld ",a[i]);

    puts("");

    for(int i = 1; i <= lenb; i++) printf("%lld ",b[i]);
}

void Polynomial_work()
{
    cin.getline(formula,maxn);
    printf("Please input the polynomial you want to solve:");
    cin.getline(formula,maxn);

    printf("%s\n",formula);

    int len = strlen(formula);
    top = 1;

    for(int i = 0; i < len; i++)
    {
        if(formula[i] == '(') bracket_place[++num] = top;
        else if(formula[i] >= '0' && formula[i] <= '9') Stack[top] += formula[i];
        else if(formula[i] == '*' || formula[i] == '+' || formula[i] == '-') {
            if(Operator[num_operator] == '*')
            {
                Prepare_Mul();
            }
            Operator[++num_operator] = formula[i];
        }

        else if(formula[i] == ')')
        {
            
        }
    }
}

void Mathematical_work()
{
    cin.getline(formula,maxn);
    printf("Please input the mathematical function you want to solve:");
    cin.getline(formula,maxn);
}

void Algebraic_expre_work()
{
    cin.getline(formula,maxn);
    printf("Please input the equation you want to solve:");
    cin.getline(formula,maxn);
}