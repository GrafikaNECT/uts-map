#ifndef GIS3D_cpp
#define GIS3D_cpp

#include "../include/GIS3D.h"

#define PANSTEP 5
#define ZOOMSTEP 5

GIS3D::GIS3D(){

}

void GIS3D::add(Model3D model3D){
	layers.push_back(model3D);
	layerEnabled.push_back(true);
	updateCombinedModel();
}

void GIS3D::pan(std::string dir){
	if (dir=="left"){
		panX-=PANSTEP;
	} else
	if (dir=="right"){
		panX+=PANSTEP;
	} else
	if (dir=="up"){
		panY-=PANSTEP;
	} else
	if (dir=="down"){
		panY+=PANSTEP;
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
//TODO void GIS3D::rotate(std::string dir);


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

Point3D eye(400,400,50);

void GIS3D::draw(){
	combinedModel.moveResult(-panX,-panY,zoomAmount)
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
