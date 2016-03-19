#include "../include/Weather.h"
#include "../include/WeatherAnimation.h"

WeatherAnimation::WeatherAnimation(int weatherType) {
	type = weatherType;
	switch (type) {
		case Weather::CLOUDY:
		  createCloudyWeather();
		  break;
		case Weather::RAINY:
		  createRainyWeather();
		  break;
		case Weather::SUNNY:
		  createSunnyWeather();
		  break;
		case Weather::STORMY:
		  createStormyWeather();
		  break;
		case Weather::SUNCLOUD:
		  createSunnyCloudyWeather();
		  break;
		default:
		  break;
	}
}

WeatherAnimation::~WeatherAnimation() {
}

void WeatherAnimation::createCloudyWeather() {
	addFrame("../assets/weather/cloudy/cloudy_1.txt");
	addFrame("../assets/weather/cloudy/cloudy_2.txt");
}

void WeatherAnimation::createRainyWeather() {
	addFrame("../assets/weather/rainy/rainy_1.txt");
	addFrame("../assets/weather/rainy/rainy_2.txt");
}

void WeatherAnimation::createSunnyWeather() {
	addFrame("../assets/weather/sunny/sunny_1.txt");
	addFrame("../assets/weather/sunny/sunny_2.txt");
}

void WeatherAnimation::createSunnyCloudyWeather() {
	addFrame("../assets/weather/sunnycloudy/suncloud_1.txt");
	addFrame("../assets/weather/sunnycloudy/suncloud_3.txt");
	addFrame("../assets/weather/sunnycloudy/suncloud_2.txt");
	addFrame("../assets/weather/sunnycloudy/suncloud_3.txt");


}

void WeatherAnimation::createStormyWeather() {
	addFrame("../assets/weather/thunder/thunder_1.txt");
	addFrame("../assets/weather/thunder/thunder_2.txt");
}
