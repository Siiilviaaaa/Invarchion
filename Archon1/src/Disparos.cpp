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
	rebotes = 0;
}

void Disparo::moverDisparo()
{
	if (!activo) return;
	x += velo_x;
	y += velo_y;
}

bool Disparo::Impacto(Personaje& objetivo, bool haceDano)
{
	if (!activo) return false;

	double dx = x - objetivo.return_X();
	double dy = y - objetivo.return_Y();

	if (sqrt(dx * dx + dy * dy) < 0.6) //SI EL DISPARO IMPACTA AL ENEMIGO
	{
		if (haceDano == true) //SOLO DAÑA SI LE PASAMOS TRUE
			objetivo.setVida(objetivo.return_Vida() - danio); //REDUCIR VIDA DEL ENEMIGO

		this->activo = false; //DESACTIVAR DISPARO AL CHOCAR
		return true;
	}
	return false;
}