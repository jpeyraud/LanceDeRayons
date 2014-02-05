/*
 * Rayon.h
 *
 *  Created on: 22 janv. 2014
 *      Author: Altarrys
 */

#ifndef RAYON_H_
#define RAYON_H_

#include "Pvect.h"
//#include "Sphere.h"

class Rayon
{

public:
	Rayon(PVect o, PVect v);
	virtual ~Rayon();

	PVect m_o;
	PVect m_v;
	bool m_hit;
	float m_t;
};

#endif /* RAYON_H_ */
