#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "mul.hpp"
#include "add.hpp"
#include "Get_Num.hpp"
#include "numToString.hpp"
#include "Polynomial_work.hpp"
#define ll long long
using namespace std;

const int maxn = 1000000+5;
const ll mod = 1e8;


char formula[maxn];
string Stack[maxn];
char Operator[maxn];
int top,num_operator;
int front_bracket[maxn],num;
ll a[maxn],b[maxn],c[maxn];
bool symbol[maxn];

void Prepare_Mul()
{
    puts("mul");
    memset(a,0,sizeof(a)); memset(b,0,sizeof(b)); memset(c,0,sizeof(c));
    Operator[num_operator] = 0;
    num_operator--;

    // for(int i = 1; i <= top; i++) cout <<"++++"<<symbol[i]<<' '<<Stack[i]<<endl;

    int len1 = Stack[top].length(), len2 = Stack[top-1].length();
    bool symbol1 = symbol[top], symbol2 = symbol[top-1];
    int lena = ceil(len1/8.0), lenb = ceil(len2/8.0);
    int lenc = 0;
    
    Get_Num(a,len1,lena,Stack[top]);
    Stack[top] = ""; symbol[top] = false; top--;

    Get_Num(b,len2,lenb,Stack[top]);
    Stack[top] = ""; symbol[top] = false; top--;
    

    // for(int i = 0; i <= lena; i++) printf("%lld ",a[i]);
    // puts("");

    // for(int i = 0; i <= lenb; i++) printf("%lld ",b[i]);
    // puts("");

    mul(a,b,c,lena,lenb,lenc,symbol1,symbol2,symbol[top+1]);

    string s = Change_Num_To_String(c,lenc);

    Stack[++top] = s;
    // cout<<"===="<<s<<endl;

    for(int i = 1; i <= top; i++)
        cout <<"***"<<symbol[i]<<' '<<Stack[i]<<endl;
    
    puts("------------");
}

void Work_For_Add(int start)
{
    puts("add");
    // for(int i = 1; i <= top; i++)
    // cout <<"***"<<symbol[i]<<' '<<Stack[i]<<endl;

    // puts("------------");

    int cnt = 0;

    for(int i = start; i < top; i++)
    {
        memset(a,0,sizeof(a)); memset(b,0,sizeof(b)); memset(c,0,sizeof(c));

        bool symbol1 = symbol[i], symbol2 = symbol[i+1];
        int len1 = Stack[i].length(), len2 = Stack[i+1].length();
        int lena = ceil(len1/8.0), lenb = ceil(len2/8.0);
        int lenc = 0;

        Get_Num(a,len1,lena,Stack[i]);
        Stack[i] = ""; symbol[i] = false;

        Get_Num(b,len2,lenb,Stack[i+1]);
        Stack[i+1] = ""; symbol[i+1] = false;

        // for(int j = 1; j <= lena; j++) printf("%lld ",a[j]);
        // puts("");
        // for(int j = 1; j <= lenb; j++) printf("%lld ",b[j]);
        // puts("");

        if(Operator[i] == '+') add(a,b,c,lena,lenb,lenc,symbol1,symbol2,symbol[i+1]);
        else add(a,b,c,lena,lenb,lenc,symbol1,!symbol2,symbol[i+1]);
        Operator[i] = 0; cnt++;

        string s = Change_Num_To_String(c,lenc);

        Stack[i+1] = s;

        // cout<<"/////"<<symbol[i+1]<<' '<<s<<endl;
    }
    
    if(start != top)
    {
        Stack[start] = Stack[top];
        symbol[start] = symbol[top];
        Stack[top] = ""; symbol[top] = false;
        top = start;
        num_operator -= cnt;
    }
    
    for(int i = 1; i <= top; i++)
    cout <<"***"<<symbol[i]<<' '<<Stack[i]<<endl;

    puts("------------");
}

void PreHandle_1()
{
    top = 0;

    for(int i = 0; i < maxn; i++) Stack[i] = "";

    num_operator = 0;

    memset(Operator,0,sizeof(Operator));

    memset(symbol,false,sizeof(symbol));

    memset(formula,0,sizeof(formula));
}

void work()
{
    int len = strlen(formula);
    top = 1;

    for(int i = 0; i < len; i++)
    {
        if(formula[i] == '(') front_bracket[++num] = top;
        else if(formula[i] >= '0' && formula[i] <= '9') Stack[top] += formula[i];
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
            
            Work_For_Add(front_bracket[num]); num--;
        }
    }

    if(Operator[num_operator] == '*') Prepare_Mul();

    Work_For_Add(1);

    if(symbol[1]) cout<<'-';
    cout<<Stack[1]<<endl;
}

void Polynomial_work()
{
    PreHandle_1();
    cin.getline(formula,maxn);
    printf("Please input the polynomial you want to solve:");
    cin.getline(formula,maxn);

    work();
}

void Input_Formula(string s)
{
    PreHandle_1();

    int len = s.length();

    for(int i = 0; i < len; i++)
        formula[i] = s[i];
    
    work();
}