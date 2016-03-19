#ifndef GIS3D_cpp
#define GIS3D_cpp

#include "../include/GIS3D.h"
#include <cmath>

#define PANSTEP 5
#define ZOOMSTEP 20
#define ROTATESTEP 5

#define ROTATEDEGXSTART 0
#define ROTATEDEGYSTART (-90)
#define ROTATEDEGZSTART 0

#define ROTATEMIN (-90)
#define ROTATEMAX 90

#define ROTATEMINZ (ROTATEDEGZSTART+ROTATEMIN)
#define ROTATEMAXZ (ROTATEDEGZSTART+ROTATEMAX)
#define ROTATEMINY (ROTATEDEGYSTART+ROTATEMIN)
#define ROTATEMAXY (ROTATEDEGYSTART+ROTATEMAX)
#define ROTATEMINX (ROTATEDEGXSTART+ROTATEMIN)
#define ROTATEMAXX (ROTATEDEGXSTART+ROTATEMAX)


GIS3D::GIS3D(){
	rotateDegX = ROTATEDEGXSTART;
	rotateDegY = ROTATEDEGYSTART;
	rotateDegZ = ROTATEDEGZSTART;
}

void GIS3D::add(Model3D model3D){
	layers.push_back(model3D);
	layerEnabled.push_back(true);
	updateCombinedModel();
}

double degToRad(double deg){
	return (deg*M_PI)/180;
}

void GIS3D::pan(std::string dir){
	double rot = degToRad(rotateDegZ);
	if (dir=="left"){
		panX-=PANSTEP*cos(rot);
		panY+=PANSTEP*sin(rot);
	} else
	if (dir=="right"){
		panX+=PANSTEP*cos(rot);
		panY-=PANSTEP*sin(rot);
	} else
	if (dir=="up"){
		panY-=PANSTEP*cos(rot);
		panX-=PANSTEP*sin(rot);
	} else
	if (dir=="down"){
		panY+=PANSTEP*cos(rot);
		panX+=PANSTEP*sin(rot);
	} 
}
void GIS3D::zoom(std::string dir){
	if (dir=="in"){
		zoomAmount+=ZOOMSTEP;
	} else
	if (dir=="out"){
		zoomAmount-=ZOOMSTEP;
	} 
}
void GIS3D::rotate(std::string dir){
	if (dir=="xMin"){
		if (rotateDegX>ROTATEMINX)
		rotateDegX-=ROTATESTEP;
	}else if (dir=="xPlus"){
		if (rotateDegX<ROTATEMAXX)
		rotateDegX+=ROTATESTEP;
	}else 
	if (dir=="yMin"){
		if (rotateDegY>ROTATEMINY)
		rotateDegY-=ROTATESTEP;
	}else if (dir=="yPlus"){
		if (rotateDegY<ROTATEMAXY)
		rotateDegY+=ROTATESTEP;
	}else 
	if (dir=="zMin"){
		if (rotateDegZ>ROTATEMINZ)
		rotateDegZ-=ROTATESTEP;
	}else if (dir=="zPlus"){
		if (rotateDegZ<ROTATEMAXZ)
		rotateDegZ+=ROTATESTEP;
	}
}


void GIS3D::enableLayer(int layerNum){
	if (layerNum<layerEnabled.size()){
		layerEnabled[layerNum]=true;
		updateCombinedModel();
	}
}

void GIS3D::disableLayer(int layerNum){
	if (layerNum<layerEnabled.size()){
		layerEnabled[layerNum]=false;
		updateCombinedModel();
	}
}
void GIS3D::toggleLayer(int layerNum){
	if (layerNum<layerEnabled.size()){
		if (isLayerEnabled(layerNum))
			disableLayer(layerNum);
		else
			enableLayer(layerNum);
	}
}

bool GIS3D::isLayerEnabled(int layerNum){
	return layerEnabled[layerNum];
}

Point3D eye(400,400,1000);
Point3D centerPoint(400,400,0);

void GIS3D::draw(){
	combinedModel.moveResult(-panX,-panY,zoomAmount)
		     .rotationResult(rotateDegZ,centerPoint,'z')
                     .rotationResult(rotateDegX,centerPoint,'x')
		     .rotationResult(rotateDegY,centerPoint,'y')
		     .draw(eye);
}

void GIS3D::updateCombinedModel(){
	Model3D combinedModelBaru;
	for (int i=0;i<layers.size()&&i<layerEnabled.size();i++){
		if (isLayerEnabled(i)){
			combinedModelBaru.combine(layers[i]);
		}
	}

	std::vector<SolidPolygon3D> orderedSolidPolygon3D(combinedModelBaru.orderSolidPolygon());
	combinedModel = orderedSolidPolygon3D;
}
#endif
