#include "../include/AlphabetCurve.h"
#include "../include/Printer.h"
#include "../include/Texture.h"
#include <iostream>
int main() {
	Printer::initializePrinter();
	Printer::drawCanvas(255,255,255,255);
	std::ifstream fileAlphabet("../assets/fonts/Alphabet.txt");
	AlphabetCurve alphabet(fileAlphabet);
	alphabet.drawTextCentered("A B C DEF",100,0.1,Texture::createSingleColorTexture(0,0,255,255));
	Printer::printToScreen();
	Printer::finishPrinter();
	return 0;
}