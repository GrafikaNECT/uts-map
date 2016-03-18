#ifndef GIS2D_h
#define GIS2D_h

#include "SolidPolygon.h"
#include "Image.h"
#include "SistemWindowView.h"

#include <vector>

#define MARGIN 100
#define DEFAULTWINDOWWIDTH 400
#define BOTTOMTEXTSPACE 200

//warnawarna
#define VIEWCANVASTEXTURE Texture::createSingleColorTexture(0,0,0,255)
#define BGTEXTURE Texture::createSingleColorTexture(100,100,100,255)

class GIS2D{
	public:
	GIS2D();

	void add(Image i);

	void pan(std::string dir);
	void zoom(std::string dir);

	void enableLayer(int layerNum);
	void disableLayer(int layerNum);
	void toggleLayer(int layernum);

	bool isLayerEnabled(int layerNum);

	void draw();

	private:
	SistemWindowView sistemWindowView;
	std::vector<Image> layers;
	std::vector<bool> layerEnabled;
	SolidPolygon viewCanvas;
	SolidPolygon minimapCanvas;

	void updateSistemWindowViewImage();
};

#endif
