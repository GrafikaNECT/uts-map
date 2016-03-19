#ifndef Weather_h
#define Weather_h

#include "../include/WeatherAnimation.h"
#include <cstdlib>
#include <string.h>
#include <unistd.h>

class Weather {
public:
	Weather(int weatherType, int _humidity, int _temperature, string _wind);
	~Weather();

	int getHumidity() { return humidity; };
	int getTemperature() { return temperature; };
	string getWind() { return wind; };

	void setHumidity(int _humidity) { humidity = _humidity; };
	void setTemperature(int _temperature) { temperature = _temperature };
	void setWind(string _wind) { wind = _wind; };

private:
	WeatherAnimation weatherAnimation;
	int humidity;
	int temperature;
	string wind;

};

#endif
