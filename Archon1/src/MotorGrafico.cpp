#include "MotorGrafico.h"

MotorGrafico::MotorGrafico():
	Flecha("Recursos/flecha.png"),
	Paralisis("Recursos/hechizo1.png"),
	Velocidad("Recursos/hechizo2.png"),
	Pocion("Recursos/pocion.png")
{
	//CONFIGURAR POSICIONES Y TAMAÑOS INICIALES
}

void MotorGrafico::dibujarDisparo(const Disparo& disparo)
{
	if (disparo.return_Activo())
	{
		Flecha.setPos(disparo.return_X(), disparo.return_Y());
		Flecha.draw();
	}
}

void MotorGrafico::dibujarHechizo(const Hechizo& hechizo)
{
	if (hechizo.return_Activo())
	{
		if (hechizo.return_Tipo() == Hechizo::PARALISIS)
		{
			Paralisis.setPos(hechizo.return_X(), hechizo.return_Y());
			Paralisis.draw();
		}
		else if(hechizo.return_Tipo() == Hechizo::HIPERVELOCIDAD)
		{
			Velocidad.setPos(hechizo.return_X(), hechizo.return_Y());
			Velocidad.draw();
		}
		else if(hechizo.return_Tipo() == Hechizo::POCION)
		{
			Pocion.setPos(hechizo.return_X(), hechizo.return_Y());
			Pocion.draw();
		}
	}
}