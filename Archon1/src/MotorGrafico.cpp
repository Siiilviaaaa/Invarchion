#include "MotorGrafico.h"

MotorGrafico::MotorGrafico():
	Flecha("Recursos/flecha.png"),
	Paralisis("Recursos/hechizo1.png"),
	Velocidad("Recursos/hechizo2.png"),
	Pocion("Recursos/pocion.png")
{
	//CONFIGURAR POSICIONES Y TAMAÑOS
}

void MotorGrafico::dibujarDisparo(const Disparo& disparo)
{
	if (disparo.return_Activo())
	{
		Flecha.setPos(disparo.return_X(), disparo.return_Y());
		Flecha.draw();
	}
}