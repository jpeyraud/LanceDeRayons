/*
 * Lambert.cpp
 *
 *  Created on: 25 févr. 2014
 *      Author: Tanguy
 */

#include "Lambert.h"

Lambert::Lambert(PVect kd) {
	// TODO Auto-generated constructor stub
	Brdf(kd);
}

//applique le modele de lambert sur la sphere "sphere" au point de contact avec le rayon avec une source en i,j de l'image
PVect Lambert::ModeleLambert(Image *img,PVect vo,Source source,Rayon rayon)
{
	PVect Pix=PVect(0.0,0.0,0.0);
		PVect Ps = source.getPosition();
		//calcul point d'impact
		PVect I=rayon.m_o+(rayon.m_t*rayon.m_v);

		//calcul de la normale
		PVect N=I-vo;
		N.normalize();


		//calcul du Vi
		PVect Vi=Ps-I;
		Vi.normalize();

		//calcul du teta
		float teta=N*Vi;

		if (teta<0.0){
			teta=0.0;
		}

		//préparation du PVect couleur
		Pix.x+=(source.getPuissance().x*m_kd.x)*teta;
		Pix.y=+(source.getPuissance().y*m_kd.y)*teta;
		Pix.z+=(source.getPuissance().z*m_kd.z)*teta;

	return Pix;
}
