#pragma once
#include <iostream>
#include <cmath>
#define ll long long

int ComForInt(ll a[], ll b[], int lena, int lenb);
int ComForDec(ll a[], ll b[], int len);
void add(ll a_int[], ll b_int[], ll ans_int[], ll a_dec[], ll b_dec[], ll ans_dec[], int lena_int, int lenb_int, int &len_ans_int, int lena_dec, int lenb_dec, int &len_ans_dec, bool symbol1, bool symbol2, bool &sy_ans);