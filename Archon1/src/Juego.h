#pragma once

class Juego
{
private:
	enum EstadosJuego :int {
		EstadoMenu,
		EstadoTablero,
		EstadoBatalla,
		EstadoFinDePartida
	};

	enum Turno : int {
		TurnoHumanos,
		TurnoAliens
	};

	Turno turnoActual{ TurnoHumanos };
	bool ejecutandose{ 0 };

public:

	void IniciarJuego();

	int getTurno();

	void cambiarTurno();

	void procesarEntradas(); //teclas y tal

	void actualizar();

	
	void dibujarTablero();

	void dibujarCampoBatalla();

	void dibujarMenu();

	void ejecutar();


};

//DEFINIDA AQUI PARA NO HACER COPIAS
//ASI CADA VEZ QUE #INCLUDE JUEGO.H UTILIZAMOS MISMO JUEGO
extern Juego juego;
