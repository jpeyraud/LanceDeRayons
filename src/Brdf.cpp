/*
 * Brdf.cpp
 *
 *  Created on: 25 févr. 2014
 *      Author: Tanguy
 */

#include "Brdf.h"




//applique le modele de lambert sur la sphere "sphere" au point de contact avec le rayon avec une source en i,j de l'image
PVect Lambert::Modele(PVect vo,PVect Vi,PVect N)
{
	PVect Pix=PVect(0.0,0.0,0.0);
		//PVect Ps = source.getPosition();
		//calcul point d'impact
		//PVect I=rayon.m_o+(rayon.m_t*rayon.m_v);

		//calcul de la normale
		//PVect N=I-vo;
		//N.normalize();


		//calcul du Vi
		//PVect Vi=Ps-I;
		//Vi.normalize();

		//calcul du teta
		float teta=N*Vi;

		if (teta<0.0){
			teta=0.0;
		}

		//préparation du PVect couleur
		Pix.x+=m_kd.x*teta;
		Pix.y+=m_kd.y*teta;
		Pix.z+=m_kd.z*teta;

//		Pix.x+=(source.getPuissance().x*m_kd.x)*teta;
//		Pix.y+=(source.getPuissance().y*m_kd.y)*teta;
//		Pix.z+=(source.getPuissance().z*m_kd.z)*teta;

	return Pix;
}


//applique le modele de phong sur la sphere "sphere" au point de contact avec le rayon avec une source en i,j de l'image
//avec un coefficient n de spécularité et Ks la composante couleur de la spécularité
PVect Phong::Modele(PVect vo,PVect vi,PVect N)
{
	//calcul du teta
		//PVect Ps = source.getPosition();
		//calcul point d'impact
		//PVect I=rayon.m_o+(rayon.m_t*rayon.m_v);

		//calcul de la normale
		//PVect N=I-sphere.getCentre();
		N.normalize();


		//calcul du Vi
		//PVect Vi=Ps-I;
		//Vi.normalize();

		//calcul du teta
		float teta=N*vi;

		if (teta<0.0){
			teta=0.0;
		}

		PVect vd=vo-vi;
		//calcul alpha
		PVect H=vi-vd;
		H.normalize();
		float alpha=H*N;

		if (alpha<0.0){
			alpha=0.0;
		}

	return(CalcModelePhong(alpha,teta));
}
//---------------------------------------------------------------------------
//renvoie le calcul de phong avec la partie diffuse et la partie spéculaire
PVect Phong::CalcModelePhong(float alpha,float teta){

		PVect partie_dif;
		PVect partie_spec;
		PVect P;

		//calcul du cosalpha puissance n
	    float value = pow(alpha, m_n);

	    //calcul de la partie diffuse de Phong
	    partie_dif.x = (1.0/M_PI)*m_kd.x;
	    partie_dif.y = (1.0/M_PI)*m_kd.y;
	    partie_dif.z = (1.0/M_PI)*m_kd.z;

	    //calcul de la partie speculaire de Phong
	    partie_spec.x = ((m_n+2.0)/(2.0*M_PI))*m_ks.x*value;
	    partie_spec.y = ((m_n+2.0)/(2.0*M_PI))*m_ks.y*value;
	    partie_spec.z = ((m_n+2.0)/(2.0*M_PI))*m_ks.z*value;

	    //Application du modele de Phong
	    P.x = (partie_dif.x + partie_spec.x)*teta;
	    P.y = (partie_dif.y + partie_spec.y)*teta;
	    P.z = (partie_dif.z + partie_spec.z)*teta;

	    return P;
}

