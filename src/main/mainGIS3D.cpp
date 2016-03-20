#include <fstream>

#include "../include/GIS3D.h"

#include "../include/Printer.h"
#include "../include/Kbhit.h"

void drawAllCanvas(){
	Printer::drawCanvas(100,100,100,255);
}
#include "../include/AlphabetCurve.h"
int main(){
	//load file-file
	std::ifstream fileLaut("assets/indonesia_map_elements_3d/Laut.txt");
	std::ifstream filePulau("assets/indonesia_map_elements_3d/Pulau.txt");
	std::ifstream fileKontur("assets/indonesia_map_elements_3d/Kontur.txt");

	//inisialisasi printer
	Printer::initializePrinter();

	//test

	static std::ifstream textFile("assets/fonts/Alphabet.txt");
	static AlphabetCurve text(textFile);
	text.drawTextCentered("INDONESIA",30,0.2,Texture::createSingleColorTexture(255,0,0,255));

	GIS3D gis3D;
	gis3D.add(Model3D::fromStreamFormatMap(fileLaut));
	gis3D.add(Model3D::fromStreamFormatMap(filePulau));
	gis3D.add(Model3D::fromStreamFormatMap(fileKontur));
	gis3D.parseWeatherInformation();

	//looping menerima kontrol untuk pan dan zoom serta menggambar
	//jangan lupa ada kontrol untuk quit

	drawAllCanvas();
	gis3D.draw();
	Printer::printToScreen();
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
			gis3D.toggleLayer(layerNum);
		}else
		switch(c){
		case 'c':
			gis3D.toggleWeather();
		break;
		case 'n':
			gis3D.toggleCityName();
		break;
		case 'w':
			gis3D.pan("up");
		break;
		case 's':
			gis3D.pan("down");
		break;
		case 'a':
			gis3D.pan("left");
		break;
		case 'd':
			gis3D.pan("right");
		break;
		case 'z':
			gis3D.zoom("in");
		break;
		case 'x':
			gis3D.zoom("out");
		break;
		case 'r':
			gis3D.rotate("zMin");
		break;
		case 'y':
			gis3D.rotate("zPlus");
		break;
		case 't':
			gis3D.rotate("xMin");
		break;
		case 'g':
			gis3D.rotate("xPlus");
		break;
		case 'f':
			gis3D.rotate("yMin");
		break;
		case 'h':
			gis3D.rotate("yPlus");
		break;
		case 'q':
			cont=false;
		break;
		default:
			cerr<<"No action bound for key '"<<c<<"'"<<endl;
		break;
		}
		drawAllCanvas();
		gis3D.draw();
		text.drawTextCentered("INDONESIA",30,0.2,Texture::createSingleColorTexture(255,0,0,255));
		Printer::printToScreen();
	}

	Kbhit::resetTermios();
	//quit
	Printer::finishPrinter();
}
