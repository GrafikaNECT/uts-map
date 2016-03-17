#ifndef Letter_h
#define Letter_h

#include "Polygon.h"
#include "PixelBoolMatrix.h"
#include <vector>

using namespace std;

class Letter {
	public:
	Letter(){};
	Letter(vector<Polygon> bidang, vector<Polygon> lubang, int width, int height);
	//~Letter();

	//mengubah ke PixelBoolMatrix
	//bila resize lebih dari 1, yang didapat adalah PixelBoolMatrix yang diperbesar
	PixelBoolMatrix toPixelBoolMatrix(float resize = 1);

	protected:
	vector<Polygon> bidang;
	vector<Polygon> lubang;
	int width;
	int height;
};

#endif
