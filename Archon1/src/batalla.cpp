#include <iostream>
#include "Batalla.h"

using std::cout, std::cin, std::endl;

void start_combat(Personajes_carac& humanos, Personajes_carac& aliens)
{
	while (humanos.return_Vida() > 0 && aliens.return_Vida() > 0) //EL COMBATE CONTINUA HASTA QUE UNO DE LOS DOS SE QUEDE SIN VIDA
	{
		//HUMANOS ATACAN
		aliens.setVida(aliens.return_Vida() - humanos.return_Danio());

		if (aliens.return_Vida() <= 0)
		{
			cout << "¡Humanos ganan!" << endl;
			break;
		}
		//ALIENS ATACAN
		humanos.setVida(humanos.return_Vida() - aliens.return_Danio());

		if (humanos.return_Vida() <= 0)
		{
			cout << "¡Aliens ganan!" << endl;
			break;
		}
	}
}

void Disparo::dispararObjeto(double posX, double posY, GLuint png)
{
	Disparo nuevo[10]; //10 DISPAROS ACTIVOS A LA VEZ

	for (int i=0;i<10;i++)
		if(!nuevo[i].activo) //SI EL DISPARO NO ESTA ACTIVO, SE DISPARA
		{
			nuevo[i].x = posX;
			nuevo[i].y = posY;
			nuevo[i].velo_x = 0.2; //VELOCIDAD EN X
			nuevo[i].velo_y = 1; //VELOCIDAD EN Y
			nuevo[i].danio = 10; //DAÑO QUE CAUSA
			nuevo[i].activo = true; //SE ACTIVA EL DISPARO
			nuevo[i].flecha = png; //IMAGEN DE LA FLECHA
			break;
		}
}