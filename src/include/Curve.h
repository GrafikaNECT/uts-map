#ifndef Curve_h
#define Curve_h

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Point.h"
#include "Texture.h"

class Curve: public std::vector<Point>{
public:
	Curve(std::string fileName);
	Curve(Texture t = Texture::createSingleColorTexture(0,0,0,0)):std::vector<Point>(){texture=t;};
	Curve(std::vector<Point>& vec, Texture t = Texture::createSingleColorTexture(0,0,0,0)):std::vector<Point>(vec),texture(t){};

	void push_back(int x, int y); 
	void push_back(const Point& p){std::vector<Point>::push_back(p);};

	void draw();
	std::vector<Point> getPathPoints();
	Point calculateBezier(double t);

	// Operations
	void move(int dx, int dy);
	void scale(float s);
	void scale(float sx, float sy);
	void scale(float s, int cx, int cy);
	void scale(float s, Point& cp);
	void rotate(float t);
	void rotate(float t, int cx, int cy);
	void rotate(float t, const Point& cp);
	
private:
	Texture texture;
	Point getCasteljauPoint(int r, int i, double t);
};

#endif
