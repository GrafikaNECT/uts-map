#include "../include/Alphabet.h"
#include "../include/Animation.h"
#include "../include/Curve.h"
#include "../include/CurveShape.h"
#include "../include/CurveCollection.h"
#include "../include/Girl.h"
#include "../include/Kbhit.h"
#include "../include/Printer.h"
#include "../include/WeatherAnimation.h"

#include <unistd.h>
#include <iostream>

#include <vector>

int main(){
	//inisialisasi printer
	Printer::initializePrinter();
	Printer::drawCanvas(255,255,255,255);

	WeatherAnimation cloudy = WeatherAnimation(WeatherAnimation::SUNNY);
	cloudy.startAnimation();

	while (true) {
		cloudy.getFrame().draw();
		Printer::printToScreen();
		Printer::drawCanvas(255,255,255,255);
	}

	return 0;
}
