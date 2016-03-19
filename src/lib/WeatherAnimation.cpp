#include "../include/WeatherAnimation.h"

WeatherAnimation::WeatherAnimation(int weatherType) {
	type = weatherType;
	switch (type) {
		case WeatherAnimation::CLOUDY:
		  createCloudyWeather();
		  break;
		case WeatherAnimation::RAINY:
		  createRainyWeather();
		  break;
		case WeatherAnimation::SUNNY:
		  createSunnyWeather();
		  break;
		case WeatherAnimation::STORMY:
		  createStormyWeather();
		  break;
		case WeatherAnimation::SUNCLOUD:
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
}

void WeatherAnimation::createStormyWeather() {
	addFrame("../assets/weather/thunder/thunder_1.txt");
	addFrame("../assets/weather/thunder/thunder_2.txt");
}
