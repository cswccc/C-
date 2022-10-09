#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#define ll long long
using namespace std;

const int maxn = 1000000+5;

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