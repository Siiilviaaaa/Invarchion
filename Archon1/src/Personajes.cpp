#include "Batalla.h"
#include "Hechizos.h"
#include "Disparos.h"
#include <iostream>
#include "Juego.h"

Personaje::Personaje(Tipo_figura t, Bando b, double posX, double posY)
{
	tipo = t;
	bando = b;
	x = posX;
	y = posY;
	disparosRealizados = 0;
	t_recarga = 0.0;
	hechizoUtilizado = 0;
	hechizosRestantes = 3;
	t_paralisis = 0;
	dirX = 0;
	dirY = 0;
	moviendose = false;
}

Personaje::~Personaje()
{}

//constructores de las clases hijo:
Luchador::Luchador(Bando b, double posX, double posY) : Personaje(LUCHADOR, b, posX, posY) {
	vida = 100; 
	vida_max = 100;
	danio = 15; 
	vel_base = 2.0; 
	movimientos = 10; 
	v = vel_base;
}

Arquero::Arquero(Bando b, double posX, double posY) : Personaje(ARQUERO, b, posX, posY) {
	vida = 80; 
	vida_max = 80; 
	danio = 15; 
	vel_base = 2.6; 
	movimientos = 2; 
	v = vel_base;
}

Volador::Volador(Bando b, double posX, double posY) : Personaje(VOLADOR, b, posX, posY) {
	vida = 120; 
	vida_max = 120; 
	danio = 20; 
	vel_base = 3.1; 
	movimientos = 3; 
	v = vel_base;
}

Excavador::Excavador(Bando b, double posX, double posY) : Personaje(EXCAVADOR, b, posX, posY) {
	vida = 200; 
	vida_max = 200; 
	danio = 40; 
	vel_base = 1.2; 
	movimientos = 3; 
	v = vel_base;
}

Hechicero::Hechicero(Bando b, double posX, double posY) : Personaje(HECHICERO, b, posX, posY) {
	vida = 90; 
	vida_max = 90; 
	danio = 10; 
	vel_base = 1.7; 
	movimientos = 10; 
	v = vel_base;
}


Personaje* Personaje::crearPieza(Tipo_figura tipo, Bando b, double posX, double posY)
{
	switch (tipo)
	{
	case LUCHADOR: 
		return new Luchador(b, posX, posY);
	case ARQUERO:   
		return new Arquero(b, posX, posY);
	case VOLADOR:   
		return new Volador(b, posX, posY);
	case EXCAVADOR: 
		return new Excavador(b, posX, posY);
	case HECHICERO: 
		return new Hechicero(b, posX, posY);
	default:        
		return nullptr;
	}
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

bool Personaje::gestionRecarga()
{
	if (t_recarga > 0.0) {
		t_recarga -= 0.02;

		//CUANDO SE AGOTA EL TIEMPO, RECARGE DE MUNICION
		if (t_recarga <= 0.0) {
			disparosRealizados = 0;
			t_recarga = 0.0;
			std::cout << "Municion recargada!" << std::endl;
			return true;
		}
	}
	//CUANDO NOS QUEDAMOS SIN BALAS, INICIAMOS EL TIEMPO
	else if (disparosRealizados >= 10) {
		t_recarga = 10.0; //TIEMPO
	}
	return false;
}

bool Personaje::actualizarEfectos()
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
			return true;
		}
	}
	return false;
}