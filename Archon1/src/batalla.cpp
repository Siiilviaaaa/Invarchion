#include <iostream>
#include "Personajes.h"

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