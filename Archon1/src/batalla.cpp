#include <iostream>
#include <cmath>
#include "Batalla.h"
#include "Juego.h"

using std::cout, std::cin, std::endl;

//VARIABLES GLOBALES
const int Max_disparos = 10; //10 DISPAROS ACTIVOS A LA VEZ

Disparo nDisparos[Max_disparos]; 
Hechizo hechizos[3];  //3 HECHIZOS DISPONIBLES
bool usoPocion = false;

void Disparo::dibujarDisparo()
{
	if (!activo) return;

	sprite.setPos(x, y);
	sprite.draw();
}

void Disparo::crearDisparo(double posX, double posY)
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
			break;
		}
}

void Disparo::actualizarDisparos(Personajes_carac& j1, Personajes_carac& j2)
{
	for (int i = 0;i < Max_disparos;i++)
	{
		if (nDisparos[i].activo)
		{
			nDisparos[i].x += nDisparos[i].velo_x; //ACTUALIZAR POSICION EN X
			nDisparos[i].y += nDisparos[i].velo_y; //ACTUALIZAR POSICION EN Y
			if (nDisparos[i].y > 10) //SI EL DISPARO SALE DE PANTALLA, SE DESACTIVA
			{
				nDisparos[i].activo = false;
				continue;
			}

			//COMPROBAR IMPACTO
			//JUGADOR 1
			double dx1 = nDisparos[i].x - j1.return_X();
			double dy1 = nDisparos[i].y - j1.return_Y();

			if (sqrt(dx1 * dx1 + dy1 * dy1) < 1.0) //SE CONSIDERA UN IMPACTO
			{
				j1.setVida(j1.return_Vida() - nDisparos[i].danio);
				nDisparos[i].activo = false; //SE DESACTIVA EL DISPARO AL IMPACTAR
				continue;
			}

			//JUGADOR 2
			double dx2 = nDisparos[i].x - j2.return_X();
			double dy2 = nDisparos[i].y - j2.return_Y();

			if (sqrt(dx2 * dx2 + dy2 * dy2) < 1.0)
			{
				j2.setVida(j2.return_Vida() - nDisparos[i].danio);
				nDisparos[i].activo = false;
			}
		}
	}
}

void Hechizo::conf_Hechizos()
{
	hechizos[0].t_recarga = 5.0; //TIEMPO DE RECARGA PARALISIS
	hechizos[1].t_recarga = 5.0; //TIEMPO DE RECARGA HIPERVELOCIDAD
	
	hechizos[2].usos_max = 1;
	hechizos[2].usos_restantes = 1;
}

void Hechizo::dibujarHechizo()
{
	if (!activo) return;

	sprite.setPos(posX, posY);
	sprite.draw();
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
		if (j1.return_Tipo() == ARQUERO)
		{
			Disparo d;
			d.crearDisparo(x1, y1);
		}
		else
			pegar(j1, j2, x1, y1, x2, y2);
		break;
	case 13: //ALIENS PELEAN O DISPARAN CON ENTER
		if (j2.return_Tipo() == ARQUERO)
		{
			Disparo d;
			d.crearDisparo(x2, y2);
		}
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
	Disparo d;
	Hechizo h;

	d.actualizarDisparos(j1, j2);

	for (int i = 0;i < Max_disparos;i++)
		nDisparos[i].dibujarDisparo();

	h.actualizarTiempos(0.1);

}