#ifndef Alphabet_h
#define Alphabet_h

#include "CurveCollection.h"
#include <map>

#include <string>

#include <fstream>

class Alphabet {
	public:
	Alphabet();
	Alphabet(std::ifstream& file);
	void initAlphabet();
	Letter getLetter(char c);

	void drawChar(char a, int X, int Y, float scale);
	void drawText(std::string a, int X, int Y, float scale);
	void drawTextCentered(std::string a, int Y, float scale);

	protected:
	std::map<char, CurveCollection> Letters;
	int default_width,default_height;

	int calculateOneCharSpace(float size);
};

#endif
