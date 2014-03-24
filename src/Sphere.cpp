/*
 * Sphere.cpp
 *
 *  Created on: 22 janv. 2014
 *      Author: Tanguy
 */

#include "Sphere.h"
#include "math.h"

using namespace std;

//sphere

//constructeur vide...
Sphere::Sphere()
{

}

//------------------------------------------------------------------------
//retourne le rayon de la sphere
float Sphere::getRayon()
{
	return m_r;
}
//------------------------------------------------------------------------
//retourne le centre de la sphere
PVect Sphere::getCentre()
{
	return m_c;
}
//------------------------------------------------------------------------
//lance un rayon vers la sphere objet et modifie le rayon s'il touche la sph�re
void Sphere::intersect(Rayon &R)
{
	PVect Cs = 	R.m_o - m_c;
	float A = 1.0;
	float B = (Cs*R.m_v)*2.0;
	float C = Cs.squareLength()-m_r*m_r;
	float delta=B*B-4*A*C;

	if (delta<0.0)
	{
		// D�ja Initialis� � false
	}
	else if(delta==0.0)
	{
		R.m_hit=true;
		R.m_t=-B+2*A;
	}
	else
	{
		float sqrtDelta=sqrt(delta);
		R.m_hit=true;
		float t1=(-B-sqrtDelta)/(2.0*A);
		float t2=(-B+sqrtDelta)/(2.0*A);
		if (t1<t2)
		{
			R.m_t=t1;
		}
		else
		{
			R.m_t=t2;
		}
	}
}

//------------------------------------------------------------------------
//Renvoi le PVect de la Brdf selon Lambert ou phong
PVect Sphere::getBrdf(PVect vo,PVect vi,PVect N)
{
	return (m_brdf->Modele(vo,vi,N));
}
//------------------------------------------------------------------------
//Red�finition de l'op�rateur !=
bool Sphere::operator!=(Sphere const& a){
	return !(this->m_c==a.m_c && a.m_r==this->m_r);
}

//retourne true si c'est une sphere miroir, else = false
bool Sphere::isMiroir()
{
	return m_brdf->isMiroir();
}
