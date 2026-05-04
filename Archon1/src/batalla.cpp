#include <iostream>
#include <cmath>
#include "Batalla.h"

using std::cout, std::cin, std::endl;

void Batalla::actualizarCombate(Personaje& j1, Personaje& j2,Caja &caja, Obstaculo& obs)
{
	for (int i = 0;i < 3;i++)
		hechizos[i].actualizarTiempos(0.1); //ACTUALIZAR TIEMPOS DE RECARGA DE HECHIZOS

	//ESTO AHORA YA NO DEPENDE DE LA CLASE PADRE DEL PERSONAJE, AHORA L OGESTIONA O EL HIJO O LA CLASE DISPARO
	//j1.actualizarEfectos();
	//j2.actualizarEfectos();

	//j1.gestionarDisparos(j2);
	//j2.gestionarDisparos(j1);

	//for (int i = 0;i < 10;i++)
	//{
	//	//DISPAROS DEL J1
	//	if (j1.return_Disparos()[i] != nullptr)
	//	{
	//		limites_d(*j1.return_Disparos()[i], caja);
	//		choqueObstaculo(*j1.return_Disparos()[i], obs);
	//	}

	//	//DISPAROS DEL J2
	//	if (j1.return_Disparos()[i] != nullptr)
	//	{
	//		limites_d(*j2.return_Disparos()[i], caja);
	//		choqueObstaculo(*j2.return_Disparos()[i], obs);
	//	}
	//}

	limites_p(j1, caja);
	limites_p(j2, caja);

	choqueObstaculo(j1, obs);
	choqueObstaculo(j2, obs);

	FinCombate(j1, j2);
}

int Batalla::FinCombate(Personaje& humanos, Personaje& aliens)
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

void Batalla::pegar(Personaje& atacante, Personaje& objetivo,
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
	atacante.sumarPuntos(10); //10 PUNTOS POR GOLPEAR
}

void Batalla::KeyBatalla(unsigned char key, Personaje& j1, Personaje& j2,
				 double x1, double y1, double x2, double y2)
{
	switch (key)
	{
	case ' ': //HUMANOS PELEAN O DISPARAN CON EL ESPACIO
		if (j1.return_Tipo() == ARQUERO) j1.ataque();
		else
			pegar(j1, j2, x1, y1, x2, y2);
		break;
	case 13: //ALIENS PELEAN O DISPARAN CON ENTER
		if (j2.return_Tipo() == ARQUERO) j2.ataque();
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

bool Batalla::NoMover(Personaje& j, const Pared& p)
{
	if (p.distancia(j.return_X(), j.return_Y()) < 1.0)
		return true; //CHOCA
	return false;
}

bool Batalla::reboteDisparos(Disparo& d, const Pared& p)
{
	double dx, dy;
	if (p.distancia(d.return_X(), d.return_Y()) < 0.5)
	{
		d.setVX(d.return_VX());
		d.setVY(d.return_VY());
		return true;
	}
	return false;
}

bool Batalla::choqueObstaculo(Personaje& j, const Obstaculo& o)
{
	double dx = j.return_X() - o.return_X();
	double dy = j.return_Y() - o.return_Y();
	double dist = sqrt(dx * dx + dy * dy);

	if (dist < (o.return_Radio() + 0.8)) {
		//EMPUJAR HACIA FUERA
		double angulo = atan2(dy, dx);
		j.setX(o.return_X() + (o.return_Radio() + 0.81) * cos(angulo));
		j.setY(o.return_Y() + (o.return_Radio() + 0.81) * sin(angulo));
	}
	return false;
}

bool Batalla::choqueObstaculo(Disparo& d, const Obstaculo& o)
{
	if (d.return_Activo()) {
		double dx = d.return_X() - o.return_X();
		double dy = d.return_Y() - o.return_Y();
		double dist = sqrt(dx * dx + dy * dy);

		if (dist < o.return_Radio())
		{
			//INVERTIR SEGÚN DONDE GOLPEE
			if (std::abs(dx) > std::abs(dy))	//SI GOLPEA MAS POR LOS LADOS QUE POR ARRIBA
				d.setVX(-d.return_VX());		//REBOTE HORIZONTAL
			else
				d.setVY(-d.return_VY());		//REBOTE VERTICAL

			//NUEVA VELOCIDAD
			d.setX(d.return_X() + d.return_VX());
				d.setY(d.return_Y() + d.return_VY());

			return true;
		}
	}
	else return false;
}

void Batalla::limites_d(Disparo& d, Caja& c)
{
	reboteDisparos(d, c.return_suelo());
	reboteDisparos(d, c.return_techo());
	reboteDisparos(d, c.return_izq());
	reboteDisparos(d, c.return_dcha());
}

void Batalla::limites_p(Personaje& j, Caja& c)
{
	NoMover(j, c.return_suelo());
	NoMover(j, c.return_techo());
	NoMover(j, c.return_izq());
	NoMover(j, c.return_dcha());
}