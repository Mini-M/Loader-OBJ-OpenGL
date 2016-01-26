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
	GLfloat v1,v2,v3,t1,t2,t3,n1,n2,n3;
	//triplet qui sert de "tampon" pour remplir les vertex et les normales
	Triplet stockv; 
	//paire qui sert de "tampon" pour remplir les coordonnées de textures
	Paire stockt; 
	//vector et triplet "tampon" pour les données de faces
	vector<Triplet> face (3);
	Triplet sommet1;
	Triplet sommet2;
	Triplet sommet3;

	//Lecture du fichier et enregistrement
    if (!fp.is_open())
    {
        printf("can't open file %s\n", filename);
        exit(1);
    }
    while(!fp.eof())
	{
		getline (fp,line);
		//Detection et stockage des lignes correspondant aux vertex
		if (line.substr(0,2) =="v ")
		{
			line[0] = ' ';
			sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
			stockv.x = x;
			stockv.y = y;
			stockv.z = z;
			vertex.push_back(stockv);
		}
		////Detection et stockage des lignes correspondant aux normales
		if (line.substr(0,2) =="vn")
		{
			line[0] = ' ';
			line[1] = ' ';
			sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
			stockv.x = x;
			stockv.y = y;
			stockv.z = z;
			normales.push_back(stockv);
		}
		//Detection et stockage des lignes correspondant aux coordonnées de textures
		if (line.substr(0,2)=="vt")
		{
			line[0] = ' ';
			line[1] = ' ';
			sscanf(line.c_str(), "%f %f", &x, &y);
			stockt.x = x;
			stockt.y = y;
			vtext.push_back(stockt);
		}
		//Detection et stockage des faces
		if (line.c_str()[0] == 'f')
		{
			line[0] = ' ';
			sscanf(line.c_str(), "%f/%f/%f %f/%f/%f %f/%f/%f",&v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);
			sommet1.x=v1-1;
			sommet1.y=t1-1;
			sommet1.z=n1-1;
			sommet2.x=v2-1;
			sommet2.y=t2-1;
			sommet2.z=n2-1;
			sommet3.x=v3-1;
			sommet3.y=t3-1;
			sommet3.z=n3-1;
			face[0] = sommet1;
			face[1] = sommet2;
			face[2] = sommet3;
			faces.push_back(face);
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

GLvoid PointObj::dispObjFace()
{
	//Liste d'affichage
	GLuint liste;

	//Taille du vertex pour connaitre le nombre de point
	int ilim;
	ilim = faces.size();

	//Tampon pour la lecture
	int position;

	//Remplissage de la liste
	liste=glGenLists(1);
	glNewList(liste, GL_COMPILE);
	{
		glPushMatrix();
		glBegin(GL_TRIANGLES);
		//Parcourt tous les points enregistrés
		for (int i = 0; i < ilim; i++)
		{
			for (int j = 0; j<3; j++)
			{
				
				position = (faces[i][j].x);
				glVertex3f(vertex[position].x,vertex[position].y,vertex[position].z);
				position = (faces[i][j].z);
				glNormal3f(normales[position].x,normales[position].y,normales[position].z);
			}
		}
		glEnd();
	}
    glEndList();
    glCallList(liste);
}