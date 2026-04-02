#include <iostream>
#include "Batalla.h"
#include "Juego.h"

using std::cout, std::cin, std::endl;

//VARIABLES GLOBALES
Disparo nDisparos[10]; //10 DISPAROS ACTIVOS A LA VEZ
Hechizo hechizos[3]; //3 TIPOS DE HECHIZOS

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
	for (int i=0;i<10;i++)
		if(!nDisparos[i].activo) //SI EL DISPARO NO ESTA ACTIVO, SE DISPARA
		{
			nDisparos[i].x = posX;
			nDisparos[i].y = posY;
			nDisparos[i].velo_x = 0.2; //VELOCIDAD EN X
			nDisparos[i].velo_y = 1; //VELOCIDAD EN Y
			nDisparos[i].danio = 10; //DAÑO QUE CAUSA
			nDisparos[i].activo = true; //SE ACTIVA EL DISPARO
			nDisparos[i].flecha = png; //IMAGEN DE LA FLECHA
			break;
		}
}

//HECHIZOS USADOS EN BATALLA
void Hechizo::usar_Hechizo(int tipoHechizo, Personajes_carac& objetivo)
{
	//INICIALIZAR TIEMPOS DE RECARGA
	hechizos[0].t_recarga = 5.0;
	hechizos[1].t_recarga = 3.0;

	if(hechizos[tipoHechizo].t_restante>0)
		return; //EN RECARGA
	
	if (hechizos[tipoHechizo].usos_restantes <= 0)
		return; //MAXIMOS USADOS
	else
	hechizos[tipoHechizo].usos_restantes--;

	switch (tipoHechizo)
	{
	case 0: //PARALIZAR AL ENEMIGO
		objetivo.setVelocidad(objetivo.return_Velocidad() * 0.1); //REDUCE MUCHO LA VELOCIDAD
		objetivo.set_paralisis(5.0); //TIEMPO DE PARALISIS
		break;
	case 1: //VELOCIDAD
		objetivo.setVelocidad(objetivo.return_Velocidad() * 1.5); //REDUCE LA VELOCIDAD A LA MITAD
		objetivo.set_hiperVelocidad(4.0); //TIEMPO DE HIPER VELOCIDAD
		break;
	}
	hechizos[tipoHechizo].activo = true;
	hechizos[tipoHechizo].t_restante = hechizos[tipoHechizo].t_recarga; //INICIAR DE VUELTA TIEMPO DE RECARGA
}

//HECHIZO USADO EN TABLERO
void Hechizo::usar_Pocion(Personajes_carac & aliado)
{
	//INICIALIZAR TIEMPO DE RECARGA
	hechizos[2].t_recarga = 10.0;

	int nuevaVida;

	if(movioPieza || usoPocion) //SI SE MOVIO O USO POCION
		void cambiarTurno(); //CAMBIAR TURNO

	if (hechizos[2].usos_restantes <= 0)
		return; //MAXIMOS USADOS
	
	//COMPROBAR SI PIEZA NECESITA CURARSE
	if (aliado.return_Vida() < aliado.return_Vida()) //VIDA ACTUAL < VIDA MAX
	{
		hechizos[2].usos_restantes--;

		aliado.setVida(aliado.return_Vida() + 30); //SUMAR A LA VIDA ACTUAL
			aliado.setVida(aliado.return_Vida());

			hechizos[2].activo = true;
			usoPocion = true;
	}
	
}