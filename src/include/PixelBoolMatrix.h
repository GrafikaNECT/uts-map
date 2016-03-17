#ifndef pixelboolmatrix_h
#define pixelboolmatrix_h

#include <vector>
#include "Printer.h"
#include "Point.h"
#include "Polygon.h"

class PixelBoolMatrix{
	public:
	PixelBoolMatrix(int _width, int _height);
	PixelBoolMatrix(const PixelBoolMatrix& rhs);
	PixelBoolMatrix& operator=(const PixelBoolMatrix& rhs);
	~PixelBoolMatrix();

	void draw(int x, int y, unsigned char R, unsigned char G, unsigned char B, unsigned char Alpha);
	void draw(Point p, unsigned char R, unsigned char G, unsigned char B, unsigned char Alpha);

	void set(int x, int y, bool menyala);
	void set(Point p, bool menyala);

	void setAll(bool menyala);

	bool get(int x, int y);
	bool get(Point p);

	int getWidth();
	int getHeight();

	void setLine(int x1, int y1, int x2, int y2, bool menyala);
	void setLine(Point p1, Point p2, bool menyala);

	void fill(int xIgnition, int yIgnition, bool menyala);
	void fill (Point pIgnition, bool menyala);

	void setWireframe(Polygon p, bool menyala);
	void setSolid(Polygon p, bool menyala);

	private:
	int width,height;
	std::vector<std::vector<bool> >tab;

	int sign(int x);

	void swap(int * a, int * b);

	void bresenham_drawline_notvertical(int x1, int x2, int y1, int y2, bool menyala);	

	void drawline_vertical_simple(int x1, int x2, int y1, int y2, bool menyala);

	void bresenham_drawline(int x1, int x2, int y1, int y2, bool menyala);
};

#endif
