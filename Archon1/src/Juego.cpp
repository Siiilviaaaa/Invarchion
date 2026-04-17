#include "Juego.h"

///VARIABLE GLOBAL DEFINIDA EN HECHIZOS.CPP
extern bool usoPocion;

Juego::Juego():
    turnoActual{ TurnoHumanos },
    ejecutandose {true}
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



void Juego::JuegoHaTerminado()
{

}

void Juego::spawnPersonaje(Tipo_figura t, Bando e, int x, int y)
{
    for (int i = 0; i < MAX_PERSONAJES;i++) {
        if (figuras[i] == nullptr) {
            figuras[i] = new Personaje();
        }
    }
}

