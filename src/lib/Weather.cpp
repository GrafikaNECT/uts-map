#include "../include/Weather.h"

Weather::Weather(int weatherType, int _temperature, string _windDirection,
		int _wind, int _humidity, int _dewPoint, float _pressure,
		float _visibility, int _uvIndex){
	weatherAnimation = WeatherAnimation(weatherType);
	temperature = _temperature;
	windDirection = _windDirection;
	wind = _wind;
	humidity = _humidity;
	dewPoint = _dewPoint;
	pressure = _pressure;
	visibility = _visibility;
	uvIndex = _uvIndex;
}
