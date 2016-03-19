#ifndef WeatherAnimation_h
#define WeatherAnimation_h

#include "../include/Animation.h"
#include <cstdlib>
#include <string.h>
#include <unistd.h>

class WeatherAnimation : public Animation {
public:
	WeatherAnimation() {};
	WeatherAnimation(int weatherType, int x, int y);
	~WeatherAnimation();
		
private:
	void createCloudyWeather(int x, int y);
	void createRainyWeather(int x, int y);
	void createSunnyWeather(int x, int y);
	void createSunnyCloudyWeather(int x, int y);
	void createStormyWeather(int x, int y);


	int type;
};

#endif
