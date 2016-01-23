#pragma once

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
    //glutDisplayFunc(display);
    // glutIdleFunc(display);
    //loadObj("Z:/Adrien et Bryan/Projet/opengl_objloader-master/data/teddy.obj");//replace elepham.obj withp orsche.obj or radar.obj or any other .obj to display it
	myObject teddy("Z:/Adrien et Bryan/Projet/opengl_objloader-master/data/teddy.obj");
	teddy.loadObj();
	//teddy.dispObj();
    glutMainLoop();
	
    return 0;
}