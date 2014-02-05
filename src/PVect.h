#ifndef PVECT_H_
#define PVECT_H_
#include <iostream>
#include <Math.h>
class PVect {
public:
	//coordonnées
	float x,y,z;

	//constructeur
	PVect(float x, float y, float z);
	PVect();

	//surcharge d'opérateurs
public:
	friend PVect operator+(PVect const& a, PVect const& b);
	friend PVect operator-(PVect const&  a, PVect const&  b);
	friend float operator*(PVect  const& a, PVect const&  b);
	friend PVect operator*(float k, PVect const& v);
	//friend PVect operator^(PVect const& a);
	void operator+=(PVect const& a);
	void operator-=(PVect const& a);
	void operator*=(float k);
	void operator/=(float k);
	void operator=(PVect const&P);

	//méthodes utiles
	void print();
	float length();
	float lengthpow();
	void normalize();
	PVect setVecteur(PVect const& P1, PVect const& P2);
};

#endif /* PVECT_H_ */
