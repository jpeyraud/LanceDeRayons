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
	//première ligne de la matrice
	PVect m_m0;

	//deuxième ligne de la matrice
	PVect m_m1;

	//troisième ligne de la matrice
	PVect m_m2;


public:
	//constructeur de matrice
	Matrice(PVect a,PVect b,PVect c);

	//opérator * pour deux matrice
	friend Matrice operator*(Matrice const& a, Matrice const& b);

};

#endif /* MATRICE_H_ */
