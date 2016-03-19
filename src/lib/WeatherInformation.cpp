#include "../include/WeatherInformation.h"
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
  	std::ifstream myfile("../assets/indonesia_city_coordinates/kota.txt");
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

          std::cout << i << " "  << line << '\n';
          std::istringstream iss(line);
          getline (myfile,line);  

          if (i == 0) { //coordinate
            iss >> x;
            iss >> y;
          } else if (i == 1) { //weatherType
            if (line == "cloudy")
              weatherType = 1;
            else if (line == "rainy")
              weatherType = 2;
            else if (line == "sunny")
                weatherType = 3;
            else if (line == "stormy")
                weatherType = 4;
            else if (line == "partially cloudy")
                weatherType = 5;
          } else if (i == 3) {
            iss >> _temperature;
          } else if (i == 4) {
            iss >> _windDirection;
            iss >> _wind;
          } else if (i == 5) {
            iss >> _humidity;
          } else if (i == 6) {
            iss >> _dewPoint;
          } else if (i == 7) {
            iss >> _pressure;
          } else if (i == 8) {
            iss >> _visibility;
          } else if (i == 9) {
            iss >> _uvIndex;
          }
        }

    		City city = City(_name, x, y, weatherType, _temperature, _windDirection, _wind, _humidity, _dewPoint, _pressure,
    _visibility, _uvIndex);

        listOfCities.push_back(city);
    	}
    	myfile.close();
  	}

  	else std::cout << "Unable to open file";
}
