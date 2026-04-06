#include "Juego.h"
#include "Batalla.h"

void Juego::IniciarJuego() {

    ejecutandose = 1;

    //// Constructor cuando sepamos como va le añadiré cosas
    //Juego();

    //// Destructor lo mismo
    //~Juego();

    //hay que decri que se cree el menu, el teblero y la pantalla de batalla
};

void Juego::cambiarTurno() {
    if (turnoActual == TurnoHumanos) turnoActual = TurnoAliens;
    else turnoActual = TurnoHumanos;

    //RESET FLAG PARA EL USO DE LA POCION
	usoPocion = false;
}

int Juego::getTurno() {
    return turnoActual;
}

void Juego::procesarEntradas() {

}

void Juego::actualizar() {
	//actualizarCombate(j1, j2); //ME DA ERROR EN J1 Y J2
}


void Juego::dibujarTablero() {

}

void Juego::dibujarCampoBatalla() {

}

void Juego::dibujarMenu() {

}

void Juego::ejecutar() {

}