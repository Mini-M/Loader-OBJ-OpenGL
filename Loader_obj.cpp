#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "objet.h"

using namespace std;

//Variable globale pour la rotation automatique du modèle
float rot = 0.0f;
PointObj Mba = PointObj("Z:/Adrien et Bryan/Projet/opengl_objloader-master/data/mba1.obj");

//Autres fonctions et main

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//Cree un objet et le charge
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glPushMatrix();
    glTranslatef(0,-3,-20);
    glColor3f(1.0,0.23,0.27);
    glScalef(0.1,0.1,0.1);
    glRotatef(rot,0,1,0);
	
	//Affiche l'objet
	//Mba.dispObjPoint();
	Mba.dispObjFace();

	glPopMatrix();

	//augmente l'incrément de rotation
	//rot=rot+0.6;
    //if(rot>360)rot=rot-360;

    glutSwapBuffers(); //swap the buffers
}

int main(int argc,char **argv)
{
	Mba.loadObj();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,450);
    glutInitWindowPosition(20,20);
    glutCreateWindow("ObjLoader");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}