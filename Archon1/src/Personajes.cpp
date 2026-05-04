#include "Batalla.h"
#include "Hechizos.h"
#include "Disparos.h"

////VARIABLES GLOBALES
int Personaje::puntuacionHumanos = 0;
int Personaje::puntuacionAliens = 0;

//personaje::personaje(tipo_figura t, bando e, int x, int y)
Personaje::Personaje()
{
	for (int i = 0;i < MAX_DISPAROS;i++)
		nDisparos[i] = nullptr;
}

Personaje::~Personaje()
{
	//LIMPIAR MEMORIA DE LOS DISPAROS CUANDO EL PERSOANJE MUERE
	for (int i = 0; i < MAX_DISPAROS; i++)
	{
		if (nDisparos[i] != nullptr)
		{
			delete nDisparos[i];
			nDisparos[i] = nullptr;
		}
	}
}

void Personaje::sumarPuntos(int puntos)
{
	if (bando == HUMANO)
		puntuacionHumanos += puntos;
	else
		puntuacionAliens += puntos;
}

Personaje Personaje::crearPieza(Tipo_figura tipo, Bando b, double posX, double posY)
{
	Personaje pieza;

	pieza.setTipo(tipo);
	pieza.setBando(b);
	pieza.setX(posX);
	pieza.setY(posY);
	pieza.set_paralisis(0.0);
	pieza.set_hiperVelocidad(0.0);

	//DECIDIR CARACTERISTICAS SEGUN EL TIPO DE PIEZA
	switch (tipo)
	{
	case LUCHADOR:
		pieza.setVida(100);
		pieza.setVidaMax(100);
		pieza.setDanio(10);
		pieza.setV_base(0.8);
		break;
	case ARQUERO:
		pieza.setVida(80);
		pieza.setVidaMax(80);
		pieza.setDanio(15);
		pieza.setV_base(1.2);
		break;
	case VOLADOR:
		pieza.setVida(140);
		pieza.setVidaMax(140);
		pieza.setDanio(8);
		pieza.setV_base(1.5);
		break;
	case EXCAVADOR:
		pieza.setVida(60);
		pieza.setVidaMax(60);
		pieza.setDanio(30);
		pieza.setV_base(1.0);
		break;
	case HECHICERO:
		pieza.setVida(90);
		pieza.setVidaMax(90);
		pieza.setDanio(25);
		pieza.setV_base(1.3);
		break;
	}
	pieza.setVelocidad(pieza.return_Vbase());

	return pieza;
}

void Personaje::lanzarDisparo()
{
	if (tipo != ARQUERO) return;

	for (int i = 0;i < MAX_DISPAROS;i++)
	{
		if (nDisparos[i]==nullptr)
		{
			nDisparos[i] = new Disparo(); //RESERVA MEMORIA

			nDisparos[i]->setX(x);
			nDisparos[i]->setY(y);
			nDisparos[i]->setVX(0.2);
			nDisparos[i]->setVY(1.0);
			nDisparos[i]->setActivo(true);
			break;
		}
	}
}

void Personaje::gestionarDisparos(Personaje& enemigo)
{
	for (int i = 0;i < MAX_DISPAROS;i++)
		if (nDisparos[i] != nullptr)
		{
			nDisparos[i]->moverDisparo();

			if (nDisparos[i]->Impacto(enemigo, *this) || !nDisparos[i]->return_Activo())
			{ //SI NO ESTA ACTIVO Y SI IMPACTA
				delete nDisparos[i]; //LIBERAR MEMORIA
				nDisparos[i] = nullptr; //DEJAR HUECO LIBRE
			}
		}
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