#include <cmath>
#include <iostream>
#include "Hechizos.h"
#include "Juego.h"

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

void Hechizo::aplicarCuracionMasiva(int turno, Hechicero* hech, Juego* ptrJuego)
{
	if (hech == nullptr || ptrJuego == nullptr) return;
	if (hech->return_HechizosRestantes() > 0) { //VERIFICAMOS QUE TENGA HECHIZOS DISPONIBLES

		//RECORREMOS LOS PERSONAJES BUSCANDO ALIADOS
		for (int i = 0; i < 20; i++) {
			Personaje* aliado = ptrJuego->getPersonaje(i); //OBTENEMOS EL PERSONAJE DE LA CASILLA i, SI NO HAY PERSONAJE DEVUELVE NULLPTR
			if (aliado != nullptr && aliado->return_Bando() == turno && aliado->return_Vida() > 0) { //SI EL PERSONAJE EXISTE Y ES UN ALIADO

				//CURAMOS UN TERCIO DE LA VIDA
				int cura = aliado->return_VidaMax() / 3;
				int nuevaVida = aliado->return_Vida() + cura;

				//SIN SUPERAR EL MAXIMO
				if (nuevaVida > aliado->return_VidaMax()) {
					nuevaVida = aliado->return_VidaMax();
				}
				aliado->setVida(nuevaVida);
			}
		}
		hech->usarHechizo(); //RESTAMOS UN HECHIZO AL MAGO
	}
}