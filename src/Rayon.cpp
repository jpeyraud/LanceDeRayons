/*
 * Rayon.cpp
 *
 *  Created on: 22 janv. 2014
 *      Author: Altarrys
 */

#include "Rayon.h"

//construction d'une rayon. m_t est placé en "infini", hit en false; o correspond à l'origine v au point d'impact.
Rayon::Rayon(PVect o, PVect v)
{
	m_o=o;
	m_v=v;
	m_hit=false;
	m_t=9999999.0;
}
//--------------------------------------------------------------------------------
//destructeur de rayon...
Rayon::~Rayon()
{

}
//--------------------------------------------------------------------------------
