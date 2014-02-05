/*
 * Matrice.h
 *
 *  Created on: 4 févr. 2014
 *      Author: Tanguy
 */

#ifndef MATRICE_H_
#define MATRICE_H_

#include "PVect.h"

class Matrice {

private :
	PVect m_m0;
	PVect m_m1;
	PVect m_m2;


public:
	Matrice(PVect a,PVect b,PVect c);
	friend Matrice operator*(Matrice const& a, Matrice const& b);

};

#endif /* MATRICE_H_ */
