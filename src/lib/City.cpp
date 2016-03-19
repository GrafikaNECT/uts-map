#include "../include/Weather.h"

Weather(std::string name, int x, int y, int weatherType, int _temperature, string _windDirection,
		int _wind, int _humidity, int _dewPoint, float _pressure,
		float _visibility, int _uvIndex){
	name = _name;
	location = Point(x,y);
	Weather = Weather(weatherType, temperature, windDirection,
		wind, humidity, dewPoint, pressure,
		visibility, uvIndex);
}
