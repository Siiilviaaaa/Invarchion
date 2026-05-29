#pragma once
//declaracion del tablero a partir de las casillas
#include "casilla.h"
#include "Informacion Casilla.h"
class Juego;

//ELENA CREO QUE ESTO VA AQUI, LO DEJO TODO COMENTADO POR SI ACASO, SOY SILVIA ;)
//#include "Personajes.h" //PARA PODER POSICIONAR LAS PIEZAS

class Tablero {
    InfoCasilla datos[9][9]; //para la informacion
    Casilla matriz[9][9]; 
    

public:
    // Constructor
    Tablero();

    // Funciones principales
    void inicializa();
    void reseteoColores();
    const Casilla* getCasilla(int f, int c) const { 
        return &matriz[f][c];
    }
    Casilla* casillaModificable(int f, int c) {
        return &matriz[f][c];
    }
    InfoCasilla* getInfoCasilla(int fila, int columna) {
        if (fila >= 0 && fila < 9 && columna >= 0 && columna < 9) {
            return &datos[fila][columna];
        }
      return nullptr;
    }
    void setInfoCasilla(int fila, int columna,  Personaje* personaje)
    {
        if (fila >= 0 && fila < 9 && columna >= 0 && columna < 9) {
            datos[fila][columna].setPersonaje(personaje);
        }
    }
    
    int getTurno(Juego* juego) const;
    //INCIALIZAR POSICIONES PIEZAS
	//void inicializarPiezas();


    

};
extern Tablero miTablero;
