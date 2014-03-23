/*
 * Sphere.h
 *
 *  Created on: 22 janv. 2014
 *      Author: Tanguy
 */


//sphere

#ifndef SPHERE_H_
#define SPHERE_H_

#include <iostream>
#include "PVect.h"
#include "Rayon.h"
#include "Brdf.h"

class Sphere {

private :
	//centre de la sph�re
	PVect m_c;
	//rayon de la sph�re
	float m_r;
	//couleur de la sph�re
	PVect m_color;
	//Brdf demand�e
	Brdf *m_brdf;
public :
	//lance un rayon vers la sphere objet et modifie le rayon s'il touche la sph�re
	void intersect(Rayon &R);

	//Constructeur d'une sphere avec c son centre, r son rayon et color sa couleur face � une lumi�re blanche
	Sphere(PVect c, float r,Brdf *b):m_c(c),m_r(r),m_brdf(b){};

	//constructeur vide...
	Sphere();

	//retourne le centre de la sphere
	PVect getCentre();

	//retourne le rayon de la sphere
	float getRayon();

	//get Brdf
	PVect getBrdf(PVect vo,PVect vi,PVect N);

	//renvoi le bool�en pour savoir si la sphere demand�e correspond � la sphere pr�sent�e
	bool operator!=(Sphere const& a);

	//retourne vrai si la sphere est une sphere miroir, sinon false
	bool isMiroir();
};


#endif /* SPHERE_H_ */
