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
string Time(int a); // a in seconds;






string Time(int a) {
	string Time = "";
	int hours = (a - a % 3600) / 3600;
	int minutes = (a % 3600-a%60)/60;
	int seconds = a % 60;

	hours %= 24;
	if (hours <= 9) {
		Time += '0';
		Time += hours + '0';
	}
	else {
		Time += floor(hours / 10) + '0';
		Time += hours % 10 + '0';
	}

	Time += ':';

	if (minutes <= 9) {
		Time += '0';
		Time += minutes + '0';
	}
	else {
		Time += floor(minutes / 10) + '0';
		Time += minutes % 10 + '0';
	}

	Time += ':';

	if (seconds <= 9) {
		Time += '0';
		Time += seconds + '0';
	}
	else {
		Time += floor(seconds / 10) + '0';
		Time += seconds % 10 + '0';
	}
	return Time;
}

int Rand(int max) {
	int a = floor(max / RAND_MAX), n = max - a * RAND_MAX, x = 0;

	for (int i = 0; i < a; i++) {

		x += rand() % RAND_MAX;
	}

	x += rand() % n;
	return x;
}


void Swap(double* x, double* y) {
	int temp=*x;
	*x = *y;
	*y = temp;
}

int place(double Arr[], int min, int max) {
	int i, count = min, pivot = Arr[max - 1];

	for (i = min; i < max; i++) {
		if (Arr[i] <= pivot) {
			Swap(&Arr[i], &Arr[count]);
			count++;
		}
		
	}
	count--;
	return count;
}

void quicksort(double Arr[], int min, int max){
	int pl;
	pl = place(Arr, min, max);
	
	if (pl>min) {
		quicksort(Arr, min, pl);
		
		quicksort(Arr, pl + 1, max);
		
	}
}
void QuickSort(double Arr[], int n) {
	int pl;
	pl = place(Arr, 0, n);
	quicksort(Arr,0 ,pl);
	quicksort(Arr, pl+1 , n);


}





void heap(double Arr[], int n, int i) {
	int l = 2 * i + 1, r = 2 * i + 2, big = i;
	double temp;
	if (l <= n && Arr[l] > Arr[big]) {
		big = l;
	}
	if (r <= n && Arr[r] > Arr[big]) {
		big = r;
	}
	if (big != i) {
		temp = Arr[i];
		Arr[i] = Arr[big];
		Arr[big] = temp;
		heap(Arr, n, big);
	}
}

void HeapSort(double Arr[], int a) {
	int imax, i, j;
	double temp;

	for (i = ceil((double)(a - 1) / (double)2) - 1; i >= 0; i--) {
		heap(Arr, a - 1, i);
	}

	for (j = a - 1; j > 0; j--) {
		temp = Arr[j];
		Arr[j] = Arr[0];
		Arr[0] = temp;
		heap(Arr, j - 1, 0);

	}

}






void SelectionSort(double Arr[], int a) {
	int i, j, countr = 0, Min_dx = 0;
		double temp, Min = INT_MAX ;
	for (j = countr;j < a;j++) {
		for (i = countr;i < a;i++) {
			if (Min > Arr[i]) {
				Min = Arr[i];
				Min_dx = i;
			}

		}
		temp = Arr[countr];
		Arr[countr] = Arr[Min_dx];
		Arr[Min_dx] = temp;
		Min = INT_MAX;
		countr += 1;
	}
}






void CountSort(int Arr[], int a) {
	int i, j, temp, countr = 0, Min = INT_MAX, Min_dx = 0,Max=INT_MIN;
	for (i = 0; i < a; i++) {
		if (Max < Arr[i])
			Max = Arr[i];
	}
	int *S= new int[Max], *X=new int[a];

	for (i = 0; i < Max+1;i++) {
		S[i] = 0;
	}


	for (i = 0; i < a;i++) {
		S[Arr[i]] += 1;
	}

	for (i = 1; i < Max+1;i++) {
		S[i] += S[i - 1];
	}

	for (i = 0; i < Max+1 ;i++) {
  		if (S[i] == 0 && i == 0) {
			continue;
		} else if (S[i] > S[i -1] || S[0]>0) {
			if (i == 0) {
				temp = S[0];
			}
			else {
				temp = S[i] - S[i - 1];
			}
			countr = S[i];
			for (j = 0;j < temp;j++) {
				countr -= 1;
				X[countr] = i;
			}
			
			

		}
	}
	for ( i = 0; i < a; i++) {
		Arr[i] = X[i];
	
	}
}






void print(double Arr[], int a) {
	int i, Max=INT_MIN;
	for (i = 0; i < a; i++) {
		if (Max < Arr[i])
			Max = Arr[i];
	}
	int n, max= floor(log(Max) / log(10));
	for (int i = 0; i < a; i++) {
		n =max - floor(log(Arr[i]) / log(10)) + 1;
		if (Arr[i] == 0)
			n = 1;
		cout << Arr[i];
		for (int space = 0;space < n;space++)
			cout << " ";
		
		if ((i+1) % 10 == 0) 
			cout << "\n";
		
	}
	cout << "\n";
}