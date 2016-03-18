#ifndef GIS2D_cpp
#define GIS2D_cpp

#include "../include/GIS2D.h"
#include "../include/Printer.h"

GIS2D::GIS2D():viewCanvas(VIEWCANVASTEXTURE),minimapCanvas(BGTEXTURE){
	Point viewMin(MARGIN,MARGIN);
	Point viewMax(Printer::getXRes()-MARGIN,Printer::getYRes()-BOTTOMTEXTSPACE-MARGIN);
	Point windowMin(0,0);
	Point windowMax(DEFAULTWINDOWWIDTH,viewMax.getY()*DEFAULTWINDOWWIDTH/viewMax.getX());
	Image i;
	sistemWindowView=SistemWindowView(windowMin,windowMax,viewMin,viewMax,i,Point(viewMin.getX(),viewMax.getY()+50),0.2);


	viewCanvas.push_back(viewMin);
	viewCanvas.push_back(Point(viewMin.getX(),viewMax.getY()));
	viewCanvas.push_back(viewMax);
	viewCanvas.push_back(Point(viewMax.getX(),viewMin.getY()));


	minimapCanvas.push_back(0,viewMax.getY());
	minimapCanvas.push_back(0,viewMax.getY()+500);
	minimapCanvas.push_back(viewMin.getX()+500,viewMax.getY()+500);
	minimapCanvas.push_back(viewMin.getX()+500,viewMax.getY());
}

void GIS2D::add(Image i){
	layers.push_back(i);
	layerEnabled.push_back(true);
	updateSistemWindowViewImage();
}

void GIS2D::pan(std::string dir){
	sistemWindowView.pan(dir);
}
void GIS2D::zoom(std::string dir){
	sistemWindowView.zoom(dir);
}

void GIS2D::enableLayer(int layerNum){
	if (layerNum<layerEnabled.size()){
		layerEnabled[layerNum]=true;
		updateSistemWindowViewImage();
	}
}

void GIS2D::disableLayer(int layerNum){
	if (layerNum<layerEnabled.size()){
		layerEnabled[layerNum]=false;
		updateSistemWindowViewImage();
	}
}
void GIS2D::toggleLayer(int layerNum){
	if (layerNum<layerEnabled.size()){
		if (isLayerEnabled(layerNum))
			disableLayer(layerNum);
		else
			enableLayer(layerNum);
	}
}

bool GIS2D::isLayerEnabled(int layerNum){
	return layerEnabled[layerNum];
}

void GIS2D::draw(){
	viewCanvas.draw();
	minimapCanvas.draw();
	sistemWindowView.draw();
}


void GIS2D::updateSistemWindowViewImage(){
	Image imageBaru;
	for (int i=0;i<layers.size()&&i<layerEnabled.size();i++){
		if (isLayerEnabled(i)){
			imageBaru.combine(layers[i]);
		}
	}
	sistemWindowView.setMap(imageBaru);
}
#endif
