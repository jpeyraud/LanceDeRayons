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
	//position de la source lumineuse
	PVect m_source;

	//R,V,B (de 0.0 à 1.0)
	PVect m_puissance;

public:
	//constructeur d'une source lumineuse ponctuelle
	Source(PVect position,PVect puissance);

	//retourne la puissance de la source en PVect
	PVect getPuissance();

	//retourne la position de la source
	PVect getPosition();

};

#endif /* SOURCE_H_ */
