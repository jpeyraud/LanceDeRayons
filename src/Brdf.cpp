/*
 * Brdf.cpp
 *
 *  Created on: 25 févr. 2014
 *      Author: Tanguy
 */

#include "Brdf.h"


//brdf
bool Brdf::isMiroir(){
	return m_miroir;
}
//applique le modele de lambert sur la sphere "sphere" au point de contact avec le rayon avec une source en i,j de l'image
PVect Lambert::Modele(PVect vo,PVect Vi,PVect N)
{
	PVect Pix=PVect(0.0,0.0,0.0);

	//calcul du teta
	float teta=N*Vi;
	//cout<<teta<<endl;
	if (teta<0.0){
		teta=0.0;
	}

	//préparation du PVect couleur
	Pix.x=m_kd.x*teta;
	Pix.y=m_kd.y*teta;
	Pix.z=m_kd.z*teta;

	return Pix;
}

//applique le modele de blin phong sur la sphere "sphere" au point de contact avec le rayon avec une source en i,j de l'image
//avec un coefficient n de spécularité et Ks la composante couleur de la spécularité
PVect Phong::Modele(PVect vo,PVect vi,PVect N)
{
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

	return(CalcModelePhong(alpha,teta,false));
}
//---------------------------------------------------------------------------
//renvoie le calcul de phong avec la partie diffuse et la partie spéculaire
PVect Phong::CalcModelePhong(float alpha,float teta,bool base){

	PVect partie_dif;
	PVect partie_spec;
	PVect P;

	//calcul du cosalpha puissance n
	float value = pow(alpha, m_n);

	if(!base){
		//calcul de la partie diffuse de Phong
		partie_dif.x = (1.0/M_PI)*m_kd.x*teta;
		partie_dif.y = (1.0/M_PI)*m_kd.y*teta;
		partie_dif.z = (1.0/M_PI)*m_kd.z*teta;

		//calcul de la partie speculaire de Phong
		partie_spec.x = (((m_n+2.0)/(2.0*M_PI))*value)*m_ks.x;
		partie_spec.y = (((m_n+2.0)/(2.0*M_PI))*value)*m_ks.y;
		partie_spec.z = (((m_n+2.0)/(2.0*M_PI))*value)*m_ks.z;

		//Application du modele de Phong
		P.x = (partie_dif.x + partie_spec.x);
		P.y = (partie_dif.y + partie_spec.y);
		P.z = (partie_dif.z + partie_spec.z);
	}
	else{
		//calcul de la partie diffuse de Phong
		partie_dif.x = m_kd.x*teta;
		partie_dif.y = m_kd.y*teta;
		partie_dif.z = m_kd.z*teta;

		//calcul de la partie speculaire de Phong
		partie_spec.x = value*m_ks.x;
		partie_spec.y = value*m_ks.y;
		partie_spec.z = value*m_ks.z;

		//Application du modele de Phong
		P.x = (partie_dif.x + partie_spec.x);
		P.y = (partie_dif.y + partie_spec.y);
		P.z = (partie_dif.z + partie_spec.z);
	}

	return P;
}
//---------------------------------------------------------------------------
PVect PhongMod::Modele(PVect vo,PVect vi,PVect N)
{
	PVect Vm=vo-2.0*(N*vo)*N;
	Vm.normalize();
	//calcul du teta
	float teta=N*vi;
	if (teta<0.0){
		teta=0.0;
	}
	float alpha=Vm*vi;

	if (alpha<0.0){
		alpha=0.0;
	}

	return(CalcModelePhong(alpha,teta,false));

}
//---------------------------------------------------------------------------
PVect PhongBase::Modele(PVect vo,PVect vi,PVect N)
{
	PVect Vm=vo-2.0*(N*vo)*N;
	Vm.normalize();
	//calcul du teta
	float teta=N*vi;
	if (teta<0.0){
		teta=0.0;
	}
	float alpha=Vm*vi;

	if (alpha<0.0){
		alpha=0.0;
	}

	return(CalcModelePhong(alpha,teta,true));
}
//---------------------------------------------------------------------------
PVect Miroir::Modele(PVect vo,PVect vi,PVect N){
	PVect Vm;
	Vm.x=vo.x+(2.0*N.x*(-1.0*N.x*vo.x));
	Vm.y=vo.y+(2.0*N.y*(-1.0*N.y*vo.y));
	Vm.z=vo.z+(2.0*N.z*(-1.0*N.z*vo.z));
	Vm.normalize();
	return Vm;
}
