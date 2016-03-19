#include "../include/WeatherInformation.h"
#include <assert.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


WeatherInformation::WeatherInformation() {
	parse();
}

WeatherInformation::~WeatherInformation() {

}

void WeatherInformation::parse() {
	std::string line;
  	std::ifstream myfile("assets/indonesia_city_coordinates/kota.txt");
  	if (myfile.is_open())
  	{
		while ( getline (myfile,line) )
    	{
        string _name;
        int x;
        int y;
        int weatherType;
        int _temperature;
        std::string _windDirection;
        int _wind;
        int _humidity; 
        int _dewPoint;
        float _pressure;
        float _visibility;
        int _uvIndex;

    		_name = line;

        for (int i = 0; i < 10; i++) {

          //std::cout << i << " "  << line << '\n';
          getline (myfile,line);  
          std::istringstream iss(line);

          if (i == 0) { //coordinate
            iss >> x;
            iss >> y;
          } else if (i == 1) { //weatherType
            if (line == "cloudy")
              weatherType = Weather::CLOUDY;
            else if (line == "rainy")
              weatherType = Weather::RAINY;
            else if (line == "sunny")
                weatherType = Weather::SUNNY;
            else if (line == "stormy")
                weatherType = Weather::STORMY;
            else if (line == "partially cloudy") {
                assert(line == "partially cloudy");
                weatherType = Weather::SUNCLOUD;
            }
          } else if (i == 2) {
            iss >> _temperature;
          } else if (i == 3) {
            iss >> _windDirection;
            iss >> _wind;
          } else if (i == 4) {
            iss >> _humidity;
          } else if (i == 5) {
            iss >> _dewPoint;
          } else if (i == 6) {
            iss >> _pressure;
          } else if (i == 7) {
            iss >> _visibility;
          } else if (i == 8) {
            iss >> _uvIndex;
          }
        }
        // std::cout << "Create city " << _name << "; (" << x << "," << y << "); weatherType " << weatherType << "; temp " << _temperature << "; winddir " << _windDirection << "; wind " << _wind << "; humid " << _humidity << "; dewpoint " << _dewPoint << "; pressure" << _pressure << endl;
    		City city = City(_name, x, y, weatherType, _temperature, _windDirection, _wind, _humidity, _dewPoint, _pressure,
    _visibility, _uvIndex);

        listOfCities.push_back(city);
    	}
    	myfile.close();

      std::cout << "Number of cities : " << listOfCities.size() << "\n";
  	}

  	else std::cout << "Unable to open file";
}
