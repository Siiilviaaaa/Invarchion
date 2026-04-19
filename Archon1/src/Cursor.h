#pragma once
#include "Personajes.h"

class Cursor {
public:
	int filaEstoy, columnaEstoy;
	int filaVengo, columnaVengo;
	Personaje persona;

	Cursor();
	void dibuja();
	void inicializa(int turno);
	void preguntar_coger(Matriz &m,int turno, Cursor cursor);//se le pasa por referencia para poder editarla 
	void preguntar_soltar(Matriz &m, int turno, Cursor cursor);
	void coger();
	void soltar();
};