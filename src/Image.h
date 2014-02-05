#ifndef IMAGE_H_
#define IMAGE_H_

#include <iostream>
#include <fstream>
#include "PVect.h"
#include "Source.h"
#include "Sphere.h"

class Image
{

//---------------------------------------------------------------------------
public :
	Image(const int rx, const int ry);
	void save(std::string filename);
	void load(std::string filename);
	void setPixel(int x, int y, PVect p);
	PVect getPixel(int x, int y);
	int getRezX();
	int getRezY();
	void Image::ModeleLambert(Source source,Sphere sphere,Rayon rayon,int i,int j);
	void Image::ModelePhong(Source source,Sphere sphere,PVect Ks,float n,Rayon rayon,int i,int j);
	PVect Image::CalcModelePhong(PVect puissance,PVect Kd,PVect Ks,float n,float alpha,float teta);

//---------------------------------------------------------------------------
private :
	int m_rezX; // nb colonne
	int m_rezY; // nb ligne
	PVect* m_img;
//---------------------------------------------------------------------------

};



#endif /* IMAGE_H_ */
