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

bool setMode= false;
PointObj Mba = PointObj("Z:/Adrien et Bryan/Projet/opengl_objloader-master/data/mba1.obj");


// Rotations autour de X et Y

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLint oldX = 0;
GLint oldY = 0;
GLboolean boutonClick = false;


//Autres fonctions et main
GLvoid souris(int bouton, int etat, int x, int y){
   // Test pour voir si le bouton gauche de la souris est appuyé
   if(bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN) {
      boutonClick = true;
      oldX = x;
      oldY = y;
   }
   
   // si on relache le bouton gauche
   if(bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP) {
      boutonClick = false;
   }
}
GLvoid clavier(unsigned char touche, int x, int y) {
   
   // Suivant les touches pressees, nous aurons un comportement different de l'application
   // ESCAPE ou 'q' : fermera l'application
   // 'f' : affichage faces
   // 's' : affichage des sommets
   
   switch(touche) {
      case 'f' : // faces
		  setMode=true;
         break;
      case 's' : // points
		 setMode=false;
         break;      
         
      case 'q' : // quitter
      case 27 :
         exit(0);
         break;
   }
   
   // Demande a GLUT de reafficher la scene
   glutPostRedisplay();
}

GLvoid deplacementSouris(int x, int y) {
   // si le bouton gauche est appuye et qu'on se deplace
   // alors on doit modifier les angles de rotations du cube
   // en fonction de la derniere position de la souris 
   // et de sa position actuelle
   if(boutonClick) {
      angleX += (x-oldX);
      angleY += (y-oldY);
      // Appeler le re-affichage de la scene OpenGL
      glutPostRedisplay();
   }
   
   // Mise a jour des anciennes positions de la souris en X et Y
   oldX = x;
   oldY = y;
}

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
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glPushMatrix();
    glTranslatef(0,-3,-20);
    glColor3f(1.0,0.23,0.27);
    glScalef(0.1,0.1,0.1);
	glRotatef(angleY,1.0f,0.0f,0.0f);
	glRotatef(angleX,0.0f,1.0f,0.0f);
	
	//Affiche l'objet en fonction du mode selectionne
	
	Mba.dispChoice(setMode);

	glPopMatrix();
	glFlush();

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
	//fonctions de callbacks	
	glutKeyboardFunc(clavier);
    glutMouseFunc(souris);
    glutMotionFunc(deplacementSouris);
    glutMainLoop();
    return 0;
}