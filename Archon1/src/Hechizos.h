#pragma once
#include "Personajes.h"

class Hechizo
{
	friend class MotorGrafico;

public:
	enum TipoHechizo : int { PARALISIS, HIPERVELOCIDAD, POCION };
private:
	TipoHechizo tipo;
	bool activo;
	double posX, posY;
	double vx, vy;
	Bando bando;

	int usos_restantes;
	double t_recarga;
	double t_restante;

public:
	double return_RESTANTE() const { return t_restante; }
	bool return_Activo() const { return activo; }
	double return_X() const { return posX; }
	double return_Y() const { return posY; }
	void setPosicion(double x, double y) { posX = x; posY = y; }
	void setVelocidad(double velX, double velY) { vx = velX; vy = velY; }

	Hechizo(); //CONSTRUCTOR 
	void mover();
	void configurar(TipoHechizo t);
	void activar(double x, double y, double dirX, double dirY);
	void efectos(Personaje& objetivo);
};