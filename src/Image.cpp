#ifndef IMAGE_CPP_
#define IMAGE_CPP_

#include "Image.h"
using namespace std;


//---------------------------------------------------------------------------
//Formation d'une image avec un fond unie PVect color en paramètre
Image::Image(const int rx, const int ry,PVect color)
{
	m_rezX=rx;
	m_rezY=ry;
	m_img = new PVect[m_rezY*m_rezX];

	for (int i=0; i<m_rezX*m_rezY; i++)
	{
			m_img[i].x = color.x;
			m_img[i].y = color.y;
			m_img[i].z = color.z;
	}
}
//---------------------------------------------------------------------------
//sauvegarde du fichier image
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
//chargement d'une image pré-éxistante
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
//attribut les couleur PVect de p au pixel en x,y
void Image::setPixel(int x, int y, PVect p)
{
	m_img[m_rezY*y+x]=p;
}
//---------------------------------------------------------------------------
//retourne un PVect des couleur du pixel en x,y de l'image courante
PVect Image::getPixel(int x, int y)
{
	return m_img[m_rezY*y+x];
}
//---------------------------------------------------------------------------
//retourne la taille en X de l'image(nombre de colonnes)
int Image::getRezX()
{
	return m_rezX;
}
//---------------------------------------------------------------------------
//retourne la taille en Z de l'image(nombre de lignes)
int Image::getRezY()
{
	return m_rezY;
}
//---------------------------------------------------------------------------
//applique le modele de lambert sur la sphere "sphere" au point de contact avec le rayon avec une source en i,j de l'image
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
//applique le modele de phong sur la sphere "sphere" au point de contact avec le rayon avec une source en i,j de l'image
//avec un coefficient n de spécularité et Ks la composante couleur de la spécularité
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
//renvoie le calcul de phong avec la partie diffuse et la partie spéculaire
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
//---------------------------------------------------------------------------
//Envoie le rayon Vm rayon miroir de "rayon" et attribut la couleur trouvée au point de contact I de la sphere
void Image::imageMiroir(Source source,Rayon rayon,Sphere sphere,int i,int j){
//calcul du teta
	PVect Ps = source.getPosition();
	//calcul point d'impact
	PVect I=rayon.m_o+(rayon.m_t*rayon.m_v);

	//calcul de la normale
	PVect N=I-sphere.getCentre();
	N.normalize();

	//calcul du rayon miroir
	PVect Vm=rayon.m_v-2.0*(N*rayon.m_v)*N;
	this->setPixel(i,j,this->getPixel((int)Vm.x,(int)Vm.z));
}
#endif /* IMAGE_CPP_ */
