#ifndef WeatherAnimation_h
#define WeatherAnimation_h

#include "../include/Animation.h"
#include <cstdlib>
#include <string.h>
#include <unistd.h>

class WeatherAnimation : public Animation {
public:
	WeatherAnimation() {};
	WeatherAnimation(int weatherType);
	~WeatherAnimation();
		
private:
	void createCloudyWeather();
	void createRainyWeather();
	void createSunnyWeather();
	void createSunnyCloudyWeather();
	void createStormyWeather();


	int type;
};

#endif
