#pragma once
#include "Pared.h"

class Caja
{
	friend class MotorGrafico;
	const double alto = 20;
	const double ancho = 20;
	Pared suelo, techo, izq, dcha;
	

public:
	Caja() :
		suelo(0, 0, 20, 0, 92, 64, 51),
		techo(0, 15, 20, 15, 75, 50, 35),
		izq(0, 0, 0, 15, 110, 80, 65),
		dcha(20, 0, 20, 15, 85, 60, 45) {}
	Pared return_suelo() const { return suelo; }
	Pared return_techo()const { return techo;}
	Pared return_izq()const { return izq;}
	Pared return_dcha()const { return dcha; }
};

