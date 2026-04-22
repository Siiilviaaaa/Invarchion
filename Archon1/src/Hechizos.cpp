#include "Hechizos.h"
#include "Personajes.h"
#include "Juego.h"

///VARIABLES GLOBALES///
Hechizo hechizos[3];
bool usoPocion = false;
extern Juego juego;

Hechizo::Hechizo()
{
	tipo = PARALISIS;
	usos_restantes = 0;
	activo = false;
	posX = 0.0;
	posY = 0.0;
	t_recarga = 0.0;
	t_restante = 0.0;
}

void Hechizo::configurar(TipoHechizo t)
{
	tipo = t;

	switch (tipo)
	{
	case PARALISIS:
		t_recarga = 5.0;
		usos_restantes = 2;
		break;
	case HIPERVELOCIDAD:
		t_recarga = 5.0;
		usos_restantes = 2;
		break;
	case POCION:
		t_recarga = 0.0; //LA POCION NO TIENE RECARGA, SOLO USOS LIMITADOS
		usos_restantes = 1;
		break;
	}
}

void Hechizo::actualizarTiempos(double Time)
{
	if (t_restante > 0)
	{
		t_restante -= Time;
		if (t_restante <= 0)
		{
			t_restante = 0;
			activo = false; //EL HECHIZO YA NO ESTA ACTIVO, PERO SIGUE EN RECARGA
		}
	}
}

//HECHIZOS USADOS EN BATALLA
void Hechizo::usar_Hechizo(int tipoHechizo, Personaje& objetivo)
{
	if (t_restante > 0)
		return; //EN RECARGA

	if (usos_restantes <= 0)
		return; //MAXIMOS USADOS
	else
		usos_restantes--;

	t_restante = t_recarga; //INICIAR RECARGA
	activo = true;

	if (tipoHechizo == PARALISIS) objetivo.set_paralisis(5.0);
	else if (tipoHechizo == HIPERVELOCIDAD) objetivo.set_hiperVelocidad(5.0);
}

//HECHIZO USADO EN TABLERO
void Hechizo::usar_Pocion(Personaje& aliado)
{
	int nuevaVida;

	if (usoPocion) //SI USO POCION
		return;

	if (hechizos[2].usos_restantes <= 0)
		return; //MAXIMOS USADOS

	if (aliado.return_Vida() >= aliado.return_VidaMax())
		return; //NO NECESITA CURARSE
	else
	{
		hechizos[2].usos_restantes--;

		nuevaVida = aliado.return_Vida() + 30; //SUMAR A LA VIDA ACTUAL

		if (nuevaVida > aliado.return_VidaMax())
			nuevaVida = aliado.return_VidaMax();

		aliado.setVida(nuevaVida);

		hechizos[2].activo = true;
		usoPocion = true;

		juego.cambiarTurno(); //CAMBIAR TURNO AL USARSE POCION
	}
}
