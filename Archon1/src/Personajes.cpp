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
		pieza.setDaño(20);
		pieza.setVelocidad(1.0);
		break;
	case ARQUERO:
		pieza.setVida(100);
		pieza.setDaño(20);
		pieza.setVelocidad(1.0);
		break;
	case VOLADOR:
		pieza.setVida(100);
		pieza.setDaño(20);
		pieza.setVelocidad(1.0);
		break;
	case EXCAVADOR:
		pieza.setVida(100);
		pieza.setDaño(20);
		pieza.setVelocidad(1.0);
		break;
	case HECHICERO:
		pieza.setVida(100);
		pieza.setDaño(20);
		pieza.setVelocidad(1.0);
		break;
	default:
		break;
	}
	return pieza;
}
