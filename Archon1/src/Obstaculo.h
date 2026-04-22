#pragma once
#include "Disparos.h"
#include "Personajes.h"

class Obstaculo
{
	double x, y;
	double radio;
	//SERA ALGO GRAFICO O UNA IMAGEN??

public:
	Obstaculo(double pos_x, double pos_y, double r);

	static void reboteDisparo(Disparo& d);
	static void NoPasar(Personaje& j1, Personaje& j2);

	double getX() const { return x; }
	double getY() const { return y; }
	double getRadio() const { return radio; }

};

