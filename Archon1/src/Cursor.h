#pragma once
#include "Informacion Casilla.h"

class Cursor {
	int fila, columna;
	InfoCasilla* informacion;
	int contador_selecciones;//indica si se ha dado ya a coger y soltar personajes
public:
	int obt_fila() const { return fila; }
	int obt_columna() const { return columna; }
	void inicializar_tablero(int turno);
	void mover_cursor_tablero(unsigned char key, int turno);
	void mover_tablero(unsigned char key, int turno);
	int coger(int turno);
	int soltar();
 };