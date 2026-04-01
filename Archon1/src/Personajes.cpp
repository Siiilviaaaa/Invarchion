#include "Personajes.h"

using std::cout, std::cin, std::endl;

Personajes_carac Personajes_carac::crearPieza(Tipo tipo)
{
	Personajes_carac pieza;
	pieza.setTipo(tipo);

	//DECIDIR CARACTERISTICAS SEGUN EL TIPO DE PIEZA
	switch (tipo)
	{
	case SOLDADO:
		pieza.setVida(100);
		pieza.setDanio(10);
		pieza.setVelocidad(0.8);
		break;
	case ARQUERO:
		pieza.setVida(80);
		pieza.setDanio(15);
		pieza.setVelocidad(1.2);
		break;
	case VOLADOR:
		pieza.setVida(140);
		pieza.setDanio(8);
		pieza.setVelocidad(1.5);
		break;
	case EXCAVADOR:
		pieza.setVida(60);
		pieza.setDanio(30);
		pieza.setVelocidad(1.0);
		break;
	case HECHICERO:
		pieza.setVida(90);
		pieza.setDanio(25);
		pieza.setVelocidad(1.3);
		break;
	default:
		break;
	}
	return pieza;
}
