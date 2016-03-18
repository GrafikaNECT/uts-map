#ifndef sistemwindowview_h
#define sistemwindowview_h

#define ZOOM 5
#define PAN 5

#include "../include/Point.h"
#include "../include/Image.h"
#include <string>

class SistemWindowView{

protected:
	Point windowMin;
	Point windowMax;
	Point viewMin;
	Point viewMax;
	Image map;
	Point minimapPos;
	float minimapScale;
	Image minimap;

public:
	SistemWindowView(Point windowMin, Point windowMax, Point viewMin, Point viewMax, Image map, Point minimapPos, float minimapScale);

	Point getWindowMin();
	Point getWindowMax();
	Point getViewMin();
	Point getViewMax();
	Image getMap();

	void setWindowMin(Point min);
	void setWindowMax(Point max);
	void setViewMin(Point min);
	void setViewMax(Point max);
	void setMap(Image map);


	void pan(std::string direction);
	void zoom(std::string direction);
	void draw();
	void drawMinimap();
};

#endif
