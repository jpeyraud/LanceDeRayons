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
//Constructeur d'une sphere avec c son centre, r son rayon et color sa couleur face à une lumière blanche
Sphere::Sphere(PVect c, float r,Brdf *b)
{
	m_c=c;
	m_r=r;
	m_brdf=b;
}
//------------------------------------------------------------------------
//retourne le centre de la sphere
PVect Sphere::getCentre()
{
	return m_c;
}
//------------------------------------------------------------------------
//lance un rayon vers la sphere objet et modifie le rayon s'il touche la sphère
	void Sphere::intersect(Rayon &R)
	{
		PVect Cs = 	R.m_o - m_c;
		float A = 1.0;
			float B = (Cs*R.m_v)*2.0;
			float C = Cs.lengthpow()-m_r*m_r;
			float delta=B*B-4*A*C;

			if (delta<0.0)
			{
				// Déja Initialisé à false
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
