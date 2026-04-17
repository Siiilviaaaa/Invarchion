#pragma once
#include <Personajes.h>

#define MAX_PERSONAJES 20

enum Turno : int {
	TurnoHumanos,
	TurnoAliens
};
enum bando_jugador {
	Bando_jugador_es_Humano,
	Bando_jugador_es_Alien
};
class Juego
{
private:

	
	Turno turnoActual{ TurnoHumanos };
	bool ejecutandose{ 0 };
	bando_jugador bandoJugador;

	Personaje* figuras[MAX_PERSONAJES]; //hay 20 figuritas en el tablero

public:

	Juego();

	int getTurno();

	void setBandoJugador(bando_jugador b);

	void cambiarTurno();

	//void procesarEntradas(); //teclas y tal

	//void actualizar();

	//
	//void dibujarTablero();

	//void dibujarCampoBatalla();

	//void dibujarMenu();

	void JuegoHaTerminado();

	void spawnPersonaje(Tipo_figura t, Bando e, int x, int y);



};

//DEFINIDA AQUI PARA NO HACER COPIAS
//ASI CADA VEZ QUE #INCLUDE JUEGO.H UTILIZAMOS MISMO JUEGO
extern Juego juego;
