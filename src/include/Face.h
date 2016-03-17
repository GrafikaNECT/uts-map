#ifndef Face_h
#define Face_h

#include "CurveCollection.h"

class Face{
	public:
	//definisikan konstruktor dan kopi konstruktor di sini



	//..........
	//methods
	//buat getter dan setter
	//..........

	//method-method utama
	void smile();
	void unsmile();

	void bukamata();
	void tutupmata();
	void ngintipmata();


	void draw();

	private:
	CurveCollection matamerem;
	CurveCollection matangintip;
	CurveCollection matabuka;

	enum {merem,ngintip,buka} statusmata;

	CurveCollection mulutbiasa;
	CurveCollection mulutsenyum;
	CurveCollection dagubiasa;
	CurveCollection dagusenyum;

	bool sedangTersenyum;

	CurveCollection lainlain;//rambut, frame wajah, telinga, dll.
};

#endif
