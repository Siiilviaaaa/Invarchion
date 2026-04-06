#pragma once

#include "Batalla.h"

//ASEGURARNOS QUE TODOS LOS ELEMENTOS SE INICIALICEN BIEN
Disparo::Disparo() :flecha("Recursos/flecha.png")
{
	x = 0;
	y = 0;
	velo_x = 0;
	velo_y = 0;
	danio = 0;
	activo = false;
}

Hechizo::Hechizo():
	hechizo1("Recursos/hechizo1.png"),
	hechizo2("Recursos/hechizo2.png"),
	pocion("Recursos/pocion.png")
{
	usos_max = 2;
	usos_restantes = 2;
	activo = false;
	t_recarga = 0;
	t_restante = 0;
	posX = 0;
	posY = 0;
}
