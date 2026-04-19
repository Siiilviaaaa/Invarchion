#pragma once
#include "ETSIDI.h"

class Personaje; //DECLARACION ANTICIPADA

class Disparo
{
	double x, y; // POSICION
	double velo_x, velo_y; // VELOCIDAD
	int danio; // DAÑO QUE CAUSA
	bool activo; // SI ESTA O NO EN PANTALLA

	ETSIDI::Sprite flecha;

public:
	//////////GETTERS Y SETTERS///////////
	bool return_Activo() const { return activo; }
	void setX(double nuevoX) { x = nuevoX; }
	void setY(double nuevoY) { y = nuevoY; }
	void setVX(double nuevoVX) { velo_x = nuevoVX; }
	void setVY(double nuevoVY) { velo_y = nuevoVY; }
	void setActivo(bool nuevoActivo) { activo = nuevoActivo; }

	////////////////METODOS///////////////
	Disparo();//COSNTRUCTOR
	void dibujarDisparo();
	void moverDisparo();
	bool Impacto(Personaje& objetivo);

};

