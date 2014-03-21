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
	float sizeX=32.0,sizeY=24.0; // en mm
	float f=50.0;
	int resX=640, resY=480;

	Image img = Image(resX,resY,PVect(0.0,0.0,0.0));

	float dx=sizeX/resX, dz=sizeY/resY;
	PVect p0 = PVect(-sizeX/2.0+dx/2.0,f,sizeY/2.0-dz);
	PVect origin = PVect(0.0,0.0,0.0);

	PVect BLANC = PVect(255.0,255.0,255.0);

	Scene myScene = Scene();
	myScene.testAA();

	img.takePictureOmbre(f, dx, dz, p0, origin, myScene, 1);

	img.save("sphereTest.ppm");

	system("Pause");

	return 0;
}

