#include "Batalla.h"

Disparo::Disparo() : flecha("Recursos/flecha.png")
{
	x = 0.0;
	y = 0.0;
	velo_x = 0.0;
	velo_y = 0.0;
	danio = 15;
	activo = false;
}

Hechizo::Hechizo() : mis_hechizos("Recursos/hechizo1.png")
{
	tipo = PARALISIS;
	usos_restantes = 0;
	activo = false;
	posX = 0.0;
	posY = 0.0;
	t_recarga = 0.0;
	t_restante = 0.0;
}