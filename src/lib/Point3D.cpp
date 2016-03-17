#include "../include/Point3D.h"
#include "../include/Point.h"
#include <math.h>
#include <iostream>

// Constructor
Point3D::Point3D(int _x, int _y, int _z) {
	x = _x;
	y = _y;
	z = _z;
}

// Getter
int Point3D::getX() const {
	return x;
}

int Point3D::getY() const {
	return y;
}

int Point3D::getZ() const {
	return z;
}

// Setter
void Point3D::setXYZ(int _x,int _y, int _z) {
	x = _x;
	y = _y;
	z = _z;
}

void Point3D::setX(int _x) {
	x = _x;
}

void Point3D::setY(int _y) {
	y = _y;
}

void Point3D::setZ(int _z) {
	z = _z;
}

// Operations
void Point3D::move(int dx, int dy, int dz) {
	x = x + dx;
	y = y + dy;
	z = z + dz;
}

void Point3D::scale(float s) {
	x = (int)x*s;
	y = (int)y*s;
	z = (int)z*s;
}

void Point3D::scale(float sx, float sy, float sz){
	x*=sx;
	y*=sy;
	z*=sz;
}

void Point3D::scale(float s, int cx, int cy, int cz) {
	move(-cx,-cy,-cz);
	scale(s);
	move(cx,cy,cz);
}

void Point3D::scale(float s, Point3D& cp) {
	scale(s,cp.getX(),cp.getY(),cp.getZ());
}

void Point3D::rotate(float t, char axis) {
	if (axis == 'x') {
		int y1 = round(cos(t)*y - sin(t)*z);
		int z1 = round(sin(t)*y + cos(t)*z);
		y = y1;
		z = z1;	
	} else if (axis == 'y') {
		int z1 = round(cos(t)*z - sin(t)*x);
		int x1 = round(sin(t)*z + cos(t)*x);
		z = z1;
		x = x1;	
	} else if (axis == 'z') {
		int x1 = round(cos(t)*x - sin(t)*y);
		int y1 = round(sin(t)*x + cos(t)*y);
		x = x1;
		y = y1;	
	}
}

void Point3D::rotate(float t, int cx, int cy, int cz, char axis) {
	move(-cx,-cy,-cz);
	rotate(t,axis);
	move(cx,cy,cz);
}

void Point3D::rotate(float t, const Point3D& cp, char axis){
	rotate(t,cp.getX(),cp.getY(),cp.getZ(),axis);
}

Point3D Point3D::rotationResult(float deltaDegree, char axis) const{
	float deltaRad = deltaDegree*M_PI/180.0;
	Point3D p;
	if (axis == 'x') {
		p.setXYZ(x,(double)y*cos(deltaRad)-(double)z*sin(deltaRad),(double)y*sin(deltaRad)+(double)z*cos(deltaRad));	
	} else if (axis == 'y') {
		p.setXYZ((double)z*cos(deltaRad)-(double)x*sin(deltaRad),y,(double)z*sin(deltaRad)+(double)x*cos(deltaRad));	
	} else if (axis == 'z') {
		p.setXYZ((double)x*cos(deltaRad)-(double)y*sin(deltaRad),(double)x*sin(deltaRad)+(double)y*cos(deltaRad),z);	
	}
	return p;
}

Point3D Point3D::mirrorResult() const{
	Point3D p;
	p.setXYZ(-x,-y,-z);	
	return p;
}

Point3D Point3D::mirrorResult(char axis) const{
	Point3D p;
	if (axis == 'x') {
		p.setXYZ(x,-y,-z);
	} else if (axis == 'y')	{
		p.setXYZ(-x,y,-z);
	} else if (axis == 'z') {
		p.setXYZ(-x,-y,z);	
	}
	
	return p;
}

Point Point3D::projectionResult (Point3D eye) {
	Point p;
	int sx = (eye.getZ() * (x-eye.getX())) / (eye.getZ() + z) + eye.getX();
	int sy = (eye.getZ() * (y-eye.getY())) / (eye.getZ() + z) + eye.getY();
	p.setX(sx);
	p.setY(sy);
	return p;
}
