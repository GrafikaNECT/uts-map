#ifndef WeatherAnimation_h
#define WeatherAnimation_h

#include "../include/Animation.h"
#include <cstdlib>
#include <string.h>
#include <unistd.h>

class WeatherAnimation : public Animation {
public:
	WeatherAnimation(int weatherType);
	~WeatherAnimation();

	static const int CLOUDY = 1;
	static const int RAINY = 2;
	static const int SUNNY = 3;
	static const int STORMY = 4;
private:
	void createCloudyWeather();
	void createRainyWeather();
	void createSunnyWeather();
	void createStormyWeather();

	int type;
};

#endif
