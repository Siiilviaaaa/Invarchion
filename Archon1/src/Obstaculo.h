#pragma once

class Obstaculo
{
	friend class MotorGrafico;

	double x, y;
	double radio;

public:
	Obstaculo(double pos_x, double pos_y, double r);

	double return_X() const { return x; }
	double return_Y() const { return y; }
	double return_Radio() const { return radio; }
};