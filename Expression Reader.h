#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <iostream>
#include <cmath>
using namespace std;



//const int LEN = 256;

void SpecificDelete(double A[], int d, int N);
int DetermineID(char a);
int DeterminePriority(int a);
double toInt(char A[], int a, int b);
int FindOpenBracket(char A[], int a);
int FindCloseBracket(char A[], int a);
double Operation(double* A, int i);
double* Transform(char A[], int L, int R, double var);
double Execute(double  A[]);
int Check(char A[],int L, int end);
char* CreateLine();
int writeNum(char A[], int i);
char* Rewrite(char A[],int end);
char IDtochar(int a);




#endif // FUNCTIONS_H_INCLUDED
#pragma once

