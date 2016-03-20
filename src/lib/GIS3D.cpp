#ifndef GIS3D_cpp
#define GIS3D_cpp

#include "../include/GIS3D.h"
#include "../include/Point3D.h"
#include "../include/Point.h"
#include "../include/City.h"
#include "../include/Alphabet.h"
#include <iostream>

#include <cmath>

#define PANSTEP 5
#define ZOOMSTEP 20
#define ROTATESTEP 5

#define ROTATEDEGXSTART 0
#define ROTATEDEGYSTART (-90)
#define ROTATEDEGZSTART 0

#define ROTATEMIN (-45)
#define ROTATEMAX 45

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

void GIS3D::enableWeather(){
	weatherEnabled=true;
	//TODO tambahkan juga enable/disable animasi bila pakai animasi
}
void GIS3D::disableWeather(){
	weatherEnabled=false;
	//TODO tambahkan juga enable/disable animasi bila pakai animasi
}
void GIS3D::toggleWeather(){
	if (isWeatherEnabled())
		disableWeather();
	else
		enableWeather();
}

bool GIS3D::isLayerEnabled(int layerNum){
	return layerEnabled[layerNum];
}

bool GIS3D::isWeatherEnabled(){
	return weatherEnabled;
}

Point3D eye(400,400,1000);
Point3D centerPoint(400,400,0);

void GIS3D::draw(){
	Alphabet text;
	std::cout << "Start draw maps, vector size = " << combinedModel.size() << "\n";
	combinedModel.moveResult(-panX,-panY,zoomAmount)
		     .rotationResult(rotateDegZ,centerPoint,'z')
                     .rotationResult(rotateDegX,centerPoint,'x')
		     .rotationResult(rotateDegY,centerPoint,'y')
		     .draw(eye);
	//TODO tambahkan untuk draw weather jika enabled
	
	int i;
	Point3D temploc3;
	Point temploc;
	
	std::cout << "Start draw weather information:\n";
	for (i=0;i<weatherInformation.getSize();i++) {
		std::cout << "City number " << i << "\n";
		City currentCity = weatherInformation.getCity(i);
		// 1. Get point projection
		// TODO how about edit City.h so that it uses Point3D?
		// Get Point3D of the city
		temploc3.setX(currentCity.getLocation().getX());
		temploc3.setY(currentCity.getLocation().getY());
		temploc3.setZ(100);
		
		// Follow the transformations
		temploc3.move(-panX,-panY,zoomAmount);
		temploc3.rotate(rotateDegZ,centerPoint,'z');
		temploc3.rotate(rotateDegX,centerPoint,'x');
		temploc3.rotate(rotateDegY,centerPoint,'y');
		
		temploc = temploc3.projectionResult(eye);
		
		if (temploc.getX()>0 && temploc.getX()<640 && temploc.getY()>0 && temploc.getY()<480) {
		// 2. Draw the city name
		//text.drawText(currentCity.getCityName(),temploc.getX(),temploc.getY(),100, 255,255,255,255);
		
		// 3. Draw the city's other stats
		// 3.1. Draw cuaca
		//currentCity.getWeather().getWeatherAnimation().startAnimation();
		}
	}
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
