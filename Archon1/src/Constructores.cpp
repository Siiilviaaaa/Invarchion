#include "Batalla.h"

//ASEGURARNOS QUE TODOS LOS ELEMENTOS SE INICIALICEN BIEN
Disparo::Disparo() : activo(false), danio(15)
{
	flecha = ETSIDI::Sprite("Recursos/flecha.png");
}

Hechizo::Hechizo() : activo(false), t_restante(0) {}