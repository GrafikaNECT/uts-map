#include "../include/Weather.h"
#include "../include/WeatherAnimation.h"

WeatherAnimation::WeatherAnimation(int weatherType, int x, int y) {
	type = weatherType;
	switch (type) {
		case Weather::CLOUDY:
		  createCloudyWeather(x, y);
		  break;
		case Weather::RAINY:
		  createRainyWeather(x, y);
		  break;
		case Weather::SUNNY:
		  createSunnyWeather(x, y);
		  break;
		case Weather::STORMY:
		  createStormyWeather(x, y);
		  break;
		case Weather::SUNCLOUD:
		  createSunnyCloudyWeather(x, y);
		  break;
		default:
		  break;
	}
	scale(0.1);
}

WeatherAnimation::~WeatherAnimation() {
}

void WeatherAnimation::createCloudyWeather(int x, int y) {
	addFrame("assets/weather/cloudy/cloudy_1.txt", x, y);
	addFrame("assets/weather/cloudy/cloudy_2.txt", x, y);
}

void WeatherAnimation::createRainyWeather(int x, int y) {
	addFrame("assets/weather/rainy/rainy_1.txt", x, y);
	addFrame("assets/weather/rainy/rainy_2.txt", x, y);
}

void WeatherAnimation::createSunnyWeather(int x, int y) {
	addFrame("assets/weather/sunny/sunny_1.txt", x, y);
	addFrame("assets/weather/sunny/sunny_2.txt", x, y);
}

void WeatherAnimation::createSunnyCloudyWeather(int x, int y) {
	addFrame("assets/weather/sunnycloudy/suncloud_1.txt", x, y);
	addFrame("assets/weather/sunnycloudy/suncloud_3.txt", x, y);
	addFrame("assets/weather/sunnycloudy/suncloud_2.txt", x, y);
	addFrame("assets/weather/sunnycloudy/suncloud_3.txt", x, y);
}

void WeatherAnimation::createStormyWeather(int x, int y) {
	addFrame("assets/weather/thunder/thunder_1.txt", x, y);
	addFrame("assets/weather/thunder/thunder_2.txt", x, y);
}
