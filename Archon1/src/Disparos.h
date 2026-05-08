#pragma once
#include "Personajes.h"

class Disparo
{
	friend class MotorGrafico;

	double x, y; // POSICION
	double velo_x, velo_y; // VELOCIDAD
	int danio; // DAÑO QUE CAUSA
	bool activo; // SI ESTA O NO EN PANTALLA
	int rebotes;
	Bando bando;

public:
	//////////GETTERS Y SETTERS///////////
	bool return_Activo() const { return activo; }
	double return_X() const { return x; }
	double return_Y() const { return y; }
	double return_VX() const { return velo_x; }
	double return_VY() const { return velo_y; }
	int return_Rebotes() const { return rebotes; }
	Bando return_Bando() const { return bando; }
	void setX(double nuevoX) { x = nuevoX; }
	void setY(double nuevoY) { y = nuevoY; }
	void setVX(double nuevoVX) { velo_x = nuevoVX; }
	void setVY(double nuevoVY) { velo_y = nuevoVY; }
	void setActivo(bool nuevoActivo) { activo = nuevoActivo; }
	void setRebotes(int r) { rebotes = r; }
	void setBando(Bando nuevo) { bando = nuevo; }

	////////////////METODOS///////////////
	Disparo();//COSNTRUCTOR
	void moverDisparo();
	bool Impacto(Personaje& objetivo, bool haceDano);
	void sumarRebote() { rebotes++; }
};

