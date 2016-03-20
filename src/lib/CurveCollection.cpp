#include "../include/CurveCollection.h"
#include <limits.h>
#include <unistd.h>

std::string getexepath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}

CurveCollection::CurveCollection(std::string fileName) {
	std::ifstream infile(fileName);
    if (!infile) {
        cerr << "File not found. in " << getexepath << " " << fileName << endl;
        
    }
    // std::cout << "HOHO";
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
        Texture  outlineTexture = Texture::createSingleColorTexture(R,G,B,alpha);
        // std::cout << "outline " << R << " " << G << " " << B << " " << alpha << endl;


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
        Texture fillTexture = Texture::createSingleColorTexture(R,G,B,alpha);
        // std::cout << "fill " << R << " " << G << " " << B << " " << alpha << endl;

        getline(infile, line); // koor
        std::istringstream coor(line);
        std::vector<Point> vec;
        int tempX;
        while (coor >> next) {
            if (isX) {
                isX = 0;
                tempX = next;
            } else {
                isX = 1;
                vec.push_back(Point(tempX, next));
                // std::cout << "x,y " << tempX << "," << next << endl; 
            }
        }
        if (R==0 && G==0 && B==0 && alpha==0) {
        	// std::cout << "curve" << endl;
        	Curve curve(vec,outlineTexture);
        	addCurve(curve);
        } else {
        	// std::cout << "curveshape" << endl;
        	CurveShape curveShape(vec,outlineTexture,fillTexture);
        	addCurveShape(curveShape);
        }       
        // std::cout << endl;
    }

    infile.close();
}

//menambah Curve
//perhatikan orderGambar (spek di bawah)
void CurveCollection::addCurve(Curve c){
	curves.push_back(c);
	orderGambarCurve.push_back(numElmts);
	numElmts++;
}



//menambah CurveShape
//perhatikan orderGambar (spek di bawah)
void CurveCollection::addCurveShape(CurveShape curveShape){
	curveShapes.push_back(curveShape);
	orderGambarCurveShape.push_back(numElmts);
	numElmts++;
}


//gambar
//curve dan curveshapeigon
void CurveCollection::draw(){
	std::list<Curve>::iterator itcurve = curves.begin();
	std::list<CurveShape>::iterator itcurveshape = curveShapes.begin();
	std::list<int>::iterator itordcurve = orderGambarCurve.begin();
	std::list<int>::iterator itordcurveshape = orderGambarCurveShape.begin();
	
	while (itcurve != curves.end() || itcurveshape != curveShapes.end()){
		if (itordcurveshape==orderGambarCurveShape.end()){
			itcurve->draw();
			itcurve++;
			itordcurve++;
		}else if(itordcurve==orderGambarCurve.end()){
			itcurveshape->draw();
			itcurveshape++;
			itordcurveshape++;
		}else if (*itordcurve<*itordcurveshape){
			itcurve->draw();
			itcurve++;
			itordcurve++;
		}else{
			itcurveshape->draw();
			itcurveshape++;
			itordcurveshape++;
		}
	}
}

// Operations
void CurveCollection::move(int dx, int dy) {
    std::list<Curve>::iterator itcurve = curves.begin();
    std::list<CurveShape>::iterator itcurveshape = curveShapes.begin();
    std::list<int>::iterator itordcurve = orderGambarCurve.begin();
    std::list<int>::iterator itordcurveshape = orderGambarCurveShape.begin();

    while(itcurve != curves.end()) {
        itcurve->move(dx, dy);
        itcurve++;
    }
    while(itcurveshape != curveShapes.end()) {
        itcurveshape->move(dx, dy);
        itcurveshape++;
    }
}

void CurveCollection::scale(float s) {
    std::list<Curve>::iterator itcurve = curves.begin();
    std::list<CurveShape>::iterator itcurveshape = curveShapes.begin();
    std::list<int>::iterator itordcurve = orderGambarCurve.begin();
    std::list<int>::iterator itordcurveshape = orderGambarCurveShape.begin();

    while(itcurve != curves.end()) {
        itcurve->scale(s);
        itcurve++;
    }
    while(itcurveshape != curveShapes.end()) {
        itcurveshape->scale(s);
        itcurveshape++;
    }
}

void CurveCollection::scale(float sx, float sy) {
    std::list<Curve>::iterator itcurve = curves.begin();
    std::list<CurveShape>::iterator itcurveshape = curveShapes.begin();
    std::list<int>::iterator itordcurve = orderGambarCurve.begin();
    std::list<int>::iterator itordcurveshape = orderGambarCurveShape.begin();

    while(itcurve != curves.end()) {
        itcurve->scale(sx, sy);
        itcurve++;
    }
    while(itcurveshape != curveShapes.end()) {
        itcurveshape->scale(sx, sy);
        itcurveshape++;
    }
}

void CurveCollection::scale(float s, int cx, int cy) {
    std::list<Curve>::iterator itcurve = curves.begin();
    std::list<CurveShape>::iterator itcurveshape = curveShapes.begin();
    std::list<int>::iterator itordcurve = orderGambarCurve.begin();
    std::list<int>::iterator itordcurveshape = orderGambarCurveShape.begin();

    while(itcurve != curves.end()) {
        itcurve->scale(s, cx, cy);
        itcurve++;
    }
    while(itcurveshape != curveShapes.end()) {
        itcurveshape->scale(s, cx, cy);
        itcurveshape++;
    }
}

void CurveCollection::scale(float s, Point& cp) {
    std::list<Curve>::iterator itcurve = curves.begin();
    std::list<CurveShape>::iterator itcurveshape = curveShapes.begin();
    std::list<int>::iterator itordcurve = orderGambarCurve.begin();
    std::list<int>::iterator itordcurveshape = orderGambarCurveShape.begin();

    while(itcurve != curves.end()) {
        itcurve->scale(s, cp);
        itcurve++;
    }
    while(itcurveshape != curveShapes.end()) {
        itcurveshape->scale(s, cp);
        itcurveshape++;
    }
}

void CurveCollection::rotate(float t) {
    std::list<Curve>::iterator itcurve = curves.begin();
    std::list<CurveShape>::iterator itcurveshape = curveShapes.begin();
    std::list<int>::iterator itordcurve = orderGambarCurve.begin();
    std::list<int>::iterator itordcurveshape = orderGambarCurveShape.begin();

    while(itcurve != curves.end()) {
        itcurve->rotate(t);
        itcurve++;
    }
    while(itcurveshape != curveShapes.end()) {
        itcurveshape->rotate(t);
        itcurveshape++;
    }
}

void CurveCollection::rotate(float t, int cx, int cy) {
    std::list<Curve>::iterator itcurve = curves.begin();
    std::list<CurveShape>::iterator itcurveshape = curveShapes.begin();
    std::list<int>::iterator itordcurve = orderGambarCurve.begin();
    std::list<int>::iterator itordcurveshape = orderGambarCurveShape.begin();

    while(itcurve != curves.end()) {
        itcurve->rotate(t, cx, cy);
        itcurve++;
    }
    while(itcurveshape != curveShapes.end()) {
        itcurveshape->rotate(t, cx, cy);
        itcurveshape++;
    }
}

void CurveCollection::rotate(float t, const Point& cp) {
    std::list<Curve>::iterator itcurve = curves.begin();
    std::list<CurveShape>::iterator itcurveshape = curveShapes.begin();
    std::list<int>::iterator itordcurve = orderGambarCurve.begin();
    std::list<int>::iterator itordcurveshape = orderGambarCurveShape.begin();

    while(itcurve != curves.end()) {
        itcurve->rotate(t, cp);
        itcurve++;
    }
    while(itcurveshape != curveShapes.end()) {
        itcurveshape->rotate(t, cp);
        itcurveshape++;
    }
}

void CurveCollection::setCurveTexture(Texture t){
    for (std::list<Curve>::iterator it = curves.begin();it!=curves.end();it++){
         it->setTexture(t);
    }
}
void CurveCollection::setCurveShapeFillTexture(Texture t){
    for (std::list<CurveShape>::iterator it = curveShapes.begin();it!=curveShapes.end();it++){
         it->setFillTexture(t);
    }
}
void CurveCollection::setCurveShapeOutlineTexture(Texture t){
    for (std::list<CurveShape>::iterator it = curveShapes.begin();it!=curveShapes.end();it++){
         it->setOutlineTexture(t);
    }
}

void CurveCollection::setTexture(Texture t){
    setCurveTexture(t);
    setCurveShapeFillTexture(t);
    setCurveShapeOutlineTexture(t);
}

CurveCollection CurveCollection::moveResult(Point delta){
    move(delta.getX(), delta.getY());
    return *this;
}

CurveCollection CurveCollection::moveResult(int deltax, int deltay){
    move(deltax, deltay);
    return *this;
}
CurveCollection CurveCollection::scaleResult(float s){
    scale(s);
    return *this;
}

CurveCollection CurveCollection::scaleResult(float scaleX, float scaleY){
    scale(scaleX, scaleY);
    return *this;
}

CurveCollection CurveCollection::rotationResult(float deltaDegree){
    rotate(deltaDegree);
    return *this;
}

CurveCollection CurveCollection::rotationResult(float deltaDegree, Point poros){
    rotate(deltaDegree, poros);
    return *this;
}
