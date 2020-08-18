#include <iomanip>
#include <fstream>
#include "Neural.h"
using namespace std;


//Neural.h function defenitions

void Network::ReInitialize() {

	for (int i = 0; i < depth; i++) {
		layers[i].bias.Init(layers[i].bias.getRow(), layers[i].bias.getCol(), 's');
		layers[i].wei.Init(layers[i].wei.getRow(), layers[i].wei.getCol(), 's');
	}

}

void Network::Exe(double a[]) {



	for (int i = 0; i < inN; i++) // copy the input value to the input layer
		Input.val[i][0] = a[i];

	layers[0].val = Input.wei * Input.val; //current layer only transfers data according to the weights
	layers[0].val = layers[0].val + layers[0].bias;	//adding of biases ->
	layers[0].val = layers[0].val.doSigma();	//->and doing Sigma is conducted in the next layer with its resourses

	for (int L = 0; L < depth - 1; L++) {


		layers[L + 1].val = layers[L].wei * layers[L].val;
		layers[L + 1].val = layers[L + 1].val + layers[L + 1].bias;
		layers[L + 1].val = layers[L + 1].val.doSigma();


	}
	Output = layers[depth - 1].wei * layers[depth - 1].val;
	Output = Output.doSigma();

}

void Network::BackProp(double realOut[], double learnRate) {
	double sum = 0;
	double cost = 0;

	for (int outRow = 0; outRow < outN; outRow++) {

		cost = -realOut[outRow] + Output.it[outRow][0];


		for (int NeurRow = 0; NeurRow < layers[depth - 1].height; NeurRow++) { //from the top of the first layer from the right
			layers[depth - 1].DerBias.it[NeurRow][0] = DS(Output.it[outRow][0]) * layers[depth - 1].wei.it[outRow][NeurRow] * DS(layers[depth - 1].val.it[NeurRow][0]); //(der. of the output * weight towards outp * der of the input of the neuron)
			layers[depth - 1].bias.it[NeurRow][0] += -2 * learnRate * cost * layers[depth - 1].DerBias.it[NeurRow][0];

			layers[depth - 1].DerWei.it[outRow][NeurRow] = DS(Output.it[outRow][0]) * layers[depth - 1].val.it[NeurRow][0];
			layers[depth - 1].wei.it[outRow][NeurRow] += -2 * learnRate * cost * layers[depth - 1].DerWei.it[outRow][NeurRow];

		}





		for (int L = depth - 2; L >= 0; L--) { // from the second from the right 

			for (int NeurRow = 0; NeurRow < layers[L].height; NeurRow++) { //from the top

				for (int nextRow = 0; nextRow < layers[L + 1].height; nextRow++) {

					if (nextRow == 0) {
						layers[L].DerBias.it[NeurRow][0] = 0;  //set the derivative to zero each cycle 
					}

					layers[L].DerBias.it[NeurRow][0] += layers[L + 1].DerBias.it[nextRow][0] * layers[L].wei.it[nextRow][NeurRow];

					layers[L].DerWei.it[nextRow][NeurRow] = weiDer( L, NeurRow, nextRow, outRow);
					layers[L].wei.it[nextRow][NeurRow] += -2 * learnRate * cost * layers[L].DerWei.it[nextRow][NeurRow];
				}
				layers[L].DerBias.it[NeurRow][0] *= DS(layers[L].val.it[NeurRow][0]); // moved out of the cycle


				layers[L].bias.it[NeurRow][0] += -2 * learnRate * cost * layers[L].DerBias.it[NeurRow][0];
			}

		}


		for (int inR = 0; inR < inN; inR++) {
			for (int nexR = 0; nexR < layers[0].height; nexR++) {
				Input.DerWei.it[nexR][inR] = weiDer( -1, inR, nexR, outRow);
				Input.wei.it[nexR][inR] += -2 * learnRate * cost * Input.DerWei.it[nexR][inR];
			}
		}

	}
}

void Network::Export(double learnRate) {
	string path = "C:/Users/Michael/Documents/Basic/Visual Studio/Exports/Neural Nets/export_";
	toStr(path, layers[0].height, 0);
	path = path + "x";
	toStr(path, depth, 0);
	path += "...";
	toStr(path, learnRate, 4);
	path += "_";
	fstream file;
	string line = "";
	int key = 0;




	while (key == 0) {
		file.open(path + ".txt", ios::in);
		if (file.good()) {
			path += "(";
			path += (char)(rand() % 10 + (int)'0');
			path += ")";
			file.close();
		}
		else {
			file.open(path + ".txt", ios::out);
			key = 1;
		}

	}

	line += " inN = ";
	toStr(line, inN, 0);
	line += ";\n outN = ";
	toStr(line, outN, 0);
	//line += "\n Height = ";
	//toStr(line, layers[0].height,0);
	line += ";\n depth = ";
	toStr(line, depth, 0);
	file << line;
	line = "";
	line += ";\n heights = {";
	for (int i = 0; i < depth; i++) {
		toStr(line, layers[i].height, 0);
		if (i < depth - 1)
			line += ",";
		else line += " ";
	}
	line += "}";
	line += ";\n\n// learnRate = ";
	toStr(line, learnRate, 5);
	line += ";\n\n";

	line += "** input weights;\n\n";
	file << line;
	line = "";
	for (int next = 0; next < layers[0].height; next++) {
		for (int inN = 0; inN < inN; inN++) {
			toStr(line, Input.wei[next][inN], 5);
			line += " ";
		}
		line += ";\n";
		file << line;
		line = "";
	}
	file << "\n\n";
	line = "";
	for (int L = 0; L < depth; L++) {
		line += "** ";
		toStr(line, L, 0);
		line += " layer weights;\n // height =";
		toStr(line, layers[L].height, 0);
		line += ";\n\n";
		file << line;
		line = "";
		for (int next = 0; next < layers[L].wei.getRow(); next++) {
			for (int dis = 0; dis < layers[L].wei.getCol(); dis++) {
				toStr(line, layers[L].wei[next][dis], 5);
				line += " ";
				file << line;
				line = "";
			}
			line += ";\n";
			file << line;
			line = "";
		}
		line += "\n**bias;\n\n";
		file << line;
		line = "";
		for (int i = 0; i < layers[L].height; i++) {
			toStr(line, layers[L].bias[i][0], 5);
			line += " ";
		}
		line += ";\n\n\n\n";
		file << line;
		line = "";
	}






	file.close();

}
void Network::Export() {
	string path = "C:/Users/Michael/Documents/Basic/Visual Studio/Exports/Neural Nets/export_";
	toStr(path, layers[0].height, 0);
	path = path + "x";
	toStr(path, depth, 0);
	path += "_";
	fstream file;
	string line = "";
	int key = 0;




	while (key == 0) {
		file.open(path + ".txt", ios::in);
		if (file.good()) {
			path += "(";
			path += (char)(rand() % 10 + (int)'0');
			path += ")";
			file.close();
		}
		else {
			file.open(path + ".txt", ios::out);
			key = 1;
		}

	}

	line += " inN = ";
	toStr(line, inN, 0);
	line += ";\n outN = ";
	toStr(line, outN, 0);
	//line += "\n Height = ";
	//toStr(line, layers[0].height,0);
	line += ";\n depth = ";
	toStr(line, depth, 0);
	file << line;
	line = "";
	line += ";\n heights = {";
	for (int i = 0; i < depth; i++) {
		toStr(line, layers[i].height, 0);
		if (i < depth - 1)
			line += ",";
		else line += " ";
	}
	line += "}";
	
	line += ";\n\n";

	line += "** input weights;\n\n";
	file << line;
	line = "";
	for (int next = 0; next < layers[0].height; next++) {
		for (int inN = 0; inN < inN; inN++) {
			toStr(line, Input.wei[next][inN], 5);
			line += " ";
		}
		line += ";\n";
		file << line;
		line = "";
	}
	file << "\n\n";
	line = "";
	for (int L = 0; L < depth; L++) {
		line += "** ";
		toStr(line, L, 0);
		line += " layer weights;\n // height =";
		toStr(line, layers[L].height, 0);
		line += ";\n\n";
		file << line;
		line = "";
		for (int next = 0; next < layers[L].wei.getRow(); next++) {
			for (int dis = 0; dis < layers[L].wei.getCol(); dis++) {
				toStr(line, layers[L].wei[next][dis], 5);
				line += " ";
				file << line;
				line = "";
			}
			line += ";\n";
			file << line;
			line = "";
		}
		line += "\n**bias;\n\n";
		file << line;
		line = "";
		for (int i = 0; i < layers[L].height; i++) {
			toStr(line, layers[L].bias[i][0], 5);
			line += " ";
		}
		line += ";\n\n\n\n";
		file << line;
		line = "";
	}






	file.close();

}

void Network::Import(string path) {//replaces values of the layers in the already created Network
	ifstream file;
	string temp;
	char buff[256];
	int iLi = -1, ich = 0, len = 0, ich_1 = 0, L = 0, row = 0, col = 0;
	int endKey = 0;
	int input_switch = 0, heights_count = 0;
	double val;
	int* heights = new int[1];
	Layer* Lay;
	file.open(path, ios::in);
	if (!file) {
		cout << "Failed to open the desired network export file.\n";
		return;
	}

	while (getline(file, temp))   //reading file line by line, skipping the empty ones
	{
		if (temp != "\n" && temp != "" && temp != " ") { //the skipper of blank lines
			iLi++;

		}
		else continue;


		if (iLi == 3) {//if reading the heights array --  create array
			heights = new int[depth + 1];
			heights[depth] = outN;
		}


		//endKey = 0; not here
		for (ich = 0; ich < temp.length(); ich++) { //examining the line

			if (temp[ich] == '/' && temp[ich + 1] == '/') {//break upon slashes
				iLi--;
				break;

			}

			len = 0;

			if (iLi >= 4) { //if reading the matrix section
				if (temp[ich] == '*' && temp[ich + 1] == '*') {
					input_switch++;
					if (input_switch == 1) {//first stars are for input weights

						Lay = new Layer(inN, heights[0]);
						Input = *Lay;
						//delete layers;
						layers = new Layer[depth];

					}
					if (input_switch % 2 == 0) {//every even stars should create new layer

						Lay = new Layer(heights[L], heights[L + 1]);
						layers[L] = *Lay;
						L++;
						row = 0;//reset the coordinates of the cursor
						col = 0;
					}
					if (input_switch % 2 == 1) {
						row = 0;
						col = 0;
					}
					break;
				}
				if (input_switch == 1) {//reading input layer stuff

					if ((temp[ich] >= '0' && temp[ich] <= '9') || temp[ich] == '-') {//if any part of a double

						len = 0;
						ich_1 = ich;

						while ((temp[ich_1] >= '0' && temp[ich_1] <= '9') || temp[ich_1] == '-' || temp[ich_1] == '.') {
							buff[len] = temp[ich_1];
							len++;
							ich_1++;
						}
						ich = ich_1;
						Input.wei[row][col] = toDb(buff, len);
						col++;

					}
					if (temp[ich] == ';') {
						row++;
						col = 0;
						endKey = 1;
						break;
					}

				}


				else if (input_switch % 2 == 0) {//filling up weights matrix

					if ((temp[ich] >= '0' && temp[ich] <= '9') || temp[ich] == '-') {
						len = 0;
						ich_1 = ich;

						while ((temp[ich_1] >= '0' && temp[ich_1] <= '9') || temp[ich_1] == '-' || temp[ich_1] == '.') {
							buff[len] = temp[ich_1];
							len++;
							ich_1++;
						}
						ich = ich_1;
						layers[L - 1].wei[row][col] = toDb(buff, len);
						col++;

					}
					if (temp[ich] == ';') {
						row++;
						col = 0;
						endKey = 1;
						break;
					}
				}


				else if (input_switch % 2 == 1) {//filling up biases matrix

					if ((temp[ich] >= '0' && temp[ich] <= '9') || temp[ich] == '-') {
						len = 0;
						ich_1 = ich;

						while ((temp[ich_1] >= '0' && temp[ich_1] <= '9') || temp[ich_1] == '-' || temp[ich_1] == '.') {
							buff[len] = temp[ich_1];
							len++;
							ich_1++;
						}
						ich = ich_1;
						layers[L - 1].bias[row][0] = toDb(buff, len);
						row++;

					}
					if (temp[ich] == ';') {
						row = 0;
						col = 0;
						endKey = 1;
						break;
					}

				}
			}









			else { //if reading the general info section
				if (iLi == 3) {//if reading the heights array
					if (temp[ich] >= '0' && temp[ich] <= '9') {
						len = 0;
						ich_1 = ich;

						while (temp[ich_1] >= '0' && temp[ich_1] <= '9') {
							buff[len] = temp[ich_1];
							len++;
							ich_1++;
						}
						ich = ich_1;
						heights[heights_count] = toDb(buff, len);
						heights_count++;
					}
				}
				else {//if NOT heights array
					if (temp[ich] >= '0' && temp[ich] <= '9') {

						len = 0;
						ich_1 = ich;

						while (temp[ich_1] >= '0' && temp[ich_1] <= '9') {
							buff[len] = temp[ich_1];
							len++;
							ich_1++;
						}
						ich = ich_1;
						val = toDb(buff, len);

						switch (iLi) {//based on the line put the value into:

						case 0:
							inN = val;
							break;
						case 1:
							outN = val;
							break;
						case 2:
							depth = val;
							break;
						}
					}
				}
			}


		}

	}
	file.close();
}



/////////////////////
///
//Support Functions
///
/////////////////////


//For Back Propagation

double Sum(matrix A) { //used to minimise code when summing the derivatives of the previous layer to the right
	double a = 0;
	for (int i = 0; i < A.row; i++) {
		for (int k = 0; k < A.col; k++) {
			a += A.it[i][k];
		}
	}
	return a;
}


double DS(double a) {
	return a - a * a;
}


double weiDer(Network Net, int L, int fr, int to, int OutLayer) { //calculate the wei der in the L layer connection from "fr" to "to" neuron. Weight belong to layer to the left 
	double S=0;
	if (Net.depth - L > 2) {
		for (int i = 0; i < Net.N[L+2].height; i++) {
			S += Net.N[L + 1].wei.it[i][to] * Net.N[L + 1].DerWei.it[i][to] * DS(Net.N[L + 2].val.it[i][0]);
		}
	}
	else {
		
			S += Net.N[L + 1].wei.it[OutLayer][to]  * Net.N[L + 1].DerWei.it[OutLayer][to] * DS(Net.Output.it[OutLayer][0]);
		
	}

	if (L!=-1) {
		S = S * (1-Net.N[L + 1].val.it[to][0]) * Net.N[L].val.it[fr][0];
	}
	else {
		S = S * (1-Net.N[L + 1].val.it[to][0]) * Net.Input.val.it[fr][0];
	}
	return S;
}


//For Export/Import

void toStr(string& X, double a, int precision) {

	int spaces = 0;
	if (a < 0) {
		X += "-";
		a = abs(a);
	}
	else X += " ";
	int len;
	if (a == 0) {
		len = 1;
	}
	else len = log10(a) + 1;
	int temp;

	if (a >= 1) {
		for (len; len > 0; len--) {
			temp = (int)a;
			for (int i = 0; i < len - 1; i++) {
				temp /= 10;
			}
			X += (char)(temp + '0');
			a -= temp * pow(10, len - 1);
		}
	}
	else X += '0';


	if (a == floor(a)) {
		for (spaces = 0; spaces < precision; spaces++) {
			X += " ";
		}
		return;
	}
	else {
		len = precision;
		X += '.';
		a = round((a - (int)a) * pow(10, precision));

		for (int i = precision - 1; i > 0; i--) {
			if ((int)a % (int)pow(10, i) == 0) {
				a /= pow(10, i);
				len = precision - i;
				spaces = i;

			}
		}

		for (len; len > 0; len--) {
			temp = (int)a;
			for (int i = 0; i < len - 1; i++) {
				temp /= 10;
			}
			X += (char)(temp + '0');
			a -= temp * pow(10, len - 1);
		}
		for (int i = 0; i < spaces; i++) {
			X += " ";
		}
	}

}
string toStr (double a, int precision) {
	string X="";
	int spaces = 0;
	if (a < 0) {
		X += "-";
		a = abs(a);
	}
	else X += " ";
	int len;
	if (a == 0) {
		len = 1;
	}
	else len = log10(a) + 1;
	int temp;

	if (a >= 1) {
		for (len; len > 0; len--) {
			temp = (int)a;
			for (int i = 0; i < len - 1; i++) {
				temp /= 10;
			}
			X += (char)(temp + '0');
			a -= temp * pow(10, len - 1);
		}
	}
	else X += '0';


	if (a == floor(a)) {
		for (spaces = 0; spaces < precision; spaces++) {
			X += " ";
		}
		return X;
	}
	else {
		len = precision;
		X += '.';
		a = round((a - (int)a) * pow(10, precision));

		for (int i = precision - 1; i > 0; i--) {
			if ((int)a % (int)pow(10, i) == 0) {
				a /= pow(10, i);
				len = precision - i;
				spaces = i;

			}
		}

		for (len; len > 0; len--) {
			temp = (int)a;
			for (int i = 0; i < len - 1; i++) {
				temp /= 10;
			}
			X += (char)(temp + '0');
			a -= temp * pow(10, len - 1);
		}
		for (int i = 0; i < spaces; i++) {
			X += " ";
		}
	}
	return X;
}

double toDb(char num[], int len) {

	double a = 0;
	int sw = -1;
	

	for (int i = 0; i < len; i++) {
		if (num[i] == '.') {
			sw = i;
			break;
		}
	}
	if (num[0] != '-') {
		if (sw == -1) {
			for (int i = 0; i < len; i++) {
				a += pow(10, len - i - 1) * ((int)num[i] - '0');
			}
			return a;
		}
		else {
			for (int i = 0; i < sw; i++) {
				a += pow(10, sw - i - 1) * ((int)num[i] - '0');
			}
			for (int i = sw + 1; i < len; i++) {
				a += (int)(num[i] - '0') * pow(10, sw - i);
			}
			return a;
		}
	}
	else {
		if (sw == -1) {
			for (int i = 1; i < len; i++) {
				a += pow(10, len - i - 1) * ((int)num[i] - '0');
			}
			return -a;
		}
		else {
			for (int i = 1; i < sw; i++) {
				a += pow(10, sw - i - 1) * ((int)num[i] - '0');
			}
			for (int i = sw + 1; i < len; i++) {
				a += (int)(num[i] - '0') * pow(10, sw - i);
			}
			return -a;
		}
	}

	

}




