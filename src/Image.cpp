#ifndef IMAGE_CPP_
#define IMAGE_CPP_

#include "Image.h"
using namespace std;

//image

//---------------------------------------------------------------------------
//Formation d'une image avec un fond uni PVect color en paramètre
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

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void Image::takePicture(float f, float dx, float dz, PVect p0, PVect origin, Scene myScene)
{
	vector<Source> source=myScene.getSource();
	PVect pixFinal=PVect(0.0,0.0,0.0);
	PVect pixInt=PVect (0.0,0.0,0.0);
	PVect v,vR;
	v.y = f;
	for (int i=0; i<getRezY(); i++)
	{
		v.z = p0.z-i*dz;
		for (int j=0; j<getRezX(); j++)
		{
			v.x = p0.x+j*dx;
			vR= v;
			vR.normalize();

			Rayon r = Rayon(origin, vR);
			Sphere s = myScene.lanceRayon(r);

			if (r.m_hit)
			{
				//PVect Ps = source.getPosition();
				//calcul point d'impact
				PVect I=r.m_o+(r.m_t*r.m_v);

				//calcul de la normale
				PVect N=I-s.getCentre();
				N.normalize();



				pixFinal=PVect(0.0,0.0,0.0);
				for (unsigned int z = 0; z<source.size();z++)
				{
					//calcul du Vi
					PVect vi=source[z].getPosition()-I;
					vi.normalize();
					PVect pix = s.getBrdf(origin,vi,N);
					pixInt.x=pix.x*(source[z].getPuissance().x/M_PI);
					pixInt.y=pix.y*(source[z].getPuissance().y/M_PI);
					pixInt.z=pix.z*(source[z].getPuissance().z/M_PI);
					pixFinal.x+=pixInt.x;
					pixFinal.y+=pixInt.y;
					pixFinal.z+=pixInt.z;
				}
				if (pixFinal.x>255.0){
					pixFinal.x=255.0;
				}
				else if(pixFinal.y>255.0){
					pixFinal.y=255.0;
				}
				else if(pixFinal.z>255.0){
					pixFinal.z=255.0;
				}
				setPixel(i,j,pixFinal);
			}
	    }
	}
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
