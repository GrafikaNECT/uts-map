#ifndef AlphabetCurve_h
#define AlphabetCurve_h

#include "CurveCollection.h"
#include <map>

#include <string>

#include <fstream>

class AlphabetCurve {
	public:
	AlphabetCurve(std::ifstream& file);
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
