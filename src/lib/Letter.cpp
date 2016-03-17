#include "../include/Letter.h"
#include "../include/Polygon.h"
#include "../include/PixelBoolMatrix.h"
#include <vector>

using namespace std;

Letter::Letter(vector<Polygon> _bidang, vector<Polygon> _lubang, int _width, int _height) {
	bidang = _bidang;
	lubang = _lubang;
	width = _width;
	height = _height;
}

/*
void Letter::draw() {
	for (vector<Polygon>::iterator i=bidang.begin(); i!=bidang.end();i++) {
		Lettermatrix.setSolid(*i,true);
	}
	
	for (vector<Polygon>::iterator i=lubang.begin(); i!=lubang.end();i++) {
		Lettermatrix.setSolid(*i,false);
	}
}
*/
#define padding_size 3
PixelBoolMatrix Letter::toPixelBoolMatrix(float resize){
	int matwidth = (width+padding_size) * resize;
	int matheight = (height+padding_size) * resize;
	PixelBoolMatrix Lettermatrix(matwidth,matheight);
	Lettermatrix.setAll(false);
	for (vector<Polygon>::iterator i=bidang.begin(); i!=bidang.end();i++) {
		Polygon p = i->hasilPerbesar(resize);
		Lettermatrix.setSolid(p,true);
	}
	for (vector<Polygon>::iterator i=lubang.begin(); i!=lubang.end();i++) {
		Polygon p = i->hasilPerbesar(resize);
		Lettermatrix.setSolid(p,false);
	}
	return Lettermatrix;
}
