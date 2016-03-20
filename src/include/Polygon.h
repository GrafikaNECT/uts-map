#ifndef Polygon_h
#define Polygon_h

#include <vector>
#include "Point.h"

class Polygon: public std::vector<Point>{
	public:
	Polygon():std::vector<Point>(){};
	Polygon(std::vector<Point>::size_type s):std::vector<Point>(s){};
	Polygon hasilGeser(Point delta);
	Polygon hasilGeser(int deltax, int deltay);
	Polygon hasilPerbesar(float scale);

	Polygon hasilSkala(float scaleX, float scaleY);
	Polygon hasilRotasi(float deltaDegree);
	Polygon hasilRotasi(float deltaDegree, Point poros);

	void push_back(int x, int y); 
	void push_back(const Point& p){std::vector<Point>::push_back(p);};

	void draw(int x, int y, int R, int G, int B, int A, bool wireframeOnly=false);

	private:
	
};

#endif
