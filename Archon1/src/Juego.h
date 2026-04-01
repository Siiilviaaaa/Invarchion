#pragma once
class Juego
{
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

	void IniciarJuego();

	
	void procesarEntradas(); //teclas y tal

	void actualizar();

	
	void dibujarTablero();

	void dibujarCapoBatalla();

	void dibujarMenu();

	void ejecutar();


};

