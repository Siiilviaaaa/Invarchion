#pragma once
#include "tablero.h"
#include "freeglut.h"

class Dibujar_tablero {
	Tablero* tablero;
	float lado;
public:
	Dibujar_tablero(Tablero* t, float l = 1.0f);
	void dibuja();
	void dibujarFondo();
	void dibujarBordeTurno();
	void dibujarCasilla(const Casilla* c);
};