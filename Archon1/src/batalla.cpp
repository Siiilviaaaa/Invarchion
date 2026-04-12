#include <iostream>
#include <cmath>
#include "Batalla.h"
#include "Disparos.h"
#include "Hechizos.h"

using std::cout, std::cin, std::endl;

void pegar(Personajes_carac& atacante, Personajes_carac& objetivo,
	double x1, double y1, double x2, double y2)
{
	if (atacante.return_Tipo() == ARQUERO) //EL ARQUERO NO PEGA, SOLO DISPARA
		return;

	double dx = x1 - x2;
	double dy = y1 - y2;

	if (sqrt(dx * dx + dy * dy) > 1.5) //NO SE CONSIDERA GOLPE
		return;

	int nuevaVida = objetivo.return_Vida() - atacante.return_Danio();

	if (nuevaVida < 0)
		nuevaVida = 0;

	objetivo.setVida(nuevaVida);
}

void KeyBatalla(unsigned char key, Personajes_carac& j1, Personajes_carac& j2,
				 double x1, double y1, double x2, double y2)
{
	switch (key)
	{
	case ' ': //HUMANOS PELEAN O DISPARAN CON EL ESPACIO
		if (j1.return_Tipo() == ARQUERO) j1.lanzarDisparo();
		else
			pegar(j1, j2, x1, y1, x2, y2);
		break;
	case 13: //ALIENS PELEAN O DISPARAN CON ENTER
		if (j2.return_Tipo() == ARQUERO) j2.lanzarDisparo();
		else
			pegar(j2, j1, x1, y1, x2, y2);
		break;
	case 'h': //HUMANOS USAN HECHIZO
		juego.getTurno() == 0 ? hechizos[0].usar_Hechizo(0,j2) : hechizos[0].usar_Hechizo(0,j1);
		break;
	case 'v': //HUMANOS USAN HECHIZO
		juego.getTurno() == 0 ? hechizos[1].usar_Hechizo(1,j2) : hechizos[1].usar_Hechizo(1,j1);
		break;
	default:
		break;
	}
}

void actualizarCombate(Personajes_carac& j1, Personajes_carac& j2)
{
	for (int i=0;i<3;i++)
		hechizos[i].actualizarTiempos(0.1); //ACTUALIZAR TIEMPOS DE RECARGA DE HECHIZOS

	j1.gestionarDisparos(j2);
	j2.gestionarDisparos(j1);

	j1.actualizarEfectos();
	j2.actualizarEfectos();
}

int FinalBatalla(Personajes_carac& humanos, Personajes_carac& aliens)
{
	//RETORNA 0 SI SIGUEN PELEANDO
	//RETORNA 1 SI HUMANOS GANAN
	//RETORNA 2 SI ALIENS GANAN

	if (aliens.return_Vida() <= 0)
	{
		cout << "HUMANS WIN!" << endl;
		return 1;
	}
	else if (humanos.return_Vida() <= 0)
	{
		cout << "ALIENS WIN!" << endl;
		return 2;
	}

	return 0;
}