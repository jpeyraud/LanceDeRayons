/*
 * Matrice.cpp
 *
 *  Created on: 4 févr. 2014
 *      Author: Tanguy
 */

#include "Matrice.h"

Matrice::Matrice(PVect a,PVect b,PVect c) {


}

Matrice operator*(Matrice const& a, Matrice const& b){
	PVect c1,c2,c3;
	c1.x=a.m_m0.x*b.m_m0.x;
	c1.y=a.m_m0.y*b.m_m0.y;
	c1.z=a.m_m0.z*b.m_m0.z;

	c2.x=a.m_m1.x*b.m_m1.x;
	c2.y=a.m_m1.y*b.m_m1.y;
	c2.z=a.m_m1.z*b.m_m1.z;

	c3.x=a.m_m2.x*b.m_m2.x;
	c3.y=a.m_m2.y*b.m_m2.y;
	c3.z=a.m_m2.z*b.m_m2.z;

	Matrice c(c1,c2,c3);
	return c;
}
