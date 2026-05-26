#pragma once
#include "Personajes.h"
#include "tablero.h"

#define MAX_PERSONAJES 20
enum Estado { MENU, SELECCION, JUEGO, RANKING, BATALLA, FIN_PARTIDA };

enum Turno : int {
	TurnoHumanos,
	TurnoAliens
};
enum bando_jugador {
	Bando_jugador_es_Humano,
	Bando_jugador_es_Alien
};

enum HanGanado {
	AunEnCurso,
	GanaronHumanos,
	GanaronAliens
};

class Juego
{
private:
	Tablero* ptrTablero;
	
	Turno turnoActual{ TurnoHumanos};
	bool ejecutandose{ 0 };
	bando_jugador bandoJugador{};
	HanGanado estado_victoria;
	Personaje* figuras[MAX_PERSONAJES]; //hay 20 figuritas en el tablero
	Personaje* atacanteBatalla{ nullptr };
	Personaje* defensorBatalla{ nullptr };
public:

	Juego(Tablero* t);

	//getters
	int getTurno();
	Personaje* getPersonajeEnCasilla(int fila, int columna) const;
	Personaje* getPersonaje(int index) const;

	//setters
	void setBandoJugador(bando_jugador b);
	void cambiarTurno();


	HanGanado DeterminarSiJuegoHaTerminado();

	void spawnPersonaje(Tipo_figura t, Bando e, int x, int y);
	void inicializarPartida();

	//batalla
	Personaje* getAtacanteBatalla() const { return atacanteBatalla; }
	Personaje* getDefensorBatalla() const { return defensorBatalla; }
	void cambiarEscenarioABatalla(Personaje* atacante, Personaje* defensor);
	void cambiarEscenarioATablero(const Personaje& ganador);

	bool casillaFavorable(Personaje* p, Tipocasilla colorCasilla);
};