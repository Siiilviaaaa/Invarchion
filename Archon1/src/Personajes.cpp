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
		pieza.setV_base(0.8);

		pieza.setVelocidad(0.8);
		pieza.t_paralisis = 0;
		pieza.t_hiperVelocidad = 0;
		break;
	case ARQUERO:
		pieza.setVida(80);
		pieza.setDanio(15);
		pieza.setV_base(1.2);

		pieza.setVelocidad(1.2);
		pieza.t_paralisis = 0;
		pieza.t_hiperVelocidad = 0;
		break;
	case VOLADOR:
		pieza.setVida(140);
		pieza.setDanio(8);
		pieza.setV_base(1.5);

		pieza.setVelocidad(1.5);
		pieza.t_paralisis = 0;
		pieza.t_hiperVelocidad = 0;
		break;
	case EXCAVADOR:
		pieza.setVida(60);
		pieza.setDanio(30);
		pieza.setV_base(1.0);

		pieza.setVelocidad(1.0);
		pieza.t_paralisis = 0;
		pieza.t_hiperVelocidad = 0;
		break;
	case HECHICERO:
		pieza.setVida(90);
		pieza.setDanio(25);
		pieza.setV_base(1.3);
		pieza.setVelocidad(1.3);
		break;
	default:
		break;
	}
	return pieza;
}

void Personajes_carac::actualizarEfectos()
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