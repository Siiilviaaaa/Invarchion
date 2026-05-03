#pragma once

class Personaje; //DECLARACION ANTICIPADA

class Disparo
{
	friend class MotorGrafico;

	double x, y; // POSICION
	double velo_x, velo_y; // VELOCIDAD
	int danio; // DAÑO QUE CAUSA
	bool activo; // SI ESTA O NO EN PANTALLA

public:
	//////////GETTERS Y SETTERS///////////
	bool return_Activo() const { return activo; }
	double return_X() const { return x; }
	double return_Y() const { return y; }
	double return_VX() const { return velo_x; }
	double return_VY() const { return velo_y; }
	void setX(double nuevoX) { x = nuevoX; }
	void setY(double nuevoY) { y = nuevoY; }
	void setVX(double nuevoVX) { velo_x = nuevoVX; }
	void setVY(double nuevoVY) { velo_y = nuevoVY; }
	void setActivo(bool nuevoActivo) { activo = nuevoActivo; }

	////////////////METODOS///////////////
	Disparo();//COSNTRUCTOR
	void moverDisparo();
	bool Impacto(Personaje& objetivo, Personaje& atacante);
};

