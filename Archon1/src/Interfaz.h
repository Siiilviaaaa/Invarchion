#pragma once

#include "freeglut.h"
#include "Juego.h" 

// Prototipos de las funciones
void OnDraw();
void OnTimer(int value);
void OnKeyboardDown(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mousePassive(int x, int y);
void redimensionar(int width, int height);