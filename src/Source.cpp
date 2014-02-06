/*
 * Source.cpp
 *
 *  Created on: 4 févr. 2014
 *      Author: Tanguy
 */

#include "Source.h"

//--------------------------------------------------------------------------------
//constructeur d'une source lumineuse ponctuelle
Source::Source(PVect position,PVect puissance){
	m_source=position;
	m_puissance=puissance;
}

//--------------------------------------------------------------------------------
//retourne la puissance de la source en PVect
PVect Source::getPuissance(){
	return m_puissance;
}

//--------------------------------------------------------------------------------
//retourne la position de la source
PVect Source::getPosition(){
	return m_source;
}
