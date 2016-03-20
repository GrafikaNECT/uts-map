#ifndef CurveShape_h
#define CurveShape_h

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Point.h"
#include "Texture.h"

class CurveShape: public std::vector<Point>{
public:
	CurveShape(std::string fileName);
	CurveShape(Texture tOutline = Texture::createSingleColorTexture(0,0,0,0), Texture tFill = Texture::createSingleColorTexture(250,220,210,255)):std::vector<Point>(){outlineTexture=tOutline;fillTexture=tFill;};
	CurveShape(std::vector<Point>& vec, Texture tOutline = Texture::createSingleColorTexture(0,0,0,0), Texture tFill = Texture::createSingleColorTexture(250,220,210,255)):std::vector<Point>(vec),outlineTexture(tOutline), fillTexture(tFill){};

	void push_back(int x, int y); 
	void push_back(const Point& p){std::vector<Point>::push_back(p);};

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

	CurveShape moveResult(Point delta);
	CurveShape moveResult(int deltax, int deltay);
	CurveShape scaleResult(float scale);

	CurveShape scaleResult(float scaleX, float scaleY);
	CurveShape rotationResult(float deltaDegree);
	CurveShape rotationResult(float deltaDegree, Point poros);

private:
	Texture outlineTexture;
	Texture fillTexture;
};

#endif
