#include <iostream>
#include "Batalla.h"
#include "Juego.h"

using std::cout, std::cin, std::endl;
bool fin_turno = false;
bool movioPieza = false;
bool usoPocion = false;
//VARIABLES GLOBALES
const int Max_disparos = 10; //10 DISPAROS ACTIVOS A LA VEZ

Disparo nDisparos[Max_disparos]; 
Hechizo hechizos[3];  //3 HECHIZOS DISPONIBLES
bool usoPocion = false;

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
	for (int i = 0;i < Max_disparos;i++)
		if (!nDisparos[i].activo) //SI EL DISPARO NO ESTA ACTIVO, SE DISPARA
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

void Hechizo::conf_Hechizos()
{
	hechizos[0].t_recarga = 5.0; //TIEMPO DE RECARGA PARALISIS
	hechizos[1].t_recarga = 5.0; //TIEMPO DE RECARGA HIPERVELOCIDAD
	
	hechizos[2].usos_max = 1;
	hechizos[2].usos_restantes = 1;
}

//HECHIZOS USADOS EN BATALLA
void Hechizo::usar_Hechizo(int tipoHechizo, Personajes_carac& objetivo)
{
	conf_Hechizos();

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
		//objetivo.set_paralisis(5.0); //TIEMPO DE PARALISIS
		break;
	case 1: //VELOCIDAD
		objetivo.setVelocidad(objetivo.return_Velocidad() * 1.5); //REDUCE LA VELOCIDAD A LA MITAD
		//objetivo.set_hiperVelocidad(4.0); //TIEMPO DE HIPER VELOCIDAD
		break;
	}
	hechizos[tipoHechizo].activo = true;
	hechizos[tipoHechizo].t_restante = hechizos[tipoHechizo].t_recarga; //INICIAR DE VUELTA TIEMPO DE RECARGA
	juego.actualizar(); //ACTIALIZAR LOS TIEMPOS

}

//HECHIZO USADO EN TABLERO
void Hechizo::usar_Pocion(Personajes_carac & aliado)
{
	conf_Hechizos();

	int nuevaVida;

	if (usoPocion) //SI USO POCION
		return;

	if (hechizos[2].usos_restantes <= 0)
		return; //MAXIMOS USADOS

	if (aliado.return_Vida() >= aliado.return_VidaMax())
		return; //NO NECESITA CURARSE
	else
	{
		hechizos[2].usos_restantes--;

		nuevaVida=aliado.return_Vida() + 30; //SUMAR A LA VIDA ACTUAL
		
		if (nuevaVida > aliado.return_VidaMax())
			nuevaVida = aliado.return_VidaMax();

		aliado.setVida(nuevaVida);

		hechizos[2].activo = true;
		usoPocion = true;

		juego.cambiarTurno(); //CAMBIAR TURNO AL USARSE POCION
	}
}