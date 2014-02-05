/*
 * Sphere.cpp
 *
 *  Created on: 22 janv. 2014
 *      Author: Tanguy
 */

#include "Sphere.h"
#include "math.h"

using namespace std;


Sphere::Sphere()
{

}
//------------------------------------------------------------------------
Sphere::Sphere(PVect c, float r,PVect color)
{
	m_c=c;
	m_r=r;
	m_color=color;
}
//------------------------------------------------------------------------
PVect Sphere::getColor()
{
	return m_color;
}
//------------------------------------------------------------------------
PVect Sphere::getCentre()
{
	return m_c;
}
//------------------------------------------------------------------------
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
