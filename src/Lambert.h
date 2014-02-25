/*
 * Lambert.h
 *
 *  Created on: 25 févr. 2014
 *      Author: Tanguy
 */

#ifndef LAMBERT_H_
#define LAMBERT_H_

#include "Brdf.h"

class Lambert : public Brdf {
public:
	Lambert(PVect kd);
	PVect ModeleLambert(Image *img,PVect vo,Source source,Rayon rayon);
};

#endif /* LAMBERT_H_ */
