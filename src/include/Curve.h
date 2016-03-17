#ifndef Curve_h
#define Curve_h

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Point.h"
#include "Texture.h"

class Curve: public std::vector<Point>{
	public:
	Curve(std::string fileName);
	Curve(Texture t = Texture::createSingleColorTexture(0,0,0,0)):std::vector<Point>(){texture=t;};
	Curve(std::vector<Point>& vec, Texture t = Texture::createSingleColorTexture(0,0,0,0)):std::vector<Point>(vec),texture(t){};

	/*Curve moveResult(Point delta);
	Curve moveResult(int deltax, int deltay);
	Curve scaleResult(float scale);

	Curve scaleResult(float scaleX, float scaleY);
	Curve rotationResult(float deltaDegree);
	Curve rotationResult(float deltaDegree, Point poros);
	*/

	void push_back(int x, int y); 
	void push_back(const Point& p){std::vector<Point>::push_back(p);};

	void draw();
	std::vector<Point> getPathPoints();
	Point calculateBezier(double t);

	private:
	Texture texture;
	Point getCasteljauPoint(int r, int i, double t);
};

#endif
