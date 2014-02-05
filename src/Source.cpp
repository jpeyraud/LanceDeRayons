/*
 * Source.cpp
 *
 *  Created on: 4 févr. 2014
 *      Author: Tanguy
 */

#include "Source.h"

Source::Source(PVect position,PVect puissance){
	m_source=position;
	m_puissance=puissance;
}

PVect Source::getPuissance(){
	return m_puissance;
}

PVect Source::getPosition(){
	return m_source;
}
