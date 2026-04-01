#pragma once
#include "Personajes.h"
#include "freeglut.h"

//CABECERAS DE FUNCIONES
void start_combat(Personajes_carac& humanos, Personajes_carac& aliens);

struct Disparo
{
	double x, y; // POSICION
	double velo_x, velo_y; // VELOCIDAD
	int danio; // DAÑO QUE CAUSA
	bool activo; // SI ESTA O NO EN PANTALLA
	GLuint flecha; // IMAGEN

	void dispararObjeto(double posX, double posY, GLuint png);
};