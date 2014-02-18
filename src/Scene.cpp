/*
 * Scene.cpp
 *
 *  Created on: 4 févr. 2014
 *      Author: Altarrys
 */

#include "Scene.h"
#include "Rayon.h"
#include "Image.h"
#include "Sphere.h"

//mise en place des spheres dans une scène.
Scene::Scene()
{
	//plus tard faire une fonction
	for (int i = 0 ; i< 11 ; i++)
	{
		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,1.0), 0.2, PVect(0.0,0.0,255.0)));
		m_objectsList.push_back(Sphere(PVect(-1.0,6.0,1.0-(float(i)/5.0)), 0.2, PVect(0.0,0.0,255.0)));

		m_objectsList.push_back(Sphere(PVect(1.0,6.0,-1.0+(float(i)/5.0)), 0.2, PVect(0.0,0.0,255.0)));
		m_objectsList.push_back(Sphere(PVect(1.0-(float(i)/5.0),6.0,-1.0), 0.2, PVect(0.0,0.0,255.0)));

		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,1.0-(float(i)/5.0)), 0.2, PVect(0.0,0.0,255.0)));
		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,-1.0+(float(i)/5.0)), 0.2, PVect(0.0,0.0,255.0)));

	}



//	m_objectsList.push_back(Sphere(PVect(0.5,6.0,0.0), 0.5, PVect(0.0,0.0,255.0)));
//	m_objectsList.push_back(Sphere(PVect(0.5,6.0,0.0), 0.5, PVect(0.0,0.0,255.0)));
//	m_objectsList.push_back(Sphere(PVect(0.5,6.0,0.0), 0.5, PVect(0.0,0.0,255.0)));
//	m_objectsList.push_back(Sphere(PVect(0.5,6.0,0.0), 0.5, PVect(0.0,0.0,255.0)));
//	m_objectsList.push_back(Sphere(PVect(0.5,6.0,0.0), 0.5, PVect(0.0,0.0,255.0)));
//	m_objectsList.push_back(Sphere(PVect(0.5,6.0,0.0), 0.5, PVect(0.0,0.0,255.0)));
//	m_objectsList.push_back(Sphere(PVect(0.5,6.0,0.0), 0.5, PVect(0.0,0.0,255.0)));
//	m_objectsList.push_back(Sphere(PVect(0.5,6.0,0.0), 0.5, PVect(0.0,0.0,255.0)));
//	m_objectsList.push_back(Sphere(PVect(0.5,6.0,0.0), 0.5, PVect(0.0,0.0,255.0)));
//	m_objectsList.push_back(Sphere(PVect(0.5,6.0,0.0), 0.5, PVect(0.0,0.0,255.0)));

}
//--------------------------------------------------------------------------------
//destructeur de la scène...
Scene::~Scene()
{

}
//--------------------------------------------------------------------------------
//Lance un rayon r et retourne la sphere avec un intersect retournant le plus petit des m_t.
//On ne modifie le rayon que si intersect retourne un m_hit=true et un plus petit m_t que le courant
Sphere Scene::lanceRayon(Rayon& r)
{
	Rayon rInt=r;
	Sphere Cs;
	for (unsigned int i=0; i<m_objectsList.size(); i++)
	{
		m_objectsList[i].intersect(rInt);
		if (rInt.m_hit && rInt.m_t < r.m_t)
		{
			r=rInt;
			Cs=m_objectsList[i];
		}
	}

	return Cs;
}
//--------------------------------------------------------------------------------
