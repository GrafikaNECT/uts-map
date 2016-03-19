#include "../include/Curve.h"
#include "../include/Printer.h" 

Curve::Curve(std::string fileName) : std::vector<Point>() {
    std::ifstream infile(fileName);
    if (!infile) {
        cerr << "File not found." << endl;
        
    }

    // Using getline() to read one line at a time.
    std::string line;
    int next;
    bool isX = 1;
    while (getline(infile, line)) {

        if (line.empty()) continue;

        // Using istringstream to read the line into integers.
        std::istringstream outl(line);
        outl >> next;
        int R = next;
        outl >> next;
        int G = next;
        outl >> next;
        int B = next;
        outl >> next;
        int alpha = next;
        texture = Texture::createSingleColorTexture(R,G,B,alpha);
        //cout << "outline " << R << " " << G << " " << B << " " << alpha << endl;


        getline(infile, line); // fill
        getline(infile, line); // koor
        std::istringstream coor(line);

        int tempX;
        while (coor >> next) {
            if (isX) {
                isX = 0;
                tempX = next;
            } else {
                isX = 1;
                push_back(tempX, next);
                //cout << "x,y " << tempX << "," << next << endl; 
            }
        }        
        //cout << endl;
    }

    infile.close();
}

void Curve::push_back(int x, int y){
	Point p(x,y);
	push_back(p);
}

void Curve::draw(){
    Point tmp;
    for (double t = 0; t <= 1; t += 0.001) { 
        //tmp = getCasteljauPoint(this->size()-1, 0, t);
        tmp = calculateBezier(t);
        texture.draw(tmp.getX(), tmp.getY());
    }
}

std::vector<Point> Curve::getPathPoints() {
    std::vector<Point> tmp;
    for (double t = 0; t <= 1; t += 0.001) { 
        tmp.push_back(calculateBezier(t));
    }
    return tmp;
}

Point Curve::getCasteljauPoint(int r, int i, double t) {
	if (r==0) return this->at(i);
	Point p1 = getCasteljauPoint(r-1,i,t);
	Point p2 = getCasteljauPoint(r-1,i+1,t);
	return Point((int) ((1 - t) * p1.getX() + t * p2.getX()), (int) ((1 - t) * p1.getY() + t * p2.getY()));
}

Point Curve::calculateBezier(double t) {
    double t2 = t * t;
    double t3 = t2 * t;
    double mt = 1-t;
    double mt2 = mt * mt;
    double mt3 = mt2 * mt;
    int x = this->at(0).getX()*mt3 + 3*this->at(1).getX()*mt2*t + 3*this->at(2).getX()*mt*t2 + this->at(3).getX()*t3;
    int y = this->at(0).getY()*mt3 + 3*this->at(1).getY()*mt2*t + 3*this->at(2).getY()*mt*t2 + this->at(3).getY()*t3;
    return Point(x,y);
}

// cubic bezier
/* function Bezier(3,t,w[]):
  t2 = t * t
  t3 = t2 * t
  mt = 1-t
  mt2 = mt * mt
  mt3 = mt2 * mt
  return w[0]*mt3 + 3*w[1]*mt2*t + 3*w[2]*mt*t2 + w[3]*t3
  */

// caseljau in c#
/*
private void drawCasteljau(List<point> points) {
    Point tmp;
    for (double t = 0; t <= 1; t += 0.001) { 
        tmp = getCasteljauPoint(points.Count-1, 0, t);
        image.SetPixel(tmp.X, tmp.Y, color);
    }
}


private Point getCasteljauPoint(int r, int i, double t) { 
    if(r == 0) return points[i];

    Point p1 = getCasteljauPoint(r - 1, i, t);
    Point p2 = getCasteljauPoint(r - 1, i + 1, t);

    return new Point((int) ((1 - t) * p1.X + t * p2.X), (int) ((1 - t) * p1.Y + t * p2.Y));
}
*/