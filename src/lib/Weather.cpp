#include "../include/Weather.h"

Weather::Weather(int weatherType, int _humidity, int _temperature, string _wind) {
	weatherType = WeatherAnimation(weatherType);
	humidity = _humidity;
	temperature = _temperature;
	wind = _wind;
}
