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
    const Casilla* getCasilla(int f, int c) const { 
        return &matriz[f][c];
    }
    Casilla* casillaModificable(int f, int c) {
        return &matriz[f][c];
    }
    InfoCasilla* getInfoCasilla(int fila, int columna) {
        if (fila >= 0 && fila < 5 && columna >= 0 && columna < 7) {
            return &datos[fila][columna];
        }
      return nullptr;
    }
    void setInfoCasilla(int fila, int columna,  Personaje* personaje)
    {
        if (fila >= 0 && fila < 5 && columna >= 0 && columna < 7) {
            datos[fila][columna].setPersonaje(personaje);
        }
    }
    
    int getTurno(Juego* juego) const;
    //INCIALIZAR POSICIONES PIEZAS
	//void inicializarPiezas();


    

};
extern Tablero miTablero;
