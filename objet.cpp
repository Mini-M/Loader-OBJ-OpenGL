#include "objet.h"

void myObject :: loadObj(std::string nomdufichier)
{
	std::ifstream fp;
	fp.open (nomdufichier, std::ifstream::in);
	std::string line;
    GLfloat x, y, z;
	Triplet stockv; //triplet à push_back dans le vecteur
	Paire stockt; //paire à push_back dans le vecteur
	int ilim; //taille du vertex
    GLuint elephant;
	elephant=glGenLists(1);
    if (!fp.is_open())
    {
        printf("can't open file %s\n", nomdufichier);
        exit(1);
    }

    glNewList(elephant, GL_COMPILE);
    {
        glPushMatrix();
        while(!fp.eof())
        {
			getline (fp,line);
			if (line.substr(0,2) == "v")
			{
				line[0] = ' ';
				sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
				stockv.x = x;
				stockv.y = y;
				stockv.z = z;
				vertex.push_back(stockv);
				ilim = vertex.size();
			}

			if (line.substr(0,2) =="vn")
			{
				line[0] = ' ';
				line[1]=' ';
				sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
				stockv.x = x;
				stockv.y = y;
				stockv.z = z;
				normales.push_back(stockv);
			}

			if (line.substr(0,2) =="vt")
			{
				line[0] = ' ';
				line[1] = ' ';
				sscanf(line.c_str(), "%f %f", &x, &y);
				stockt.x = x;
				stockt.y = y;
				vtextures.push_back(stockt);
			}
        }
		
    }
    glPopMatrix();
    glEndList();
    fp.close();
}