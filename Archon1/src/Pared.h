#pragma once
class Pared
{
	friend class MotorGrafico;

	double x1{}, y1{}; //LIMITE 1
	double x2{}, y2{}; //LIMITE 2
	unsigned char r, g, b; //COLORES

public:
	Pared(double x_1, double y_1, double x_2, double y_2, unsigned char rojo, unsigned char verde, unsigned char azul);
	
	double distancia(double px, double py)const;

	double return_X1() const { return x1; }
	double return_X2() const { return x2; }
	double return_Y1() const { return y1; }
	double return_Y2() const { return y2; }
};