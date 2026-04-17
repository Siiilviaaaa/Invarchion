#pragma once
#include "Juego.h"
#include "tablero.h"
#include "Personajes.h"

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

    //condicion de "exterminio"--> matan a todas las piezas de un bando
    int contador_humanos{};
    int contador_aliens{};
    for (int i = 0;i < MAX_PERSONAJES;i++) {//se recorren todos los personajes y se cuantos quedan vivos
        if (figuras[i] != nullptr && figuras[i]->return_Vida() > 0) {
            if (figuras[i]->return_Bando() == HUMANO) contador_humanos++;
            else contador_aliens++;
        }
    }

    if (contador_humanos == 0) return GanaronAliens;
    if (contador_aliens == 0) return GanaronAliens;
    if (contador_aliens > 0 && contador_humanos > 0) return AunEnCurso;
}

void Juego::spawnPersonaje(Tipo_figura t, Bando e, int x, int y)
{
    for (int i = 0; i < MAX_PERSONAJES;i++) {
        if (figuras[i] == nullptr) {
            figuras[i] = new Personaje();
        }
    }
}

