#pragma once
#include "Pared.h"
#include "ETSIDI.h"
class Caja
{
	friend class MotorGrafico;
	const double alto = 20;
	const double ancho = 20;
	Pared suelo, techo, izq, dcha;
	

public:
	Caja() :
		suelo(0, 0, 20, 0, 26, 9, 26),
		techo(0, 15, 20, 15, 61, 28, 43),
		izq(0, 0, 0, 15, 107, 45, 45),
		dcha(20, 0, 20, 15, 107, 45, 50) {}
	Pared return_suelo() const { return suelo; }
	Pared return_techo()const { return techo;}
	Pared return_izq()const { return izq;}
	Pared return_dcha()const { return dcha; }
};

