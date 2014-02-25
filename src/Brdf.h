/*
 * Brdf.h
 *
 *  Created on: 25 févr. 2014
 *      Author: Tanguy
 */

#ifndef BRDF_H_
#define BRDF_H_

#include "PVect.h"
#include "vector.h"

class Brdf {
protected:
	PVect m_kd;
public:
	Brdf();
	Brdf(PVect color):m_kd(color){};
	virtual PVect Modele(PVect vo,PVect vi,PVect N) = 0;
};




class Lambert : public Brdf {
public:
	Lambert(PVect kd):Brdf(kd){};
	PVect Modele(PVect vo,PVect vi,PVect N);
};

class Phong : public Brdf{
private :
	PVect m_ks;
	float m_n;
public :
	Phong(PVect kd,PVect ks,float n):Brdf(kd),m_ks(ks),m_n(n){};
	PVect Modele(PVect vo,PVect vi,PVect N);
	PVect CalcModelePhong(float alpha,float teta);
};

#endif /* BRDF_H_ */
