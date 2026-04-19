#pragma once
#include "ETSIDI.h"
#include "Disparos.h"
#include "Hechizos.h"
#include "Personajes.h"

class MotorGrafico
{
	////PERSONAJES HUMANOS////
	ETSIDI::Sprite luchador; //SIN HACER PERO PARA PODER CREAR LA FUNCION ME LO INVENTO, CAMBIAR LUEGO LOS NORMBRES
	ETSIDI::Sprite soldado;
	ETSIDI::Sprite volador; //SIN HACER
	ETSIDI::Sprite minero;
	ETSIDI::Sprite hechicero; //SIN HACER

	////PERSONAJES ALIENS////
	ETSIDI::Sprite golem;
	ETSIDI::Sprite arquero;
	ETSIDI::Sprite murcielago;
	ETSIDI::Sprite gusano; //SIN HACER
	ETSIDI::Sprite mago; //SIN HACER
	
	////ELEMENTOS BATALLA////
	ETSIDI::Sprite barraVida;
	ETSIDI::Sprite calavera;
	ETSIDI::Sprite Flecha;
	ETSIDI::Sprite Paralisis;
	ETSIDI::Sprite Velocidad;
	ETSIDI::Sprite Pocion;

	////TABLERO////

	////MENU////

public:
	MotorGrafico();
	void dibujarDisparo(const Disparo& disparo);
	void dibujarHechizo(const Hechizo& hechizo);
	void dibujarPersonaje(const Personaje& personaje);
	void dibujarCalavera(const Personaje& personaje);
};

