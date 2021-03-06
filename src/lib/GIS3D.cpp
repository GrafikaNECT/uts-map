#ifndef GIS3D_cpp
#define GIS3D_cpp

#include "../include/GIS3D.h"
#include "../include/Point3D.h"
#include "../include/Point.h"
#include "../include/Printer.h"
#include "../include/City.h"
#include "../include/AlphabetCurve.h"
#include <iostream>

#include <cmath>

#define PANSTEP 5
#define ZOOMSTEP 20
#define ROTATESTEP 5

#define ROTATEDEGXSTART 0
#define ROTATEDEGYSTART 0
#define ROTATEDEGZSTART 0

#define ROTATEMIN (-45)
#define ROTATEMAX 45

#define ROTATEMINZ (ROTATEDEGZSTART+ROTATEMIN)
#define ROTATEMAXZ (ROTATEDEGZSTART+ROTATEMAX)
#define ROTATEMINY (ROTATEDEGYSTART+ROTATEMIN)
#define ROTATEMAXY (ROTATEDEGYSTART+ROTATEMAX)
#define ROTATEMINX (ROTATEDEGXSTART+ROTATEMIN)
#define ROTATEMAXX (ROTATEDEGXSTART+ROTATEMAX)


GIS3D::GIS3D():panX(0),panY(0),zoomAmount(0){
	rotateDegX = ROTATEDEGXSTART;
	rotateDegY = ROTATEDEGYSTART;
	rotateDegZ = ROTATEDEGZSTART;
}

void GIS3D::add(Model3D model3D){
	layers.push_back(model3D);
	layerEnabled.push_back(true);
	updateCombinedModel();
}

void GIS3D::parseWeatherInformation(){
	weatherInformation.parse();
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

void GIS3D::enableCityName(){
	cityNameEnabled=true;
	//TODO tambahkan juga enable/disable animasi bila pakai animasi
}
void GIS3D::disableCityName(){
	cityNameEnabled=false;
	//TODO tambahkan juga enable/disable animasi bila pakai animasi
}
void GIS3D::toggleCityName(){
	if (isCityNameEnabled())
		disableCityName();
	else
		enableCityName();
}

bool GIS3D::isLayerEnabled(int layerNum){
	return layerEnabled[layerNum];
}

bool GIS3D::isWeatherEnabled(){
	return weatherEnabled;
}

bool GIS3D::isCityNameEnabled(){
	return cityNameEnabled;
}

Point3D eye(400,400,1000);
Point3D centerPoint(400,400,0);

void GIS3D::draw(){
	combinedModel.moveResult(-panX,-panY,zoomAmount)
		     .rotationResult(rotateDegZ,centerPoint,'z')
                     .rotationResult(rotateDegX,centerPoint,'x')
		     .rotationResult(rotateDegY,centerPoint,'y')
		     .draw(eye);

	static std::ifstream textFile("assets/fonts/Alphabet.txt");
	static AlphabetCurve text(textFile);
	//TODO tambahkan untuk draw weather jika enabled
	
	int i;
	Point3D temploc3;
	Point temploc;

	if (isWeatherEnabled()||isCityNameEnabled())
	for (i=0;i<weatherInformation.getSize();i++) {
		City currentCity = weatherInformation.getCity(i);
		// 1. Get point projection
		// TODO how about edit City.h so that it uses Point3D?
		// Get Point3D of the city
		temploc3.setX(currentCity.getLocation().getX());
		temploc3.setY(currentCity.getLocation().getY());
		temploc3.setZ(0);
		
		//Follow the transformations
		temploc3=temploc3
			.moveResult(-panX,-panY,zoomAmount)
			.rotationResult(rotateDegZ,centerPoint,'z')
			.rotationResult(rotateDegX,centerPoint,'x')
			.rotationResult(rotateDegY,centerPoint,'y');
		
		temploc = temploc3.projectionResult(eye);
		
		if (temploc.getX()>0 && temploc.getX()<Printer::getXRes() && temploc.getY()>0 && temploc.getY()<Printer::getYRes()) {
			Printer::drawPixSquare(temploc.getX(),temploc.getY(),5,255,0,255,255);
			// 2. Draw the city name
			if (isCityNameEnabled())
				text.drawText(currentCity.getCityName(),temploc.getX(),temploc.getY()-12,0.05, Texture::createSingleColorTexture(0,0,0,255));

				// 3. Draw the city's other stats
				// 3.1. Draw cuaca
				/*if (!currentCity.getWeather().getWeatherAnimation().getRunning())
					currentCity.getWeather().getWeatherAnimation().startAnimation();*/
				if (isWeatherEnabled()){
				CurveCollection weatherPic = currentCity.getWeather().getWeatherAnimation().getFrame();
				weatherPic = weatherPic.moveResult(temploc.getX()-currentCity.getLocation().getX()*0.1,temploc.getY()-40-currentCity.getLocation().getY()*0.1);
				weatherPic.draw();
			}
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
