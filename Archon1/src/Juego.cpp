#include "Juego.h"
#include <iostream>
#include "MotorGrafico.h"
#include "casilla.h"
#include "Batalla.h"

extern MotorGrafico motor;
extern Estado estado;
extern Cursor micursor;
extern Batalla miBatalla;
extern int puntuacion_humanos;
extern int puntuacion_aliens;
extern int puntuacion_actual;

Juego::Juego(Tablero* t) :
    ptrTablero(t)
{
    
    for (int i = 0; i < MAX_PERSONAJES;i++) {
        figuras[i] = nullptr;
    }
    inicializarPartida();

}

Juego::~Juego()
{
    //personajes
    for (int i = 0; i < MAX_PERSONAJES; i++) {
        if (figuras[i] != nullptr) {
            delete figuras[i];
            figuras[i] = nullptr;
        }
    }

    //tablero
    for (int f = 0; f < 9; f++) {
        for (int c = 0; c < 9; c++) {
            ptrTablero->setInfoCasilla(f, c, nullptr);
        }
    }
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
        return GanaronHumanos;
    }
    if (contador_aliens > 0 && contador_humanos > 0) return AunEnCurso;

    //condicion de que estan las casillas guays ocuapadas (necesito que se añadan esas casillas)
}

HanGanado Juego::victoriaPuntosPoder()
{
    int puntosHumanos = 0;
    int puntosAliens = 0;
    const int puntos_totales = 5;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            InfoCasilla* info = ptrTablero->getInfoCasilla(i, j);
            if (info && info->getPuntoPoder() && info->estaOcupada()) {
                if (info->getPersonaje()->return_Bando() == HUMANO) {
                    puntosHumanos++;
                }
                if (info->getPersonaje()->return_Bando() == ALIEN) {
                    puntosAliens++;
                }
            }
        }
    }
    if (puntosAliens == puntos_totales) {
        puntuacion_aliens += 500;
        return GanaronAliens;
    }
    if (puntosHumanos == puntos_totales) {
        puntuacion_humanos += 500;
        return GanaronHumanos;
    }
    return AunEnCurso;
}

void Juego::spawnPersonaje(Tipo_figura t, Bando e, int fila, int columna)
{
    for (int i = 0; i < MAX_PERSONAJES; i++) {
        if (figuras[i] == nullptr) {//si esta posición está vacía
            figuras[i] = Personaje::crearPieza(t, e, 0, 0);
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
    spawnPersonaje(ARQUERO, HUMANO, 2, 0);
    spawnPersonaje(EXCAVADOR, HUMANO, 3, 0);
    spawnPersonaje(HECHICERO, HUMANO, 4, 0);
    spawnPersonaje(EXCAVADOR, HUMANO, 5, 0);
    spawnPersonaje(ARQUERO, HUMANO, 6, 0);
    spawnPersonaje(VOLADOR, HUMANO, 7, 0);
    spawnPersonaje(ARQUERO, HUMANO, 8, 0);
 
    for (int i = 0; i < 9;i++) {
        spawnPersonaje(LUCHADOR, HUMANO, i, 1);
    }
    //ALIENS
    spawnPersonaje(ARQUERO, ALIEN, 0, 8);
    spawnPersonaje(VOLADOR, ALIEN, 1, 8);
    spawnPersonaje(ARQUERO, ALIEN, 2, 8);
    spawnPersonaje(EXCAVADOR, ALIEN, 3, 8);
    spawnPersonaje(HECHICERO, ALIEN, 4, 8);
    spawnPersonaje(EXCAVADOR, ALIEN, 5, 8);
    spawnPersonaje(ARQUERO, ALIEN, 6, 8);
    spawnPersonaje(VOLADOR, ALIEN, 7, 8);
    spawnPersonaje(ARQUERO, ALIEN, 8, 8);
    
    for (int i = 0; i < 9;i++) {
        spawnPersonaje(LUCHADOR, ALIEN, i, 7);
    }
}

void Juego::cambiarEscenarioABatalla(Personaje* atacante, Personaje* defensor)
{
    if (atacante == nullptr || defensor == nullptr) return;
    std::cout << "[SISTEMA] Abriendo escenario de batalla..." << std::endl;
    atacanteBatalla = atacante;
    defensorBatalla = defensor;
    
   
    int f = micursor.obt_fila();
    int c = micursor.obt_columna();
    InfoCasilla* info = ptrTablero->getInfoCasilla(f, c);

    if (info != nullptr) {
        Tipocasilla color = info->getColor();
        if (casillaFavorable(atacante, color)) {
            int danioAnteriorAtac = atacante->return_Danio();
            atacante->setDanio(danioAnteriorAtac + 5);
            std::cout << "[BONO] Atacante en terreno aliado: +5 HP" << std::endl;
            miBatalla.setMensajeBonus("ATACANTE +5 ATAQUE");
        }
        if (casillaFavorable(defensor, color)) {
            int danioAnteriorDef = defensor->return_Danio();
            atacante->setDanio(danioAnteriorDef + 5);
            std::cout << "[BONO] Defensor en terreno aliado: +5 HP" << std::endl;
            miBatalla.setMensajeBonus("DEFENSOR +5 ATAQUE");
        }
    }

    if (ptrTablero != nullptr) {
        origenAntesDeBatalla = ptrTablero->casillaModificable(defensor->y, defensor->x);

        for (int fila = 0; fila < 9; fila++) { //esto me lo ha hecho la ia, no consegui hacerlo sin mirar todas las casillas ns porqué
            for (int col = 0; col < 9; col++) {
                Casilla* cas = ptrTablero->casillaModificable(fila, col);
                if (cas != nullptr && cas->getInfo() != nullptr) {
                    if (cas->getInfo()->getPersonaje() == atacante) {
                        cas->getInfo()->setPersonaje(nullptr);
                    }
                }
            }
        }
    }

    if (origenAntesDeBatalla != nullptr) {
        origenAntesDeBatalla = ptrTablero->casillaModificable(defensor->y, defensor->x);
        origenAntesDeBatalla->getInfo()->setPersonaje(nullptr);

    }
    if (atacante->return_Bando() == HUMANO) {
        atacante->x = 5.0;
        atacante->y = 7.5;
        atacante->direccion(1.0, 0.0); //el atacante siempre va a la izq

        defensor->x = 15.0;
        defensor->y = 7.5;
        defensor->direccion(-1.0, 0.0);//el defensor a la derecha
    }
    else {
        atacante->x = 15.0;
        atacante->y = 7.5;
        atacante->direccion(-1.0, 0.0); //el atacante siempre va a la izq

        defensor->x = 5.0;
        defensor->y = 7.5;
        defensor->direccion(1.0, 0.0);//el defensor a la derecha
    }
   
    cambiarTurno();
    miBatalla.inicializarBatalla();
    estado = BATALLA;

}

void Juego::finalizarBatalla()
{
    std::cout << "[SISTEMA] volviendo a tablero" << std::endl;
    if (atacanteBatalla == nullptr || defensorBatalla == nullptr || origenAntesDeBatalla == nullptr) return;
    int f = micursor.obt_fila();
    int c = micursor.obt_columna();
    InfoCasilla* info = ptrTablero->getInfoCasilla(f, c);
    Personaje* ganador = nullptr;
    Personaje* perdedor = nullptr;

    if (atacanteBatalla->return_Vida() <= 0) {
        ganador = defensorBatalla;
        perdedor = atacanteBatalla;
    }
    else {
        ganador = atacanteBatalla;
        perdedor = defensorBatalla;
    }

    if (ganador != nullptr) {
        origenAntesDeBatalla->getInfo()->setPersonaje(ganador);
        InfoCasilla* info = origenAntesDeBatalla->getInfo();
        if (info != nullptr) {
            Tipocasilla color = info->getColor();
            if (casillaFavorable(atacanteBatalla, color)) {
                atacanteBatalla->setDanio(atacanteBatalla->return_Danio() - 5);
                std::cout << "Daño restablecido" << std::endl;
            }
            if (casillaFavorable(defensorBatalla, color)) {
                defensorBatalla->setDanio(defensorBatalla->return_Danio() - 5);
                std::cout << "Daño restablecido" << std::endl;
            }

        }
        ganador->x = origenAntesDeBatalla->getcolumna();
        ganador->y = origenAntesDeBatalla->getfila();
        ganador->direccion(0.0, 0.0);

        InfoCasilla* casillaActual = ptrTablero->getInfoCasilla(ganador->return_X(), ganador->return_Y());
        if (casillaActual != nullptr&&casillaActual->getPuntoPoder()) {
            ganador->setVida(ganador->return_VidaMax());
            std::cout << "¡Ganador curado en Punto de Poder ("
                << ganador->return_X() << "," << ganador->return_Y() << ")! Nueva vida: "
                << ganador->return_Vida() << std::endl;
        }
        perdedor->setVida(0);
        perdedor->setX(-5);
    }
    
    atacanteBatalla = nullptr;
    defensorBatalla = nullptr;
    origenAntesDeBatalla = nullptr;
    cambiarTurno();
    estado = JUEGO;
}

bool Juego::casillaFavorable(Personaje* p, Tipocasilla colorCasilla)
{
    if (p == nullptr) return false;
    if (p->return_Bando() == HUMANO && colorCasilla == blanca) return true;
    if (p->return_Bando() == ALIEN && colorCasilla == negra) return true;
    return false;
}

void Juego::reiniciarJuego()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            InfoCasilla* info = ptrTablero->getInfoCasilla(i, j);
            if (info) info->setPersonaje(nullptr);
        }
    }
    for (int i = 0; i < MAX_PERSONAJES; i++) {
        if (figuras[i] != nullptr) {
            delete figuras[i];
            figuras[i] = nullptr;
        }
    }

    

    inicializarPartida();
}
