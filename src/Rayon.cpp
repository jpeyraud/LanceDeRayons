/*
 * Rayon.cpp
 *
 *  Created on: 22 janv. 2014
 *      Author: Altarrys
 */

#include "Rayon.h"

Rayon::Rayon(PVect o, PVect v)
{
	m_o=o;
	m_v=v;
	m_hit=false;
	m_t=9999999.0;
}
//--------------------------------------------------------------------------------
Rayon::~Rayon()
{

}
//--------------------------------------------------------------------------------
