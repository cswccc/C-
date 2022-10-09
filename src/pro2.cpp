#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#define ll long long
using namespace std;

void Polynomial_work();
void Mathematical_work();
void Solve_equa_work();

void Dialog()
{
    puts("0: Exit");
    puts("1: Polynomial Arithmetic");
    puts("2: Mathematical Functions");
    puts("3: Solve equations");
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
        case 3: Solve_equa_work(); break;
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

void Polynomial_work()
{

}

void Mathematical_work()
{

}

void Solve_equa_work()
{

}