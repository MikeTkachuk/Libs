#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
using namespace std;


void print(double Arr[], int a);
int Rand(int max);
void Swap(double* x, double* y);
int place(double Arr[], int min, int max);
void quicksort(double Arr[], int min, int max);
void QuickSort(double Arr[], int n);
void heap(double Arr[], int n, int i);
void HeapSort(double Arr[], int a);
void SelectionSort(double Arr[], int a);
void CountSort(int Arr[], int a);
void print(double Arr[], int a);
string Time(int a);
#endif // FUNCTIONS_H_INCLUDED
#pragma once
