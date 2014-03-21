/*
 * Rayon.h
 *
 *  Created on: 22 janv. 2014
 *      Author: Altarrys
 */

#ifndef RAYON_H_
#define RAYON_H_

#include "Pvect.h"

class Rayon
{

public:

	Rayon(PVect o, PVect v);
	Rayon();
	//destructeur de rayon...
	virtual ~Rayon();

	//Origine du rayon
	PVect m_o;

	//direction du rayon
	PVect m_v;

	//boolean indiquant si le rayon touche une sphère ou pas
	bool m_hit;

	//coefficient t dans o+t*v
	float m_t;
};

#endif /* RAYON_H_ */
