#ifndef Point_h
#define Point_h

using namespace std;

class Point {
	int x, y;
public:
	// Constructor
	Point(int _x, int _y);
	Point() {Point(0,0);};
	
	// Getter
	int getX() const;
	int getY() const;
	
	// Setter
	void setX(int _x);
	void setY(int _y);
	
	// Operations
	void move(int dx, int dy);
	void scale(float s);
	void scale(float sx, float sy);
	void scale(float s, int cx, int cy);
	void scale(float s, Point& cp);
	void rotate(float t);
	void rotate(float t, int cx, int cy);
	void rotate(float t, const Point& cp);

	Point hasilGeser(int _x, int _y) const{
		Point p(getX()+_x,getY()+_y);
		return p;
	};
	Point rotationResult(float deltaDegree) const;
	Point hasilMirror00() const;
};

#endif // POINT_H
