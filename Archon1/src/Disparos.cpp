#include <cmath>
#include "Disparos.h"
#include "Personajes.h"

Disparo::Disparo()
{
	x = 0.0;
	y = 0.0;
	velo_x = 0.0;
	velo_y = 0.0;
	danio = 15;
	activo = false;
}

void Disparo::moverDisparo()
{
	if (!activo) return;
	x += velo_x;
	y += velo_y;
	//SI EL DISPARO SALE DE PANTALLA, SE DESACTIVA
	if (x < 0 || x > 800 || y < 0 || y > 600) activo = false;
}

bool Disparo::Impacto(Personaje& objetivo)
{
	if (!activo) return false;

	double dx = x - objetivo.return_X();
	double dy = y - objetivo.return_Y();

	if (sqrt(dx * dx + dy * dy) < 1.0) //SI EL DISPARO IMPACTA AL ENEMIGO
	{
		objetivo.setVida(objetivo.return_Vida() - danio); //REDUCIR VIDA DEL ENEMIGO
		activo = false; //DESACTIVAR DISPARO AL CHOCAR
		return true;
	}
	return false;
}
