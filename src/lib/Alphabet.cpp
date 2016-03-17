#include "../include/Alphabet.h"
#include "../include/Letter.h"
#include <string>
#include <vector>
#include <ctype.h>

Alphabet::Alphabet() {
	initAlphabet();
}
#include <iostream>
Alphabet::Alphabet(std::ifstream& file){
	int width,height;
	file>>width;
	file>>height;

	default_width=width;
	default_height=height;
	
	int n;
	file>>n;
	for (int i=0;i<n;i++){
		char c;
		file>>c;
		std::cout<<"reading Alphabet "<<c<<std::endl;

		int numBidang;
		file>>numBidang;

		vector<Polygon> bidang(numBidang);
		for (int j=0;j<numBidang;j++){
			int numPoint;
			file>>numPoint;
			for (int k=0;k<numPoint;k++){
				int x,y;
				file>>x;
				file>>y;

				bidang[j].push_back(x,y);
			}
		}
		

		int numLubang;
		file >> numLubang;

		vector<Polygon> lubang(numLubang);
		for (int j=0;j<numLubang;j++){
			int numPoint;
			file>>numPoint;
			for (int k=0;k<numPoint;k++){
				int x,y;
				file>>x;
				file>>y;

				lubang[j].push_back(x,y);
			}
		}
		
		Letter l(bidang, lubang, width,height);
		Letters[c]=l;

		PixelBoolMatrix pbm = l.toPixelBoolMatrix();
		for (int _y=0;_y<pbm.getHeight();_y++){
			for (int _x=0;_x<pbm.getWidth();_x++){
				std::cout<<pbm.get(_x,_y);
			}
			std::cout<<std::endl;
		}
	}
	//tambah karakter blank (spasi)
	std::vector<Polygon> bidangnul(0);
	std::vector<Polygon> lubangnul(0);
	Letter ll(bidangnul, lubangnul, width, height);
	Letters[' ']=ll;
}

void Alphabet::initAlphabet() {
	//baca Alphabet.txt dan isi array Alphabet
}

Letter Alphabet::getLetter(char c) {
	return Letters[c];
}
int Alphabet::calculateOneCharSpace(float size){
	return (default_width+5)*size;
}

void Alphabet::drawChar(char a, int X, int Y, float size, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha){
	PixelBoolMatrix pbm = getLetter(a).toPixelBoolMatrix(size);
	pbm.draw(X,Y,R,G,B,alpha);
}

void Alphabet::drawText(std::string a, int X, int Y, float size, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha){
	int onecharspace = calculateOneCharSpace(size);
	for (int i=0;i<a.length();i++){
		drawChar(a[i],X+onecharspace*i,Y,size,R,G,B,alpha);
	}
}

void Alphabet::drawTextCentered(std::string a, int Y, float size, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha){
	int onecharspace = calculateOneCharSpace(size);
	int X = (Printer::getXRes()-a.length()*onecharspace)/2;
	drawText(a,X,Y,size,R,G,B,alpha);
    
}
