#include <iostream>
#include <cmath>
#include <iomanip>
#include "Matrix.h"
#include "Linear Algebra 3d.h"
#include <fstream>
#include <string>
#include "Hammer VMF.h"

using namespace std;

 int rnd = 5;
 int fixd = 50;


string toStr(double a, int precision) {
	string X = "";
	int spaces = 0;
	if (a < 0) {
		X += "-";
		a = abs(a);
	}
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
		
	}
	return X;
}



void vectToStr(string& L, const vect& x) {
	L += toStr(x.it[0], 5) + " " + toStr(x.it[1], 5) + " " + toStr(x.it[2], 5);

}












vect** SetPlanes(int& N, vect& origin) {

	int conf_key = 0;
	if (N < 30) {
		N += 6;
		conf_key = 6;
	}
	vect initializer;
	vect* normal=new vect[N];
	
	
	vect** planes = new vect * [N];
	
	vect a(origin);
	vect b(origin);
	vect c(origin);


	int radius;


	for (int i = 0; i < N-conf_key; i++) {
		normal[i] = initializer.randomize(1);
															//			normal[i].printVect();
	}

	if (conf_key > 0) {

		normal[N - conf_key] = initializer.randomize(1);
		normal[N - conf_key+1] = (normal[N - conf_key].vectMult(initializer.randomize(1))).ort();
		normal[N - conf_key + 2] = (normal[N - conf_key].vectMult(normal[N - conf_key + 1])).ort();
		for (int i = 3; i < 6; i++) {
			normal[N-conf_key+i]=-normal[N-conf_key+i-3];
		}


	}

	for (int i = 0; i < N; i++) {
		radius = rand() % rnd + fixd;
		if (i > N - 7) {
			radius = rnd + fixd;
		}
	  /*a.it[0] = floor(radius / normal[i].it[0]);
		b.it[1] = floor(radius / normal[i].it[1]);
		c.it[2] = floor(radius / normal[i].it[2]);*/

		a.it[0] = origin.it[0] + radius / normal[i].it[0];
		b.it[1] = origin.it[1] + radius / normal[i].it[1];
		c.it[2] = origin.it[2] + radius / normal[i].it[2];
		if (normal[i].scalMult((a - c).vectMult(b - c)) < 0) {
			planes[i] = new vect[3];
			planes[i][0] = a;
			planes[i][1] = b;
			planes[i][2] = c;

		}
		else {
			planes[i] = new vect[3];
			planes[i][0] = b;
			planes[i][1] = a;
			planes[i][2] = c;
		}
	}

	
	return planes;

}

void CreateVMF(int N, int M){

	
	int TEMP_sides=N;
	string path = "C:/Users/Michael/Documents/Basic/Visual Studio/Custom Files/map_" + toStr(N, 0)+"."+toStr(M,0);

	fstream file;
	string line = "";

	int key_file_create = 0;
	int sides_id = 1;
	
	vect** planes; //prepared planes
	vect* origins = new vect[M];
	vect initializer;
	
	for (int i = 0; i < M; i++) {
		origins[i] = initializer.randomize(rand()%10000+100+2*sqrt(3)*(rnd+fixd)+N);
	}

	

	//FILE OUTPUT BLOCK
	while (key_file_create == 0) {
		file.open(path + ".vmf", ios::in);
		if (file.good()) {
			path += "(";
			path += (char)(rand() % 10 + (int)'0');
			path += ")";
			file.close();
		}
		else {
			file.open(path + ".vmf", ios::out);
			key_file_create = 1;
		}

	}

	line = "versioninfo\n{ \n\t\"editorversion\" \"400\"\n\t\"editorbuild\" \"8419\"\n\t\"mapversion\" \"3\"\n\t\"formatversion\" \"100\"\n\t\"prefab\" \"0\"\n}\nvisgroups\n{\n}\nviewsettings\n{\n\t\"bSnapToGrid\" \"1\"\n\t\"bShowGrid\" \"1\"\n\t\"bShowLogicalGrid\" \"0\"\n\t\"nGridSpacing\" \"8\"\n\t\"bShow3DGrid\" \"0\"\n}\nworld\n{\n\t\"id\" \"1\"\n\t\"mapversion\" \"3\"\n\t\"classname\" \"worldspawn\"\n\t\"detailmaterial\" \"detail/detailsprites\"\n\t\"detailvbsp\" \"detail.vbsp\"\n\t\"maxblobcount\" \"250\"\n\t\"maxpropscreenwidth\" \"-1\"\n\t\"skyname\" \"sky_black_nofog\"\n";
	file << line;
	line = "";

	for (int solid = 0; solid < M; solid++) {
		line = "solid\n{\n\"id\" \"" + toStr(solid + 2, 0) + "\"\n";
		file << line;
		line = "";
		TEMP_sides = N;
		planes = SetPlanes(TEMP_sides,origins[solid]);
		for (int side = 0; side < TEMP_sides; side++) {

			line += "\t\tside\n\t\t{\n\t\t\t\"id\" \"" + toStr(sides_id, 0) + "\"\n\t\t\t\"plane\" \"";
			for (int i = 0; i < 3; i++) {
				line += "(";
				vectToStr(line, planes[side][i]);
				line += ") ";
			}
			line += "\"\n\t\t\t\"material\" \"ANIM_WP/FRAMEWORK/BACKPANELS\"\n\t\t\t\"uaxis\" \"[1 0 0 -256] 0.25\"\n\t\t\t\"vaxis\" \"[0 -1 0 0] 0.25\"\n\t\t\t\"rotation\" \"0\"\n\t\t\t\"lightmapscale\" \"16\"\n\t\t\t\"smoothing_groups\" \"0\"\n\t\t}\n";
			file << line;
			line = "";
			sides_id++;

		}
		
		line = "editor\n\t\t{\n\t\t\t\"color\" \"0 182 159\"\n\t\t\t\"visgroupshown\" \"1\"\n\t\t\t\"visgroupautoshown\" \"1\"\n\t\t}\n\t}\n";
		file << line;
		line = "";
	}
	line = "}\ncameras\n{\n\t\"activecamera\" \"-1\"\n}\ncordons\n{\n\t\"active\" \"0\"\n}\n";
	file << line;
	line = "";
	file.close();
}