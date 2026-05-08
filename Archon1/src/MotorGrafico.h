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
	ETSIDI::Sprite Paralisis;
	ETSIDI::Sprite Velocidad;
	ETSIDI::Sprite Pocion;

	Obstaculo* listaObstaculos[5];
	int numObstaculos;

	void recortarBarra(float vida, float x, float y, float ancho, float alto);
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
	void dibujarHechizo(Hechizo* hechizo);
	void dibujarPersonaje(const Personaje& personaje);
	void dibujarBarraVida(Personaje& j1, Personaje& j2);

	/////////METODOS////////////
	//DIRECCION QUE APUNTA A OTRA DIRECCION
	Obstaculo* (&obtenerObstaculos())[5] {return listaObstaculos;}
};