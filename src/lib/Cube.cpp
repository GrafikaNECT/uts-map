#include "../include/Cube.h"

static std::vector<SolidPolygon3D> __emptyvectorsolidpolygon;

Cube::Cube(Point3D centerPoint, int dim,std::vector<Texture> textures):Model3D(__emptyvectorsolidpolygon){
		Point3D a(centerPoint),b(centerPoint),c(centerPoint),d(centerPoint),e(centerPoint),f(centerPoint),g(centerPoint),h(centerPoint);
		int halfd = dim/2;
		a.move(-halfd,halfd,halfd);
		b.move(halfd,halfd,halfd);
		c.move(halfd,halfd,-halfd);
		d.move(-halfd,halfd,-halfd);
		e.move(-halfd,-halfd,halfd);
		f.move(halfd,-halfd,halfd);
		g.move(halfd,-halfd,-halfd);
		h.move(-halfd,-halfd,-halfd);

		SolidPolygon3D face1(textures[0%textures.size()]);
		face1.push_back(a);
		face1.push_back(b);
		face1.push_back(c);
		face1.push_back(d);

		SolidPolygon3D face2(textures[1%textures.size()]);
		face2.push_back(b);
		face2.push_back(c);
		face2.push_back(g);
		face2.push_back(f);

		SolidPolygon3D face3(textures[2%textures.size()]);
		face3.push_back(d);
		face3.push_back(c);
		face3.push_back(g);
		face3.push_back(h);

		SolidPolygon3D face4(textures[3%textures.size()]);
		face4.push_back(a);
		face4.push_back(b);
		face4.push_back(f);
		face4.push_back(e);

		SolidPolygon3D face5(textures[4%textures.size()]);
		face5.push_back(a);
		face5.push_back(d);
		face5.push_back(h);
		face5.push_back(e);

		SolidPolygon3D face6(textures[5%textures.size()]);
		face6.push_back(e);
		face6.push_back(f);
		face6.push_back(g);
		face6.push_back(h);

		std::vector<SolidPolygon3D> vec;

		Model3D::push_back(face1);
		Model3D::push_back(face2);
		Model3D::push_back(face3);
		Model3D::push_back(face4);
		Model3D::push_back(face5);
		Model3D::push_back(face6);
	}
