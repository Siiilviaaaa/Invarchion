#pragma once
#include "Personajes.h"
#include "freeglut.h"
#include "Juego.h"
#include "ETSIDI.h"

//CABECERAS DE FUNCIONES
void KeyBatalla(unsigned char key, Personajes_carac& j1, Personajes_carac& j2,
				double x1, double y1, double x2, double y2);
int FinalBatalla(Personajes_carac& humanos, Personajes_carac& aliens);
void actualizarCombate(Personajes_carac& j1, Personajes_carac& j2);
void pegar(Personajes_carac& atacante, Personajes_carac& objetivo,
			double x1, double y1, double x2, double y2);