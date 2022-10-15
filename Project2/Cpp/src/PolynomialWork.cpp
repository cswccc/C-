#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <stack>
#include "mul.hpp"
#include "add.hpp"
#include "StringToNum.hpp"
#include "NumToString.hpp"
#include "PolynomialWork.hpp"
#include "MathematicalWork.hpp"
#include "WrongDialog.hpp"
#define ll long long
using namespace std;

struct EachNum//store the message of each number
{
    string integer;
    string decimal;
    bool decimal_point;
    bool symbol;
};

const int maxn = 1000000+5;

string input_Po;
string postfix_expression;
stack<EachNum> work;
int cnt_for_work;
ll a_int[maxn],b_int[maxn],c_int[maxn];
ll a_dec[maxn], b_dec[maxn], c_dec[maxn];

void PreWork()
{
    input_Po = "";
    postfix_expression = "";

    cnt_for_work = 0;
    while(!work.empty()) work.pop();
}

string PreHandleFormula(string formula)//handle for mathematical functions
{
    string ret = "";
    int len = formula.length();

    // cout << "len = " << len << endl;

    for(int i = 0; i < len; i++)
    {
        // cout << "formula[i] = " << formula[i] << endl;

        if(formula[i] == ' ') continue;

        if((formula[i] >= '0' && formula[i] <= '9')
            || (formula[i] == '.' || formula[i] == '+' || formula[i] == '-' || formula[i] == '*')
            || (formula[i] == '(' || (formula[i] == ')')))
        {
            ret += formula[i];
        }
        //for mathematical function, they always have english name, so when we meet the letter, we should check whether it is the function name
        else if(formula[i] >= 'a' && formula[i] <= 'z')
        {
            string function_name = "";
            while(i < len && (formula[i] >= 'a' && formula[i] <= 'z'))
            {
                function_name += formula[i];
                i++;
            }

            int type = Function_Type(function_name);//return the type of function

            // cout << "type = " << type << endl;

            if(type == -1) WrongDialog();//wrong type

            string num1_part = "", num2_part = "";
            bool front_bra = false, back_bra = false;
            bool num1_finished = false;
            bool num1_point = false, num2_point = false;
            //num1 and num2 are used to memory the number in the mathematical function

            while(i < len)
            {
                // cout << "i = " << i << endl;
                if(formula[i] == ' ') continue;
                if(formula[i] == '(' && !front_bra) front_bra = true;//the symbol of front_bracket
                else if(front_bra)
                {
                    if(i == len-1 && formula[i] != ')') WrongDialog();//no back bracket

                    if((formula[i] >= '0' && formula[i] <= '9'))
                    {
                        if(!num1_finished) num1_part += formula[i];
                        else num2_part += formula[i];
                    }
                    else if(formula[i] == '.')//decimal point
                    {
                        if(!num1_finished)
                        {
                            if(!num1_point && (formula[i-1] >= '0' && formula[i-1] <= '9') && (formula[i+1] >= '0' && formula[i+1] <= '9')) num1_point = true, num1_part += formula[i];
                            else WrongDialog();
                        }
                        else
                        {
                            if(!num2_point && (formula[i-1] >= '0' && formula[i-1] <= '9') && (formula[i+1] >= '0' && formula[i+1] <= '9')) num2_point = true, num2_part += formula[i];
                            else WrongDialog();
                        }
                    }
                    else if(formula[i] == ',')//the second number
                    {
                        if(!num1_finished) num1_finished = true;
                        else WrongDialog();
                    }
                    else if(formula[i] == ')')
                    {
                        back_bra = true;
                        break;
                    }
                    else WrongDialog();
                }
                else WrongDialog();

                i++;
            }

            if(!back_bra || (type == 0 && num2_part == "") || num1_part == "") WrongDialog();//no second number for pow() or no first number or no back bracket

            switch(type)
            {
                case 0: ret += pow(num1_part,num2_part); break;
                case 1: ret+= abs(num1_part); break;
            }
        }
        else WrongDialog();
    }

    // cout << "ret = " << ret << endl;

    return ret;
}

void FormulaToPostfix()// Convert infix expression to postfix expression 
{
    int len = input_Po.length();//length of infix expression

    string now_get = "";//use to record what we get now
    bool have_dec = false;//sign of decimal point
    string Stack = "";//Stack of operators

    for(int i = 0; i < len; i++)
    {
        if(input_Po[i] >= '0' && input_Po [i] <= '9' || input_Po[i] == '.') //we get numbers
        {
            if(input_Po[i] == '.')
            {
                if(i == len-1 || have_dec || input_Po[i+1] > '9' || input_Po[i+1] < '0') WrongDialog();//wrong input about the decimal part
                else have_dec = true;//sign of decimal point
            }
            now_get += input_Po[i];
        }
        else
        {
            if(now_get != "")
            {
                postfix_expression += now_get;//when we meet the operator, it stands that the numbers input is ended.
                postfix_expression += ' ';//use ' ' to seperate each numbers
                now_get = "";
                have_dec = false;
            }

            if(input_Po[i] == ' ') continue;
            else if(input_Po[i] == '(') Stack += '(';//we meet a '('
            else if(input_Po[i] == '+' || input_Po[i] == '-')//we meet a '+' or '-' operator
            {
                int len_Sta = Stack.length();//num of the operators in the Stack
                while(len_Sta != 0 && Stack[len_Sta-1] != '(')// '+' and '-' has the lowest level, so we should pop all of the operators in the Stack until we meet '(' or the Stack is null
                {
                    postfix_expression += Stack[len_Sta-1];//all popped operators should be storaged in the final expression
                    Stack.pop_back();//pop the top of tht Stack
                    len_Sta--;
                }
                Stack += input_Po[i];//push the operator into the Stack
            }
            else if(input_Po[i] == '*')//we meet a '*'
            {
                int len_Sta = Stack.length();
                while(len_Sta != 0 && Stack[len_Sta-1] != '(' && Stack[len_Sta-1] != '-' && Stack[len_Sta-1] != '+')//pop all the operators before '+' or '-' or '('
                {
                    postfix_expression += Stack[len_Sta-1];
                    Stack.pop_back();
                    len_Sta--;
                }
                Stack += input_Po[i];
            }
            else if(input_Po[i] == ')')//when we meet a ')', it stands for the end of '('
            {
                int len_Sta = Stack.length();
                while(len_Sta != 0 && Stack[len_Sta-1] != '(')//pop all the operators before '('
                {
                    postfix_expression += Stack[len_Sta-1];
                    Stack.pop_back();
                    len_Sta--;
                }
                if(len_Sta == 0) WrongDialog();//no one '(' matches with ')'
                else Stack.pop_back();
            }
        }
    }

    if(now_get != "")//the last number
    {
        postfix_expression += now_get;
        postfix_expression += ' ';
        now_get = "";
    }
    
    for(int i = Stack.length(); i >= 0; i--)//operators in the stack
    {
        if(Stack[i] == '(') WrongDialog();//too many '('

        postfix_expression += Stack[i];
    }
    // cout << postfix_expression << endl;
}

void HandlePostfix()//solve the postfix pxression
{
    int len = postfix_expression.length();
    EachNum now_get;
    now_get.decimal = "";
    now_get.integer = "";
    now_get.decimal_point = false;
    now_get.symbol = false;

    for(int i = 0; i < len; i++)
    {
        // cout << "postfix_expression[i] = " << postfix_expression[i] << ' ' << "i = " << i << endl;
        if(postfix_expression[i] <= '9' && postfix_expression[i] >= '0')//numbers
        {
            if(now_get.decimal_point) now_get.decimal += postfix_expression[i];//number for decimal part
            else now_get.integer += postfix_expression[i];//number for integer part
        }
        else if(postfix_expression[i] == '.')//sign of decimal point
        {
            now_get.decimal_point = true;
        }
            
        else
        {
            if(postfix_expression[i] == ' ')//sign of the ending of each number
            {
                // cout << now_get.integer << ' ' << now_get.decimal << endl;
                work.push(now_get); cnt_for_work++;//work is the Stack used to storage numbers

                now_get.decimal = "";
                now_get.integer = "";
                now_get.decimal_point = false;
                now_get.symbol = false;
            }
            else if(postfix_expression[i] == '+' || postfix_expression[i] == '-' || postfix_expression[i] == '*')
            {
                //cnt_for_work stands for the quantity of numbers in the Stack
                if(cnt_for_work < 2) WrongDialog();//too less numbers in the Stack

                EachNum b_st = work.top(); work.pop();
                EachNum a_st = work.top(); work.pop();//a & b are the top two numbers of the Stack
                EachNum c_st;
                bool symbol_b = b_st.symbol, symbol_a = a_st.symbol;
                cnt_for_work -= 2;

                memset(a_int,0,sizeof(a_int)); memset(b_int,0,sizeof(b_int)); memset(c_int,0,sizeof(c_int));
                memset(a_dec,0,sizeof(a_dec)); memset(b_dec,0,sizeof(b_dec)); memset(c_dec,0,sizeof(c_dec));
                
                int lena_int = 0, lena_dec = 0;
                int lenb_int = 0, lenb_dec = 0;
                int lenc_int = 0, lenc_dec = 0;//length of each array

                StringToNum(a_int, a_dec, lena_int, lena_dec, a_st.integer, a_st.decimal);
                StringToNum(b_int, b_dec, lenb_int, lenb_dec, b_st.integer, b_st.decimal);
                //change string type into long long type and stores in the arrays

                // puts("a:");
                // for(int j = 0; j <= lena_int; j++) cout << a_int[j] << ' ';
                // cout << '.';
                // for(int j = 1; j <= lena_dec; j++) cout << a_dec[j] << ' ';
                // puts("");

                // puts("b:");
                // for(int j = 0; j <= lenb_int; j++) cout << b_int[j] << ' ';
                // cout << '.';
                // for(int j = 1; j <= lenb_dec; j++) cout << b_dec[j] << ' ';
                // puts("");

                // cout << a_st.symbol << ' ' << a_st.integer << ' ' << a_st.decimal << endl;
                // cout << b_st.symbol << ' ' << b_st.integer << ' ' << b_st.decimal << endl;

                if(postfix_expression[i] == '+')//add part
                {
                    add(a_int, b_int, c_int, a_dec, b_dec, c_dec, lena_int, lenb_int, lenc_int, lena_dec, lenb_dec, lenc_dec, symbol_a, symbol_b, c_st.symbol);
                }
                    // add(a,b,c,lena,lenb,lenc,symbol_a,symbol_b,symbol[cnt_for_work+1]);
                else if(postfix_expression[i] == '-')//for minus, it changed the symbol of the second number
                {
                    add(a_int, b_int, c_int, a_dec, b_dec, c_dec, lena_int, lenb_int, lenc_int, lena_dec, lenb_dec, lenc_dec, symbol_a, !symbol_b, c_st.symbol);
                }
                    // add(a,b,c,lena,lenb,lenc,symbol_a,!symbol_b,symbol[cnt_for_work+1]);
                else//multiply part
                {
                    mul(a_int, b_int, c_int, a_dec, b_dec, c_dec, lena_int, lenb_int, lenc_int, lena_dec, lenb_dec, lenc_dec, symbol_a, symbol_b, c_st.symbol);
                }
                    // mul(a,b,c,lena,lenb,lenc,symbol_a,symbol_b,symbol[cnt_for_work+1]);
                
                // string c_st = ChangeNumToString(c,lenc);
                c_st.integer = ChangePartNumToString(c_int, lenc_int, false);
                c_st.decimal = ChangePartNumToString(c_dec, lenc_dec, true);
                //after we get the answer, we change the long long type into string type
                // puts("c:");
                // cout << c_st.integer << ' ' << c_st.decimal << endl;

                work.push(c_st); cnt_for_work++;//we push the answer into the Stack
            }
        }
    }
}

void Print()
{
    if(!work.empty() && cnt_for_work == 1)
    {
        if(work.top().symbol) cout << '-';//the answer is negative

        if(work.top().integer == "") cout << '0';

        cout << work.top().integer;//integeter part

        if(work.top().decimal != "") cout << '.' << work.top().decimal;//decimal part

        puts("");
    }
    else WrongDialog();
}

void PolynomialWork(string formula)
{
    PreWork();
    // cout << formula << endl;

    input_Po = PreHandleFormula(formula);

    // cout << input_Po << endl;
    
    FormulaToPostfix();

    // cout << postfix_expression << endl;

    HandlePostfix();

    Print();
}