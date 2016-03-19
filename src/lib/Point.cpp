#include "../include/Point.h"
#include <math.h>
#include <iostream>

// Constructor
Point::Point(int _x, int _y) {
	x = _x;
	y = _y;
}

// Getter
int Point::getX() const {
	return x;
}
int Point::getY() const {
	return y;
}

// Setter
void Point::setX(int _x) {
	x = _x;
}
void Point::setY(int _y) {
	y = _y;
}

// Operations
void Point::move(int dx, int dy) {
	x = x + dx;
	y = y + dy;
}
void Point::scale(float s) {
	x = (int)x*s;
	y = (int)y*s;
}
void Point::scale(float sx, float sy){
	x = x * sx;
	y = x * sy;
}
void Point::scale(float s, int cx, int cy) {
	move(-cx,-cy);
	scale(s);
	move(cx,cy);
}
void Point::scale(float s, Point& cp) {
	scale(s,cp.getX(),cp.getY());
}
void Point::rotate(float t) {
	int x1 = round(cos(t)*x - sin(t)*y);
	int y1 = round(sin(t)*x + cos(t)*y);
	x = x1;
	y = y1;
}
void Point::rotate(float t, int cx, int cy) {
	move(-cx,-cy);
	rotate(t);
	move(cx,cy);
}

void Point::rotate(float t, const Point& cp){
	rotate(t,cp.getX(),cp.getY());
}

Point Point::rotationResult(float deltaDegree) const{
	float deltaRad = deltaDegree*M_PI/180.0;
	Point p((double)x*cos(deltaRad)-(double)y*sin(deltaRad),(double)x*sin(deltaRad)+(double)y*cos(deltaRad));
	return p;
}

Point Point::hasilMirror00() const{
	Point p(-x,-y);
	return p;
}

bool Point::operator==(const Point& rhs) const{
	return rhs.getX()==getX() && rhs.getY()==getY();
}
