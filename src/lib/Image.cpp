
/*
 * Nama Berkas			: Image.cpp
 * Deskripsi			: Realisasi dari Image.h
 */

#include "../include/Image.h"
#include "../include/Texture.h"

#include <vector>
#include <climits>

//menambah Line
//perhatikan orderGambar (spek di bawah)
void Image::addLine(Line l){
	lines.push_back(l);
	orderGambarLine.push_back(numElmts);
	numElmts++;
}

//memanggil addLine
//misal: isi points adalah {p0,p1,p2, ... pn-1}
//	maka, panggil 	addLine(Line(p0,p1))
//			addLine(Line(p1,p2))
//			.
//			.
//			.
//			addLine(Line(pn-2,pn-1))
void Image::addLines(const std::list<Point>& points){
	std::list<Point>::const_iterator it = points.begin();
	std::list<Point>::const_iterator prev = it;
	for (it++;it!=points.end();it++){
		addLine(Line(*prev,*it));
		prev=it;
	}
}

//menambah SolidPolygon
//perhatikan orderGambar (spek di bawah)
void Image::addSolidPolygon(SolidPolygon solidPolygon){
	solidPolygons.push_back(solidPolygon);
	orderGambarSolidPolygon.push_back(numElmts);
	numElmts++;
}

//menambah CurveCollections
//perhatikan orderGambar (spek di bawah)
void Image::addCurveCollection(CurveCollection curveCollection){
	curveCollections.push_back(curveCollection);
	orderGambarCurveCollection.push_back(numElmts);
	numElmts++;
}

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
Image Image::fromStream(std::istream& streamGambar,
			std::istream& streamTekstur){
	//load tekstur
	int N;
	std::vector<Texture> textures;
	streamTekstur>>N;
	for (int i=0;i<N;i++){
		textures.push_back(Texture::fromStream(streamTekstur));
	}

	Image retval;
	streamGambar>>N;
	for (int i=0;i<N;i++){
		int jenis;
		streamGambar>>jenis;
		int no_tekstur;
		streamGambar>>no_tekstur;
		int M;
		streamGambar>>M;
		std::vector<Point> points(M);
		for (int i=0;i<M;i++){
			int X,Y;
			streamGambar>>X>>Y;
			points[i].setX(X);
			points[i].setY(Y);
		}
		int prev;
		switch(jenis){
		case 0:
			prev=0;
			for (int i=1;i<M;i++){
				retval.addLine(Line(points[prev],points[i],textures[no_tekstur]));
				prev=i;
			}
		break;
		case 1:
			retval.addSolidPolygon(SolidPolygon(points,textures[no_tekstur]));
		break;
		}
	}
	return retval;
}

#include <sstream>
#include <string>

Image Image::fromStreamFormatMap(std::istream& infile){
	Image retval;
	int num = 0;

	// Using getline() to read one Line at a time.
	std::string Line;
	while (std::getline(infile, Line)) {

		if (Line.empty()) continue;

		// Using istringstream to read the Line into integers.
		std::getline(infile, Line);
		std::istringstream iss(Line);

		int next;
		bool isX = 1;

		num++;

		iss >> next;
		int R = next;
		iss >> next;
		int G = next;
		iss >> next;
		int B = next;
		iss >> next;
		int alpha = next;

		SolidPolygon smallIsland(Texture::createSingleColorTexture(R,G,B,alpha)); //TODO: kasih grain
	
		std::getline(infile, Line);
		std::istringstream issCoor(Line);

		int tempX;
		while (issCoor >> next) {
			if (isX) {
				isX = 0;
				tempX = next;
			} else {
				isX = 1;
				smallIsland.push_back(tempX, next);
			}
			
			if (issCoor.peek() == ',')
				issCoor.ignore();
		}

		retval.addSolidPolygon(smallIsland);

	}

	return retval;
}


// List of weather images
Image Image::fromWeatherInformation(WeatherInformation weatherInformation) {
	Image retval;

	for(int i=0; i<weatherInformation.getListOfCities().size(); i++) {
		//cout << weatherInformation.getListOfCities().at(i).getCityName() << " ";
		//cout << weatherInformation.getListOfCities().at(i).getWeather().getWeatherAnimation().getCurrentFrame() << endl;
		//cout << weatherInformation.getListOfCities().at(i).getWeather().getWeatherAnimation().getFrames().size() << endl;
		if (weatherInformation.getListOfCities().at(i).getWeather().getWeatherAnimation().getFrames().size()>0)
			retval.addCurveCollection(weatherInformation.getListOfCities().at(i).getWeather().getWeatherAnimation().getFrame());
	}
	cout << "CURVE COL " << retval.curveCollections.size() << endl;
	return retval;
}


Image Image::combineImages(std::vector<Image>& image){
	Image retval;
	for (std::vector<Image>::iterator it=image.begin();it!=image.end();it++){
		retval.combine(*it);
	}
	return retval;
}

void Image::combine(Image& image){
	std::list<Line>::iterator itline = image.lines.begin();
	std::list<SolidPolygon>::iterator itpol = image.solidPolygons.begin();
	std::list<CurveCollection>::iterator itcur = image.curveCollections.begin();

	//pakai sentinel
	std::list<int> orderGambarLine = image.orderGambarLine;
	std::list<int> orderGambarSolidPolygon = image.orderGambarSolidPolygon;
	std::list<int> orderGambarCurveCollection = image.orderGambarCurveCollection;
	orderGambarLine.push_back(INT_MAX);
	orderGambarSolidPolygon.push_back(INT_MAX);
	orderGambarCurveCollection.push_back(INT_MAX);

	std::list<int>::iterator itordline = orderGambarLine.begin();
	std::list<int>::iterator itordpol = orderGambarSolidPolygon.begin();
	std::list<int>::iterator itordcur = orderGambarCurveCollection.begin();
	int i=0;
	cout << "COMBINE CUR " << image.curveCollections.size() << endl;
	while (itline != image.lines.end() || itpol != image.solidPolygons.end() || itcur != image.curveCollections.end()){
		if (*itordline<*itordpol && *itordline<*itordcur) {
			addLine(*itline);
			itline++;
			itordline++;
		} else if (*itordpol<*itordline && *itordpol<*itordcur) {
			addSolidPolygon(*itpol);
			itpol++;
			itordpol++;
		} else {
			addCurveCollection(*itcur);
			itcur++;
			itordcur++;
		}
	}
}

//clip semua elemen
Image Image::clip(Point min, Point max){
	Image retval;
	std::list<Line>::iterator itline = lines.begin();
	std::list<SolidPolygon>::iterator itpol = solidPolygons.begin();
	std::list<CurveCollection>::iterator itcur = curveCollections.begin();

	//pakai sentinel
	std::list<int> orderGambarLine = this->orderGambarLine;
	std::list<int> orderGambarSolidPolygon = this->orderGambarSolidPolygon;
	std::list<int> orderGambarCurveCollection = this->orderGambarCurveCollection;
	orderGambarLine.push_back(INT_MAX);
	orderGambarSolidPolygon.push_back(INT_MAX);
	orderGambarCurveCollection.push_back(INT_MAX);
	std::list<int>::iterator itordline = orderGambarLine.begin();
	std::list<int>::iterator itordpol = orderGambarSolidPolygon.begin();
	std::list<int>::iterator itordcur = orderGambarCurveCollection.begin();
	int i=0;
	while (itline != lines.end() || itpol != solidPolygons.end() || itcur != curveCollections.end()){
		if (*itordline<*itordpol && *itordline<*itordcur) {
			Line l = itline->clip(min,max);
			if (!(l.getX1()==-1 && l.getX2()==-1
				&&l.getY1()==-1 && l.getY2()==-1)){
				retval.addLine(l);
			}
			itline++;
			itordline++;
		} else if (*itordpol<*itordline && *itordpol<*itordcur) {
			retval.addSolidPolygon(itpol->clip(min,max));
			itpol++;
			itordpol++;
		} else {
			// TODO
			retval.addCurveCollection(*itcur);
			itcur++;
			itordcur++;
		}
	}
	return retval;
}

//geser semua elemen
Image Image::moveResult(Point delta){
	Image retval=*this;
	for (std::list<Line>::iterator itline = retval.lines.begin();
		itline!=retval.lines.end();itline++){
		itline->move(delta);
	}
	for (std::list<SolidPolygon>::iterator itpol = retval.solidPolygons.begin();
		itpol!=retval.solidPolygons.end();itpol++){
		*itpol = itpol->moveResult(delta);
	}
	// for (std::list<CurveCollection>::iterator itcur = retval.curveCollections.begin();
	// 	itcur!=retval.curveCollections.end();itcur++){
	// 	*itcur = itcur->moveResult(delta);
	// }
	return retval;
}

//skala semua elemen gambar
Image Image::scaleResult(float scaleX, float scaleY){
	Image retval=*this;
	for (std::list<Line>::iterator itline = retval.lines.begin();
		itline!=retval.lines.end();itline++){
		itline->scale(scaleX,scaleY);
	}
	for (std::list<SolidPolygon>::iterator itpol = retval.solidPolygons.begin();
		itpol!=retval.solidPolygons.end();itpol++){
		*itpol = itpol->scaleResult(scaleX,scaleY);
	}
	// for (std::list<CurveCollection>::iterator itcur = retval.curveCollections.begin();
	// 	itcur!=retval.curveCollections.end();itcur++){
	// 	*itcur = itcur->scaleResult(scaleX,scaleY);
	// }
	return retval;
}

//gambar
//Line dan poligon
void Image::draw(){
	std::list<Line>::iterator itline = lines.begin();
	std::list<SolidPolygon>::iterator itpol = solidPolygons.begin();
	std::list<CurveCollection>::iterator itcur = curveCollections.begin();

	//pakai sentinel
	std::list<int> orderGambarLine = this->orderGambarLine;
	std::list<int> orderGambarSolidPolygon = this->orderGambarSolidPolygon;
	std::list<int> orderGambarCurveCollection = this->orderGambarCurveCollection;
	orderGambarLine.push_back(INT_MAX);
	orderGambarSolidPolygon.push_back(INT_MAX);
	orderGambarCurveCollection.push_back(INT_MAX);

	std::list<int>::iterator itordline = orderGambarLine.begin();
	std::list<int>::iterator itordpol = orderGambarSolidPolygon.begin();
	std::list<int>::iterator itordcur = orderGambarCurveCollection.begin();
	
	while (itline != lines.end() || itpol != solidPolygons.end() || itcur != curveCollections.end()){
		if (*itordline<*itordpol && *itordline<*itordcur) {
			itline->draw();
			itline++;
			itordline++;
		} else if (*itordpol<*itordline && *itordpol<*itordcur) {
			itpol->draw();
			itpol++;
			itordpol++;
		} else {
			itcur->draw();
			itcur++;
			itordcur++;
		}
	}
}
