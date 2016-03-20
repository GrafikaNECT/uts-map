#include "../include/AlphabetCurveCurve.h"
#include "../include/CurveCollection.h"
#include <string>
#include <vector>
#include <ctype.h>

#include <iostream>
AlphabetCurve::AlphabetCurve(std::ifstream& file){
	int width,height;
	file>>width;
	file>>height;

	default_width=width;
	default_height=height;

	int n;
	file>>n;
	for (int i=0;i<n;i++) {
		char c;
		file>>c;
		string letterfile;
		file>>letterfile;
		Letters[c] = CurveCollection(letterfile);
	}

	//tambah karakter blank (spasi)
	/*std::vector<Polygon> bidangnul(0);
	std::vector<Polygon> lubangnul(0);
	Letter ll(bidangnul, lubangnul, width, height);
	Letters[' ']=ll;*/
}

CurveCollection AlphabetCurve::getLetter(char c) {
	return Letters[c];
}
int AlphabetCurve::calculateOneCharSpace(float size){
	return (default_width+5)*size;
}

void AlphabetCurve::drawChar(char a, int X, int Y, float scale){
	getLetter(a).move(X,Y).scale(scale).draw();
}

void AlphabetCurve::drawText(std::string a, int X, int Y, float scale){
	int onecharspace = calculateOneCharSpace(scale);
	for (int i=0;i<a.length();i++){
		drawChar(a[i],X+onecharspace*i,Y);
	}
}

void AlphabetCurve::drawTextCentered(std::string a, int Y, float scale){
	int onecharspace = calculateOneCharSpace(scale);
	int X = (Printer::getXRes()-a.length()*onecharspace)/2;
	drawText(a,X,Y,scale);
    
}
