#ifndef DRAWER_H
#define DRAWER_H

#include "SolidPolygon.h"
	
class Drawer {
public:
	static void drawModel();

private:
	SolidPolygon transform();
	std::vector<SolidPolygon3D> orderSolidPolygon();

};

#include <algorithm>
// Fungsi untuk orderSolidPolygon
std::vector<SolidPolygon3D> Model3D::orderSolidPolygon() {
	std::vector<SolidPolygon3D> retval = *this;
	std::sort( retval.begin(), retval.end() );
	return retval;
}

#endif