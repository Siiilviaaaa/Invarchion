#pragma once
#include "ETSIDI.h"
#include "Disparos.h"
#include "Hechizos.h"
#include "Personajes.h"
#include "Caja.h"
#include "Obstaculo.h"
#include "Cursor.h"

//RELACION DE AMISTAD DE PERSONAJES, HECHIZOS, DISPAROS PARA PODER ACCEDER A SUS ATRIBUTOS PRIVADOS

class MotorGrafico
{
	const int numColumnasSpritePersonaje{ 3 };
	const int numFilasSpritePersonaje{ 4 };
	////PERSONAJES HUMANOS////
	ETSIDI::SpriteSequence luchador; //SIN HACER PERO PARA PODER CREAR LA FUNCION ME LO INVENTO, CAMBIAR LUEGO LOS NORMBRES
	ETSIDI::SpriteSequence soldado;
	ETSIDI::SpriteSequence volador; //SIN HACER
	ETSIDI::SpriteSequence minero;
	ETSIDI::SpriteSequence hechicero; //SIN HACER

	////PERSONAJES ALIENS////
	ETSIDI::SpriteSequence golem;
	ETSIDI::SpriteSequence arquero;
	ETSIDI::SpriteSequence murcielago;
	ETSIDI::SpriteSequence gusano; //SIN HACER
	ETSIDI::SpriteSequence mago; //SIN HACER
	
	////ELEMENTOS BATALLA////
	ETSIDI::Sprite barraVida;
	ETSIDI::Sprite calavera;
	ETSIDI::Sprite Paralisis;
	ETSIDI::Sprite Velocidad;
	ETSIDI::Sprite Pocion;

	Obstaculo* listaObstaculos[5];
	int numObstaculos;

	////TABLERO////

	////MENU////

public:
	MotorGrafico();
	
	void inicializarBatalla();
	void dibujarPared(const Pared& p);
	void dibujarCursor(Cursor cursor);
	void dibujarObstaculo(const Obstaculo& obs);
	void dibujarCaja(const Caja& c);
	
	void dibujarDisparo(Disparo* disparo);
	void dibujarHechizo(const Hechizo& hechizo);
	void dibujarPersonaje(const Personaje& personaje);
	void dibujarVida_Muerte(const Personaje& humano, const Personaje& alien);
	
};