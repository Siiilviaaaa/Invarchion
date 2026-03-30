#pragma once
#ifndef TABLERO_H
#define TABLERO_H

#include "freeglut.h" // Para las funciones de dibujo de OpenGL

class Tablero {
private:
    int filas;
    int cols;
    float tamCasilla;

public:
    // Constructor
    Tablero();

    // Funciones principales
    void inicializarCamara();
    void dibujar();

    // Getters por si los necesitas después
    int getFilas() { return filas; }
    int getCols() { return cols; }
};

#endif