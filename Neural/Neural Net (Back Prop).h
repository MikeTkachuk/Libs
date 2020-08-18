
#ifndef Neural_h
#define Neural_h




#include <iostream>
#include <cmath>
#include <string>
#include "Matrix.h"

using namespace std;




struct Layer {

	matrix val;  //values array (colomn vector)
	matrix wei;  //weights matrix
	matrix bias;	 //bias array  (colomn vector)
	matrix DerWei; //a matrix of the derivatives of the weights
	matrix DerBias; //a matrix of the derivatives of the biases
	int height; //number of neurons in a layer | actually equals to the "matrix val" size


	Layer() {
		height = 0;
	}

	Layer(int dis, int next) {
		Init(dis, next);

	}
	void Init(int dis, int next) {
		height = dis;

		val.Init(dis, 1);

		wei.Init(next, dis, 's');

		bias.Init(dis, 1, 's');

		DerWei.Init(next, dis);

		DerBias.Init(dis, 1);

	}

	Layer(const Layer& A) {
		Init(A);
	}
	void Init(const Layer& A) {

		height = A.height;
		val.Init(A.val);
		wei.Init(A.wei);

		bias.Init(A.bias);

		DerWei.Init(A.DerWei);

		DerBias.Init(A.DerBias);
	}

	Layer& operator = (const Layer& A) {

		height = A.height;

		val = A.val;

		wei = A.wei;

		bias = A.bias;

		DerWei = A.DerWei;

		DerBias = A.DerBias;

		return *this;

	}
};

class Network {

private:
	Layer* layers;
	int depth;

	Layer Input;
	int inN;

	matrix Output;
	int outN;

public:
	Network() {
		layers = 0;
		depth = 0;

		Input;
		inN = 0;

		Output;
		outN = 0;

	}

	Network(int input, int dpth, int height, int output) {

		Init(input, dpth, height, output);

	}
	void Init(int input, int dpth, int height, int output) {
		if (dpth > 0 && output > 0 && input > 0 && height > 0) {

			layers = new Layer[dpth];
			depth = dpth;

			for (int i = 0; i < dpth - 1; i++) {
				layers[i].Init(height, height);
			}
			layers[dpth - 1].Init(height, output);

			Input.Init(input, height);
			inN = input;

			Output.Init(output, 1);
			outN = output;
		}
		else
		{

			layers = 0;
			depth = dpth;

			Input;
			inN = 0;

			Output;
			outN = 0;

		}
	}

	Network(int input, int dpth, int* Heights, int output) {
		Init(input, dpth, Heights, output);
	}
	void Init(int input, int dpth, int* Heights, int output) {
		if (dpth > 0 && output > 0 && input > 0) {

			layers = new Layer[dpth];
			depth = dpth;
			for (int i = 0; i < dpth - 1; i++) {
				layers[i].Init(Heights[i], Heights[i + 1]);
			}

			layers[dpth - 1].Init(Heights[dpth - 1], output);

			Input.Init(input, Heights[0]);
			inN = input;

			Output.Init(output, 1);
			outN = output;
		}
		else
		{

			layers = 0;
			depth = dpth;

			Input;
			inN = 0;

			Output;
			outN = 0;

		}
	}

	void ReInitialize();

	void Exe(double a[]);

	void BackProp(double realOut[], double learnRate);

	void Export(double learnRate);
	void Export();

	void Import(string path);


};



#endif // !Neural_h
#pragma once

