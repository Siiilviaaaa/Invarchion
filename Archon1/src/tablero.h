#pragma once
//declaracion del tablero a partir de las casillas
#include "casilla.h"

#include "freeglut.h" // Para las funciones de dibujo de OpenGL

#define ANCHO_TABLERO 5
#define ALTO_TABLERO 7
//ELENA CREO QUE ESTO VA AQUI, LO DEJO TODO COMENTADO POR SI ACASO, SOY SILVIA ;)
//#include "Personajes.h" //PARA PODER POSICIONAR LAS PIEZAS

class Tablero {
private:
    Casilla matriz[ANCHO_TABLERO][ALTO_TABLERO];
    float lado;
    int turno; //por ejemplo 0 para humanos y 1 para aliens

    //Personajes_carac pieza[][];

public:
    // Constructor
    Tablero();

    // Funciones principales
    void inicializa();
    void dibuja();

    // Getters por si los necesitas después
    //int getFilas() { return filas; }
    //int getCols() { return cols; }

    //INCIALIZAR POSICIONES PIEZAS
	//void inicializarPiezas();


    //funciones logica del cursor con sofia
    Casilla datos_casilla(int x, int y);
    void vacia_casilla(int x, int y);
    void rellena_casilla(int x, int y, Casilla nueva); //procesar si tiene sentido lo q hace en casilla
    

};
