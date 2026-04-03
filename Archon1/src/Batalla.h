#pragma once
#include "Personajes.h"
#include "freeglut.h"

//VARIABLES GLOBALES DEFINIDAS EN BATALLA.CPP
extern bool usoPocion;

//CABECERAS DE FUNCIONES
void start_combat(Personajes_carac& humanos, Personajes_carac& aliens);

class Disparo
{
	double x, y; // POSICION
	double velo_x, velo_y; // VELOCIDAD
	int danio; // DAÑO QUE CAUSA
	bool activo; // SI ESTA O NO EN PANTALLA
	GLuint flecha; // IMAGEN

public:
	void dispararObjeto(double posX, double posY, GLuint png);
};

class Hechizo
{
	GLuint imagen;
	int usos_max;
	int usos_restantes;
	bool activo; // "HECHIZO LANZADO DE MANERA VISUAL"
	double posX, posY; // POSICION DEL HECHIZO EN PANTALLA

	double t_recarga; // TIEMPO TOTAL DE RECARGA
	double t_restante; // TIEMPO RESTANTE PARA USAR DE NUEVO

public:
	Hechizo(); //CONSTRUCTOR
	void conf_Hechizos(); //DIFERENCIAR TIPOS DE HECHIZOS
	void usar_Hechizo(int tipoHechizo, Personajes_carac& objetivo);
	void usar_Pocion(Personajes_carac& aliado);
};