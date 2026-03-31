#pragma once
#include <iostream>

enum Tipo { SOLDADO, ARQUERO, VOLADOR, EXCAVADOR, HECHICERO };

class Personajes_carac
{
	Tipo tipo;
	int vida;
	int daño;
	double velocidad;

public:

	static Personajes_carac crearPieza(Tipo tipo);

	//LEER LOS VALORES
	Tipo return_Tipo() const { return tipo; }
	int return_Vida() const { return vida; }
	int return_Daño() const { return daño; }
	double return_Velocidad() const { return velocidad; }

	//MODIFICAN NUEVOS VALORES
	void setTipo(Tipo nuevoTipo) { tipo = nuevoTipo; }
	void setVida(int nuevaVida) { vida = nuevaVida; }
	void setDaño(int nuevoDaño) { daño = nuevoDaño; }
	void setVelocidad(double nuevaVelocidad) { velocidad = nuevaVelocidad; }
};