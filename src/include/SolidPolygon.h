#ifndef SolidPolygon_h
#define SolidPolygon_h

#include <vector>
#include "Point.h"
#include "Texture.h"

class SolidPolygon: public std::vector<Point>{
public:
	SolidPolygon(Texture t = Texture::createSingleColorTexture(0,0,0,0)):std::vector<Point>(){texture=t;};
	SolidPolygon(std::vector<Point>::size_type s,Texture t = Texture::createSingleColorTexture(0,0,0,0)):std::vector<Point>(s){texture=t;};
	SolidPolygon(std::vector<Point>& vec, Texture t = Texture::createSingleColorTexture(0,0,0,0)):std::vector<Point>(vec),texture(t){};

	SolidPolygon moveResult(Point delta);
	SolidPolygon moveResult(int deltax, int deltay);
	SolidPolygon scaleResult(float scale);

	SolidPolygon scaleResult(float scaleX, float scaleY);
	SolidPolygon rotationResult(float deltaDegree);
	SolidPolygon rotationResult(float deltaDegree, Point poros);

	void push_back(int x, int y); 
	void push_back(const Point& p){std::vector<Point>::push_back(p);};

	void draw();

	const Texture& getTexture() const;

	SolidPolygon clip(Point min, Point max);

private:

	Texture texture;
	
};

#endif
