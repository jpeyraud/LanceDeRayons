#include "PVect.h"
#include <iostream>
#include <Math.h>
#include <string>

using namespace std;

PVect::PVect(float x, float y, float z):x(x),y(y),z(z) {}


PVect PVect::duplicate(){
	return (PVect (this->x,this->y,this->z));
}
//------------------------------------------------------
//affectation
//PVect PVect::operator=(PVect& P){
//	x=P.x;
//	y=P.y;
//	z=P.z;
//	return *this;
//}
/* **************** SURCHARGE OPERATEURS ******************** */
//-----------------------------------------------------------
bool PVect::operator==(PVect const& B){
	return this->x == B.x && this->y == B.y && this->z == B.z;
}
//-----------------------------------------------------------
PVect PVect::operator+(PVect const& B){
	return PVect(this->x + B.x, this->y + B.y, this->z + B.z);
}

void PVect::operator+=(PVect const& a){
	x+=a.x;
	y+=a.y;
	z+=a.z;
}
void PVect::operator+=(float k){
	x += k;
	y += k;
	z += k;
}
//-----------------------------------------------------------
PVect PVect::operator-(PVect const& B){
	return PVect(this->x - B.x, this->y - B.y, this->z - B.z);
}
void PVect::operator-=(PVect const& a){
	x-=a.x;
	y-=a.y;
	z-=a.z;
}
//-----------------------------------------------------------
//multiplication par un  réel
PVect PVect::operator*(float k){
	return (PVect(this->x*k, this->y*k, this->z*k));
}
void PVect::operator*=(float k){
	this->x *= k;
	this->y *= k;
	this->z *= k;
}
PVect& operator*(float k, PVect &v){
	v *= k;
	return v;
}
//-----------------------------------------------------------
//division par un réel
PVect PVect::operator/(float k){
	return PVect(this->x/k,this->y/k,this->z/k);
}
void PVect::operator/=(float k){
	x/=k;
	y/=k;
	z/=k;
}
//-----------------------------------------------------------
//produit scalaire
float PVect::operator*(PVect const& B){
	return B.x*this->x+B.y*this->y+B.z*this->z;
}

//produit vectoriel
PVect PVect::operator^(PVect const& B){
	return PVect(this->y*B.z - this->z*B.y,this->z*B.x - this->x*B.z,this->x*B.y - this->y*B.x);
}

PVect PVect::dotProduct(PVect const& B){
	return(PVect(this->x*B.x, this->y*B.y, this->z*B.z));
}

/* **************** METHODES UTILES ****************************** */
//affichage du vecteur
void PVect::print(){
	cout << "(" << this->x <<"," << this->y <<","<< this->z << ")" << endl;
}

// norme du vecteur
float PVect::length() {
	return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}
float PVect::squareLength(){
	return this->x*this->x + this->y*this->y + this->z*this->z;
}

// normalisation du vecteur
void PVect::normalize() {
	float norm = this->length();
	*this /= norm;
}

PVect PVect::setVecteur(PVect const& P1, PVect const& P2){
	//return P2-P1;
	return PVect(-1, -1, -1);
}

//***************************************************************

void PVect::rotate(PVect const& l1, PVect const& l2, PVect const& l3){
	PVect v=PVect(this->x,this->y,this->z);
	this->x=l1.x*v.x+l1.y*v.y+l1.z*v.z;
	this->y=l2.x*v.x+l2.y*v.y+l2.z*v.z;
	this->z=l3.x*v.x+l3.y*v.y+l3.z*v.z;
}
