//includes
#include <iostream>
#include <fstream>

#include "../include/Curve.h"
#include "../include/CurveShape.h"
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


int main(int argc, char *argv[] ){
	//inisialisasi printer
	Printer::initializePrinter();

	Printer::drawCanvas(255,255,255,255);

	// Curve curve = Curve("testcurve.txt");
	CurveShape curve = CurveShape("testcurveshape.txt");
	curve.draw();

	Printer::printToScreen();
	bool cont=true;
	char c;
	Kbhit::initTermios();
	while (cont)
	if (Kbhit::kbhit())
	{
		c=Kbhit::getch();
		switch(c){
			case 'w':
				curve.move(0,-10);
			break;
			case 's':
				curve.move(0,10);
			break;
			case 'a':
				curve.move(-10,0);
			break;
			case 'd':
				curve.move(10,0);
			break;
			case 'z':
				curve.scale(2);
			break;
			case 'x':
				curve.scale(0.5);
			break;
			case 'f':
				curve.rotate(2);
			break;
			case 'h':
				curve.rotate(-2);
			break;
			case 'q':
				cont=false;
			break;
			default:
				cerr<<"No action bound for key '"<<c<<"'"<<endl;
			break;
		}
		Printer::drawCanvas(255,255,255,255);
		curve.draw();
		Printer::printToScreen();
	}

	Kbhit::resetTermios();
	//quit
	Printer::finishPrinter();
}
