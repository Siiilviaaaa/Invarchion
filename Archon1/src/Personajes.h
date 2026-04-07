#pragma once
#include <iostream>
#include "Batalla.h"

enum Tipo { SOLDADO, ARQUERO, VOLADOR, EXCAVADOR, HECHICERO };

class Personajes_carac
{
	Tipo tipo;
	int vida;
	int danio;
	double velocidad;
	double vel_base;
	double x, y;

	//DISPAROS
	static const int MAX_DISPAROS = 10;
	Disparo nDisparos[MAX_DISPAROS];

	//HECHIZOS
	double t_paralisis;
	double t_hiperVelocidad;
	int vida_max; //VARIABLE PARA COMPROBAR SU USAR POCION

public:
	////////////GETTERS/////////////////
	Tipo return_Tipo() const { return tipo; }
	int return_Vida() const { return vida; }
	int return_Danio() const { return danio; }
	double return_Velocidad() const { return velocidad; }
	double return_Vbase() const { return vel_base; }
	double return_X() const { return x; }
	double return_Y() const { return y; }

	double return_paralisis() const { return t_paralisis; }
	double return_hiperVelocidad() const { return t_hiperVelocidad; }

	int return_VidaMax() const { return vida_max; }

	///////////SETTERS/////////////////
	void setTipo(Tipo nuevoTipo) { tipo = nuevoTipo; }
	void setVida(int nuevaVida) { vida = nuevaVida; }
	void setDanio(int nuevoDaño) { danio = nuevoDaño; }
	void setVelocidad(double nuevaVelocidad) { velocidad = nuevaVelocidad; }
	void setV_base(double nuevaVelocidad) { vel_base = nuevaVelocidad; }
	void setX(double nuevaX) { x = nuevaX; }
	void setY(double nuevaY) { y = nuevaY; }

	void set_paralisis(double nuevoTiempo) { t_paralisis = nuevoTiempo; }
	void set_hiperVelocidad(double nuevoTiempo) { t_hiperVelocidad = nuevoTiempo; }

	void setVidaMax(int nuevaVidaMax) { vida_max = nuevaVidaMax; }

	//////////METODOS//////////////
	static Personajes_carac crearPieza(Tipo tipo);
	void actualizarEfectos();

	void gestionarDisparos(Personajes_carac& enemigo);
	void lanzarDisparo();
};