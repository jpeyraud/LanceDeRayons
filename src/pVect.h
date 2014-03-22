/*
 * PVect.h
 *
 *  Created on: 20 janv. 2014
 *      Author: MrCake
 */

#ifndef PVECT_H_
#define PVECT_H_

class PVect {
public:
	//coordonnées
	float x,y,z;

	//constructeur
	PVect(){};
	PVect(float x, float y, float z);

	PVect duplicate();

	/* **** SURCHARGE D OPERATEURS  **** */
	bool operator==(PVect const& B);
	
	PVect operator+(PVect const& B);
	void operator+=(PVect const& a);
	void operator+=(float k);

	PVect operator-(PVect const& B);
	void operator-=(PVect const& a);
	void operator-=(float k);

	PVect operator*(float k);
	void operator*=(float k);
	friend PVect& operator*(float k, PVect  &v); //multiplication par la gauche
	
	PVect operator/(float k);
	void operator/=(float k);

	//Produit x*x y*y z*z 
	PVect dotProduct(PVect const& B);

	//produit scalaire
	float operator*(PVect const& B);

	//produit vectoriel
	PVect operator^(PVect const& B);

	//méthodes utiles
	void print();
	float length();
	float squareLength();
	void normalize();
	PVect setVecteur(PVect const& P1, PVect const& P2);

	//RAJOUTS
	void rotate(PVect const& l1, PVect const& l2, PVect const& l3);
};

#endif /* PVECT_H_ */
