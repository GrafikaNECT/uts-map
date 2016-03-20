#ifndef Point3D_h
#define Point3D_h

#include "Point.h"

class Point3D {
	int x, y, z;
public:
	// Constructor
	Point3D(int _x, int _y, int _z);
	Point3D() {Point3D(0,0,0);};
	Point3D(Point p){Point3D(p.getX(),p.getY(),0);}
	
	// Getter
	int getX() const;
	int getY() const;
	int getZ() const;
	
	// Setter
	void setXYZ(int _x,int _y, int _z);
	void setX(int _x);
	void setY(int _y);
	void setZ(int _z);
	
	// Operations
	void move(int dx, int dy, int dz);
	void scale(float s);
	void scale(float sx, float sy, float sz);
	void scale(float s, int cx, int cy, int cz);
	void scale(float s, Point3D& cp);
	void rotate(float t, char axis);
	void rotate(float t, int cx, int cy, int cz, char axis);
	void rotate(float t, const Point3D& cp, char axis);

	Point3D moveResult(int _x, int _y, int _z) const{
		Point3D p(getX()+_x,getY()+_y,getZ()+_z);
		return p;
	};
	Point3D rotationResult(float deltaDegree, const Point3D& cp, char axis) const;
	Point3D rotationResult(float deltaDegree, char axis) const;
	Point3D mirrorResult() const;
	Point3D mirrorResult(char axis) const;

	Point projectionResult(Point3D eye);
};

#endif // Point3D_H
