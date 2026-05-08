#include "Hechizos.h"
#include <cmath>
#include <iostream>

Hechizo::Hechizo()
{
	tipo = PARALISIS;
	usos_restantes = 0;
	activo = false;
	posX = 0.0;
	posY = 0.0;
	t_recarga = 0.0;
	t_restante = 0.0;
	vx = 0.0;
	vy = 0.0;
}

void Hechizo::activar(double x, double y, double dirX, double dirY)
{
	this->posX = x;
	this->posY = y;
	this->activo = true;

	double dist = sqrt(dirX * dirX + dirY * dirY);
	double velBase = 0.1;

	if (dist > 0) {
		this->vx = (dirX / dist) * velBase;
		this->vy = (dirY / dist) * velBase;
	}
	else {
		this->vx = velBase;
		this->vy = 0;
	}

	std::cout << "[HECHIZO] Posicion " << posX << "," << posY << std::endl;
}

void Hechizo::mover()
{
	if (activo) {
		posX += vx;
		posY += vy;
	}
}

bool Hechizo::Impacta(double Obx, double Oby, double Obr)
{
	if (!activo) return false;

	double dx = posX - Obx;
	double dy = posY - Oby;
	return (sqrt(dx * dx + dy * dy) < Obr);
}

void Hechizo::configurar(TipoHechizo t)
{
	tipo = t;

	switch (tipo)
	{
	case PARALISIS:
		t_recarga = 5.0;
		usos_restantes = 2;
		break;
	case HIPERVELOCIDAD:
		t_recarga = 5.0;
		usos_restantes = 2;
		break;
	case POCION:
		t_recarga = 0.0; //LA POCION NO TIENE RECARGA, SOLO USOS LIMITADOS
		usos_restantes = 1;
		break;
	}
}

void Hechizo::efectos(Personaje& objetivo)
{
	if (tipo == PARALISIS) {

	}
	else if (tipo == HIPERVELOCIDAD) {
	
	}

	this->activo = false;
}
