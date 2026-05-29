#pragma once
#include "Informacion Casilla.h"
#include <string>

class Juego; //declaro clase anticipadamente para eviatr conflictos

class Cursor {
	int fila, columna;
	int color_r{}, color_v{}, color_a{};
	int filaAntes, columnaAntes;
	InfoCasilla informacion;
	int contador_selecciones;//indica si se ha dado ya a coger y soltar personajes
	int movimientos_restantes;
	Personaje* atacante;
	Personaje* defensor;	
	Personaje* personajeSeleccionado; // Guarda el PUNTERO original, no una copia
	Juego* ptrJuego;//para avisar al juego del cambio de turno

	std::string mensaje = "JUEGO INICIADO";//para imprimir la situacion del juego actual
public:
	int obt_fila() const { return fila; }
	int obt_columna() const { return columna; }
	int obt_color_r() const { return color_r; }
	int obt_color_v() const { return color_v; }
	int obt_color_a() const { return color_a; }
	int obt_contador_selecciones() const { return contador_selecciones; }
	int obt_movimientos_restantes() const { return movimientos_restantes; }
	std::string obt_mensaje() const { return mensaje; }


	void inicializar_tablero(int turno);
	void mover_humanos(unsigned char key, int turno);
	void mover_aliens(int key,int turno);
	void movimiento(int mov_filas, int mov_columnas, const std::string& mensaje, int turno);

	void seleccion_personaje_tablero(unsigned char key, int turno);
	bool tieneMovimientoPosible(int filaOrigen, int columnaOrigen, int turno, int movimientos) const;
	void colorearMovimientosPosibles(int filaOrigen, int columnaOrigen, int turno, int movimientos);
	int coger(int turno);
	int soltar(int turno);

	void aplicarCuracionMasiva(int turno, Personaje* mago);

	void setJuego(Juego* j) { ptrJuego = j; }
	void insertar_mensaje(std::string nuevo_msg) { mensaje = nuevo_msg; }
 };