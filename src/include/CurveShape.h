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

	private:
	Texture outlineTexture;
	Texture fillTexture;
};

#endif
