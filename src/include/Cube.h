#ifndef Cube_h
#define Cube_h

#include "Model3D.h"

class Cube : public Model3D{
	public:
	Cube(Point3D centerPoint, int d,std::vector<Texture> textures);
};

#endif
