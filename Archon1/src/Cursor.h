#pragma once
#include "Informacion Casilla.h"

class Cursor {
	int fila, columna;
	InfoCasilla* informacion;
	int contador_selecciones;//indica si se ha dado ya a coger y soltar personajes
public:
	void inicializar(int turno);
	void dibuja();
	void mueve(unsigned char key, int turno);
	void coger();
	void soltar();
 };