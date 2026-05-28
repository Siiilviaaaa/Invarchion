#include <cmath>
#include <iostream>
#include "Hechizos.h"

Hechizo::Hechizo(TipoHechizo t, Bando b)
{
	this->tipo = t;
	this->bando = b; //SE EMPLEA EL THIS PARA UTILIZAR LOS ATRIBUTOS PROPIOS DE LA CLASE
}

void Hechizo::activar(double x, double y, double dirX, double dirY) //SE ACTIVA EL HECHIZO EN LA POSICION DEL MAGO
{
	this->posX = x;
	this->posY = y;
	this->activo = true;

	double dist = sqrt(dirX * dirX + dirY * dirY);
	double velBase = 0.1;

	//VELOCIDAD HASTA EL OBJETIVO, INDEPENDIENTEMENTE DE LA DISTANCIA
	if (dist > 0) {
		this->vx = (dirX / dist) * velBase;
		this->vy = (dirY / dist) * velBase;
	}
	else {
		this->vx = velBase;
		this->vy = 0;
	}
}

void Hechizo::mover()
{
	if (!activo || objetivo == nullptr) return; // SI NO ESTA ACTIVO O NO TIENE OBJETIVO, NO SE MUEVE

	//DISTANCIA ACTUAL AL OBJETIVO
	double dirX = objetivo->return_X() - posX;
	double dirY = objetivo->return_Y() - posY;
	double dist = sqrt(dirX * dirX + dirY * dirY);

	//AJUSTAR VELOCIDAD
	double velBase = 0.12;
	vx = (dirX / dist) * velBase;
	vy = (dirY / dist) * velBase;

	//MOVIMIENTO
	posX += vx;
	posY += vy;
}

bool Hechizo::Impacta(double Obx, double Oby, double Obr)
{
	if (!activo) return false; // SI NO ESTA ACTIVO, NO HAY IMPACTO

	double dx = posX - Obx;
	double dy = posY - Oby;
	return (sqrt(dx * dx + dy * dy) < Obr);
}