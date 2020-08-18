#include <iostream>
#include <cmath>
using namespace std;
const int LEN = 256;

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
char* Rewrite(char A[], int end);
char IDtochar(int a);


void SpecificDelete(double A[], int d, int N) { //deletes d-th and (d+1)-th element from an array
	int a = d + 2;
	while (a < N) {
		A[a - 2] = A[a];
		a++;
	}
}


int DetermineID(char a) {
	if (a == '^') {
		return 4;
	}
	if (a == '*') {
		return 3;
	}
	if (a == '/') {
		return 2;
	}
	if (a == '+') {
		return 1;
	}
	if (a == '-') {
		return 0;
	}

}

int DeterminePriority(int a) {
	if (a == 4) {
		return 2;
	}
	if (a == 3) {
		return 1;
	}
	if (a == 2) {
		return 1;
	}
	if (a == 1) {
		return 0;
	}
	if (a == 0) {
		return 0;
	}

}


double toInt(char A[], int a, int b) {
	double x = 0, tenpow;
	for (int i = b; i >= a; i--) {
		tenpow = 1;
		for (int j = 0; j < b - i; j++)
			tenpow *= 10;
		x += (A[i] - '0') * tenpow;
	}
	return x;
}



int FindOpenBracket(char A[], int a) {
	int count = 0;
	for (int i = a; i >= 0; i--) {
		if (A[i] == '(')
			count--;
		if (A[i] == ')')
			count++;
		if (count == 0)
			return i;

	}
}



int FindCloseBracket(char A[], int a) {
	int count = 0;
	for (int i = a; i < LEN; i++) {
		if (A[i] == ')')
			count--;
		if (A[i] == '(')
			count++;
		if (count == 0)
			return i;

	}
}



int Operations(char A[]) {
	int count = 0;
	for (int i = 0; i < LEN; i++) {
		if (A[i] == '+' || A[i] == '-' || A[i] == '*' || A[i] == '/' || A[i] == '^' || (A[i] == 's' && A[i + 1] == 'q' && A[i + 2] == 'r' && A[i + 3] == 't')) {
			count++;
		}

	}
	return count;
}

double Operation(double* A, int i) {
	double operand1 = A[i - 1], operand2 = A[i + 1], result;
	int a, b;


	switch ((int)A[i]) {
	case 4:
		result = pow(operand1, operand2);
		return result;
		break;
	case 3:
		result = operand1 * operand2;
		return result;
		break;
	case 2:
		if (operand2 == 0) {
			cout << "\nDivision by zero!\n";
			return -INFINITY;
		}
		result = operand1 / operand2;
		return result;
		break;
	case 1:
		result = operand1 + operand2;
		return result;
		break;
	case 0:
		result = operand1 - operand2;
		return result;
		break;
	}

}



double* Transform(char A[], int L, int R, double var) {
	int a, b, count = 0 , outofSwitch=0;
	double* Results = new double[LEN];

	for (int i = L; i < R; i++) {
		if (A[i] == '(') {
			b = FindCloseBracket(A, i);
			Results[count] = Execute(Transform(A, i + 1, b, var));
			count++;
			i = b;
			continue;
		}


		if (A[i] == '^' || A[i] == '*' || A[i] == '/' || A[i] == '+' || A[i] == '-') {
			Results[count] = DetermineID(A[i]);
			if (Results[count] == 0 && (i==L||A[i-1]=='(')) {
				Results[count] = -1;
				count++;
				Results[count] = DetermineID('*');
			}
			count++;
			continue;
		}


		if (A[i] >= '0' && A[i] <= '9') {
			b = i + 1;
			while (A[b] >= '0' && A[b] <= '9')
				b++;
			b--;
			Results[count] = toInt(A, i, b);
			i = b;
			
			if (A[i + 1] == '.') {
				b = i + 2;
				while (A[b] >= '0' && A[b] <= '9')
					b++;
				b--;
				Results[count] += toInt(A, i + 2, b)/pow(10,b-i-1);
				i = b;
			}
			count++;
			if (A[b+1] == '(' || (A[b+1] >= 'a' && A[b+1] <= 'z')) {
				Results[count] = 3;
				count++;
			}

			continue;
		}


		if (A[i] >= 'a' && A[i] <= 'z') {
			switch (A[i]){
			case 's':
				switch (A[i + 1]) {
				case 'q':
					if (A[i + 2] == 'r' && A[i + 3] == 't' && A[i + 4] == '(') {
						b = FindCloseBracket(A, i+4);
						Results[count] = sqrt(Execute(Transform(A, i + 5, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
				case 'i':
					if (A[i + 2] == 'n' && A[i + 3] == '(' ) {
						b = FindCloseBracket(A, i + 3);
						Results[count] = sin(Execute(Transform(A, i + 4, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
					if (A[i + 2] == 'n' && A[i + 3] == 'h' && A[i + 4] == '(') {
						b = FindCloseBracket(A, i + 4);
						Results[count] = sinh(Execute(Transform(A, i + 5, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
				
				}
			case 'l':
				switch (A[i + 1]) {
				case 'n':
					if (A[i + 2] == '(') {
						b = FindCloseBracket(A, i + 2);
						Results[count] = log(Execute(Transform(A, i + 3, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
				case 'o':
					if (A[i + 2] == 'g' && A[i + 3] == '(') {
						b = FindCloseBracket(A, i + 3);
						Results[count] = log10(Execute(Transform(A, i + 4, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
				}
			case 'c':
				switch (A[i + 1]) {
				case 'o':
					if (A[i + 2] == 's' && A[i + 3] == '(') { //cos
						b = FindCloseBracket(A, i + 3);
						Results[count] = cos(Execute(Transform(A, i + 4, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
					if (A[i + 2] == 't' && A[i + 3] == '(') { //cot 
						b = FindCloseBracket(A, i + 3);
						Results[count] = 1/tan(Execute(Transform(A, i + 4, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}

					if (A[i + 2] == 's' && A[i + 3] == 'h' && A[i + 4] == '(') { //cosh
						b = FindCloseBracket(A, i + 4);
						Results[count] = cosh(Execute(Transform(A, i + 5, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
				case 'b':
					if (A[i + 2] == 'r' && A[i + 3] == 't' && A[i+4] == '(') { //cbrt
						b = FindCloseBracket(A, i + 4);
						Results[count] = cbrt(Execute(Transform(A, i + 5, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}

				}
			case 't':
				if (A[i + 1] == 'a' && A[i + 2] == 'n' && A[i + 3] == '(') { //tan
					b = FindCloseBracket(A, i + 3);
					Results[count] = tan(Execute(Transform(A, i + 4, b, var)));
					count++;
					i = b;
					outofSwitch = 1;
					continue;
				}
				if (A[i + 1] == 'a' && A[i + 2] == 'n' && A[i + 3] == 'h' && A[i+4]=='(') {//tanh 
					b = FindCloseBracket(A, i + 4);
					Results[count] = tanh(Execute(Transform(A, i + 5, b, var)));
					count++;
					i = b;
					outofSwitch = 1;
					continue;
				}

			case 'a':
				switch (A[i + 1]) {
				case 'c':
					if (A[i + 2] == 'o' && A[i + 3] == 's' && A[i+4]=='(') {
						b = FindCloseBracket(A, i + 4);
						Results[count] = acos(Execute(Transform(A, i + 5, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
					if (A[i + 2] == 'o' && A[i + 3] == 's' && A[i + 4] == 'h' && A[i + 5] == '(') { //tanh
						b = FindCloseBracket(A, i + 5);
						Results[count] = acosh(Execute(Transform(A, i + 6, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
				case 's':
					if (A[i + 2] == 'i' && A[i + 3] == 'n' && A[i + 4] == '(') { //asin
						b = FindCloseBracket(A, i + 4);
						Results[count] = asin(Execute(Transform(A, i + 5, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
					if (A[i + 2] == 'i' && A[i + 3] == 'n' && A[i + 4] == 'h' && A[i + 5] == '(') { //asinh
						b = FindCloseBracket(A, i + 5);
						Results[count] = asinh(Execute(Transform(A, i + 6, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
				case 't':
					if (A[i + 2] == 'a' && A[i + 3] == 'n' && A[i + 4] == '(') { //atan
						b = FindCloseBracket(A, i + 4);
						Results[count] = atan(Execute(Transform(A, i + 5, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
					if (A[i + 2] == 'a' && A[i + 3] == 'n' && A[i + 4] == 'h' && A[i + 5] == '(') { //atanh
						b = FindCloseBracket(A, i + 5);
						Results[count] = atanh(Execute(Transform(A, i + 6, b, var)));
						count++;
						i = b;
						outofSwitch = 1;
						continue;
					}
				}
			case 'e':
				if (A[i + 1] == 'r' && A[i + 2] == 'f' && A[i + 3] == '(') { //erf
					b = FindCloseBracket(A, i + 3);
					Results[count] = erf(Execute(Transform(A, i + 4, b, var)));
					count++;
					i = b;
					outofSwitch = 1;
					continue;
				}





			}

		}



		if (outofSwitch != 0) //to skip the "for" cycle after the switch was used
			continue;



		if (A[i] >= 'a' && A[i] <= 'z') {
			if (A[i] == 'e') {
				Results[count] = 2.718281828459045;
				count++;
			}
			else if (A[i] == 'p' && A[i + 1] == 'i') {
				Results[count] = 3.1415926535897932384626433832795;
				count++;
				i++;
				if (A[i + 1] == '(' || (A[i + 1] >= 'a' && A[i + 1] <= 'z')) {
					Results[count] = 3;
					count++;
				}
				continue;
			}
			else {
				Results[count] = var;
				count++;
			}
			if (A[i + 1] == '(' || (A[i + 1] >= 'a' && A[i + 1] <= 'z')) {
				Results[count] = 3;
				count++;
			}
			continue;
		}

	}
	Results[LEN - 1] = count;
	return Results;
}



double Execute(double * A) {
	double result, operand2;
	int a, b, count = A[LEN - 1], OrderCount = 0;
	int size = count; //save the number of all operations and operands (size of Results Array)
	//int* Order=new int [(count-1)/2];//an array : indexes - order; values indexes in the Results Array
	int Order;
	
	for (int i = 0; i < (count - 1) / 2; i++) { //for each operation 
		//OrderCount = 0;
		for (int pr = 2; pr >= 0; pr--) {
			for (int k = 1; k < size; k += 2) {
				if (DeterminePriority(A[k]) == pr) { //create the Order array
					Order = k;
					//OrderCount++;
					pr = -1;
					break;
				}

			}
		}
		A[Order - 1] = Operation(A, Order);
		SpecificDelete(A, Order, size);
		size -= 2;
	}
	result = A[0];
	delete[] A;
	return result;
}



int Check(char A[], int L, int end) {
	int indicator = 0;
	for (int i = L+1; i < end; i++) {
		if (A[i] == '+' || A[i] == '-' || A[i] == '*' || A[i] == '/' || A[i] == '^') {
			// from the left nothing other than a number or ')'
			if (A[i - 1] == ')' || (A[i - 1] <= '9' && A[i - 1] >= '0') || (A[i - 1] <= 'z' && A[i - 1] >= 'a')) {
				continue;
			}
			if (A[i + 1] == '(' || (A[i + 1] <= '9' && A[i + 1] >= '0') || (A[i + 1] <= 'z' && A[i + 1] >= 'a')) {
				continue;
			}
			indicator += 1;
			break;
		}
	}
	int countO = 0, countC = 0;
	for (int i = L; i < end; i++) {
		if (A[i] == '(')
			countO++;
		if (A[i] == ')')
			countC++;
	}
	if (countO != countC)
		indicator += 2;
	
	if (countO > countC) {
		cout << "Closing the remaining brackets:\n";
		indicator = 0;

		while (countO > countC) {
			A[end-1] = ')';
			end++;
			countC++;
		}
		end--;
		for (int i = L; i < end; i++)
			cout << A[i];
		cout << "\n";
	}
	if (indicator != 0)
		cout << "Error!\n";
	if (indicator % 2 == 1)
		cout << "Unallowed expression near the operator\n";
	if (indicator >= 2)
		cout << "Wrong brackets order!\n";
	
	return indicator;
}




char* CreateLine() {
	char* line = new char[LEN];
	int countrL = 0, num, brornot, brO = 0, temp, numL = 0, validBr = 0, valid = 0, bracketType = 0;


	int regulate = 20;


	for (int i = 0; i < regulate;) {
		valid = 0;
		validBr = 0;
		brornot = rand() % 2;


		if (brornot == 0 && regulate - i > 3) {

			if (countrL == 0 || (line[countrL - 1] > '9' || line[countrL - 1] < '0' && line[countrL - 1] != ')')) {
				line[countrL] = '(';
				brO++;
				countrL++;
				valid = 1;
				continue;

			}
			else if (brO > 0 && line[countrL - 1] <= '9' && line[countrL - 1] >= '0') {
				line[countrL] = ')';
				brO--;
				countrL++;
				valid = 1;
				continue;
			}
			else
				brornot++;


		}


		if (brornot == 1) {
			if (countrL == 0 || line[countrL - 1] == '^' || line[countrL - 1] == '*' || line[countrL - 1] == '/' || line[countrL - 1] == '+' || line[countrL - 1] == '-' || line[countrL - 1] == '(') {
				countrL = writeNum(line, countrL);
				i++;
				valid = 1;
				continue;

			}
			else
				brornot++;

		}
		if (brornot == 2) {
			if (line[countrL - 1] == ')' || (line[countrL - 1] <= '9' && line[countrL - 1] >= '0')) {
				line[countrL] = IDtochar(rand() % 4);
				countrL++;
				valid = 1;
				continue;
			}
		}

	}


	while (brO > 0) {
		line[countrL] = ')';
		countrL++;
		brO--;
	}
	int i = 0;
	while (line[i] != (char)-51) {
		i++;
	}
	//cout << line << "\n";
	line = Rewrite(line,i);
	return line;
}


int writeNum(char A[], int i) {
	int num, temp, numL = 0;
	num = rand() % 999 + 1;
	temp = num;
	while (temp > 0) {
		temp /= 10;
		numL++;
	}
	temp = num;
	for (int k = 0; k < numL; k++) {
		A[i + numL - k - 1] = '0' + temp % 10;
		temp /= 10;
	}
	i += numL;
	numL = 0;
	return i;
}

char* Rewrite(char* A, int end) {
	char* N = new char[end];
	int * Om = new int[end], OmW = 0, OmR = 0, chck = 0, temp=0;
	Om[OmW] = 0;
	int n = 0;
	if (A[0] == '(') {
		temp = FindCloseBracket(A, 0);
		for (int k = 1; k < temp; k++) {
			if (A[k] > '9' || A[k] < '0') {
				chck = 1;
				break;
			}
		}
	}
	if (A[0] != '(') {
		N[0] = A[0];
		n++;
	}
	else if (chck == 0) { // checking if the bracket surrounds only one number, such as (345)*2  
		Om[OmW] = temp;
		OmW++;

	}
	else if (A[temp + 1] == '^' || A[temp + 1] == '*' || A[temp + 1] == '/' || A[temp + 1] == '+' || A[temp + 1] == '-') { //checking the case of the [temp] bracket being the very last char (if yes - omitted)
		N[0] = A[0];
		n++;

	}
	else {
		Om[OmW] = temp;
		OmW++;
	}


	for (int i = 1; i < end; i++) {
		chck = 0;
		if (A[i] == '(') {
			temp = FindCloseBracket(A, i);
		}
		if (A[i] == '(' && A[i - 1] == '(' && (FindCloseBracket(A, i - 1) - temp == 1)) {
			Om[OmW] = temp;
			OmW++;
			continue;
		}
		if (A[i] == '(' && (A[i - 1] < 'a' || A[i - 1] > 'z') && (A[i - 2] < 'a' || A[i - 2] > 'z')) {

			for (int k = i + 1; k < temp; k++) {
				if (A[k] > '9' || A[k] < '0') {
					chck = 1;
					break;
				}
			}
			if (chck == 0) {
				Om[OmW] = temp;
				OmW++;
				continue;
			}
		}

		if (i == Om[OmW - 1]) {
			OmW--;
			continue;
		}
		N[n] = A[i];
		n++;

	}
	for (int i = 0; i < end; i++)
		A[i] = N[i];
	delete[] N;
	delete[] Om;
	return A;

}

char IDtochar(int a) {

	if (a == 6) {
		return ')';
	}
	if (a == 5) {
		return '(';
	}
	if (a == 4) {
		return '^';
	}
	if (a == 3) {
		return '*';
	}
	if (a == 2) {
		return '/';
	}
	if (a == 1) {
		return '+';
	}
	if (a == 0) {
		return '-';
	}


}