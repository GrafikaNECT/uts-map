#ifndef GIS3D_h
#define GIS3D_h

#include "Model3D.h"
#include "WeatherInformation.h"

class GIS3D{
	public:
	GIS3D();

	void add(Model3D model3D);
	//TODO tambahkan untuk set/add weather

	void pan(std::string dir);
	void zoom(std::string dir);
	void rotate(std::string dir);

	void enableLayer(int layerNum);
	void disableLayer(int layerNum);
	void toggleLayer(int layerNum);

	void enableWeather();
	void disableWeather();
	void toggleWeather();

	bool isLayerEnabled(int layerNum);
	bool isWeatherEnabled();

	void draw();

	private:
	WeatherInformation weatherInformation;
	std::vector<Model3D> layers;
	std::vector<bool> layerEnabled;

	Model3D combinedModel;
	void updateCombinedModel();

	//TODO tambahkan untuk informasi weather di sini
	//bebas mau pake apa aja
	bool weatherEnabled;

	int panX;
	int panY;
	int zoomAmount;
	int rotateDegX;
	int rotateDegY;
	int rotateDegZ;
};

#endif
