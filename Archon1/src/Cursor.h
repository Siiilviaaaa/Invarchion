#pragma once
#include "Informacion Casilla.h"

class Cursor {
	int fila, columna;
	int filaAntes, columnaAntes;
	InfoCasilla informacion;
	int contador_selecciones;//indica si se ha dado ya a coger y soltar personajes
	int movimientos_restantes;
	Personaje* atacante;
	Personaje* defensor;
	int color_r{}, color_v{}, color_a{};
public:
	int obt_fila() const { return fila; }
	int obt_columna() const { return columna; }
	int obt_color_r() const { return color_r; }
	int obt_color_v() const { return color_v; }
	int obt_color_a() const { return color_a; }

	void inicializar_tablero(int turno);

	void mover_cursor_tablero(unsigned char key, int turno);

	void seleccion_personaje_tablero(unsigned char key, int turno);

	int coger(int turno);
	int soltar(int turno);
 };