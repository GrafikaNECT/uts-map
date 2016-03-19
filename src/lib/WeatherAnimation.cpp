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

}

void WeatherAnimation::createSunnyWeather() {

}

void WeatherAnimation::createStormyWeather() {

}
