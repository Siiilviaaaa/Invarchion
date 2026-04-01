#include "Juego.h"

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
}

int Juego::getTurno() {
    return turnoActual;
}

void Juego::procesarEntradas() {

}

void Juego::actualizar() {

}


void Juego::dibujarTablero() {

}

void Juego::dibujarCapoBatalla() {

}

void Juego::dibujarMenu() {

}

void Juego::ejecutar() {

}