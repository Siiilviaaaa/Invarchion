#pragma once
#include "Pared.h"

class Caja
{
	friend class MotorGrafico;

	Pared suelo;
	Pared techo;
	Pared izq;
	Pared dcha;

public:
	Pared return_suelo() const { return suelo; }
	Pared return_techo()const { return techo;}
	Pared return_izq()const { return izq;}
	Pared return_dcha()const { return dcha; }
};

