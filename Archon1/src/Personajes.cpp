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
	danio = 25; 
	vel_base = 12.0; 
	movimientos = 10; //cambiar
	v = vel_base;
}

Arquero::Arquero(Bando b, double posX, double posY) : Personaje(ARQUERO, b, posX, posY) {
	vida = 110; 
	vida_max = 110; 
	danio = 25; 
	vel_base = 12.6; 
	movimientos = 3; 
	v = vel_base;
}

Volador::Volador(Bando b, double posX, double posY) : Personaje(VOLADOR, b, posX, posY) {
	vida = 120; 
	vida_max = 120; 
	danio = 30; 
	vel_base = 13.1; 
	movimientos = 3; 
	v = vel_base;
}

Excavador::Excavador(Bando b, double posX, double posY) : Personaje(EXCAVADOR, b, posX, posY) {
	vida = 150; 
	vida_max = 150; 
	danio = 35; 
	vel_base = 11.2; 
	movimientos = 4; 
	v = vel_base;
}

void Excavador::activarAtaque()
{
	Personaje::activarAtaque(); 
	temporizadorExcavacion = 250; // 5 segundos bajo tierra
}

bool Excavador::actualizarEfectos()
{
	Personaje::actualizarEfectos(); //para tmb tener la congelacion
	if (temporizadorExcavacion > 0) {
		temporizadorExcavacion--;
		std::cout << "excavando" << std::endl;
	}
	return 1;
}

bool Excavador::estaBajoTierra() const
{
	if (temporizadorExcavacion > 0) {
		return true;
	}
	else {
		return false;
	}
	
}

int Excavador::getFaseExcavacion() const
{
	if (temporizadorExcavacion == 0)
		return 0; //no esta excavando
	if (temporizadorExcavacion > 230)
		return 1; //para el frame de meterse en la tierra
	return 2; //bajo tierra
}

Hechicero::Hechicero(Bando b, double posX, double posY) : Personaje(HECHICERO, b, posX, posY) {
	vida = 200; 
	vida_max = 200; 
	danio = 30; 
	vel_base = 11.7; 
	movimientos = 5; 
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
	

	x += dirX * v * 0.1;
	y += dirY * v * 0.1;
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

void Personaje::activarAtaque()
{
	temporizadorAtaque = 15; //reseteo el tempporizador
	std::cout << "ataqueactivado"<<std::endl;
}

bool Personaje::estaAtacando() const
{
	if (temporizadorAtaque > 0) {//no puedo restarle al temp aqui porq en la llamada a la funcion el personaje es const, entonces esto tiene que ser const tmb
		//std::cout << temporizadorAtaque << std::endl;
		return true;
	}
	else {
		return false;
	}
	
}

bool Personaje::actualizarEfectos()
{
	if (temporizadorAtaque > 0) {
		temporizadorAtaque--;
		std::cout << temporizadorAtaque << std::endl;
	}

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