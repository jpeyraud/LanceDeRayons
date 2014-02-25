/*
 * Scene.h
 *
 *  Created on: 4 févr. 2014
 *      Author: Altarrys
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "vector.h"
#include "Sphere.h"
#include "Rayon.h"

class Scene
{
private:
	//vector de toutes les sphères dans la scène
	vector<Sphere> m_objectsList;

public:
	//constructeur vide...
	Scene();

	//destructeur de la scène
	virtual ~Scene();

	//Lance un rayon r et retourne la sphere avec un intersect retournant le plus petit des m_t.
	//On ne modifie le rayon que si intersect retourne un m_hit=true et un plus petit m_t que le courant
	Sphere lanceRayon(Rayon& r);

	//Différentes images
	void imageCarre();
};

#endif /* SCENE_H_ */
