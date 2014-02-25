/*
 * Brdf.h
 *
 *  Created on: 25 févr. 2014
 *      Author: Tanguy
 */

#ifndef BRDF_H_
#define BRDF_H_

#include "Source.h"
#include "Sphere.h"
#include "Image.h"
#include "Rayon.h"
#include "vector.h"

class Brdf {
private:
	PVect m_kd;
public:
	Brdf(PVect color);
};

#endif /* BRDF_H_ */
