#pragma once

class Obstaculo
{
	friend class MotorGrafico;

	double x, y;
	double radio;

public:
	Obstaculo(): x(0), y(0), radio(0){}
	Obstaculo(double pos_x, double pos_y, double r);

	double getX() const { return x; }
	double getY() const { return y; }
	double getRadio() const { return radio; }
	
};
