#include <iostream>
#include <cmath>
#include "Batalla.h"
#include "Constructores Batalla.h"
#include "Juego.h"

using std::cout, std::cin, std::endl;

//VARIABLES GLOBALES
Hechizo hechizos[3];  //3 HECHIZOS DISPONIBLES
bool usoPocion = false;

void Disparo::dibujarDisparo()
{
	if (!activo) return;

	flecha.setPos(x, y);
	flecha.draw();
}

void Disparo::moverDisparo()
{
	if (!activo) return;
	x += velo_x;
	y += velo_y;
	//SI EL DISPARO SALE DE PANTALLA, SE DESACTIVA
	if (x < 0 || x > 800 || y < 0 || y > 600) activo = false;
}

bool Disparo::Impacto(Personajes_carac& objetivo)
{
	if (!activo) return false;

	double dx = x - objetivo.return_X();
	double dy = y - objetivo.return_Y();

	if (sqrt(dx * dx + dy * dy) < 1.0) //SI EL DISPARO IMPACTA AL ENEMIGO
	{
		objetivo.setVida(objetivo.return_Vida() - danio); //REDUCIR VIDA DEL ENEMIGO
		activo = false; //DESACTIVAR DISPARO AL CHOCAR
		return true;
	}
	
	return false;
}

void Hechizo::dibujarHechizo()
{
	if (!activo) return;

	hechizo1.setPos(posX, posY);
	hechizo1.draw();
		
	hechizo2.setPos(posX, posY);
	hechizo2.draw();
		
	pocion.setPos(posX, posY);
	pocion.draw();
	
}

void Hechizo::actualizarTiempos(double Time)
{
	for (int i = 0;i < 2;i++) //SOLO LOS HECHIZOS DE BATALLA NECESITAN RECARGA
	{
		if (hechizos[i].return_RESTANTE()>0) //SI NECESITA RECARGA
		{
			double nuevoTiempo = hechizos[i].return_RESTANTE() - Time; //DISMINUIR EL TIEMPO RESTANTE
			hechizos[i].setRESTANTE(nuevoTiempo);

			if (hechizos[i].return_RESTANTE() <= 0) //SI EL TIEMPO SE ACABO, SE DESACTIVA EL HECHIZO
			{
				hechizos[i].setRESTANTE(0);
				hechizos[i].setActivo(false);
			}
		}
	}
}

//HECHIZOS USADOS EN BATALLA
void Hechizo::usar_Hechizo(int tipoHechizo, Personajes_carac& objetivo)
{
	if(hechizos[tipoHechizo].t_restante>0)
		return; //EN RECARGA
	
	if (hechizos[tipoHechizo].usos_restantes <= 0)
		return; //MAXIMOS USADOS
	else
	hechizos[tipoHechizo].usos_restantes--;

	switch (tipoHechizo)
	{
	case 0: //PARALIZAR AL ENEMIGO
		objetivo.set_paralisis(5.0); //TIEMPO DE PARALISIS
		break;
	case 1: //VELOCIDAD
		objetivo.set_hiperVelocidad(4.0); //TIEMPO DE HIPER VELOCIDAD
		break;
	}
	hechizos[tipoHechizo].activo = true;
	hechizos[tipoHechizo].t_restante = hechizos[tipoHechizo].t_recarga; //INICIAR DE VUELTA TIEMPO DE RECARGA
	juego.actualizar(); //ACTIALIZAR LOS TIEMPOS

}

//HECHIZO USADO EN TABLERO
void Hechizo::usar_Pocion(Personajes_carac & aliado)
{
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
	//ACTUALIZAR HECHIZOS
	for (int i = 0;i < 3;i++)
		hechizos[i].actualizarTiempos(0.1);

	j1.actualizarEfectos();
	j2.actualizarEfectos();
}