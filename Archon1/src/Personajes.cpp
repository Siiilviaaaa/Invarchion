#include "Batalla.h"
#include "Hechizos.h"
#include "Disparos.h"

//METER EN JUEGO.CPP
//void Personaje::sumarPuntos(int puntos)
//{
//	if (bando == HUMANO)
//		puntuacionHumanos += puntos;
//	else
//		puntuacionAliens += puntos;
//}

Personaje Personaje::crearPieza(Tipo_figura tipo, Bando b, double posX, double posY)
{
	Personaje pieza;

	pieza.setTipo(tipo);
	pieza.setBando(b);
	pieza.setX(posX);
	pieza.setY(posY);
	pieza.set_paralisis(0.0);
	pieza.set_hiperVelocidad(0.0);

	//SPRITES
	/*if (tipo == LUCHADOR)
		pieza.sprite = (b == HUMANO) ? ETSIDI::SpriteSequence("Recursos/luchador.png", 5) : ETSIDI::SpriteSequence("Recursos/golem.png", 5);
	else if (tipo == ARQUERO)
		pieza.sprite = (b == HUMANO) ? ETSIDI::SpriteSequence("Recursos/soldado.png", 5) : ETSIDI::SpriteSequence("Recursos/arquero.png", 5);
	else if (tipo == VOLADOR)
		pieza.sprite = (b == HUMANO) ? ETSIDI::SpriteSequence("Recursos/volador.png", 5) : ETSIDI::SpriteSequence("Recursos/murcielago.png", 5);
	else if (tipo == EXCAVADOR)
		pieza.sprite = (b == HUMANO) ? ETSIDI::SpriteSequence("Recursos/minero.png", 5) : ETSIDI::SpriteSequence("Recursos/gusano.png", 5);
	else if (tipo == HECHICERO)
		pieza.sprite = (b == HUMANO) ? ETSIDI::SpriteSequence("Recursos/hechicero.png", 5) : ETSIDI::SpriteSequence("Recursos/mago.png", 5);*/
	
	//CARACTERISTICAS
	switch (tipo)
	{
	case LUCHADOR:
		pieza.setVida(100);
		pieza.setVidaMax(100);
		pieza.setDanio(15);
		pieza.setV_base(1.8);
		break;
	case ARQUERO:
		pieza.setVida(80);
		pieza.setVidaMax(80);
		pieza.setDanio(15);
		pieza.setV_base(2.4);
		break;
	case VOLADOR:
		pieza.setVida(120);
		pieza.setVidaMax(120);
		pieza.setDanio(10);
		pieza.setV_base(2.9);
		break;
	case EXCAVADOR:
		pieza.setVida(200);
		pieza.setVidaMax(200);
		pieza.setDanio(40);
		pieza.setV_base(1);
		break;
	case HECHICERO:
		pieza.setVida(90);
		pieza.setVidaMax(90);
		pieza.setDanio(25);
		pieza.setV_base(1.5);
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

	dirX = 0;
	dirY = 0;
}

void Personaje::actualizarEfectos()
{
	if (t_paralisis > 0)
	{
		t_paralisis -= 0.1; //DISMINUIR TIEMPO DE PARALISIS
		if (t_paralisis < 0)
			t_paralisis = 0;
	}

	if (t_hiperVelocidad > 0)
	{
		t_hiperVelocidad -= 0.1; //DISMINUIR TIEMPO DE HIPER VELOCIDAD
		if (t_hiperVelocidad < 0)
			t_hiperVelocidad = 0;
	}

	//RECALCULAR LA VELOCIDAD ACTUAL
	if (t_paralisis > 0)
		setVelocidad(return_Vbase() * 0.5); //PARALISIS REDUCE VELOCIDAD A LA MITAD
	else if (t_hiperVelocidad > 0)
		setVelocidad(return_Vbase() * 1.5); //HIPER VELOCIDAD AUMENTA VELOCIDAD EN UN 50%
	else
		setVelocidad(return_Vbase()); //VELOCIDAD NORMAL
}