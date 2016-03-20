#include "../include/SolidPolygon.h"
#include "../include/CurveShape.h"
#include "../include/Curve.h"
#include "../include/Printer.h" 

CurveShape::CurveShape(std::string fileName) {
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
        outlineTexture = Texture::createSingleColorTexture(R,G,B,alpha);
        //cout << "outline " << R << " " << G << " " << B << " " << alpha << endl;


        getline(infile, line); // fill
        std::istringstream fill(line);
        
        fill >> next;
        R = next;
        fill >> next;
        G = next;
        fill >> next;
        B = next;
        fill >> next;
        alpha = next;
        fillTexture = Texture::createSingleColorTexture(R,G,B,alpha);
        //cout << "fill " << R << " " << G << " " << B << " " << alpha << endl;

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

void CurveShape::push_back(int x, int y){
	Point p(x,y);
	push_back(p);
}

void CurveShape::draw(){
    std::vector<Point> tmp(4);
    std::vector<Point> path;
    SolidPolygon fill(fillTexture);

    for (int i = 0; i < this->size()-3; i+=3) {
      for (int j=0;j<4;j++)
        tmp[j]=this->at(i+j);
      Curve curve(tmp,outlineTexture);
      path = curve.getPathPoints();
      fill.insert(fill.end(),path.begin(),path.end());
      path.clear();
    }

    //draw fill
    fill.draw();

    //draw outline
    for (int i=0;i<fill.size();i++) {
        outlineTexture.draw(fill.at(i).getX(), fill.at(i).getY());
    }
}

// Operations
void CurveShape::move(int dx, int dy) {
    for(int i=0; i<this->size(); i++) {
        this->at(i).move(dx, dy);
    }
}

void CurveShape::scale(float s) {
//TODO: nilta tolong editin yaaa soalnya dia bingung titik pusatnya haha
    /*if (this->size() > 0) {  
        int x = this->at(0).getX();
        int y = this->at(0).getY();
        for(int i=0; i<this->size(); i++) {
            this->at(i).scale(s);
        }
        int _x = this->at(0).getX();
        int _y = this->at(0).getY();
        for(int i=0; i<this->size(); i++) {
            if (s>0) {
                this->at(i).move(x-_x, y-_y);
            } else {
                this->at(i).move(_x-x, _y-y);
            }
        }
        outlineTexture = outlineTexture.scaleResult(s);
        fillTexture = fillTexture.scaleResult(s);
    }*/
    for(int i=0; i<this->size(); i++) {
        this->at(i).scale(s);
    } 
}

void CurveShape::scale(float sx, float sy) {
//TODO: nilta tolong editin yaaa soalnya dia bingung titik pusatnya haha
    for(int i=0; i<this->size(); i++) {
        this->at(i).scale(sx, sy);
    }
}

void CurveShape::scale(float s, int cx, int cy) {
//TODO: nilta tolong editin yaaa soalnya dia bingung titik pusatnya haha
    for(int i=0; i<this->size(); i++) {
        this->at(i).scale(s, cx, cy);
    }
}

void CurveShape::scale(float s, Point& cp) {
//TODO: nilta tolong editin yaaa soalnya dia bingung titik pusatnya haha
    for(int i=0; i<this->size(); i++) {
        this->at(i).scale(s, cp);
    }
}

void CurveShape::rotate(float t) {
//TODO: nilta tolong editin yaaa soalnya dia bingung titik pusatnya haha
    for(int i=0; i<this->size(); i++) {
        this->at(i).rotate(t);
    }
}

void CurveShape::rotate(float t, int cx, int cy) {
//TODO: nilta tolong editin yaaa soalnya dia bingung titik pusatnya haha
    for(int i=0; i<this->size(); i++) {
        this->at(0).rotate(t, cx, cy);
    }
}

void CurveShape::rotate(float t, const Point& cp) {
//TODO: nilta tolong editin yaaa soalnya dia bingung titik pusatnya haha
    for(int i=0; i<this->size(); i++) {
        this->at(0).rotate(t, cp);
    }
}


void CurveShape::setOutlineTexture(Texture t){
    outlineTexture = t;
}
void CurveShape::setFillTexture(Texture t){
    fillTexture = t;
}

void CurveShape::setTexture(Texture t){
    setOutlineTexture(t);
    setFillTexture(t);
}
