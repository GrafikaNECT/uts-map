#include "../include/AlphabetCurve.h"
#include "../include/CurveCollection.h"
#include "../include/Printer.h"
#include "../include/Texture.h"
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
		Letters[c] = CurveCollection("assets/fonts/"+letterfile);
	}
}

CurveCollection AlphabetCurve::getLetter(char c) {
	return Letters[std::toupper(c)];
}
int AlphabetCurve::calculateOneCharSpace(float size){
	return default_width*size;
}

void AlphabetCurve::drawChar(char a, int X, int Y, float scale, Texture texture){
	CurveCollection letter = getLetter(a);
	letter.setTexture(texture);
	letter.scaleResult(scale).moveResult(X,Y).draw();
}

void AlphabetCurve::drawText(std::string a, int X, int Y, float scale, Texture texture){
	int onecharspace = calculateOneCharSpace(scale);
	for (int i=0;i<a.length();i++){
		if (a[i]!=' ') {
			drawChar(a[i],X+onecharspace*i,Y,scale,texture);
		}
	}
}

void AlphabetCurve::drawTextCentered(std::string a, int Y, float scale, Texture texture){
	int onecharspace = calculateOneCharSpace(scale);
	int X = (Printer::getXRes()-a.length()*onecharspace)/2;
	drawText(a,X,Y,scale,texture);
    
}
