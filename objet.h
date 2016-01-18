#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>


struct Triplet
{
		int x,y,z;
};

struct Paire
{
	int x,y;
};

class myObject {
private :
	std::vector<Triplet> vertex;
	std::vector<Triplet> normales;
	std::vector<Paire> vtextures;
	std::string nomdufichier;

public :
	myObject(std::string filename);
	GLvoid loadObj (); //charge les vecteurs de points normales et textures
	GLvoid dispObj ();//affiche les faces et textures
	

};
