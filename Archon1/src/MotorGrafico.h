#pragma once
#include "ETSIDI.h"
#include "Disparos.h"
#include "Hechizos.h"
#include "Personajes.h"
#include "Caja.h"
#include "Obstaculo.h"
#include "Cursor.h"
#include "tablero.h"

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
	/*ETSIDI::Sprite calavera;
	ETSIDI::Sprite Paralisis;
	ETSIDI::Sprite Velocidad;
	ETSIDI::Sprite Pocion;*/

	Obstaculo* listaObstaculos[5];
	int numObstaculos;

	void recortarBarra(float vida, float x, float y, float ancho, float alto);
	////TABLERO////
	Tablero* tablero = nullptr;
	float lado = 2.0f;
	////MENU////

public:
	MotorGrafico();
	
	// Método para conectar el tablero si el motor se creó vacío
	void setTablero(Tablero* t) { tablero = t; }

	void inicializarBatalla();
	void dibujarPared(const Pared& p);
	void dibujarCursor(Cursor cursor);
	void dibujarObstaculo(const Obstaculo& obs);
	void dibujarCaja(const Caja& c);
	
	void dibujarDisparo(Disparo* disparo);
	void dibujarHechizo(Hechizo* hechizo);
	void dibujarPersonaje(const Personaje& personaje);
	void dibujarBarraVida(Personaje& j1, Personaje& j2);
	/////////TABLERO/////////////
	void dibujaTablero();
	void dibujarFondo();
	void dibujarBordeTurno();
	void dibujarCasilla(const Casilla* c);
	

	/////////METODOS////////////
	//DIRECCION QUE APUNTA A OTRA DIRECCION
	Obstaculo* (&obtenerObstaculos())[5] {return listaObstaculos;}
};