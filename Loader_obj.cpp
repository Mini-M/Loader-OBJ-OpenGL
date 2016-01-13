#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

//globals
GLuint elephant;
float elephantrot;
char ch='1';

//other functions and main

//wavefront .obj loader code begins
void loadObj(char *fname)
{
	// Creation des structures pour stocker les coordonnees des vertex et de normales
	struct Triplet
	{
		int x,y,z;
	};
	vector<Triplet> vertex; //Vecteur pour stocker les vertex
	vector<Triplet> normales; //Vecteur pour stocker les vecteurs normaux

	// Creation de la structure pour les coordonnees de textures
	struct Paire
	{
		int x,y;
	};
	vector<Paire> vtextures; //Vecteur pour les coordonées de textures

    ifstream fp;
	fp.open (fname, std::ifstream::in);
	string line;
    GLfloat x, y, z;
	Triplet stockv; //triplet à push_back dans le vecteur
	Paire stockt; //paire à push_back dans le vecteur
	int ilim; //taille du vertex
    elephant=glGenLists(1);
    if (!fp.is_open())
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glNewList(elephant, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_POINTS);
        while(!fp.eof())
        {
			getline (fp,line);
			if (line.c_str()[0] =='v')
			{
				line[0] = ' ';
				sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
				stockv.x = x;
				stockv.y = y;
				stockv.z = z;
				vertex.push_back(stockv);
				ilim = vertex.size();
			}

			if (line.c_str()[0] =='vn')
			{
				line[0] = ' ';
				sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
				stockv.x = x;
				stockv.y = y;
				stockv.z = z;
				normales.push_back(stockv);
			}

			if (line.c_str()[0] =='vt')
			{
				line[0] = ' ';
				sscanf(line.c_str(), "%f %f", &x, &y);
				stockt.x = x;
				stockt.y = y;
				vtextures.push_back(stockt);
			}
        }
		for (int i = 0; i < ilim; i++)
		{
			glVertex3f(vertex[i].x,vertex[i].y,vertex[i].z);
		}
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fp.close();
}
//wavefront .obj loader code ends here

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    //glOrtho(-25,25,-2,2,0.1,100);
    glMatrixMode(GL_MODELVIEW);
}

void drawElephant()
{
    glPushMatrix();
    glTranslatef(0,0,-10);
    glColor3f(1.0,0.23,0.27);
    glScalef(0.1,0.1,0.1);
    glRotatef(elephantrot,0,1,0);
    glCallList(elephant);
    glPopMatrix();
    elephantrot=elephantrot+0.6;
    if(elephantrot>360)elephantrot=elephantrot-360;
}

void display(void)
{
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawElephant();
    glutSwapBuffers(); //swap the buffers
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,450);
    glutInitWindowPosition(20,20);
    glutCreateWindow("ObjLoader");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    loadObj("Z:/Adrien et Bryan/Projet/opengl_objloader-master/data/teddy.obj");//replace elepham.obj withp orsche.obj or radar.obj or any other .obj to display it
    glutMainLoop();
    return 0;
}