/*
 * Scene.cpp
 *
 *  Created on: 4 févr. 2014
 *      Author: Altarrys
 */


#include "Scene.h"

//scene

//mise en place des spheres dans une scène.
Scene::Scene()
{

}
//--------------------------------------------------------------------------------
//destructeur de la scène...
Scene::~Scene()
{

}
//--------------------------------------------------------------------------------
//Lance un rayon r et retourne la sphere avec un intersect retournant le plus petit des m_t.
//On ne modifie le rayon que si intersect retourne un m_hit=true et un plus petit m_t que le courant
Object Scene::lanceRayon(Rayon& r)
{
	Rayon rInt=r;
	Object Cs;
	for (unsigned int i=0; i<m_objectsList.size(); i++)
	{
		if (m_objectsList[i].type==0){
			m_objectsList[i].s.intersect(rInt);
		}
		else {
			m_objectsList[i].p.intersect(rInt);
		}
		if (rInt.m_hit && rInt.m_t < r.m_t)
		{
			r=rInt;
			Cs=m_objectsList[i];
		}
	}

	return Cs;
}
//-----------------------------------------------------------------------------------------
Object Scene::lanceRayonOmbre(Rayon& r, Object sphere)
{
	Object Cs;
	Rayon rInt=r;
	for (unsigned int i=0; i<m_objectsList.size(); i++)
	{
		if(m_objectsList[i].s!=sphere.s){
			if (m_objectsList[i].type==0){
				m_objectsList[i].s.intersect(rInt);
			}
			else {
				m_objectsList[i].p.intersect(rInt);
			}
			if (rInt.m_hit && rInt.m_t < r.m_t && rInt.m_t>0.0)
			{
				r=rInt;
				Cs=m_objectsList[i];
			}
		}
	}
	return Cs;
}
//--------------------------------------------------------------------------------
void Scene::imageCarre()
{
	m_source.push_back(Source(PVect(0.0,0.0,5.0),PVect(1.0,1.0,1.0)));
	m_source.push_back(Source(PVect(5.0,0.0,-5.0),PVect(1.0,1.0,1.0)));
	for (int i = 0 ; i< 11 ; i++)
	{
		Object s;
		s.type=0;
		s.s=Sphere(PVect(-1.0+(float(i)/5.0),6.0,1.0), 0.1,new Lambert(PVect(255.0,120.0,0.0)));
		m_objectsList.push_back(s);
		m_objectsList.push_back(s);

		m_objectsList.push_back(s);
		m_objectsList.push_back(s);

		m_objectsList.push_back(s);
		m_objectsList.push_back(s);
	}
}
//--------------------------------------------------------------------------------
void Scene::test()
{
	Object s;
	s.type=0;
	s.s=Sphere(Sphere(PVect(0.0,3.0,0.5), 0.2,new Phong(PVect(125.0,125.0,125.0),PVect(125.0,155.0,125.0),8)));
	m_source.push_back(Source(PVect(-10.0,3.2,0.7),PVect(0.0,1.0,0.0)));
	m_source.push_back(Source(PVect(0.0,2.0,0.0),PVect(0.0,0.0,1.0)));
	m_source.push_back(Source(PVect(-2.0,3.0,-2.0),PVect(1.0,0.0,0.0)));
	//m_objectsList.push_back(Sphere(PVect(0.2,3.0,0.1), 0.2,new Phong(PVect(125.0,125.0,125.0),PVect(125.0,155.0,125.0),8)));
	m_objectsList.push_back(s);
	m_objectsList.push_back(s);
	m_objectsList.push_back(s);
	m_objectsList.push_back(s);
	m_objectsList.push_back(s);
	m_objectsList.push_back(s);
	s.s=Sphere(PVect(0.0,3.0,0.5), 0.2,new Miroir());
	m_objectsList.push_back(s);
}
//--------------------------------------------------------------------------------
void Scene::testAA()
{

	Object s;
	s.type=0;
	s.s=Sphere(Sphere(PVect(0.0,3.0,0.5), 0.2,new Phong(PVect(125.0,125.0,125.0),PVect(125.0,155.0,125.0),8)));
	Object p;
	p.type=1;
	p.p=Plan(PVect(100.0,100.0,100.0),PVect(0.0,5.0,0.0),PVect(2.0,1.0,3.0),new Phong(PVect(70.0,70.0,70.0),PVect(70.0,70.0,70.0),2.0));
	m_source.push_back(Source(PVect(-1.0,0.0,0.0),PVect(1.0,1.0,1.0)));
	m_objectsList.push_back(s);
	m_objectsList.push_back(p);
}
//--------------------------------------------------------------------------------
void Scene::testJeremy()
{
	m_source.push_back(Source(PVect(0.0,5.0,-3.0),PVect(0.0,0.0,1.0)));
	Object s;
	s.type=0;
	s.s = Sphere(PVect(0.0,5.0,0.0), 0.5,new Phong(PVect(125.0,125.0,125.0),PVect(125.0,155.0,125.0),8));
	m_objectsList.push_back(s);
}
//--------------------------------------------------------------------------------
vector<Source> Scene::getSource()
{
	return m_source;
}

