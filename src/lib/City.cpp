#include "../include/City.h"

City::City(std::string _name, int x, int y, int weatherType, int _temperature, std::string _windDirection,
		int _wind, int _humidity, int _dewPoint, float _pressure,
		float _visibility, int _uvIndex){
	name = _name;
	location = Point(x,y);
	weather = Weather(weatherType, _temperature, _windDirection,
		_wind, _humidity, _dewPoint, _pressure,
		_visibility, _uvIndex);
}
