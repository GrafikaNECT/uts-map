bin/main: bin bin/mainGIS2D.out bin/mainGIS3D.out bin/assets Makefile

bin: Makefile
	mkdir -p bin

obj: Makefile
	mkdir -p obj

bin/mainGIS2D.out: src/include/*.h src/main/mainGIS2D.cpp Makefile  obj/GIS2D.o obj/SistemWindowView.o obj/Image.o obj/Line.o obj/SolidPolygon.o obj/Point.o obj/Texture.o obj/Printer.o obj/Kbhit.o obj/Animation.o obj/WeatherAnimation.o obj/Weather.o obj/WeatherInformation.o obj/City.o obj/CurveCollection.o obj/Curve.o obj/CurveShape.o 
	g++ -g -o bin/mainGIS2D.out src/main/mainGIS2D.cpp obj/GIS2D.o obj/SistemWindowView.o obj/Image.o obj/Line.o obj/SolidPolygon.o obj/Point.o obj/Texture.o obj/Printer.o obj/Kbhit.o obj/Animation.o obj/WeatherAnimation.o obj/Weather.o obj/WeatherInformation.o obj/City.o obj/CurveCollection.o obj/Curve.o obj/CurveShape.o -std=c++11 -fpermissive -lpthread -g

bin/mainGIS3D.out: src/include/*.h src/main/mainGIS3D.cpp Makefile obj/GIS3D.o obj/Model3D.o obj/SolidPolygon3D.o obj/Point3D.o obj/SolidPolygon.o obj/Point.o obj/Printer.o obj/Texture.o obj/Kbhit.o obj/WeatherInformation.o obj/Weather.o obj/WeatherAnimation.o obj/Animation.o obj/CurveCollection.o obj/Curve.o obj/CurveShape.o obj/City.o obj/AlphabetCurve.o
	g++ -o bin/mainGIS3D.out src/main/mainGIS3D.cpp obj/GIS3D.o obj/Model3D.o obj/SolidPolygon3D.o obj/Point3D.o obj/SolidPolygon.o obj/Point.o obj/Printer.o obj/Texture.o obj/Kbhit.o obj/WeatherInformation.o obj/Weather.o obj/WeatherAnimation.o obj/Animation.o obj/CurveCollection.o obj/Curve.o obj/CurveShape.o obj/City.o obj/AlphabetCurve.o -std=c++11 -fpermissive -lpthread -g

bin/assets: src/assets src/assets/*
	rsync -rupE src/assets bin/

#object codes
#catatan: untuk dependensi include masih semuanya soalnya harus di-trace satu-satu
obj/Alphabet.o: src/lib/Alphabet.cpp src/include/Alphabet.h src/include/*
	g++ -o obj/Alphabet.o -c src/lib/Alphabet.cpp -fpermissive --std=c++11

obj/CurveCollection.o: src/lib/CurveCollection.cpp src/include/CurveCollection.h src/include/*
	g++ -o obj/CurveCollection.o -c src/lib/CurveCollection.cpp -fpermissive --std=c++11

obj/GIS3D.o: src/lib/GIS3D.cpp src/include/GIS3D.h src/include/*
	g++ -o obj/GIS3D.o -c src/lib/GIS3D.cpp -fpermissive --std=c++11

obj/LetterCurve.o: src/lib/LetterCurve.cpp src/include/LetterCurve.h src/include/*
	g++ -o obj/LetterCurve.o -c src/lib/LetterCurve.cpp -fpermissive --std=c++11

obj/Point3D.o: src/lib/Point3D.cpp src/include/Point3D.h src/include/*
	g++ -o obj/Point3D.o -c src/lib/Point3D.cpp -fpermissive --std=c++11

obj/SolidPolygon3D.o: src/lib/SolidPolygon3D.cpp src/include/SolidPolygon3D.h src/include/*
	g++ -o obj/SolidPolygon3D.o -c src/lib/SolidPolygon3D.cpp -fpermissive --std=c++11

obj/WeatherInformation.o: src/lib/WeatherInformation.cpp src/include/WeatherInformation.h src/include/*
	g++ -o obj/WeatherInformation.o -c src/lib/WeatherInformation.cpp -fpermissive --std=c++11

obj/AlphabetCurve.o: src/lib/AlphabetCurve.cpp src/include/AlphabetCurve.h src/include/*
	g++ -o obj/AlphabetCurve.o -c src/lib/AlphabetCurve.cpp -fpermissive --std=c++11

obj/Curve.o: src/lib/Curve.cpp src/include/Curve.h src/include/*
	g++ -o obj/Curve.o -c src/lib/Curve.cpp -fpermissive --std=c++11

obj/Image.o: src/lib/Image.cpp src/include/Image.h src/include/*
	g++ -o obj/Image.o -c src/lib/Image.cpp -fpermissive --std=c++11

obj/Line.o: src/lib/Line.cpp src/include/Line.h src/include/*
	g++ -o obj/Line.o -c src/lib/Line.cpp -fpermissive --std=c++11

obj/Point.o: src/lib/Point.cpp src/include/Point.h src/include/*
	g++ -o obj/Point.o -c src/lib/Point.cpp -fpermissive --std=c++11

obj/SolidPolygon.o: src/lib/SolidPolygon.cpp src/include/SolidPolygon.h src/include/*
	g++ -o obj/SolidPolygon.o -c src/lib/SolidPolygon.cpp -fpermissive --std=c++11

obj/Animation.o: src/lib/Animation.cpp src/include/Animation.h src/include/*
	g++ -o obj/Animation.o -c src/lib/Animation.cpp -fpermissive --std=c++11

obj/CurveShape.o: src/lib/CurveShape.cpp src/include/CurveShape.h src/include/*
	g++ -o obj/CurveShape.o -c src/lib/CurveShape.cpp -fpermissive --std=c++11

obj/Kbhit.o: src/lib/Kbhit.cpp src/include/Kbhit.h src/include/*
	g++ -o obj/Kbhit.o -c src/lib/Kbhit.cpp -fpermissive --std=c++11

obj/Polygon.o: src/lib/Polygon.cpp src/include/Polygon.h src/include/*
	g++ -o obj/Polygon.o -c src/lib/Polygon.cpp -fpermissive --std=c++11

obj/Texture.o: src/lib/Texture.cpp src/include/Texture.h src/include/*
	g++ -o obj/Texture.o -c src/lib/Texture.cpp -fpermissive --std=c++11

obj/City.o: src/lib/City.cpp src/include/City.h src/include/*
	g++ -o obj/City.o -c src/lib/City.cpp -fpermissive --std=c++11

obj/Girl.o: src/lib/Girl.cpp src/include/Girl.h src/include/*
	g++ -o obj/Girl.o -c src/lib/Girl.cpp -fpermissive --std=c++11

obj/Kota_.o: src/lib/Kota_.cpp src/include/Kota_.h src/include/*
	g++ -o obj/Kota_.o -c src/lib/Kota_.cpp -fpermissive --std=c++11

obj/Model3D.o: src/lib/Model3D.cpp src/include/Model3D.h src/include/*
	g++ -o obj/Model3D.o -c src/lib/Model3D.cpp -fpermissive --std=c++11

obj/Printer.o: src/lib/Printer.cpp src/include/Printer.h src/include/*
	g++ -o obj/Printer.o -c src/lib/Printer.cpp -fpermissive --std=c++11

obj/WeatherAnimation.o: src/lib/WeatherAnimation.cpp src/include/WeatherAnimation.h src/include/*
	g++ -o obj/WeatherAnimation.o -c src/lib/WeatherAnimation.cpp -fpermissive --std=c++11

obj/Cube.o: src/lib/Cube.cpp src/include/Cube.h src/include/*
	g++ -o obj/Cube.o -c src/lib/Cube.cpp -fpermissive --std=c++11

obj/GIS2D.o: src/lib/GIS2D.cpp src/include/GIS2D.h src/include/*
	g++ -o obj/GIS2D.o -c src/lib/GIS2D.cpp -fpermissive --std=c++11

obj/Letter.o: src/lib/Letter.cpp src/include/Letter.h src/include/*
	g++ -o obj/Letter.o -c src/lib/Letter.cpp -fpermissive --std=c++11

obj/PixelBoolMatrix.o: src/lib/PixelBoolMatrix.cpp src/include/PixelBoolMatrix.h src/include/*
	g++ -o obj/PixelBoolMatrix.o -c src/lib/PixelBoolMatrix.cpp -fpermissive --std=c++11

obj/SistemWindowView.o: src/lib/SistemWindowView.cpp src/include/SistemWindowView.h src/include/*
	g++ -o obj/SistemWindowView.o -c src/lib/SistemWindowView.cpp -fpermissive --std=c++11

obj/Weather.o: src/lib/Weather.cpp src/include/Weather.h src/include/*
	g++ -o obj/Weather.o -c src/lib/Weather.cpp -fpermissive --std=c++11


