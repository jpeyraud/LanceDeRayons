#ifndef IMAGE_H_
#define IMAGE_H_

#include <iostream>
#include <fstream>
#include "PVect.h"
#include "Source.h"
#include "Scene.h"
#include "Sphere.h"
#include "Rayon.h"
#include <vector>
#include "Brdf.h"

class Image
{

//---------------------------------------------------------------------------
public :
	Image(const int rx, const int ry,PVect color);
	void save(std::string filename);
	void load(std::string filename);
	void setPixel(int x, int y, PVect p);
	PVect getPixel(int x, int y);
	int getRezX();
	int getRezY();
	void takePicture(float f, float dx, float dz, PVect p0, PVect origin, Scene myScene, int AA_nbRayon);
	void imageMiroir(Source source,Rayon rayon,Sphere sphere,int i,int j);

//---------------------------------------------------------------------------
private :
	int m_rezX; // nb colonne
	int m_rezY; // nb ligne
	PVect* m_img;
//---------------------------------------------------------------------------

};



#endif /* IMAGE_H_ */
