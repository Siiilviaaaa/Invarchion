#pragma once
#include "Personajes.h"
#include "freeglut.h"
#include "Juego.h"
#include "ETSIDI.h"

//CABECERAS DE FUNCIONES
void KeyBatalla(unsigned char key, Personaje& j1, Personaje& j2,
				double x1, double y1, double x2, double y2);
int FinalBatalla(Personaje& humanos, Personaje& aliens);
void actualizarCombate(Personaje& j1, Personaje& j2);
void pegar(Personaje& atacante, Personaje& objetivo,
			double x1, double y1, double x2, double y2);