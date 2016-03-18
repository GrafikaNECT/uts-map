//includes
#include <iostream>
#include <fstream>

#include "../include/Printer.h"
#include "../include/Point.h"
#include "../include/Image.h"
#include "../include/SistemWindowView.h"
#include "../include/Kbhit.h"
#include "../include/GIS2D.h"
#include "../include/SolidPolygon.h"
#include "../include/Line.h"

#define MARGIN 100
#define DEFAULTWINDOWWIDTH 400
#define BOTTOMTEXTSPACE 200

//warnawarna
#define VIEWCANVASTEXTURE Texture::createSingleColorTexture(0,0,0,255)
#define BGTEXTURE Texture::createSingleColorTexture(100,100,100,255)

using std::endl;
using std::cerr;

//kbhit untuk kontrol?

int main(int argc, char *argv[] ){
	//cek argumen
	//buka dua buah ifstream dari nama file yang disuplai di argc argv
	//itu untuk gambar dan tekstur
	Image i;
	if (argc==2){
		std::ifstream f(argv[1]);
		i = Image::fromStreamFormatMap(f);
	}else if (argc==3){
		std::ifstream fgambar(argv[1]);
		std::ifstream ftekstur(argv[2]);
		i = Image::fromStream(fgambar,ftekstur);
	}else{
		cerr<<"usage:\
			./main <file dengan format map Candy dan Tifani - tanya Candy dan Tifani>\
			./main <file Gambar> <file Tekstur>"<<endl;
	}

	//inisialisasi printer
	Printer::initializePrinter();

	GIS2D gis2D;
	gis2D.add(i);

	//looping menerima kontrol untuk pan dan zoom serta menggambar
	//jangan lupa ada kontrol untuk quit
	gis2D.draw();
	Printer::printToScreen();
	bool cont=true;
	char c;
	Kbhit::initTermios();
	while (cont)
	if (Kbhit::kbhit())
	{
		c=Kbhit::getch();
		if (c<='9' && c>='0'){
			int layerNum=c-'0';
			gis2D.toggleLayer(layerNum);
		}else
		switch(c){
		case 'w':
			gis2D.pan("up");
		break;
		case 's':
			gis2D.pan("down");
		break;
		case 'a':
			gis2D.pan("left");
		break;
		case 'd':
			gis2D.pan("right");
		break;
		case 'z':
			gis2D.zoom("in");
		break;
		case 'x':
			gis2D.zoom("out");
		break;
		case 'q':
			cont=false;
		break;
		default:
			cerr<<"No action bound for key '"<<c<<"'"<<endl;
		break;
		}
		gis2D.draw();
		Printer::printToScreen();
	}

	Kbhit::resetTermios();
	//quit
	Printer::finishPrinter();
}
