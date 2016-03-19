#include "../include/SolidPolygon3D.h"
#include "../include/Line.h"
#include "../include/Printer.h"
#include "../include/SolidPolygon.h" 

#include <algorithm>

void SolidPolygon3D::push_back(int x, int y, int z){
	Point3D p(x,y,z);
	push_back(p);
}

bool SolidPolygon3D::operator<( const SolidPolygon3D& val ) const {
	if (this->size()==0) return false;
	else if (val.size()==0) return true;
	int maxthis = this->at(0).getZ();
	int maxval = val.at(0).getZ();

	for(int i=1; i<this->size(); i++) {
		if (maxthis <= this->at(i).getZ()) {
			maxthis = this->at(i).getZ();
		}
	}

	for(int i=1; i<val.size(); i++) {
		if (maxval <= val.at(i).getZ()) {
			maxval = val.at(i).getZ();
		}
	}
	return maxthis < maxval;
}

SolidPolygon3D SolidPolygon3D::moveResult(Point3D delta){
	return moveResult(delta.getX(), delta.getY(), delta.getZ());
}

SolidPolygon3D SolidPolygon3D::moveResult(int deltax, int deltay, int deltaz){
	SolidPolygon3D retval = *this;
	for (int i=0;i<std::vector<Point3D>::size();i++){
		retval[i].move(deltax,deltay,deltaz);
	}
	retval.texture = texture.translateResult(deltax, deltay); //TODO: Ga ngerti dengan perteksturan
	return retval;
}
SolidPolygon3D SolidPolygon3D::scaleResult(float scale){
	SolidPolygon3D retval = *this;
	for (int i=0;i<std::vector<Point3D>::size();i++){
		Point3D& p = retval[i];
		p.setX(p.getX()*scale);
		p.setY(p.getY()*scale);
		p.setZ(p.getZ()*scale);
	}
	retval.texture = texture.scaleResult(scale); //TODO: Ga ngerti ini harus diapain
	return retval;
}

SolidPolygon3D SolidPolygon3D::scaleResult(float scaleX, float scaleY, float scaleZ){
	SolidPolygon3D retval = *this;
	for (int i=0;i<std::vector<Point3D>::size();i++){
		Point3D& p = retval[i];
		p.setX(p.getX()*scaleX);
		p.setY(p.getY()*scaleY);
		p.setZ(p.getZ()*scaleZ);
	}
	retval.texture = texture.scaleResult(scaleX,scaleY); //TODO: Apalagi ini... Ini apaan ya?
	return retval;
}

//void SolidPolygon3D::rotate(float deltaDegree, char axis) {
//}
//
//void SolidPolygon3D::rotate(float deltaDegree, Point3D poros, char axis) {
//}

SolidPolygon3D SolidPolygon3D::rotationResult(float deltaDegree, char axis){
	SolidPolygon3D retval(std::vector<Point3D>::size(),texture);
	for (int i=0;i<std::vector<Point3D>::size();i++){
		const Point3D& p = at(i);
		retval[i]=p.rotationResult(deltaDegree, axis);
	}
	return retval;	
}

SolidPolygon3D SolidPolygon3D::rotationResult(float deltaDegree, Point3D poros, char axis){
	SolidPolygon3D tmp1 = moveResult(poros.mirrorResult());
	SolidPolygon3D tmp2 = tmp1.rotationResult(deltaDegree, axis);
	return tmp2.moveResult(poros);
}

SolidPolygon SolidPolygon3D::projectionResult(Point3D eye) {
	SolidPolygon retval(texture);
	for (int i=0;i<std::vector<Point3D>::size();i++){
		const Point3D& p = at(i);
		retval.push_back(p.projectionResult(eye));
	}
	return retval;
}
