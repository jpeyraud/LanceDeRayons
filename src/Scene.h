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

public:
	Scene();
	virtual ~Scene();
	Sphere lanceRayon(Rayon& r);

private:
	vector<Sphere> m_objectsList;

};

#endif /* SCENE_H_ */
