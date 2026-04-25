#pragma once
#include "Informacion Casilla.h"

class Cursor {
	int fila, columna;
	InfoCasilla* informacion;
public:
	void inicializar(int turno);
	void dibuja();
	void mueve(unsigned char key);
	void coger();
	void soltar();

 };