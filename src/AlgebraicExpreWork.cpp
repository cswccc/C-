#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "mul.hpp"
#include "add.hpp"
#include "StringToNum.hpp"
#include "NumToString.hpp"
#include "PolynomialWork.hpp"
#include "AlgebraicExpreWork.hpp"
#define ll long long
using namespace std;

const int maxn = 100+5;
const int maxm = 100000+5;

struct node
{
    string variable;
    string value;
};

node V[maxn];
int cnt;
char cc[maxm];
string ret;

int PreForVariables()
{
    int len = strlen(cc);
    bool flag = false;
    string vari = "", val = "";

    for(int i = 0; i < len; i++)
    {
        if(cc[i] == ' ') continue;
        if(cc[i] == '+' || cc[i] == '-' || cc[i] == '*') return 0;
        if(cc[i] == '=') flag = true;
        else
        {
            if(!flag) vari += cc[i];
            else val += cc[i];
        }
    }

    V[++cnt].variable = vari;
    V[cnt].value = val;

    return 1;
}

string Find(string vari)
{
    for(int i = 1; i <= cnt; i++)
        if(vari == V[i].variable) return V[i].value;
    
    return "";
}

void WorkForFormula()
{
    // for(int i = 1; i <= cnt; i++)
    // {
    //     cout<<V[i].variable<<' '<<V[i].value<<endl;
    // }
    string vari = "";

    int len = strlen(cc);

    for(int i = 0; i < len; i++)
    {
        if((cc[i] >= 'a' && cc[i] <= 'z') || (cc[i] >= 'A' && cc[i] <= 'Z')) vari += cc[i];
        else
        {
            if(vari != "") ret += Find(vari),vari = "";
            ret += cc[i];
        }
    }

    if(vari != "") ret += Find(vari);
}

void PreHandle_3()
{
    cnt = 0;
    memset(cc,0,sizeof(cc));
    ret = "";
}

void AlgebraicExpreWork()
{
    PreHandle_3();

    printf("Please input the algebraic expression you want to solve:\n");

    while(scanf("%s",cc) != EOF)
    {
        if(PreForVariables() ==0)
        {
            WorkForFormula();
            break;
        }
    }

    // cout <<ret<<endl;
    InputFormula(ret);
}