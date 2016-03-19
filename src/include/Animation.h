#ifndef Animation_h
#define Animation_h

#include "../include/Curve.h"
#include "../include/CurveShape.h"
#include "../include/CurveCollection.h"
#include "../include/Printer.h"
#include "../include/SolidPolygon.h"
#include <cstdlib>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

class Animation {
public:
	Animation();
	~Animation();
	void addFrame(string filename);
	void startAnimation();
	void stopAnimation(); 

	vector<CurveCollection> getFrames() { return frames; };
	CurveCollection getFrame() { return frames.at(currentFrame); };
	int getCurrentFrame() { return currentFrame; };
	bool getRunning() { return running; };

	void setCurrentFrame(int frame) { currentFrame = frame; };
private:
	static void *startThread(void *threadArg);

	vector<CurveCollection> frames;
	int currentFrame;
	bool running;
	pthread_t threadId;
	int rc;
};

#endif
