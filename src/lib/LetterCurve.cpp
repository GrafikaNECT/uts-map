#include "../include/LetterCurve.h"
#include "../include/CurveShape.h"
#include <vector>

using namespace std;

LetterCurve::LetterCurve(vector<CurveShape> _bidang) {
	bidang = _bidang;
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