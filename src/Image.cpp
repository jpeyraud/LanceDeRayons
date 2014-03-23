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
void Image::takePicture(float f, float dx, float dz, PVect p0, PVect origin, Scene myScene, int AA_nbRayon)
{
	vector<Source> source=myScene.getSource();
	PVect pixFinal=PVect(0.0,0.0,0.0);
	PVect pixInt=PVect (0.0,0.0,0.0);
	PVect v,vR,vo;
	float dxAA = dx / 400.0;
	float dzAA = dz / 400.0;
	v.y = f;
	for (int i=0; i<getRezY(); i++)
	{
		v.z = p0.z-i*dz;
		for (int j=0; j<getRezX(); j++)
		{
			v.x = p0.x+j*dx;
			vR= v;
			vR.normalize();
			Rayon rayon=Rayon(origin, vR);
			pixFinal=PVect(0.0,0.0,0.0);
			for (int n=0 ; n < AA_nbRayon ; n++)
			{
				Rayon rInt=Rayon(origin, vR);
				Object s;
				if (AA_nbRayon > 1)
				{
					//Position random pour le rayon
					//float dxRand = (( (float) rand() )/( (float) RAND_MAX) * dx - dx/2.0)/100000.0;
					//float dzRand = (( (float) rand() )/( (float) RAND_MAX) * dz - dz/2.0)/100000.0;

					//Position fixe
					if (n == 0){
						rInt.m_v.x = rayon.m_v.x - dxAA;
						rInt.m_v.z = rayon.m_v.z - dzAA;
					}
					else if (n == 1){
						rInt.m_v.x = rayon.m_v.x - dxAA;
						rInt.m_v.z = rayon.m_v.z + dzAA;
					}
					else if (n == 2){
						rInt.m_v.x = rayon.m_v.x + dxAA;
						rInt.m_v.z = rayon.m_v.z - dzAA;
					}
					else if (n == 3){
						rInt.m_v.x = rayon.m_v.x + dxAA;
						rInt.m_v.z = rayon.m_v.z + dzAA;
					}
				}
				s = myScene.lanceRayon(rInt);
				if (rInt.m_hit)
				{
					if(s.type==0){
						//calcul point d'impact
						PVect I=rInt.m_o+(rInt.m_t*rInt.m_v);

						//calcul de la normale
						PVect N=I-s.s.getCentre();
						N.normalize();

						for (unsigned int z = 0; z<source.size();z++)
						{
							//calcul du Vi
							PVect vi=source[z].getPosition()-I;
							vi.normalize();
							PVect pix = s.s.getBrdf(I-origin,vi,N);
							pixInt.x=pix.x*(source[z].getPuissance().x);
							pixInt.y=pix.y*(source[z].getPuissance().y);
							pixInt.z=pix.z*(source[z].getPuissance().z);
							pixFinal.x+=pixInt.x;
							pixFinal.y+=pixInt.y;
							pixFinal.z+=pixInt.z;
						}
					}
					else { // touche un plan
						//calcul point d'impact
						PVect I=rInt.m_o+(rInt.m_t*rInt.m_v);
						vo = I-origin;
						vo.normalize();
						for (unsigned int z = 0; z<source.size();z++)
						{

							//calcul du Vi
							PVect vi=source[z].getPosition()-I;
							vi.normalize();
							PVect pix = s.p.getBrdf(vo,vi,s.p.getNorm());
							pixInt.x=pix.x*(source[z].getPuissance().x);
							pixInt.y=pix.y*(source[z].getPuissance().y);
							pixInt.z=pix.z*(source[z].getPuissance().z);
							pixFinal.x+=pixInt.x;
							pixFinal.y+=pixInt.y;
							pixFinal.z+=pixInt.z;
						}
					}
				}
			}
			pixFinal.x/=(float)AA_nbRayon;
			pixFinal.y/=(float)AA_nbRayon;
			pixFinal.z/=(float)AA_nbRayon;
			if (pixFinal.x>255.0){
				pixFinal.x=255.0;
			}
			if(pixFinal.y>255.0){
				pixFinal.y=255.0;
			}
			if(pixFinal.z>255.0){
				pixFinal.z=255.0;
			}
			setPixel(i,j,pixFinal);
		}
	}
}
//---------------------------------------------------------------------------
void Image::takePictureOmbre(float f, float dx, float dz, PVect p0, PVect origin, Scene myScene, int AA_nbRayon)
{
	vector<Source> source=myScene.getSource();
	PVect pixFinal=PVect(0.0,0.0,0.0);
	PVect pixInt=PVect (0.0,0.0,0.0);
	PVect v,vR, pix,vo;
	Rayon rInt(origin,vR);

	v.y = f;
	for (int i=0; i<getRezY(); i++)
	{
		v.z = p0.z-i*dz;
		for (int j=0; j<getRezX(); j++)
		{
			v.x = p0.x+j*dx;
			vR= v;
			vR.normalize();
			Rayon rayon=Rayon(origin, vR);
			pixFinal=PVect(0.0,0.0,0.0);
			for (int n=0 ; n < AA_nbRayon ; n++)
			{
				rInt=Rayon(origin, vR);

				Object s;
				/*if (AA_nbRayon > 1){
					float dxRand = (( (float) rand() )/( (float) RAND_MAX) * dx - dx/2.0)/100000.0;
					float dzRand = (( (float) rand() )/( (float) RAND_MAX) * dz - dz/2.0)/100000.0;
					rInt.m_v.x = rayon.m_v.x + dxRand;
					rInt.m_v.z = rayon.m_v.z + dzRand;
				}*/
				s = myScene.lanceRayon(rInt);
				if (rInt.m_hit)
				{
					if (s.type==0){
						//calcul point d'impact
						PVect I=rInt.m_o+(rInt.m_t*rInt.m_v);
						//calcul de la normale
						PVect N=I-s.s.getCentre();
						N.normalize();

						for (unsigned int z = 0; z<source.size();z++)
						{
							//calcul du Vi
							PVect vi=source[z].getPosition()-I;
							vi.normalize();
							Rayon rOmbre=Rayon(I.duplicate(),vi.duplicate());
							rOmbre.m_t=rInt.m_t;
							myScene.lanceRayonOmbre(rOmbre,s);
							vo=I-origin;
							vo.normalize();
							pix = s.s.getBrdf(vo,vi,N);
							if(s.s.isMiroir()){
								Rayon rMiroir=Rayon(I.duplicate(),pix.duplicate());
								Object sphereMiroir=myScene.lanceRayonOmbre(rMiroir,s);
								if (rMiroir.m_hit){
									//calcul point d'impact
									PVect IMiroir=rMiroir.m_o+(rMiroir.m_t*rMiroir.m_v);
									//calcul de la normale
									PVect NMiroir=IMiroir-sphereMiroir.s.getCentre();
									NMiroir.normalize();
									PVect viMiroir=source[z].getPosition()-IMiroir;
									viMiroir.normalize();
									pix = sphereMiroir.s.getBrdf(IMiroir,viMiroir,NMiroir);
								}
							}
							pixInt.x=pix.x*(source[z].getPuissance().x);
							pixInt.y=pix.y*(source[z].getPuissance().y);
							pixInt.z=pix.z*(source[z].getPuissance().z);
							if(rOmbre.m_hit){
								pixInt.x/=5.0;
								pixInt.y/=5.0;
								pixInt.z/=5.0;
							}
							pixFinal.x+=pixInt.x;
							pixFinal.y+=pixInt.y;
							pixFinal.z+=pixInt.z;
						}
					}
					else {
						PVect I=rInt.m_o+(rInt.m_t*rInt.m_v);
						vo = I-origin;
						vo.normalize();
						for (unsigned int z = 0; z<source.size();z++)
						{

							//calcul du Vi
							PVect vi=source[z].getPosition()-I;
							vi.normalize();
							Rayon rOmbre=Rayon(I.duplicate(),vi.duplicate());
							rOmbre.m_t=rInt.m_t;
							myScene.lanceRayonOmbre(rOmbre,s);
							PVect pix = s.p.getBrdf(vo,vi,s.p.getNorm());
							pixInt.x=pix.x*(source[z].getPuissance().x);
							pixInt.y=pix.y*(source[z].getPuissance().y);
							pixInt.z=pix.z*(source[z].getPuissance().z);
							if(rOmbre.m_hit){
								pixInt.x/=5.0;
								pixInt.y/=5.0;
								pixInt.z/=5.0;
							}
							pixFinal.x+=pixInt.x;
							pixFinal.y+=pixInt.y;
							pixFinal.z+=pixInt.z;
						}
					}
				}
			}

			pixFinal.x/=(float)AA_nbRayon;
			pixFinal.y/=(float)AA_nbRayon;
			pixFinal.z/=(float)AA_nbRayon;
			if (pixFinal.x>255.0){
				pixFinal.x=255.0;
			}
			if(pixFinal.y>255.0){
				pixFinal.y=255.0;
			}
			if(pixFinal.z>255.0){
				pixFinal.z=255.0;
			}
			setPixel(i,j,pixFinal);
		}
	}
}
//---------------------------------------------------------------------------

void Image::setFond(PVect color)
{
	for (int i=0; i<getRezY(); i++)
	{
		for (int j=0; j<getRezX(); j++){
			setPixel(i,j,color);
		}
	}
}
#endif /* IMAGE_CPP_ */
