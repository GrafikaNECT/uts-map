#include "../include/Animation.h"

Animation::Animation() {
	currentFrame = -1;
	rc = -1;
}

Animation::~Animation() {
	stopAnimation();
}

void Animation::addFrame(string filename) {
	currentFrame = 0;
	cout << filename << endl;
	frames.push_back(CurveCollection(filename));
}

void Animation::startAnimation() {
	cout << "frame size: " << frames.size() << endl;
	if (frames.size() > 1) {
		running = true;
		rc = pthread_create(&threadId, NULL, startThread, this);
	}
}

void Animation::stopAnimation() {
	if (!rc) {
		rc = -1;
		running = false;
		pthread_exit(NULL);
	}
}

void *Animation::startThread(void *threadArg) {
	Animation * animation = static_cast<Animation *>(threadArg);
	while (animation->getRunning()) {
		animation->setCurrentFrame((animation->getCurrentFrame() + 1) % animation->getFrames().size());
		usleep(25000);
	}
}