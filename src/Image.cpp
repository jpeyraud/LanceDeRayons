#ifndef IMAGE_CPP_
#define IMAGE_CPP_

#include "Image.h"
using namespace std;


//---------------------------------------------------------------------------
Image::Image(const int rx, const int ry)
{
	m_rezX=rx;
	m_rezY=ry;
	m_img = new PVect[m_rezY*m_rezX];

	for (int i=0; i<m_rezX*m_rezY; i++)
	{
		m_img[i].x = 0;
		m_img[i].y = 0;
		m_img[i].z = 0;
	}
}
//---------------------------------------------------------------------------
void Image::save(string filename)
{
	fstream fileHandle;
	fileHandle.open(filename.c_str(), fstream::out | ios::binary);

	fileHandle << "P3" << endl;
	fileHandle << m_rezY << " " << m_rezX << endl;
	fileHandle << "255" << endl;
	for (int i=0; i<m_rezX*m_rezY; i++)
	{
		fileHandle << (int)m_img[i].x << " " << (int)m_img[i].y << " " << (int)m_img[i].z << " " ;
	}

	fileHandle.close();
}
//---------------------------------------------------------------------------
void Image::load(string filename)
{
	fstream fileHandle;
	fileHandle.open(filename.c_str(), fstream::in |ios::binary);

	for (int i=0; i<m_rezX*m_rezY; i++)
	{
		fileHandle >> m_img[i].x >> m_img[i].y >> m_img[i].z;
	}

	fileHandle.close();
}
//---------------------------------------------------------------------------
void Image::setPixel(int x, int y, PVect p)
{
	m_img[m_rezY*y+x]=p;
}
//---------------------------------------------------------------------------
PVect Image::getPixel(int x, int y)
{
	return m_img[m_rezY*y+x];
}
//---------------------------------------------------------------------------
int Image::getRezX()
{
	return m_rezX;
}
//---------------------------------------------------------------------------
int Image::getRezY()
{
	return m_rezY;
}
//---------------------------------------------------------------------------
void Image::ModeleLambert(Source source,Sphere sphere,Rayon rayon,int i,int j)
{
	PVect Pix;
	PVect Ps = source.getPosition();
	//calcul point d'impact
	PVect I=rayon.m_o+(rayon.m_t*rayon.m_v);

	//calcul de la normale
	PVect N=I-sphere.getCentre();
	N.normalize();


	//calcul du Vi
	PVect Vi=Ps-I;
	Vi.normalize();

	//calcul du teta
	float teta=N*Vi;

	if (teta<0.0){
		teta=0.0;
	}

	//préparation du PVect couleur

	Pix.x=(source.getPuissance().x*sphere.getColor().x)*teta;
	Pix.y=(source.getPuissance().y*sphere.getColor().y)*teta;
	Pix.z=(source.getPuissance().z*sphere.getColor().z)*teta;

	this->setPixel(i,j,Pix);
}
//---------------------------------------------------------------------------
void Image::ModelePhong(Source source,Sphere sphere,PVect Ks,float n,Rayon rayon,int i,int j)
{
	//calcul du teta
		PVect Ps = source.getPosition();
		//calcul point d'impact
		PVect I=rayon.m_o+(rayon.m_t*rayon.m_v);

		//calcul de la normale
		PVect N=I-sphere.getCentre();
		N.normalize();


		//calcul du Vi
		PVect Vi=Ps-I;
		Vi.normalize();

		//calcul du teta
		float teta=N*Vi;

		if (teta<0.0){
			teta=0.0;
		}

		//calcul alpha
		PVect H=Vi-rayon.m_v;
		H.normalize();
		float alpha=H*N;

		if (alpha<0.0){
			alpha=0.0;
		}

	this->setPixel(i,j,CalcModelePhong(source.getPuissance(),sphere.getColor(),Ks,n,alpha,teta));
}
//---------------------------------------------------------------------------
PVect Image::CalcModelePhong(PVect puissance,PVect Kd,PVect Ks,float n,float alpha,float teta){

		PVect partie_dif;
		PVect partie_spec;
		PVect P;

		//calcul du cosalpha puissance n
	    float value = pow(alpha, n);

	    //calcul de la partie diffuse de Phong
	    partie_dif.x = (1.0/M_PI)*Kd.x;
	    partie_dif.y = (1.0/M_PI)*Kd.y;
	    partie_dif.z = (1.0/M_PI)*Kd.z;

	    //calcul de la partie speculaire de Phong
	    partie_spec.x = ((n+2.0)/(2.0*M_PI))*Ks.x*value;
	    partie_spec.y = ((n+2.0)/(2.0*M_PI))*Ks.y*value;
	    partie_spec.z = ((n+2.0)/(2.0*M_PI))*Ks.z*value;

	    //Application du modele de Phong
	    P.x = puissance.x*(partie_dif.x + partie_spec.x)*teta;
	    P.y = puissance.y*(partie_dif.y + partie_spec.y)*teta;
	    P.z = puissance.z*(partie_dif.z + partie_spec.z)*teta;

	    return P;
}

#endif /* IMAGE_CPP_ */
