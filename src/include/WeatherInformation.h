#ifndef WeatherInformation_h
#define WeatherInformation_h

#include "../include/City.h"
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <vector>

class WeatherInformation {
public:
	WeatherInformation();
	~WeatherInformation();
	void parse();

	std::vector<City> getListOfCities() { return listOfCities; };

private:
	std::vector<City> listOfCities;
};

#endif
