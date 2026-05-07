#include <iostream>
#include <cmath>
#include "Batalla.h"

using std::cout, std::cin, std::endl;
extern bool fin_;

Batalla::Batalla()
{
	for (int i = 0;i < MAX_DISPAROS;i++)
		nDisparos[i] = nullptr;
}

Batalla::~Batalla()
{
	std::cout << "Limpiando escenario..." << std::endl;

	for (int i = 0; i < MAX_DISPAROS; i++)
	{
		if (nDisparos[i] != nullptr)
		{
			delete nDisparos[i];      // Liberamos la memoria
			nDisparos[i] = nullptr;   // Marcamos como vac�o
		}
	}
}

void Batalla::KeyBatalla(unsigned char key, Personaje& j1, Personaje& j2)
{
	switch (key)
	{
	case ' ': //HUMANOS PELEAN O DISPARAN CON EL ESPACIO
		std::cout << "J1 lleva: " << j1.return_Disparos() << std::endl;
		if (j1.return_Tipo() == ARQUERO) lanzarDisparo(j1);
		else
			pegar(j1, j2);
		break;
	case 13: //ALIENS PELEAN O DISPARAN CON ENTER
		std::cout << "J2 lleva: " << j2.return_Disparos() << std::endl;
		if (j2.return_Tipo() == ARQUERO) lanzarDisparo(j2);
		else
			pegar(j2, j1);
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
	
	if (key == 'i') { j2.setY(j2.return_Y() + j2.return_Vbase()); j2.direccion(0, 1); }
	if (key == 'k') { j2.setY(j2.return_Y() - j2.return_Vbase()); j2.direccion(0, -1); }
	if (key == 'j') { j2.setX(j2.return_X() - j2.return_Vbase()); j2.direccion(-1, 0); }
	if (key == 'l') { j2.setX(j2.return_X() + j2.return_Vbase()); j2.direccion(1, 0); }
}

void Batalla::actualizarCombate(Personaje& j1, Personaje& j2, Caja& caja, Obstaculo* lista[5])
{
	////////////////PERSONAJES//////////////////
	limites_p(j1, caja);
	limites_p(j2, caja);

	entrePersonajes(j1, j2);

	for (int k = 0; k < 5; k++) {
		if (lista[k] != nullptr) {
			choqueObstaculo(j1, *lista[k]);
			choqueObstaculo(j2, *lista[k]);
		}
	}

	//////////////// DISPAROS //////////////////
	//CHOQUE ENTRE DISPAROS:
	for (int i = 0; i < MAX_DISPAROS; i++) {
		if (nDisparos[i] == nullptr || !nDisparos[i]->return_Activo()) continue;
		for (int j = i + 1; j < MAX_DISPAROS; j++)
			if (nDisparos[j] != nullptr && nDisparos[j]->return_Activo())
				entreDisparos(*nDisparos[i], *nDisparos[j]);
	}
	//CHOQUE CON PAREDES, OBSTACULOS Y PERSONAJES:
	for (int i = 0; i < MAX_DISPAROS; i++)
	{
		if (nDisparos[i] == nullptr) continue;

		if (nDisparos[i]->return_Activo())
		{
			nDisparos[i]->moverDisparo();
			limites_d(*nDisparos[i], caja);

			for (int k = 0; k < 5; k++) {
				if (lista[k] != nullptr)
					choqueObstaculo(*nDisparos[i], *lista[k]);
			}
			
			if (nDisparos[i]->return_Bando() == HUMANO) {
				//SI ES HUMANO, SOLO DAÑAR ALIEN
				nDisparos[i]->Impacto(j2, true);
				nDisparos[i]->Impacto(j1, false);
			}
			else {
				//SI ES ALIEN, SOLO DAÑAR HUMANO
				nDisparos[i]->Impacto(j1, true);
				nDisparos[i]->Impacto(j2, false);
			}
		}

		if (!nDisparos[i]->return_Activo())
		{
			delete nDisparos[i];
			nDisparos[i] = nullptr;
		}
	}
		
	////////////////HECHIZOS//////////////////
	for (int i = 0;i < 3;i++)
		hechizos[i].actualizarTiempos(0.1); //ACTUALIZAR TIEMPOS DE RECARGA DE HECHIZOS

	j1.actualizarEfectos();
	j2.actualizarEfectos();

	////////////////FINAL//////////////////
	int resultado = FinCombate(j1, j2);
	if (resultado != 0) {
		j1.resetMunicion();
		j2.resetMunicion();

		this->~Batalla();
		fin_ = true;
	}
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

void Batalla::pegar(Personaje& atacante, Personaje& objetivo)
{
	double dx = atacante.return_X() - objetivo.return_X();
	double dy = atacante.return_Y() - objetivo.return_Y();

	if (atacante.return_Tipo() == ARQUERO) //EL ARQUERO NO PEGA, SOLO DISPARA
		return;

	if (sqrt(dx * dx + dy * dy) > 1.5) //NO SE CONSIDERA GOLPE
		return;

	int danio = atacante.return_Danio();
	int nuevaVida = objetivo.return_Vida() - danio;
	int vidaAntes = objetivo.return_Vida();

	if (nuevaVida < 0)
		nuevaVida = 0;

	std::cout << "Vida antes=" << vidaAntes << " | Nueva=" << nuevaVida << std::endl;

	objetivo.setVida(nuevaVida);

	std::cout << "[COMBATE] " << (atacante.return_Bando() == 0 ? "HUMANO" : "ALIEN")
		<< " asesta un golpe de " << danio << " de danio." << std::endl;
}

void Batalla::lanzarDisparo(Personaje& aliado)
{
	if (aliado.return_Disparos() >= 10) {
		std::cout << "Sin municion para esta ronda" << std::endl;
		return;
	}
	std::cout << "Disparando..." << std::endl;

	bool hueco = false; //PARA VER SI HAY CAPACIDAD EN EL ARRAY
	for (int i = 0;i < MAX_DISPAROS;i++)
	{
		if (nDisparos[i] == nullptr)
		{
			nDisparos[i] = new Disparo(); //RESERVA MEMORIA
			aliado.sumarDisparo();
			nDisparos[i]->setBando(aliado.return_Bando());

			double margen = 1.2; //EVITAMOS EL SUICIDIO
			nDisparos[i]->setX(aliado.return_X() + aliado.return_dirX() * margen);
			nDisparos[i]->setY(aliado.return_Y() + aliado.return_dirY() * margen);

			double vx = aliado.return_dirX() * 0.1;
			double vy = aliado.return_dirY() * 0.1;

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

void Batalla::entrePersonajes(Personaje& j1, Personaje& j2)
{
	double dx = j1.return_X() - j2.return_X();
	double dy = j1.return_Y() - j2.return_Y();
	double dist = sqrt(dx * dx + dy * dy);
	double radioChoque = 0.7;

	
	if (dist < radioChoque)
	{
		double juntos = radioChoque - dist;
		double normalx = dx / dist;
		double normaly = dy / dist;

		j1.setX(j1.return_X() + normalx * 0.3);
		j1.setY(j1.return_Y() + normaly * 0.3);

		j2.setX(j2.return_X() - normalx * 0.3);
		j2.setY(j2.return_Y() - normaly * 0.3);
	}
}

bool Batalla::entreDisparos(Disparo& d1, Disparo& d2)
{
	//SI SON DEL MISMO BANDO
	if (d1.return_Bando() == d2.return_Bando()) return false;

	double dx = d1.return_X() - d2.return_X();
	double dy = d1.return_Y() - d2.return_Y();
	double dist = sqrt(dx * dx + dy * dy);

	if (dist < 0.3)
	{
		d1.setActivo(false);
		d2.setActivo(false);
		std::cout << "[SISTEMA] Choque entre aliado y enemigo" << std::endl;
		return true;
	}
	return false;
}

bool Batalla::NoMover(Personaje& j, const Pared& p)
{
	if (p.distancia(j.return_X(), j.return_Y()) < 1.0)
		return true; //CHOCA
	return false;
}

bool Batalla::reboteDisparos(Disparo& d, const Pared& p)
{
	if (p.distancia(d.return_X(), d.return_Y()) < 0.5)
	{
		//SI y1 == y2 -> SUELO O TECHO
		if (std::abs(p.return_Y1() - p.return_Y2()) < 0.1)
			d.setVY(-d.return_VY()); //REBOTE VERTICAL
		//SI x1 == x2 -> DCH O IZQ
		else if (std::abs(p.return_X1() - p.return_X2()) < 0.1)
			d.setVX(-d.return_VX()); //REBOTE HORIZONTAL

		//MAX 2 REBOTES
		d.setRebotes(d.return_Rebotes() + 1);
		std::cout << "Rebote (caja). TOTAL: " << d.return_Rebotes() << "/2" << std::endl;

		if (d.return_Rebotes() > 2) {
			d.setActivo(false);
			std::cout << "[SISTEMA] Disparo agotado (caja)" << std::endl;

		}

		//PA QUE NO SE QUEDE UNIDO A LA PARED
		d.setX(d.return_X() + d.return_VX() * 2);
		d.setY(d.return_Y() + d.return_VY() * 2);

		return true;
	}
	return false;
}

bool Batalla::choqueObstaculo(Personaje& j, const Obstaculo& o)
{
	double dx = j.return_X() - o.return_X();
	double dy = j.return_Y() - o.return_Y();
	double dist = sqrt(dx * dx + dy * dy);

	//AJUSTAR PA QUE EL OBTACULO NO SE META DENTRO DEL PERSONAJE
	double radioSuma = o.return_Radio() + 0.3;

	if (dist < radioSuma)
	{
		double juntos = radioSuma - dist;
		double normalx = dx / dist;
		double normaly = dy / dist;

		//POSICIONAMIENTO
		j.setX(j.return_X() + normalx * juntos);
		j.setY(j.return_Y() + normaly * juntos);

		std::cout << "CHOQUE" << std::endl;

		return true;
	}
	return false;
}

bool Batalla::choqueObstaculo(Disparo& d, const Obstaculo& o)
{
	if (!d.return_Activo()) return false;

    double dx = d.return_X() - o.return_X();
    double dy = d.return_Y() - o.return_Y();
    double dist = sqrt(dx * dx + dy * dy);

    if (dist < o.return_Radio()*0.5)
    {
        if (std::abs(dx) > std::abs(dy)) d.setVX(-d.return_VX());
        else d.setVY(-d.return_VY());

        d.setRebotes(d.return_Rebotes() + 1);
		std::cout << "Rebote (obtaculo). TOTAL: " << d.return_Rebotes() << "/2" << std::endl;

        if (d.return_Rebotes() >= 2) {
			std::cout << "[SISTEMA] Disparo agotado (obtaculo)" << std::endl;
            d.setActivo(false);
        }

        d.setX(d.return_X() + d.return_VX() * 2);
        d.setY(d.return_Y() + d.return_VY() * 2);
        return true;
    }
    return false;
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