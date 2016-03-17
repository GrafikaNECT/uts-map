#ifndef Model3D_h
#define Model3D_h

#include <vector>
#include "SolidPolygon3D.h"
#include "SolidPolygon.h"
#include "Point3D.h"

class Model3D: public std::vector<SolidPolygon3D>{
	public:
	Model3D(std::vector<SolidPolygon3D>& vec):std::vector<SolidPolygon3D>(vec){};
	//Model3D hasilGeser(Point3D delta);
	//Model3D hasilGeser(int deltax, int deltay, int deltaz);
	//Model3D hasilPerbesar(float scale);

	void rotate (float deltaDegree,char axis);
	void rotate (float deltaDegree, Point3D poros, char axis);

	Model3D rotationResult(float deltaDegree,char axis);
	Model3D rotationResult(float deltaDegree, Point3D poros, char axis);

	std::vector<SolidPolygon3D> orderSolidPolygon();
	std::vector<SolidPolygon> projectionResult(Point3D eye);

	void push_back(const SolidPolygon3D& p){std::vector<SolidPolygon3D>::push_back(p);};

	void draw(Point3D eye);


	
};

#endif
