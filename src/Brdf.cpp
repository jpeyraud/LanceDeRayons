/*
 * Brdf.cpp
 *
 *  Created on: 25 févr. 2014
 *      Author: Tanguy
 */

#include "Brdf.h"

Brdf::Brdf(vector<Source> s)
{
	// TODO Auto-generated constructor stub
	m_source=s;
}

//applique le modele de lambert sur la sphere "sphere" au point de contact avec le rayon avec une source en i,j de l'image
void Brdf::ModeleLambert(Image *img,Sphere sphere,Rayon rayon,int i,int j)
{
	PVect Pix=PVect(0.0,0.0,0.0);
	for (int z=0;z<m_source.size();z++)
	{
		PVect Ps = m_source[z].getPosition();
		//calcul point d'impact
		PVect I=rayon.m_o+(rayon.m_t*rayon.m_v);

		//calcul de la normale
		PVect N=I-sphere.getCentre();
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
		Pix.x+=(m_source[z].getPuissance().x*sphere.getColor().x)*teta;
		Pix.y=+(m_source[z].getPuissance().y*sphere.getColor().y)*teta;
		Pix.z+=(m_source[z].getPuissance().z*sphere.getColor().z)*teta;
	}

	img->setPixel(i,j,Pix);
}

