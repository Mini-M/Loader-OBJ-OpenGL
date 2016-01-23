#include "objet.h"

using namespace std;

//Constructeur
PointObj::PointObj(string nom)
{
	filename = nom;
	float rot = 0.0f;
}

GLvoid PointObj::loadObj()
{
	//Ouverture du fichier
	ifstream fp;
	fp.open (filename, std::ifstream::in);
	//String servant de "tampon" pour lire les lignes du fichiers
	string line;
	//Flotant qui serviront à remplir les structures si dessous
    GLfloat x, y, z;
	//triplet qui sert de "tampon" pour remplir les vertex et les normales
	Triplet stockv; 
	//paire qui sert de "tampon" pour remplir les coordonnées de textures
	Paire stockt; 

	//Lecture du fichier et enregistrement
    if (!fp.is_open())
    {
        printf("can't open file %s\n", filename);
        exit(1);
    }
    while(!fp.eof())
	{
		getline (fp,line);
		//Detection est stockage des lignes correspondant aux vertex
		if (line.c_str()[0] =='v')
		{
			line[0] = ' ';
			sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
			stockv.x = x;
			stockv.y = y;
			stockv.z = z;
			vertex.push_back(stockv);
		}
		////Detection est stockage des lignes correspondant aux normales
		if (line.c_str()[0] =='vn')
		{
			line[0] = ' ';
			sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
			stockv.x = x;
			stockv.y = y;
			stockv.z = z;
			normales.push_back(stockv);
		}
		//Detection est stockage des lignes correspondant aux coordonnées de textures
		if (line.c_str()[0] =='vt')
		{
			line[0] = ' ';
			sscanf(line.c_str(), "%f %f", &x, &y);
			stockt.x = x;
			stockt.y = y;
			vtext.push_back(stockt);
		}
	}
	//Fermeture du fichier
	fp.close();
}

GLvoid PointObj::dispObjPoint()
{
	//Liste d'affichage
	GLuint liste;

	//Taille du vertex pour connaitre le nombre de point
	int ilim;
	ilim = vertex.size();

	//Remplissage de la liste
	liste=glGenLists(1);
	glNewList(liste, GL_COMPILE);
	{
		glPointSize(2.0);
		glPushMatrix();
		glBegin(GL_POINTS);
		//Parcours tous les points enregistrés
		for (int i = 0; i < ilim; i++)
		{
			glVertex3f(vertex[i].x,vertex[i].y,vertex[i].z);
		}
		glEnd();
	}
    glEndList();
    glCallList(liste);
}