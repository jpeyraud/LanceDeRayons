/*
 * Fond.h
 *
 *  Created on: 23 mars 2014
 *      Author: Tanguy
 */

#ifndef Plan_H_
#define Plan_H_
#include "PVect.h"
#include "Brdf.h"
#include "Rayon.h"

class Plan {
private :
	PVect m_color;
	PVect m_point;
	PVect m_norm;
	Brdf *m_brdf;

public:
	Plan(PVect color,PVect point,PVect norm,Brdf *b):m_color(color),m_point(point),m_norm(norm),m_brdf(b){};
	Plan(){};
	void intersect(Rayon &R);
	PVect getNorm();
	PVect getBrdf(PVect vo,PVect vi,PVect N);
};

#endif /* Plan_H_ */
