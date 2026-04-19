#include "MotorGrafico.h"

MotorGrafico::MotorGrafico():
	calavera ("Recursos/calavera.png"),
	Flecha ("Recursos/flecha.png"),
	Paralisis ("Recursos/hechizo1.png"),
	Velocidad ("Recursos/hechizo2.png"),
	Pocion ("Recursos/pocion.png")
{
	calavera.setSize(1.2, 1.2);
}

void MotorGrafico::dibujarPersonaje(const Personaje& personaje)
{
	//HACER ANIMACION!!!!!!!!!!!!!!!!
	switch (personaje.return_Tipo())
	{
	case Tipo_figura::LUCHADOR:
		if (personaje.return_Bando() == HUMANO)
		{
			luchador.setPos(personaje.return_X(), personaje.return_Y());
			luchador.draw();
		}else
		{
			golem.setPos(personaje.return_X(), personaje.return_Y());
			golem.draw();
		}
		break;
	case Tipo_figura::ARQUERO:
		if (personaje.return_Bando() == HUMANO)
		{
			soldado.setPos(personaje.return_X(), personaje.return_Y());
			soldado.draw();
		}
		else
		{
			arquero.setPos(personaje.return_X(), personaje.return_Y());
			arquero.draw();
		}
		break;
	case Tipo_figura::VOLADOR:
		if (personaje.return_Bando() == HUMANO)
		{
			volador.setPos(personaje.return_X(), personaje.return_Y());
			volador.draw();
		}
		else
		{
			murcielago.setPos(personaje.return_X(), personaje.return_Y());
			murcielago.draw();
		}
		break;
	case Tipo_figura::EXCAVADOR:
		if (personaje.return_Bando() == HUMANO)
		{
			minero.setPos(personaje.return_X(), personaje.return_Y());
			minero.draw();
		}
		else
		{
			gusano.setPos(personaje.return_X(), personaje.return_Y());
			gusano.draw();
		}
		break;
	case Tipo_figura::HECHICERO:
		if (personaje.return_Bando() == HUMANO)
		{
			hechicero.setPos(personaje.return_X(), personaje.return_Y());
			hechicero.draw();
		}
		else
		{
			mago.setPos(personaje.return_X(), personaje.return_Y());
			mago.draw();
		}
		break;
	default:
		break;
	}
}

void MotorGrafico::dibujarDisparo(const Disparo& disparo)
{
	if (disparo.return_Activo())
	{
		Flecha.setPos(disparo.return_X(), disparo.return_Y());
		Flecha.draw();
	}
}

void MotorGrafico::dibujarHechizo(const Hechizo& hechizo)
{
	if (hechizo.return_Activo())
	{
		if (hechizo.return_Tipo() == Hechizo::PARALISIS)
		{
			Paralisis.setPos(hechizo.return_X(), hechizo.return_Y());
			Paralisis.draw();
		}
		else if(hechizo.return_Tipo() == Hechizo::HIPERVELOCIDAD)
		{
			Velocidad.setPos(hechizo.return_X(), hechizo.return_Y());
			Velocidad.draw();
		}
		else if(hechizo.return_Tipo() == Hechizo::POCION)
		{
			Pocion.setPos(hechizo.return_X(), hechizo.return_Y());
			Pocion.draw();
		}
	}
}

void MotorGrafico::dibujarCalavera(const Personaje& personaje)
{
	double x = personaje.return_X();
	double y = personaje.return_Y() + 1.2; //DIBUJAR CALAVERA ENCIMA DEL PERSONAJE

	if (personaje.return_Vida() <= 0) //SI MUERE, DIBUJAR CALAVERA
	{
		calavera.setPos(x, y);
		calavera.draw();
	}
}