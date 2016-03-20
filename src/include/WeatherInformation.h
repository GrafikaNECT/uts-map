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
	int getSize() {return listOfCities.size();};
	City getCity(int i) { return listOfCities[i]; };
private:
	std::vector<City> listOfCities;
};

#endif
