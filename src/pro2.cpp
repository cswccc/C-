#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "mul.hpp"
#include "add.hpp"
#include "numToString.hpp"
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

    int x = 0;
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

string Stack[maxn];
char Operator[maxn];
int top,num_operator;
int front_bracket[maxn],num;
ll a[maxn],b[maxn],c[maxn];
bool symbol[maxn];

inline void Get_Num(ll a[], int len, int lena, int plc)
{
    int ci = 0;
    for(int i = len-1; i >= 0; i--)
    {
        if((Stack[plc][i]-'0')*pow(10,ci)+a[lena] >= mod) lena--,ci = 0;

        a[lena] = (Stack[plc][i]-'0')*pow(10,ci)+a[lena];
        ci++;
    }
}

inline void Prepare_Mul()
{
    memset(a,0,sizeof(a)); memset(b,0,sizeof(b)); memset(c,0,sizeof(c));
    num_operator--;

    // for(int i = 1; i <= top; i++) cout <<"++++"<<symbol[i]<<' '<<Stack[i]<<endl;

    int len1 = Stack[top].length(), len2 = Stack[top-1].length();
    int lena = ceil(len1/8.0), lenb = ceil(len2/8.0);
    int lenc = 0;
    
    Get_Num(a,len1,lena,top);
    Stack[top] = ""; symbol[top] = false; top--;

    Get_Num(b,len2,lenb,top);
    Stack[top] = ""; symbol[top] = false; top--;
    

    // for(int i = 0; i <= lena; i++) printf("%lld ",a[i]);
    // puts("");

    // for(int i = 0; i <= lenb; i++) printf("%lld ",b[i]);
    // puts("");

    mul(a,b,c,lena,lenb,lenc);

    string s = Change_Num_To_String(c,lenc);

    Stack[++top] = s;
    // cout<<"===="<<s<<endl;

    // for(int i = 1; i <= top; i++)
    //     cout <<"***"<<Stack[i]<<endl;
    
    // puts("------------");
}

inline void Prepare_Bracket()
{
    int start = front_bracket[num];

    for(int i = 1; i <= top; i++)
    cout <<"***"<<symbol[i]<<' '<<Stack[i]<<endl;

    puts("------------");

    for(int i = start; i < top; i++)
    {
        memset(a,0,sizeof(a)); memset(b,0,sizeof(b)); memset(c,0,sizeof(c));

        bool symbol1 = symbol[i], symbol2 = symbol[i+1];
        int len1 = Stack[i].length(), len2 = Stack[i+1].length();
        int lena = ceil(len1/8.0), lenb = ceil(len2/8.0);
        int lenc = 0;

        Get_Num(a,len1,lena,i);
        Stack[i] = ""; symbol[i] = false;

        Get_Num(b,len2,lenb,i+1);
        Stack[i+1] = ""; symbol[i+1] = false;

        // for(int j = 1; j <= lena; j++) printf("%lld ",a[j]);
        // puts("");
        // for(int j = 1; j <= lenb; j++) printf("%lld ",b[j]);
        // puts("");

        if(Operator[i] == '+') add(a,b,c,lena,lenb,lenc,symbol1,symbol2,symbol[i+1]);
        else if(Operator[i] == '-') add(a,b,c,lena,lenb,lenc,symbol1,!symbol2,symbol[i+1]);

        string s = Change_Num_To_String(c,lenc);

        Stack[i+1] = s;

        // cout<<"/////"<<symbol[i+1]<<' '<<s<<endl;
    }
    
    Stack[start] = Stack[top];
    symbol[start] = symbol[top];
    Stack[top] = ""; symbol[top] = false;
    top = start;
    
    for(int i = 1; i <= top; i++)
    cout <<"***"<<symbol[i]<<' '<<Stack[i]<<endl;

    puts("------------");
}

inline void PreHandle()
{
    top = 0;

    for(int i = 0; i < maxn; i++) Stack[i] = "";

    num_operator = 0;

    memset(Operator,0,sizeof(Operator));

    memset(symbol,false,sizeof(symbol));
}

void Polynomial_work()
{
    PreHandle();
    cin.getline(formula,maxn);
    printf("Please input the polynomial you want to solve:");
    cin.getline(formula,maxn);

    int len = strlen(formula);
    top = 1;

    for(int i = 0; i < len; i++)
    {
        if(formula[i] == '(') front_bracket[++num] = top;
        else if(formula[i] >= '0' && formula[i] <= '9') Stack[top] += formula[i], symbol[top] = false;
        else if(formula[i] == '*' || formula[i] == '+' || formula[i] == '-') {
            if(Operator[num_operator] == '*' && top > 1)
                Prepare_Mul();

            top++;
            Operator[++num_operator] = formula[i];
        }

        else if(formula[i] == ')')
        {
            if(Operator[num_operator] == '*')
                Prepare_Mul();
            
            Prepare_Bracket();
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