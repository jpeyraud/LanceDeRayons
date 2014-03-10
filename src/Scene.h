/*
 * Scene.h
 *
 *  Created on: 4 févr. 2014
 *      Author: Altarrys
 */
//scene

#ifndef SCENE_H_
#define SCENE_H_

#include "vector.h"
#include "Sphere.h"
#include "Rayon.h"
#include <stdlib.h>
#include "Scene.h"
#include "Source.h"

class Scene
{
private:
	//vector de toutes les sphères dans la scène
	vector<Sphere> m_objectsList;
	vector<Source> m_source;

public:
	//constructeur vide...
	Scene();

	//destructeur de la scène
	virtual ~Scene();

	//Lance un rayon r et retourne la sphere avec un intersect retournant le plus petit des m_t.
	//On ne modifie le rayon que si intersect retourne un m_hit=true et un plus petit m_t que le courant
	Sphere lanceRayon(Rayon& r);
	Sphere lanceRayonAARand(Rayon& r, int nbR, float dx, float dz);

	//Différentes images
	void imageCarre();
	void Scene::testAA();

	//renvoi les sources de la scène
	vector<Source> Scene::getSource();
};

#endif /* SCENE_H_ */
