#include <iostream>
#include <cmath>
#include "Batalla.h"

using std::cout, std::cin, std::endl;

Batalla::Batalla()
{
	for (int i = 0;i < MAX_DISPAROS;i++)
		nDisparos[i] = nullptr;
}

Batalla::~Batalla()
{
	//LIMPIAR MEMORIA DE LOS DISPAROS CUANDO EL PERSOANJE MUERE
	for (int i = 0; i < MAX_DISPAROS; i++)
	{
		if (nDisparos[i] != nullptr)
		{
			delete nDisparos[i];
			nDisparos[i] = nullptr;
		}
	}
}

void Batalla::KeyBatalla(unsigned char key, Personaje& j1, Personaje& j2)
{
	double x1 = j1.return_X(), y1 = j1.return_Y();
	double x2 = j2.return_X(), y2 = j2.return_Y();

	switch (key)
	{
	case ' ': //HUMANOS PELEAN O DISPARAN CON EL ESPACIO
		if (j1.return_Tipo() == ARQUERO) lanzarDisparo(j1);
		else
			pegar(j1, j2, x1, y1, x2, y2);
		break;
	case 13: //ALIENS PELEAN O DISPARAN CON ENTER
		if (j2.return_Tipo() == ARQUERO) lanzarDisparo(j2);
		else
			pegar(j2, j1, x1, y1, x2, y2);
		break;
	case 'h': //HUMANOS USAN HECHIZO
		juego.getTurno() == 0 ? hechizos[0].usar_Hechizo(0, j2) : hechizos[0].usar_Hechizo(0, j1);
		break;
	case 'v': //HUMANOS USAN HECHIZO
		juego.getTurno() == 0 ? hechizos[1].usar_Hechizo(1, j2) : hechizos[1].usar_Hechizo(1, j1);
		break;
	default:
		break;
	}

	if (key == 'w') { j1.setY(j1.return_Y() + j1.return_Vbase()); j1.direccion(0, 1); }
	if (key == 's') { j1.setY(j1.return_Y() - j1.return_Vbase()); j1.direccion(0, -1); }
	if (key == 'a') { j1.setX(j1.return_X() - j1.return_Vbase()); j1.direccion(-1, 0); }
	if (key == 'd') { j1.setX(j1.return_X() + j1.return_Vbase()); j1.direccion(1, 0); }
}

void Batalla::actualizarCombate(Personaje& j1, Personaje& j2,Caja &caja, Obstaculo& obs)
{
	for (int i = 0;i < 3;i++)
		hechizos[i].actualizarTiempos(0.1); //ACTUALIZAR TIEMPOS DE RECARGA DE HECHIZOS

	j1.actualizarEfectos();
	j2.actualizarEfectos();

	for (int i = 0;i < MAX_DISPAROS;i++)
	{
		if (nDisparos[i] != nullptr) {
			nDisparos[i]->moverDisparo();
			
			//COLISION CONTRA LA CAJA
			limites_d(*nDisparos[i], caja);
			choqueObstaculo(*nDisparos[i], obs);
			
			//ELIMINAR SI IMPACTA
			if (nDisparos[i]->Impacto(j1, j2) || nDisparos[i]->Impacto(j2, j1) || !nDisparos[i]->return_Activo()) {
				delete nDisparos[i];
					nDisparos[i] = nullptr;
			}
		}
	}

	limites_p(j1, caja);
	limites_p(j2, caja);

	choqueObstaculo(j1, obs);
	choqueObstaculo(j2, obs);

	int resultado = FinCombate(j1, j2);
	if (resultado != 0) return;
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
	//atacante.sumarPuntos(10); //10 PUNTOS POR GOLPEAR
}

void Batalla::lanzarDisparo(Personaje& aliado)
{
	std::cout << "Disparando..." << std::endl;

	if (aliado.return_Tipo() != ARQUERO) {
		std::cout << "No es arquero, no puede disparar" << std::endl;
		return;
	}

	bool hueco = false; //PARA VER SI HAY CAPACIDAD EN EL ARRAY
	for (int i = 0;i < MAX_DISPAROS;i++)
	{
		if (nDisparos[i] == nullptr)
		{
			nDisparos[i] = new Disparo(); //RESERVA MEMORIA

			double margen = 1.2; //EVITAMOS EL SUICIDIO
			nDisparos[i]->setX(aliado.return_X() + aliado.return_dirX() * margen);
			nDisparos[i]->setY(aliado.return_Y() + aliado.return_dirY() * margen);

			double vx = aliado.return_dirX() * 0.15;
			double vy = aliado.return_dirY() * 0.15;

			nDisparos[i]->setVX(vx);
			nDisparos[i]->setVY(vy);
			nDisparos[i]->setActivo(true);

			hueco = true;
			break;
		}
	}
	if (!hueco) {
		std::cout << "Maximo de disparos alcanzado" << std::endl;
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
	double radio = 1.0;

	//COMPROBAR CADA PARED
	//SI NOMOVER ES TRUE, LIMITE
	j.setX(NoMover(j, c.return_izq()) ? radio : j.return_X());
	j.setX(NoMover(j, c.return_dcha()) ? 20.0 - radio : j.return_X());
	j.setY(NoMover(j, c.return_suelo()) ? radio : j.return_Y());
	j.setY(NoMover(j, c.return_techo()) ? 15.0 - radio : j.return_Y());
}