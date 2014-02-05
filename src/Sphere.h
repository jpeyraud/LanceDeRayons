/*
 * Sphere.h
 *
 *  Created on: 22 janv. 2014
 *      Author: Tanguy
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <iostream>
#include "PVect.h"
#include "Rayon.h"

class Sphere {

private :
	PVect m_c;
	float m_r;
	PVect m_color;

public :
	void intersect(Rayon &R);
	Sphere(PVect c, float r,PVect color);
	Sphere();
	PVect getColor();
	PVect getCentre();
};


#endif /* SPHERE_H_ */
