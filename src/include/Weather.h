#ifndef Weather_h
#define Weather_h

#include "../include/WeatherAnimation.h"
#include <cstdlib>
#include <string.h>
#include <unistd.h>

class Weather {
public:
	Weather(int weatherType, int _temperature, string _windDirection,
		int _wind, int _humidity, int _dewPoint, float _pressure,
		float _visibility, int _uvIndex);
	~Weather();

	int getTemperature() { return temperature; };
	string getWindDirection() { return windDirection; };
	int getWind() { return wind; };
	int getHumidity() { return humidity; };
	int getDewPoint() { return dewPoint; };
	float getPressure() { return pressure; };
	float getVisibility() { return visibility; };
	int getUVIndex() { return uvIndex; };

	void setTemperature(int _temperature) { temperature = _temperature; };
	void setWindDirection(string _windDirection) { windDirection = _windDirection; };
	void setWind(int _wind) { wind = _wind; };
	void setHumidity(int _humidity) { humidity = _humidity; };
	void setDewPoint(int _dewPoint) { dewPoint = _dewPoint; };
	void setPressure(float _pressure) { pressure = _pressure; };
	void setVisibility(float _visibility) { visibility = _visibility; };
	void setUVIndex(int _uvIndex) { uvIndex = _uvIndex; };

private:
	WeatherAnimation weatherAnimation;
	int temperature;
	string windDirection;
	int wind;
	int humidity;
	int dewPoint;
	float pressure;
	float visibility;
	int uvIndex;
};

#endif
