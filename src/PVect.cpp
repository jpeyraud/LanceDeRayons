#include "PVect.h"

using namespace std;

//constructeur vide
PVect::PVect(){

}

// ===================================================
//constructeur d'une PVect
PVect::PVect(float x, float y, float z){
	this->x=x;
	this->y=y;
	this->z=z;
	}

// ===================================================
//somme & différence
PVect operator+(PVect const& a, PVect const& b){
	PVect A(a);
	A+=b;
	return A;

}

// ===================================================
void PVect::operator+=(PVect const& a){
	x+=a.x;
	y+=a.y;
	z+=a.z;
}

// ===================================================
PVect operator-(PVect const& a, PVect const& b){
	PVect A(a);
	A-=b;
	return A;

}

// ===================================================
void PVect::operator-=(PVect const& a){
	x-=a.x;
	y-=a.y;
	z-=a.z;
}

// ===================================================
//produit scalaire
float operator*(PVect const&  a, PVect const&  b){

	return b.x*a.x+b.y*a.y+b.z*a.z;
}

// ===================================================
PVect operator*(float k, PVect const&  v){
	PVect V(v);
	V*=k;
	return V;
}

// ===================================================
void PVect::operator*=(float k){
	x*=k; y*=k; z*=k;
}

// ===================================================
//produit vectoriel
//PVect PVect::operator^(PVect const& a){
//	return PVect(a.y*z-a.z*y,
//				 a.z*x-a.x*z,
//				 a.x*y-a.y*x);
//}

// ===================================================
//Division par k
void PVect::operator/=(float k){
	x/=k;
	y/=k;
	z/=k;
}

// ===================================================
//Operateur =
void PVect::operator=(PVect const& P){
	x=P.x;
	y=P.y;
	z=P.z;
	//return *this;
}

// ===================================================
//affichage du vecteur
void PVect::print(){
	cout << "(" << this->x <<"," << this->y <<","<< this->z << ")" << endl;
}

// ===================================================
// norme du vecteur
float PVect::length() {
	return sqrt(this->lengthpow());
}

// ===================================================
float PVect::lengthpow(){
	return this->x*this->x + this->y*this->y + this->z*this->z;
}

// ===================================================
// normalisation du vecteur
void PVect::normalize() {
	float norm = this->length();
	*this /= norm;
}

// ===================================================
PVect PVect::setVecteur(PVect const& P1, PVect const& P2){
	return P2-P1;
}
