bin/main: bin bin/mainGIS2D.out bin/mainGIS3D.out bin/assets Makefile

bin: Makefile
	mkdir -p bin

bin/mainGIS2D.out: src/lib/*.cpp src/include/*.h src/main/mainGIS2D.cpp Makefile
	g++ -g -o bin/mainGIS2D.out src/main/mainGIS2D.cpp src/lib/GIS2D.cpp src/lib/SistemWindowView.cpp src/lib/Image.cpp src/lib/Line.cpp src/lib/SolidPolygon.cpp src/lib/Point.cpp src/lib/Texture.cpp src/lib/Printer.cpp src/lib/Kbhit.cpp src/lib/Animation.cpp src/lib/WeatherAnimation.cpp src/lib/Weather.cpp src/lib/WeatherInformation.cpp src/lib/City.cpp src/lib/CurveCollection.cpp src/lib/Curve.cpp src/lib/CurveShape.cpp -std=c++11 -fpermissive -lpthread -g

bin/mainGIS3D.out: src/lib/*.cpp src/include/*.h src/main/mainGIS3D.cpp Makefile
	g++ -o bin/mainGIS3D.out src/main/mainGIS3D.cpp src/lib/GIS3D.cpp src/lib/Model3D.cpp src/lib/SolidPolygon3D.cpp src/lib/Point3D.cpp src/lib/SolidPolygon.cpp src/lib/Point.cpp src/lib/Printer.cpp src/lib/Texture.cpp src/lib/Kbhit.cpp -std=c++11 -fpermissive -g

bin/girl: src/main/girl/* Makefile
	mkdir -p bin/girl
	cp src/main/girl/* bin/girl/

bin/Alphabet-2.txt: src/main/Alphabet-2.txt Makefile
	cp src/main/Alphabet-2.txt bin/

bin/assets: src/assets src/assets/*
	rsync -rupE src/assets bin/
