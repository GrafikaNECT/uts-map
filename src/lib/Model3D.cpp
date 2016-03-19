#include "../include/Model3D.h"
#include <algorithm>
#include <list>
#include "../include/Printer.h"

Model3D Model3D::moveResult(int deltax, int deltay, int deltaz){
	Model3D retval = *this;
	for (int i=0;i<std::vector<SolidPolygon3D>::size();i++){
		const SolidPolygon3D& s = at(i);
		retval[i]=s.moveResult(deltax, deltay, deltaz);
	}
	return retval;
}

void Model3D::rotate(float deltaDegree, char axis) {

}

void Model3D::rotate(float deltaDegree, Point3D poros, char axis) {

}


Model3D Model3D::rotationResult(float deltaDegree, char axis){
	Model3D retval=*this;
	for (int i=0;i<std::vector<SolidPolygon3D>::size();i++){
		const SolidPolygon3D& s = at(i);
		retval[i]=s.rotationResult(deltaDegree, axis);
	}
	return retval;
}

Model3D Model3D::rotationResult(float deltaDegree, Point3D poros, char axis){
	Model3D retval=*this;
	for (int i=0;i<std::vector<SolidPolygon3D>::size();i++){
		const SolidPolygon3D& s = at(i);
		retval[i]=s.rotationResult(deltaDegree, poros, axis);
	}
	return retval;
}

void Model3D::combine(Model3D& model3D){
	insert(end(),model3D.begin(),model3D.end());
}

std::vector<SolidPolygon3D> Model3D::orderSolidPolygon() {
	std::vector<SolidPolygon3D> retval = *this;
	std::sort( retval.begin(), retval.end() );
	return retval;
}

std::vector<SolidPolygon> Model3D::projectionResult(Point3D eye) {
	std::vector<SolidPolygon> model2D;
	for (std::vector<SolidPolygon3D>::iterator it = this->begin(); it!=this->end(); it++) {
		model2D.push_back(it->projectionResult(eye));		
	}
	return model2D;
}

class ScanlineSegment{
	public:
	ScanlineSegment(){};
	ScanlineSegment(int _min, int _max, const Texture& _texture):min(_min),max(_max),texture(_texture){};
	bool operator=(const ScanlineSegment& rhs){
		min=rhs.min;
		max=rhs.max;
		texture=rhs.texture;
	}
	int min;
	int max;
	const Texture& texture;
	bool operator< (const ScanlineSegment& rhs){ return max < rhs.min;}
};

void Model3D::draw(Point3D eye){
	//Scanline algorithm

	std::vector<SolidPolygon> model2D = projectionResult(eye);
	//sementara pake painter dulu
	for (std::vector<SolidPolygon>::iterator it = model2D.begin();it!=model2D.end();it++){
		it->draw();
	}
	return;


	//cari xmin, xmax, ymin, ymax dari scanline
	int xmax = 0;
	int xmin = Printer::getXRes()-1;
	int ymax=0;
	int ymin = Printer::getYRes()-1;
	for (std::vector<SolidPolygon>::iterator it = model2D.begin(); it!=model2D.end(); it++){
		for (SolidPolygon::iterator pit = it->begin();pit!=it->end();pit++){
			if (pit->getX()<xmin) xmin=pit->getX();
			if (pit->getX()>xmax) xmax=pit->getX();
			if (pit->getY()<ymin) ymin=pit->getY();
			if (pit->getY()>ymax) ymax=pit->getY();
		}
	}


	for (int y=ymin;y<=ymax;y++){
		
		//alokasi
		std::list<ScanlineSegment> freeSegment;
		freeSegment.push_front(ScanlineSegment(xmin,xmax,Texture()));

		std::list<ScanlineSegment> allocatedSegments;
		for (std::vector<SolidPolygon>::reverse_iterator it = model2D.rbegin(); it!=model2D.rend(); it++) {
			SolidPolygon& p = *it;
						//ambil intersection dengan garis
			std::vector<int> intersections;
			for (int i=0;i<p.size()-1;i++){
				if (p[i].getY()!=p[i+1].getY())
				if ((y<p[i].getY() && y >= p[i+1].getY()) ||
					(y>=p[i].getY() && y < p[i+1].getY())){				
						int x=(int)((p[i].getX()+((float)y-p[i].getY())/((float)p[i+1].getY()-p[i].getY())*(p[i+1].getX()-p[i].getX())));
					intersections.push_back(x);
				}
			}
			int i=p.size()-1;
			if (p[i].getY()!=p[0].getY())
			if ((y<p[i].getY() && y >= p[0].getY()) ||
				 (y>=p[i].getY() && y < p[0].getY())){
				int x=(int)((p[i].getX()+((float)y-p[i].getY())/((float)p[0].getY()-p[i].getY())*(p[0].getX()-p[i].getX())));
				intersections.push_back(x);
			}

			std::sort(intersections.begin(),intersections.end());


			//alokasi
			std::list<ScanlineSegment>::iterator fsit = freeSegment.begin();

			for (int i=0;i<intersections.size();){
				if (freeSegment.empty()) break;
				if (fsit==freeSegment.end()) break;
				int intersectionmin = intersections[i];
				int intersectionmax = intersections[i+1];
				if (intersectionmin<=fsit->min){
					if (intersectionmax<fsit->min){
						i+=2;
						//do nothing
					}else if (intersectionmax<fsit->max){
						allocatedSegments.push_front(ScanlineSegment(fsit->min,intersectionmax,p.getTexture()));
						fsit->min=intersectionmax+1;
						i+=2;
					}else{
						allocatedSegments.push_front(ScanlineSegment(fsit->min,fsit->max,p.getTexture()));
						allocatedSegments.erase(fsit++);
					}
				}else if (intersectionmin<=fsit->max){
					if (intersectionmax<fsit->max){
						allocatedSegments.push_front(ScanlineSegment(intersectionmin,intersectionmax,p.getTexture()));
						freeSegment.insert(fsit,ScanlineSegment(fsit->min,intersectionmin-1,Texture()));
						fsit->min=intersectionmax+1;
					}else{
						allocatedSegments.push_front(ScanlineSegment(intersectionmin,fsit->max,p.getTexture()));
						fsit->max=intersectionmin-1;
						fsit++;
					}
				}else{
					i+=2;
				}
			}

		}

		//gambar
		for (std::list<ScanlineSegment>::iterator asit = allocatedSegments.begin(); asit !=allocatedSegments.end();asit++){
			for (int x=asit->min;x<=asit->max;x++)
				asit->texture.draw(x,y);
		}

	}
}

#include <sstream>
#include <string>

Model3D Model3D::fromStreamFormatMap(std::istream& infile){
	Model3D retval;
	int num = 0;

	// Using getline() to read one Line at a time.
	std::string Line;
	while (std::getline(infile, Line)) {

		if (Line.empty()) continue;
		std::string name(Line);

		std::getline(infile, Line);
		std::istringstream issLevel(Line);
		int level;
		issLevel>>level;

		// Using istringstream to read the Line into integers.
		std::getline(infile, Line);
		std::istringstream iss(Line);

		int next;
		bool isX = 1;

		num++;
		iss >> next;
		int R = next;
		iss >> next;
		int G = next;
		iss >> next;
		int B = next;
		iss >> next;
		int alpha = next;

		SolidPolygon3D smallIsland(Texture::createSingleColorTexture(R,G,B,alpha)); //TODO: kasih grain
	
		std::getline(infile, Line);
		std::istringstream issCoor(Line);

		int tempX;
		while (issCoor >> next) {
			if (isX) {
				isX = 0;
				tempX = next;
			} else {
				isX = 1;
				smallIsland.push_back(tempX, next, level);
			}
			
			if (issCoor.peek() == ',')
				issCoor.ignore();
		}

		retval.push_back(smallIsland);

	}

	return retval;
}
