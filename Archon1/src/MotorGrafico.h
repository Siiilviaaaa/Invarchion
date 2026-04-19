#pragma once
#include "ETSIDI.h"
#include "Disparos.h"
#include "Hechizos.h"
#include "Personajes.h"

class MotorGrafico
{
	ETSIDI::Sprite Flecha;
	ETSIDI::Sprite Paralisis;
	ETSIDI::Sprite Velocidad;
	ETSIDI::Sprite Pocion;

public:
	MotorGrafico();
	~MotorGrafico();
	void dibujarDisparo(const Disparo& disparo);
	void dibujarHechizo(const Hechizo& hechizo);
	void dibujarPersonaje(const Personaje& personaje);
};

