#pragma once
class Juego
{
	enum EstadosJuego :int {
		EstadoMenu,
		EstadoTablero,
		EstadoBatalla,
		EstadoFinDePartida
	};


	bool TurnoJugador1{ 1 };

	Pieza* PiezaSeleccionada;
};

