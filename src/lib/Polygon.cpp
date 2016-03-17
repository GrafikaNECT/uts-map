#include "../include/Polygon.h"
#include "../include/PixelBoolMatrix.h"

void Polygon::push_back(int x, int y){
	Point p(x,y);
	push_back(p);
}

Polygon Polygon::hasilGeser(Point delta){
	return hasilGeser(delta.getX(), delta.getY());
}

Polygon Polygon::hasilGeser(int deltax, int deltay){
	Polygon retval = *this;
	for (int i=0;i<std::vector<Point>::size();i++){
		retval[i].move(deltax,deltay);
	}
	return retval;
}
Polygon Polygon::hasilPerbesar(float scale){
	Polygon retval = *this;
	for (int i=0;i<std::vector<Point>::size();i++){
		Point& p = retval[i];
		p.setX(p.getX()*scale);
		p.setY(p.getY()*scale);
	}
	return retval;
}

Polygon Polygon::hasilSkala(float scaleX, float scaleY){
	Polygon retval = *this;
	for (int i=0;i<std::vector<Point>::size();i++){
		Point& p = retval[i];
		p.setX(p.getX()*scaleX);
		p.setY(p.getY()*scaleY);
	}
	return retval;
}

Polygon Polygon::hasilRotasi(float deltaDegree){
	Polygon retval(std::vector<Point>::size());
	for (int i=0;i<std::vector<Point>::size();i++){
		const Point& p = at(i);
		retval[i]=p.rotationResult(deltaDegree);
	}
	return retval;	
}

Polygon Polygon::hasilRotasi(float deltaDegree, Point poros){
	Polygon tmp1 = hasilGeser(poros.hasilMirror00());
	Polygon tmp2 = tmp1.hasilRotasi(deltaDegree);
	return tmp2.hasilGeser(poros);
}

void Polygon::draw(int x, int y, int R, int G, int B, int A, bool wireframeOnly){
	//buat pixelboolmatrix
	//cari x,y paling besar dan paling kecil
	int xmin = 0, xmax = 0, ymin = 0, ymax = 0;
	for (int i=0;i<size();i++){
		const Point& p = at(i);
		if (p.getX()<xmin) xmin=p.getX();
		if (p.getX()>xmax) xmax=p.getX();
		if (p.getY()<ymin) ymin=p.getY();
		if (p.getY()>ymax) ymax=p.getY();
	}
	PixelBoolMatrix mat(xmax-xmin+1,ymax-ymin+1);
	//biar ngga bocor ke negatif
	Polygon ptrans = hasilGeser(-xmin, -ymin);

	mat.setAll(false);	
	if (wireframeOnly)
		mat.setWireframe(ptrans,true);
	else
		mat.setSolid(ptrans,true);

	mat.draw(x+xmin,y+ymin,R,G,B,A);
}


