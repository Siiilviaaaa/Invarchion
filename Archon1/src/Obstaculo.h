#pragma once

class Obstaculo
{
	double x, y;
	double radio;
public:
	Obstaculo(double pos_x, double pos_y, double r);
	bool colisiona(double px, double py, double pr) const;

	double getX() const { return x; }
	double getY() const { return y; }
	double getRadio() const { return radio; }

};

