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
#include "math.h"

class Brdf {
protected:
	PVect m_kd;
	int m_miroir;
public:
	Brdf();
	Brdf(PVect color):m_kd(color),m_miroir(0){};
	Brdf(int miroir):m_miroir(miroir){};
	virtual PVect Modele(PVect vo,PVect vi,PVect N) = 0;
	virtual PVect ModelePlan(PVect vo,PVect vi,PVect N) = 0;
	int isMiroir();
};




class Lambert : public Brdf {
public:
	Lambert(PVect kd):Brdf(kd){};
	PVect Modele(PVect vo,PVect vi,PVect N);
	PVect Lambert::ModelePlan(PVect vo,PVect Vi,PVect N);
};

class Phong : public Brdf{
private :
	PVect m_ks;
	float m_n;
public :
	Phong(PVect kd,PVect ks,float n):Brdf(kd),m_ks(ks),m_n(n){};
	PVect Modele(PVect vo,PVect vi,PVect N);
	PVect ModelePlan(PVect vo,PVect vi,PVect N);
	PVect CalcModelePhong(float alpha,float teta,bool base);
};

class PhongMod : public Phong{
public :
	PhongMod(PVect kd,PVect ks,float n):Phong(kd,ks,n){};
	PVect Modele(PVect vo,PVect vi,PVect N);
};


class PhongBase : public Phong{
public :
	PhongBase(PVect kd,PVect ks,float n):Phong(kd,ks,n){};
	PVect Modele(PVect vo,PVect vi,PVect N);
};

class Miroir : public Brdf{
public:
	Miroir():Brdf(1){};
	PVect Modele(PVect vo,PVect vi,PVect N);
	PVect ModelePlan(PVect vo,PVect vi,PVect N);
};

class Glass : public Brdf{
public :
	Glass():Brdf(2){};
	PVect Modele(PVect vo,PVect vi,PVect N){};
	PVect ModelePlan(PVect vo,PVect vi,PVect N){};
};
#endif /* BRDF_H_ */
