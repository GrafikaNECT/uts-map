#ifndef Alphabet_h
#define Alphabet_h

#include "Letter.h"
#include <map>

#include <string>

#include <fstream>

class Alphabet {
	public:
	Alphabet();
	Alphabet(std::ifstream& file);
	void initAlphabet();
	Letter getLetter(char c);

	void drawChar(char a, int X, int Y, float size, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);
	void drawText(std::string a, int X, int Y, float size, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);
	void drawTextCentered(std::string a, int Y, float size, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);

	protected:
	std::map<char, Letter> Letters;
	int default_width,default_height;

	int calculateOneCharSpace(float size);
};

#endif
