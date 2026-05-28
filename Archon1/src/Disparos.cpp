#include <cmath>
#include "Disparos.h"
#include "Personajes.h"

extern int puntuacion_humanos;
extern int puntuacion_aliens;

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
	if (this->bando == objetivo.return_Bando()) return false;
	double dx = x - objetivo.return_X();
	double dy = y - objetivo.return_Y();

	if (sqrt(dx * dx + dy * dy) < 0.6)
	{
		if (haceDano == true && objetivo.return_Vida() > 0)
		{
			
			int vidaAntes = objetivo.return_Vida();
			objetivo.setVida(vidaAntes - danio);
			std::cout << "Impacto detectado. Vida actual: " << objetivo.return_Vida() << std::endl;
			//////PUNTOS//////
			int puntosGanados = 15;
			if (objetivo.return_Vida() <= 0) puntosGanados += 50; //BONUS POR KILL

			if (this->bando == HUMANO) puntuacion_humanos += puntosGanados;
			else puntuacion_aliens += puntosGanados;
		}

		//DESAPARECER
		this->activo = false;
		return true;
	}
	return false;
}