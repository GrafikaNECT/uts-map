#ifndef Letter_Curve_h
#define Letter_Curve_h

#include "CurveShape.h"
#include <vector>

using namespace std;

class LetterCurve {
	public:
	LetterCurve(){};
	LetterCurve(vector<CurveShape> bidang);
	//~Letter();

	protected:
	vector<CurveShape> bidang;
	// di sini tidak ada lagi width dan height karena telah ditentukan dari awal: size = 200x300.
	// nanti untuk perbesaran dan perkecilan menggunakan scale.
};

#endif
