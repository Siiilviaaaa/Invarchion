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

double Pared::distancia(double px, double py, double* pdir_x, double* pdir_y)
{
	return 0.0;
}