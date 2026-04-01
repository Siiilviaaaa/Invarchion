#pragma once
#ifndef TABLERO_H
#define TABLERO_H

#include "freeglut.h" // Para las funciones de dibujo de OpenGL

//ELENA CREO QUE ESTO VA AQUI, LO DEJO TODO COMENTADO POR SI ACASO, SOY SILVIA ;)
//#include "Personajes.h" //PARA PODER POSICIONAR LAS PIEZAS

class Tablero {
private:
    int filas;
    int cols;
    float tamCasilla;
    //Personajes_carac pieza[][];

public:
    // Constructor
    Tablero();

    // Funciones principales
    void inicializarCamara();
    void dibujar();

    // Getters por si los necesitas después
    int getFilas() { return filas; }
    int getCols() { return cols; }

    //INCICILIZAR POSICIONES PIEZAS
	//void inicializarPiezas();

};

#endif