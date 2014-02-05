/*
 * Source.h
 *
 *  Created on: 4 févr. 2014
 *      Author: Tanguy
 */

#ifndef SOURCE_H_
#define SOURCE_H_

#include "PVect.h"

class Source {
private :
	PVect m_source;    //position de la source lumineuse
	PVect m_puissance; //R,V,B

public:
	Source(PVect position,PVect puissance);
	PVect getPuissance();
	PVect getPosition();
};

#endif /* SOURCE_H_ */
