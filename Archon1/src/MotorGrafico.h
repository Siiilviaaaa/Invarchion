#pragma once
#include "ETSIDI.h"
#include "Cursor.h"
#include "tablero.h"
#include "batalla.h"
#include <string>

//RELACION DE AMISTAD DE PERSONAJES, HECHIZOS, DISPAROS PARA PODER ACCEDER A SUS ATRIBUTOS PRIVADOS
enum orientacionPersonaje {MIRANDO_HORIZONTALMENTE, MIRANDO_ABAJO, MIRANDO_ARRIBA, ACCION};
class MotorGrafico
{
	const int numColumnasSpritePersonaje{ 3 };
	const int numFilasSpritePersonaje{ 4 };

	////PERSONAJES HUMANOS////
	ETSIDI::SpriteSequence luchador; //SIN HACER
	ETSIDI::SpriteSequence soldado;
	ETSIDI::SpriteSequence volador; //SIN HACER
	ETSIDI::SpriteSequence minero;
	ETSIDI::SpriteSequence hechicero; //SIN HACER

	////PERSONAJES ALIENS////
	ETSIDI::SpriteSequence golem;
	ETSIDI::SpriteSequence arquero;
	ETSIDI::SpriteSequence murcielago;
	ETSIDI::SpriteSequence gusano; //SIN HACER
	ETSIDI::SpriteSequence mago;
	
	////ELEMENTOS BATALLA////
	ETSIDI::Sprite barraVida;
	void recortarBarra(float vida, float x, float y, float ancho, float alto);
	
	////TABLERO////
	Tablero* tablero = nullptr;
	float lado = 2.0f;

public:
	MotorGrafico();
	Juego* juego;
	// Método para conectar el tablero si el motor se creó vacío
	void setTablero(Tablero* t) { tablero = t; }

	void dibujarPared(const Pared& p);
	void dibujarCursor(Cursor cursor) const;
	void dibujarObstaculo(const Obstaculo& obs);
	void dibujarCaja(const Caja& c, Batalla& b);
	
	void dibujarDisparo(Disparo* disparo);
	void dibujarHechizo(Hechizo* hechizo);
	void dibujarPersonaje(const Personaje& personaje);
	void dibujarBarraVida(Personaje& j1, Personaje& j2);
	/////////TABLERO/////////////
	void dibujarTablero();
	void dibujarFondo();
	void dibujarBordeTurno();
	void dibujarCasilla(const Casilla* c);
	
	//nuevos mios de dibujo de instrucciones
	void dibujarMensajeBando(const std::string& textoBando);
	void dibujarInstruccionesTablero();
	void dibujarMensajesBatalla(const std::string& mensaje);
};