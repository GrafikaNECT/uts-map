#ifndef Image_h
#define Image_h

#include "../include/CurveCollection.h"
#include "../include/Line.h"
#include "../include/Point.h"
#include "../include/SolidPolygon.h"
#include "../include/WeatherInformation.h"
#include <list>
#include <vector>

#include <iostream>

class Image {
	public:

	//menambah Line
	//perhatikan orderGambar (spek di bawah)
	void addLine(Line l);

	//memanggil addLine
	//misal: isi points adalah {p0,p1,p2, ... pn-1}
	//	maka, panggil 	addLine(Line(p0,p1))
	//			addLine(Line(p1,p2))
	//			.
	//			.
	//			.
	//			addLine(Line(pn-2,pn-1))
	void addLines(const std::list<Point>& points);

	//menambah SolidPolygon
	//perhatikan orderGambar (spek di bawah)
	void addSolidPolygon(SolidPolygon solidPolygon);

	//menambah CurveCollections
	//perhatikan orderGambar (spek di bawah)
	void addCurveCollection(CurveCollection curveCollection);

	//membuat image dari streamImage
	//
	//sebelumnya meload stream tekstur terlebih dahulu
	//Tekstur: baris pertama bilangan bulat N menyatakan banyaknya tekstur
	//		selanjutnya N buah tekstur yang formatnya
	//		didefinisikan di texture.h
	//
	//streamGambar
	//baris pertama: bilangan bulat N, menyatakan banyaknya elemen
	//berikutnya, diikuti N elemen dengan format masing2 berikut:
	//sebaris bilangan bulat {0,1}: 0 menyatakan garis atau polyline,
	//				(polyline diubah jadi set of garis)
	//				1 menyatakan SolidPolygon
	//baris berikutnya menyatakan nomor tekstur untuk elemen tersebut
	//baris berikutnya, sebuah bilangan bulat M menyatakan banyak titik
	//M baris berikutnya, masing2 bilangan bulat X Y menyatakan titik
	//-titik ujung garis (Line) atau titik sudut (polygon)
	static Image fromStream(std::istream& streamGambar,
				std::istream& streamTekstur);

	static Image fromStreamFormatMap(std::istream& infile);

	static Image fromWeatherInformation(WeatherInformation weatherInformation);

	static Image combineImages(std::vector<Image>& image);

	//BERGABUNG!!
	void combine(Image& i);

	//clip semua elemen
	Image clip(Point min, Point max);

	//geser semua elemen
	Image moveResult(Point delta);

	//skala semua elemen gambar
	Image scaleResult(float scale){return scaleResult(scale,scale);}
	Image scaleResult(float scaleX, float scaleY);

	//gambar
	//Line dan poligon
	void draw();

	private:
	std::list<Line> lines;
	std::list<SolidPolygon> solidPolygons;
	std::list<CurveCollection> curveCollections;

//untuk iterasi menggambar,
//saat di-add, ini diisi dengan order gambar yang menaik
//misal: bila dipanggil addLine, addLine, addSolidPolygon, addLine, addLine, addSolidPolygon
//maka, ordergambarLine: {0,1,3,4}
//	orderGambarSolidPolygon: {2,5}
	std::list<int> orderGambarLine;
	std::list<int> orderGambarSolidPolygon;
	std::list<int> orderGambarCurveCollection;

	//untuk mentrack saat add orderGambar
	int numElmts=0;
};

#endif
