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

using namespace std;

//Definition de la structure de triplet
struct Triplet
{
	int x,y,z;
};

//Definition de la structure de paire
struct Paire
{
	int x,y;
};

//Definition de la classe .obj permettant de charger et d'afficher les fichiers .obj
class PointObj
{
private :
	//Structure pour stocker les vertex
	vector<Triplet> vertex;
	//Structure pour stocker les normales
	vector<Triplet> normales;
	//Structure pour stocker les coordonnees de textures
	vector<Paire> vtext;
	//Nom du fichier a ouvrir
	string filename;

public :
	//Constructeur
	PointObj (string nom);
	//Methode de chargement de l'objet
	GLvoid loadObj();
	//Methode d'affichage de l'objet
	GLvoid dispObjPoint();
};