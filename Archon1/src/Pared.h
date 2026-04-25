#pragma once
class Pared
{
	friend class MotorGrafico;

	double x1{}, y1{}; //LIMITE 1
	double x2{}, y2{}; //LIMITE 2
	unsigned char r, g, b; //COLORES

public:
	Pared(double x_1, double y_1, double x_2, double y_2, unsigned char rojo, unsigned char verde, unsigned char azul);
	
	double distancia(double px, double py, double* pdir_x, double* pdir_);
};