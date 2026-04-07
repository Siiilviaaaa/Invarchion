#include <iostream>
#include <cmath>
#include "Batalla.h"
#include "Juego.h"

using std::cout, std::cin, std::endl;

//VARIABLES GLOBALES
Hechizo hechizos[3];
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

void Hechizo::configurar(TipoHechizo t)
{
	tipo = t;

	switch (tipo)
	{
	case PARALISIS:
		t_recarga = 5.0;
		usos_restantes = 2;
		mis_hechizos = ETSIDI::Sprite("Recursos/paralisis.png");
		break;
	case HIPERVELOCIDAD:
		t_recarga = 5.0;
		usos_restantes = 2;
		mis_hechizos = ETSIDI::Sprite("Recursos/hiperVelocidad.png");
		break;
	case POCION:
		t_recarga = 0.0; //LA POCION NO TIENE RECARGA, SOLO USOS LIMITADOS
		usos_restantes = 1;
		mis_hechizos = ETSIDI::Sprite("Recursos/pocion.png");
		break;
	}
}

void Hechizo::dibujarHechizo()
{
	if (activo) {
		mis_hechizos.setPos(posX, posY);
		mis_hechizos.draw();
	}
}

void Hechizo::actualizarTiempos(double Time)
{
	if (t_restante > 0)
	{
		t_restante -= Time;
		if (t_restante <= 0)
		{
			t_restante = 0;
			activo = false; //EL HECHIZO YA NO ESTA ACTIVO, PERO SIGUE EN RECARGA
		}
	}
}

//HECHIZOS USADOS EN BATALLA
void Hechizo::usar_Hechizo(int tipoHechizo, Personajes_carac& objetivo)
{
	if(t_restante>0)
		return; //EN RECARGA
	
	if (usos_restantes <= 0)
		return; //MAXIMOS USADOS
	else
	usos_restantes--;

	t_restante = t_recarga; //INICIAR RECARGA
	activo = true;
}

//HECHIZO USADO EN TABLERO
/*void Hechizo::usar_Pocion(Personajes_carac& aliado)
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
*/

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