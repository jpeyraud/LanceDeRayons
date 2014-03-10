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
Sphere Scene::lanceRayonAARand(Rayon& r, int nbR, float dx, float dz)
{
	Sphere Cs;
	Rayon rInt=r;
	for (int i=0 ; i < nbR ; i++)
	{

		float dxRand = ( (float) rand() )/( (float) RAND_MAX) * dx - dx/2.0;
		float dzRand = ( (float) rand() )/( (float) RAND_MAX) * dz - dz/2.0;

		//cout << dx << " " << dxRand << endl;
		//cout << dz << " " << dzRand << endl;

		//system("Pause");

		rInt.m_o.x = r.m_o.x + dxRand;
		rInt.m_o.z = r.m_o.z + dzRand;
		for (unsigned int i=0; i<m_objectsList.size(); i++)
		{
			m_objectsList[i].intersect(rInt);
			if (rInt.m_hit && rInt.m_t < r.m_t)
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
		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,1.0), 0.1,new Lambert(PVect(255.0,120.0,0.0))));
		m_objectsList.push_back(Sphere(PVect(-1.0,6.0,1.0-(float(i)/5.0)), 0.1,new Lambert(PVect(0.0,0.0,255.0))));

		m_objectsList.push_back(Sphere(PVect(1.0,6.0,-1.0+(float(i)/5.0)), 0.1,new Phong(PVect(125.0,50.0,0.0),PVect(0.0,50.0,125.0),8)));
		m_objectsList.push_back(Sphere(PVect(1.0-(float(i)/5.0),6.0,-1.0), 0.1,new Phong(PVect(125.0,0.0,0.0),PVect(0.0,50.0,125.0),8)));

		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,1.0-(float(i)/5.0)), 0.1,new Lambert(PVect(0.0,0.0,255.0))));
		m_objectsList.push_back(Sphere(PVect(-1.0+(float(i)/5.0),6.0,-1.0+(float(i)/5.0)), 0.1,new Phong(PVect(0.0,0.0,125.0),PVect(0.0,0.0,125.0),8)));
	}
}
//--------------------------------------------------------------------------------
void Scene::testAA()
{
	m_source.push_back(Source(PVect(5.0,0.0,0.0),PVect(1.0,1.0,1.0)));
	m_objectsList.push_back(Sphere(PVect(0.0,3.0,0.0), 0.5,new Phong(PVect(125.0,25.0,0.0),PVect(125.0,25.0,0.0),8)));

}
//--------------------------------------------------------------------------------
vector<Source> Scene::getSource()
{
	return m_source;
}

