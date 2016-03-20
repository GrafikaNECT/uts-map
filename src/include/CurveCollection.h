#ifndef CurveCollection_h
#define CurveCollection_h

#include "Curve.h"
#include "CurveShape.h"
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class CurveCollection{
	public:
	CurveCollection(std::string fileName);
	CurveCollection():numElmts(0){};

	//menambah Curve
	//perhatikan orderGambar (spek di bawah)
	void addCurve(Curve c);

	//menambah CurveShape
	//perhatikan orderGambar (spek di bawah)
	void addCurveShape(CurveShape curveShape);

/*	
	//membuat image dari streamCurveCollection
	//
	//sebelumnya meload stream tekstur terlebih dahulu
	//Tekstur: baris pertama bilangan bulat N menyatakan banyaknya tekstur
	//		selanjutnya N buah tekstur yang formatnya
	//		didefinisikan di texture.h
	//
	//streamGambar
	//baris pertama: bilangan bulat N, menyatakan banyaknya elemen
	//berikutnya, diikuti N elemen dengan format masing2 berikut:
	//sebaris bilangan bulat {0,1}: 0 menyatakan garis atau polyCurve,
	//				(polyCurve diubah jadi set of garis)
	//				1 menyatakan CurveShape
	//baris berikutnya menyatakan nomor tekstur untuk elemen tersebut
	//baris berikutnya, sebuah bilangan bulat M menyatakan banyak titik
	//M baris berikutnya, masing2 bilangan bulat X Y menyatakan titik
	//-titik ujung garis (Curve) atau titik sudut (polygon)
	static CurveCollection fromStream(std::istream& streamGambar,
				std::istream& streamTekstur);

	static CurveCollection fromStreamFormatMap(std::istream& infile);

	//clip semua elemen
	CurveCollection clip(point min, point max);

	//geser semua elemen
	CurveCollection hasilGeser(point delta);

	//skala semua elemen gambar
	CurveCollection hasilSkala(float scale){return hasilSkala(scale,scale);}
	CurveCollection hasilSkala(float scaleX, float scaleY);
*/
	//gambar
	//Curve dan curveShape
	void draw();

	// Operations
	void move(int dx, int dy);
	void scale(float s);
	void scale(float sx, float sy);
	void scale(float s, int cx, int cy);
	void scale(float s, Point& cp);
	void rotate(float t);
	void rotate(float t, int cx, int cy);
	void rotate(float t, const Point& cp);

	CurveCollection moveResult(Point delta);
	CurveCollection moveResult(int deltax, int deltay);
	CurveCollection scaleResult(float scale);

	CurveCollection scaleResult(float scaleX, float scaleY);
	CurveCollection rotationResult(float deltaDegree);
	CurveCollection rotationResult(float deltaDegree, Point poros);

	private:
	std::list<Curve> curves;
	std::list<CurveShape> curveShapes;

//untuk iterasi menggambar,
//saat di-add, ini diisi dengan order gambar yang menaik
//misal: bila dipanggil addCurve, addCurve, addCurveShape, addCurve, addCurve, addCurveShape
//maka, ordergambarCurve: {0,1,3,4}
//	orderGambarCurveShape: {2,5}
	std::list<int> orderGambarCurve;
	std::list<int> orderGambarCurveShape;

	//untuk mentrack saat add orderGambar
	int numElmts;
};

#endif
