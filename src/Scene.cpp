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


Scene::Scene()
{
//	for (int i = 0 ; i< 10 ; i++)
//	{
//		m_objectsList.push_back(Sphere(PVect(i/2,5+i,0.0), 0.5, PVect(0.0,0.0,255.0)));
//	}

	m_objectsList.push_back(Sphere(PVect(0.5,6.0,0.0), 0.5, PVect(255.0,0.0,0.0)));
	m_objectsList.push_back(Sphere(PVect(1.0,7.0,0.0), 0.5, PVect(0.0,255.0,0.0)));
}
//--------------------------------------------------------------------------------
Scene::~Scene()
{

}
//--------------------------------------------------------------------------------
Sphere Scene::lanceRayon(Rayon& r)
{
	float t = 999999999;
	Sphere Cs;
	for (unsigned int i=0; i<m_objectsList.size(); i++)
	{
		m_objectsList[i].intersect(r);
		if (r.m_hit && r.m_t < t)
		{
			t = r.m_t;
			Cs=m_objectsList[i];
		}
	}

	return Cs;
}
//--------------------------------------------------------------------------------
