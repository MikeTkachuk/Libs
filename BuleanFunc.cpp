#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
using namespace std;

void Implication(double Arr1[], double Arr2[], int N);
double* PlusCircle(double Arr1[], double Arr2[], int N);
void Equal(double Arr1[], double Arr2[], int N);
double* Conunction(double Arr1[], double Arr2[], int N);
double* Disunction(double Arr1[], double Arr2[], int N);


void Implication(double Arr1[], double Arr2[], int N) {
	
}
double* PlusCircle(double Arr1[], double Arr2[], int N) {
	double* Result = new double[N];

	for (int i = 0; i < N; i++) {
		if (Arr1[i] == Arr2[i]) {
			Result[i] = 0;
		}
		else {
			Result[i] = 1;
		}
	}
	return Result;
}
void Equal(double Arr1[], double Arr2[], int N){

}
double* Conunction(double Arr1[], double Arr2[], int N){
	double* Result = new double[N];
	for (int i = 0; i < N; i++) {
		Result[i]=Arr1[i] * Arr2[i];
	}
	return Result;
}
double* Disunction(double Arr1[], double Arr2[], int N){
	double* Result = new double[N];

	for (int i = 0; i < N; i++) {
		Result[i]=Arr1[i] + Arr2[i];
		if (Result[i] > 1)
			Result[i] = 1;
	}
	return Result;

}
