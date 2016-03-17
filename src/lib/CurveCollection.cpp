#include "../include/CurveCollection.h"

CurveCollection::CurveCollection(std::string fileName) {
	std::ifstream infile(fileName);
    if (!infile) {
        cerr << "File not found." << endl;
        
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
