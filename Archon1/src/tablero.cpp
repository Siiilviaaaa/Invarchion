#include "tablero.h"

Tablero::Tablero() {
    filas = 5;
    cols = 7;
    tamCasilla = 2.0f;
}

void Tablero::inicializarCamara() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Ajustamos el mundo 2D para que quepa el 5x7 con un poco de margen
    gluOrtho2D(-1.0, (cols * tamCasilla) + 1.0, -(filas * tamCasilla) - 1.0, 1.0);
}

void Tablero::dibujar() {
    // 1. Dibujar las casillas (Fondo verde)
    glColor3f(0.0f, 0.4f, 0.0f);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            glBegin(GL_QUADS);
            glVertex2f(j * tamCasilla, -i * tamCasilla);
            glVertex2f((j + 1) * tamCasilla, -i * tamCasilla);
            glVertex2f((j + 1) * tamCasilla, -(i + 1) * tamCasilla);
            glVertex2f(j * tamCasilla, -(i + 1) * tamCasilla);
            glEnd();
        }
    }

    // 2. Dibujar la rejilla (Líneas negras)
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    // Líneas horizontales
    for (int i = 0; i <= filas; i++) {
        glBegin(GL_LINES);
        glVertex2f(0, -i * tamCasilla);
        glVertex2f(cols * tamCasilla, -i * tamCasilla);
        glEnd();
    }

    // Líneas verticales
    for (int j = 0; j <= cols; j++) {
        glBegin(GL_LINES);
        glVertex2f(j * tamCasilla, 0);
        glVertex2f(j * tamCasilla, -filas * tamCasilla);
        glEnd();
    }
}