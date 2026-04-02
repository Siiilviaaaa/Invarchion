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

	//JULI, NECESITO LA FUNCION CAMBIAR TURNO CUANDO EL HECHICERO USE LA POCION
	//QUIERO DECIR QUE CUANDO SE USE SE CAMBIE DE TURNO
	//SOY SILVIA
	void cambiarTurno();

	void procesarEntradas(); //teclas y tal

	void actualizar();

	
	void dibujarTablero();

	void dibujarCapoBatalla();

	void dibujarMenu();

	void ejecutar();


};

