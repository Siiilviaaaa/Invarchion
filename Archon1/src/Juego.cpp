#pragma once
#include "Juego.h"
#include "tablero.h"
#include "Personajes.h"
#include <iostream>
#include "MotorGrafico.h"
#include "casilla.h"
#include "Cursor.h"
#include "Batalla.h"

extern MotorGrafico motor;
extern Estado estado;
extern Cursor micursor;
extern Batalla miBatalla;

Juego::Juego(Tablero* t) :
    ptrTablero(t)
{
    
    for (int i = 0; i < MAX_PERSONAJES;i++) {
        figuras[i] = nullptr;
    }
    inicializarPartida();

}
void Juego::setBandoJugador(bando_jugador b)
{
    if (b == Bando_jugador_es_Humano) turnoActual =TurnoHumanos;
    if(b==Bando_jugador_es_Alien)turnoActual = TurnoAliens;
}

Personaje* Juego::getPersonajeEnCasilla(int fila, int columna) const {
    if (ptrTablero != nullptr) {
        const Casilla* c = ptrTablero->getCasilla(fila, columna);
        if (c != nullptr && c->getInfo() != nullptr) {
            return c->getInfo()->getPersonaje();
        }
    }
    return nullptr; // Si no se encuentra el personaje o el tablero es nulo
}

Personaje* Juego::getPersonaje(int index) const {
    if (index >= 0 && index < MAX_PERSONAJES) {
        return figuras[index];
    }
    return nullptr; // Si el índice está fuera de rango
}

void Juego::cambiarTurno() {
    if (turnoActual == TurnoHumanos) turnoActual = TurnoAliens;
    else turnoActual = TurnoHumanos;
    std::cout << "Turno cambiado a: " << turnoActual << std::endl;
}

int Juego::getTurno() {
    return turnoActual;
}

HanGanado Juego::DeterminarSiJuegoHaTerminado() //este se tiene que llamar desp de cada movimiento
{
    //condicion de "EXTERMINIO >:o"--> matan a todas las piezas de un bando
    int contador_humanos{};
    int contador_aliens{};
    for (int i = 0;i < MAX_PERSONAJES;i++) {//se recorren todos los personajes y se cuantos quedan vivos
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

void Juego::spawnPersonaje(Tipo_figura t, Bando e, int fila, int columna)
{
    for (int i = 0; i < MAX_PERSONAJES; i++) {
        if (figuras[i] == nullptr) {//si esta posición está vacía
            figuras[i] = new Personaje(Personaje::crearPieza(t, e, 0, 0));
            figuras[i]->setX(columna);
			figuras[i]->setY(fila);
			Casilla* c = ptrTablero->casillaModificable(fila, columna);
            if (c != nullptr && c->getInfo() != nullptr) //verificar que la casilla y su información no sean nulas
            {
                c->getInfo()->setPersonaje(figuras[i]); //colocamos el personaje en la casilla correspondiente
            }
			return; //salimos del bucle una vez que hemos colocado el personaje, que si no solo se pinta uno

        }
    }
}

void Juego::inicializarPartida()
{
    for (int i = 0; i < MAX_PERSONAJES; i++) { //borro memoria porq si no se llena el vector y no aparece ninguno xd
        if (figuras[i] != nullptr) {
            delete figuras[i];
            figuras[i] = nullptr;
        }
    }

    //HUMANOS
    spawnPersonaje(ARQUERO, HUMANO, 0, 0); // se puede hacer con un bucle, pero bueno asi lo edito mejor
    spawnPersonaje(VOLADOR, HUMANO, 1, 0);
    spawnPersonaje(HECHICERO, HUMANO, 2, 0);
    spawnPersonaje(EXCAVADOR, HUMANO, 3, 0);
    spawnPersonaje(ARQUERO, HUMANO, 4, 0);
    for (int i = 0; i < 5;i++) {
        spawnPersonaje(LUCHADOR, HUMANO, i, 1);
    }
    //ALIENS
    spawnPersonaje(ARQUERO, ALIEN, 0, 6);
    spawnPersonaje(VOLADOR, ALIEN, 1, 6);
    spawnPersonaje(HECHICERO, ALIEN, 2, 6);
    spawnPersonaje(EXCAVADOR, ALIEN, 3, 6);
    spawnPersonaje(ARQUERO, ALIEN, 4, 6);
    for (int i = 0; i < 5;i++) {
        spawnPersonaje(ARQUERO, ALIEN, i, 5);
    }

}

void Juego::cambiarEscenarioABatalla(Personaje* atacante, Personaje* defensor)
{
    if (atacante == nullptr || defensor == nullptr) return;
    std::cout << "[SISTEMA] Abriendo escenario de batalla..." << std::endl;
    atacanteBatalla = atacante;
    defensorBatalla = defensor;

    atacante->x = 5.0;
    atacante->y = 7.5;
    atacante->direccion(1.0, 0.0); //el atacante siempre va a la izq

    defensor->x = 15.0;
    defensor->y = 7.5;
    defensor->direccion(-1.0, 0.0);//el defensor a la derecha

    miBatalla.inicializarBatalla();
    estado = BATALLA;

}

void Juego::cambiarEscenarioATablero(const Personaje& ganador)
{
    
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