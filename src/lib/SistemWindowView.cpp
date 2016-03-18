#include "../include/SistemWindowView.h"

SistemWindowView::SistemWindowView(Point windowMin, Point windowMax, Point viewMin, Point viewMax, Image map, Point minimapPos, float minimapScale) {
	this->windowMin = windowMin;
	this->windowMax = windowMax;
	this->viewMin = viewMin;
	this->viewMax = viewMax;
	this->map = map;
	this->minimapPos = minimapPos;
	this->minimapScale = minimapScale;
	this->minimap = map.scaleResult(minimapScale).moveResult(minimapPos);
}

Point SistemWindowView::getWindowMin() {return windowMin;}
Point SistemWindowView::getWindowMax() {return windowMax;}
Point SistemWindowView::getViewMin() {return viewMin;}
Point SistemWindowView::getViewMax() {return viewMax;}
Image SistemWindowView::getMap() {return map;}

void SistemWindowView::setWindowMin(Point min) {windowMin = min;}
void SistemWindowView::setWindowMax(Point max) {windowMax = max;}
void SistemWindowView::setViewMin(Point min) {viewMin = min;}
void SistemWindowView::setViewMax(Point max) {viewMax = max;}
void SistemWindowView::setMap(Image map) {
	this->map = map;
	this->minimap = map.scaleResult(minimapScale).moveResult(minimapPos);
}

void SistemWindowView::pan(std::string direction) {
	if (direction == "left") {
		windowMin.move(-PAN,0);
		windowMax.move(-PAN,0);
	}
	else if (direction == "right") {
		windowMin.move(PAN,0);
		windowMax.move(PAN,0);
	}
	else if (direction == "up") {
		windowMin.move(0,-PAN);
		windowMax.move(0,-PAN);
	}
	else if (direction == "down") {
		windowMin.move(0,PAN);
		windowMax.move(0,PAN);
	}
}

void SistemWindowView::zoom(std::string direction) {
	int min_x = windowMin.getX();
	int min_y = windowMin.getY();
	int max_x = windowMax.getX();
	int max_y = windowMax.getY();
	int width = max_x - min_x;
	int height = max_y - min_y;
	int deltax = ZOOM;
	int deltay = ((float)deltax/width)*height;
	
	if (direction == "in") {
		windowMin.move(deltax,deltay);
		windowMax.move(-deltax,-deltay);
	} else if (direction == "out") {
		windowMin.move(-deltax,-deltay);
		windowMax.move(deltax,deltay);
	}
}

void SistemWindowView::draw() {
	int viewWidth = viewMax.getX() - viewMin.getX();
	int viewHeight = viewMax.getY() - viewMin.getY();
	int windowWidth = windowMax.getX() - windowMin.getX();
	int windowHeight = windowMax.getY() - windowMin.getY();
	float ratio_x = (float)viewWidth/windowWidth;
	float ratio_y = (float)viewHeight/windowHeight;
	Point move1(-windowMin.getX(),-windowMin.getY());
	Point move2(viewMin.getX(),viewMin.getY());

	map.clip(windowMin,windowMax)
		.moveResult(move1)
		.scaleResult(ratio_x,ratio_y)
		.moveResult(move2).draw();

	drawMinimap();
}

void SistemWindowView::drawMinimap() {
	minimap.draw();
	Texture lineTexture = Texture::createSingleColorTexture(255,0,0,255);
	Line top(windowMin,Point(windowMax.getX(),windowMin.getY()),lineTexture);
	Line bottom(Point(windowMin.getX(),windowMax.getY()),windowMax,lineTexture);
	Line left(windowMin,Point(windowMin.getX(),windowMax.getY()),lineTexture);
	Line right(Point(windowMax.getX(),windowMin.getY()),windowMax,lineTexture);
	Image window;
	window.addLine(top);
	window.addLine(bottom);
	window.addLine(left);
	window.addLine(right);
	window.scaleResult(minimapScale).moveResult(minimapPos).draw();
}
