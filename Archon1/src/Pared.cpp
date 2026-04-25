#include "Pared.h"
#include <cmath>

Pared::Pared(double x_1, double y_1, double x_2, double y_2, unsigned char rojo, unsigned char verde, unsigned char azul)
{
	x1 = x_1;
	y1 = y_1;
	x2 = x_2;
	y2 = y_2;
	r = rojo;
	g = verde;
	b = azul;
}

double Pared::distancia(double px, double py) const
{
	//CUANTO MIDE PARED DE LARGO
	double dx = x2 - x1;
	double dy = y2 - y1;
	double largo = dx * dx + dy * dy;

	//ESTAMOS BUSCANDO EL CAMINO MAS CORTO A LA PARED
	//DONDE ESTAMOS
	double donde = ((px - x1) * dx + (py - y1) * dy) / largo;

	if (donde < 0)donde = 0; //ESTAMOS ANTES DEL PUNTO 1
	if (donde > 1)donde = 1; //ESTAMOS DESPUES DEL PUNTO 2
	
	double puntox = x1 + donde * dx; //PUNTO CERCANO
	double puntoy = y1 + donde * dy;

	//DISTANCIA AL PUNTO CERCANO
	double distx = px - puntox;
	double disty = py - puntoy;

	return sqrt(distx*distx+disty*disty);
}