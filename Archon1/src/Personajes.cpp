#include "Batalla.h"
#include "Hechizos.h"
#include "Disparos.h"
#include <iostream>
#include "Juego.h"

Personaje::~Personaje()
{}

Personaje Personaje::crearPieza(Tipo_figura tipo, Bando b, double posX, double posY)
{
	Personaje pieza;

	pieza.setTipo(tipo);
	pieza.setBando(b);
	pieza.setX(posX);
	pieza.setY(posY);

	
	//CARACTERISTICAS
	switch (tipo)
	{
	case LUCHADOR:
		pieza.setVida(100);
		pieza.setVidaMax(100);
		pieza.setDanio(15);
		pieza.setV_base(2);
		pieza.setMovimientos(10);
		break;
	case ARQUERO:
		pieza.setVida(80);
		pieza.setVidaMax(80);
		pieza.setDanio(15);
		pieza.setV_base(2.6);
		pieza.setMovimientos(2);
		break;
	case VOLADOR:
		pieza.setVida(120);
		pieza.setVidaMax(120);
		pieza.setDanio(20);
		pieza.setV_base(3.1);
		pieza.setMovimientos(3); //momentaneamente para hacer pruebas
		break;
	case EXCAVADOR:
		pieza.setVida(200);
		pieza.setVidaMax(200);
		pieza.setDanio(40);
		pieza.setV_base(1.2);
		pieza.setMovimientos(3);
		break;
	case HECHICERO:
		pieza.setVida(90);
		pieza.setVidaMax(90);
		pieza.setDanio(10);
		pieza.setV_base(1.7);
		pieza.setMovimientos(10);
		break;
	}
	pieza.setVelocidad(pieza.return_Vbase());

	return pieza;
}

void Personaje::direccion(double dx, double dy)
{
	if (dx != 0 || dy != 0) { //SOLO ACTUALIZAMOS SI SE MUEVE
		dirX = dx;
		dirY = dy;
	}
}

void Personaje::moverEnBatalla()
{
	x += dirX * v * 0.05;
	y += dirY * v * 0.05;
}

void Personaje::gestionRecarga()
{
	if (t_recarga > 0.0) {
		t_recarga -= 0.02;

		//CUANDO SE AGOTA EL TIEMPO, RECARGE DE MUNICION
		if (t_recarga <= 0.0) {
			disparosRealizados = 0;
			t_recarga = 0.0;
			std::cout << "Municion recargada!" << std::endl;
		}
	}
	//CUANDO NOS QUEDAMOS SIN BALAS, INICIAMOS EL TIEMPO
	else if (disparosRealizados >= 10) {
		t_recarga = 10.0; //TIEMPO
	}
}

void Personaje::actualizarEfectos()
{
	if (t_paralisis > 0) //SIGUE CONGELADO
	{
		t_paralisis -= 0.02;

		//SI EL TIEMPO SE AGOTA
		if (t_paralisis <= 0)
		{
			t_paralisis = 0; //RESET PARA EVITAR NEGATIVOS

			this->v = this->vel_base; //DESCONGELAR

			std::cout << "JUGADOR DESCONGELADO" << std::endl;
		}
	}
}

