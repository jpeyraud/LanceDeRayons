/*
 * Brdf.h
 *
 *  Created on: 25 févr. 2014
 *      Author: Tanguy
 */

#ifndef BRDF_H_
#define BRDF_H_

#include "Source.h"
#include "Sphere.h"
#include "Image.h"
#include "Rayon.h"
#include "vector.h"

class Brdf {
protected:
	PVect m_kd;
	Brdf();
public:
	Brdf(PVect color):m_kd(color){};
};




class Lambert : public Brdf {
public:
	Lambert(PVect kd):Brdf(kd){};
	PVect ModeleLambert(Image *img,PVect vo,Source source,Rayon rayon);
};

class Phong : public Brdf{
public :
	PVect ModelePhong(Source source,Sphere sphere,PVect Ks,float n,Rayon rayon);
	PVect CalcModelePhong(PVect puissance,PVect Kd,PVect Ks,float n,float alpha,float teta);
};

#endif /* BRDF_H_ */
