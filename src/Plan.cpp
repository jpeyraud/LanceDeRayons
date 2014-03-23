/*
 * Fond.cpp
 *
 *  Created on: 23 mars 2014
 *      Author: Tanguy
 */

#include "Plan.h"


void Plan::intersect(Rayon &R)
{
	if (!((R.m_o-m_point)*m_norm==0) && !(R.m_v*m_norm==0)){

		float m=R.m_v*m_norm;
		if(m>0.01){
			float up=(R.m_o-m_point)*m_norm;
			float t=(-up/m);
			if(t>0.0){
				R.m_t=t;
				R.m_hit=true;
			}
		}
	}

}

PVect Plan::getNorm(){
	return m_norm;
}

//------------------------------------------------------------------------
//Renvoi le PVect de la Brdf selon Lambert ou phong
PVect Plan::getBrdf(PVect vo,PVect vi,PVect N)
{
	return (m_brdf->Modele(vo,vi,N));
}
