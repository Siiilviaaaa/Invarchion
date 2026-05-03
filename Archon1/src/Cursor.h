#pragma once
#include "Informacion Casilla.h"

class Cursor {
	int fila, columna;
	InfoCasilla* informacion;
	int contador_selecciones;//indica si se ha dado ya a coger y soltar personajes
public:
	int fila() const { return fila; }
	int columna() const { return columna; }
	void inicializar(int turno);
	void dibuja();
	void mover_cursor(unsigned char key, int turno);
	void mover(unsigned char key, int turno);
	int coger(int turno);
	int soltar();
 };