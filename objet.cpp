#include "objet.h"

void myObject :: loadObj()
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
			if (line.substr(0,2) == "v ")
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
myObject :: myObject( std::string fname)
{
	nomdufichier=fname;
	loadObj();
}

GLvoid myObject :: dispObj()
{
	std::ifstream fp;
	fp.open (nomdufichier, std::ifstream::in);
	std::string line;
	int po1,tex1,nor1,po2,tex2,nor2,po3,tex3,nor3; //variables pour afficher les faces triangulees
	if (!fp.is_open())
    {
        printf("can't open file %s\n", nomdufichier);
        exit(1);
    }

	 while(!fp.eof())
        {
			getline (fp,line);
			if (line.substr(0,2) == "f ")
			{
				line[0] = ' ';
				sscanf(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &po1,&tex1,&nor1,&po2,&tex2,&nor2,&po3,&tex3,&nor3);
				glBegin(GL_TRIANGLES);
				{
					glTexCoord2d(vtextures[tex1].x,vtextures[tex1].y);
					glVertex3f(vertex[po1].x,vertex[po1].y,vertex[po1].z);
					glNormal3f(normales[nor1].x,normales[nor1].y,normales[nor1].z);

					glTexCoord2d(vtextures[tex2].x,vtextures[tex2].y);
					glVertex3f(vertex[po2].x,vertex[po2].y,vertex[po2].z);
					glNormal3f(normales[nor2].x,normales[nor2].y,normales[nor2].z);

					glTexCoord2d(vtextures[tex3].x,vtextures[tex3].y);
					glVertex3f(vertex[po3].x,vertex[po3].y,vertex[po3].z);
					glNormal3f(normales[nor3].x,normales[nor3].y,normales[nor3].z);
				}
				glEnd();
				
			}
			glFlush();
			
        }


	fp.close();
}

