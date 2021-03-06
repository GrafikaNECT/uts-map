#include "../include/Weather.h"

Weather::Weather(int x, int y, int weatherType, int _temperature, string _windDirection,
		int _wind, int _humidity, int _dewPoint, float _pressure,
		float _visibility, int _uvIndex){
	std::cout << "create weather " << weatherType << " , "  << x << " , "  << y << std::endl;
	weatherAnimation = WeatherAnimation(weatherType, x, y);
	temperature = _temperature;
	windDirection = _windDirection;
	wind = _wind;
	humidity = _humidity;
	dewPoint = _dewPoint;
	pressure = _pressure;
	visibility = _visibility;
	uvIndex = _uvIndex;
	std::cout << "size: " << getWeatherAnimation().getFrames().size() << std::endl;
}
