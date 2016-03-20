#ifndef City_h
#define City_h

#include "../include/Weather.h"
#include "../include/Point.h"
#include <cstdlib>
#include <string.h>
#include <unistd.h>

class City {
public:
	City(std::string name, int x, int y, int weatherType, int _temperature, std::string _windDirection,
		int _wind, int _humidity, int _dewPoint, float _pressure,
		float _visibility, int _uvIndex);
	~City() {};

	std::string getCityName() { return name; };
	Point getLocation() { return location; };
	Weather& getWeather() { return weather; };

	void setCityName(std::string _name) { name = _name; };
	void setLocation(int x, int y ) { location = Point(x,y); };
	void setWeather (Weather _weather) { weather = _weather; };


private:
	std::string name;
	Point location;
	Weather weather;
};

#endif
