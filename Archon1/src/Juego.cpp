#pragma once
#include "Juego.h"
#include "tablero.h"
#include "Personajes.h"
#include <iostream>

///VARIABLE GLOBAL DEFINIDA EN HECHIZOS.CPP
extern bool usoPocion;

Juego::Juego(Tablero* t) :
    ptrTablero(t)
{
    
    for (int i = 0; i < MAX_PERSONAJES;i++) {
        figuras[i] = nullptr;
    }

}
void Juego::setBandoJugador(bando_jugador b)
{
    bandoJugador = b;
}


void Juego::cambiarTurno() {
    if (turnoActual == TurnoHumanos) turnoActual = TurnoAliens;
    else turnoActual = TurnoHumanos;

    //RESET FLAG PARA EL USO DE LA POCION
	usoPocion = false;
}

int Juego::getTurno() {
    return turnoActual;
}




//void Juego::dibujarTablero() {
//
//}
//
//void Juego::dibujarCampoBatalla() {
//
//}
//
//void Juego::dibujarMenu() {
//
//}



HanGanado Juego::DeterminarSiJuegoHaTerminado() //este se tiene que llamar desp de cada movimiento
{
    //condicion de "EXTERMINIO >:o"--> matan a todas las piezas de un bando
    int contador_humanos{};
    int contador_aliens{};
    for (int i = 0;i < MAX_PERSONAJES;i++) {//se recorren todos los personajes y se ve cuantos quedan vivos
        if (figuras[i] != nullptr && figuras[i]->return_Vida() > 0) {
            if (figuras[i]->return_Bando() == HUMANO) contador_humanos++;
            else contador_aliens++;
        }
    }

    if (contador_humanos == 0) {
        std::cout << "ganaron aliens por exterminio >:o";
        return GanaronAliens;
    }
    if (contador_aliens == 0) {
        std::cout << "ganaron humanos por exterminio >:o";
        return GanaronAliens;
    }
    if (contador_aliens > 0 && contador_humanos > 0) return AunEnCurso;


    //condicion de que estan las casillas guays ocuapadas (necesito que se añadan esas casillas)
}

void Juego::spawnPersonaje(Tipo_figura t, Bando e, int x, int y)
{
    for (int i = 0; i < MAX_PERSONAJES;i++) {
        if (figuras[i] == nullptr) {
            figuras[i] = Personaje::crearPieza(t, x, y, e);
        }
    }
}

//JULI NO SE DONDE PONER QUE LA BATALLA SIGUE EN CURSO, TE LO DEJO POR AQUI
//int estado = batalla.FinCombate(jugador1, jugador2);
//
//if (estado == 1) {
//    // Ganan humanos y sumar puntos extra por victoria
//    jugador1.sumarPuntos(100);
//        // Cambiar estado del juego a "TABLERO"
//}
//else if (estado == 2) {
//    // Ganan aliens y sumar puntos
//    jugador2.sumarPuntos(100);
//        // Cambiar estado del juego a "TABLERO"
//}