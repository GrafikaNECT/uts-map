bin/main: bin bin/mainGIS2D.out Makefile

bin: Makefile
	mkdir -p bin

bin/mainGIS2D.out: src/lib/*.cpp src/include/*.h src/main/mainGIS2D.cpp Makefile
	g++ -o bin/mainGIS2D.out src/main/mainGIS2D.cpp src/lib/GIS2D.cpp src/lib/SistemWindowView.cpp src/lib/Image.cpp src/lib/Line.cpp src/lib/SolidPolygon.cpp src/lib/Point.cpp src/lib/Texture.cpp src/lib/Printer.cpp src/lib/Kbhit.cpp -std=c++11 -fpermissive -lpthread -g

bin/girl: src/main/girl/* Makefile
	mkdir -p bin/girl
	cp src/main/girl/* bin/girl/

bin/Alphabet-2.txt: src/main/Alphabet-2.txt Makefile
	cp src/main/Alphabet-2.txt bin/
