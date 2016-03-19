#ifndef GIS3D_h
#define GIS3D_h

#include "Model3D.h"

class GIS3D{
	public:
	GIS3D();

	void add(Model3D model3D);

	void pan(std::string dir);
	void zoom(std::string dir);
	void rotate(std::string dir);

	void enableLayer(int layerNum);
	void disableLayer(int layerNum);
	void toggleLayer(int layerNum);

	bool isLayerEnabled(int layerNum);

	void draw();

	private:
	std::vector<Model3D> layers;
	std::vector<bool> layerEnabled;

	Model3D combinedModel;
	void updateCombinedModel();

	int panX;
	int panY;
	int zoomAmount;
	int rotateDegX;
	int rotateDegY;
	int rotateDegZ;
};

#endif
