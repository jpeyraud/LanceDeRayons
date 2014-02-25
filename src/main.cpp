#include "PVect.h"
#include "Image.h"
#include "Rayon.h"
#include "Sphere.h"
#include "Scene.h"
#include "Brdf.h"

#include <iostream>


using namespace std;

int main()
{
	float sizeX=36.0,sizeY=24.0; // en mm
	float f=50.0;
	int resX=640, resY=480;

	Image* img = new Image(resX,resY,PVect(0.0,0.0,0.0));
	float dx=sizeX/resX, dz=sizeY/resY;
	PVect v,vR;
	PVect p0 = PVect(-sizeX/2.0+dx/2.0,f,sizeY/2.0-dz);
	PVect origin = PVect(0.0,0.0,0.0);

	PVect BLANC = PVect(255.0,255.0,255.0);

	Scene myScene = Scene();
	vector<Source> source;
	source.push_back(Source(PVect(10.0,0.0,10.0),PVect(1.0,1.0,1.0)));
	source.push_back(Source(PVect(-10.0,0.0,-10.0),PVect(1.0,1.0,1.0)));
	Brdf brdf= Brdf(source);
	myScene.imageCarre();

	v.y = f;
	for (int i=0; i<img->getRezY(); i++)
	{
		v.z = p0.z-i*dz;
		for (int j=0; j<img->getRezX(); j++)
		{
			v.x = p0.x+j*dx;
			vR= v;
			vR.normalize();

			Rayon r = Rayon(origin, vR);
			Sphere s = myScene.lanceRayon(r);


			if (r.m_hit)
			{
				//img->setPixel(i,j,s.getColor());
				brdf.ModeleLambert(img,s,r,i,j);
				//img->ModelePhong(source,s,PVect(1.0,1.0,1.0),512,r,i,j);
				//img->imageMiroir(source,r,s,i,j);
			}
	    }
	}
	img->save("sphereTest.ppm");

	//system("Pause");

	return 0;
}

