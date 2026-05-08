#include <iostream>
#include <cmath>
#include "Batalla.h"

using std::cout, std::cin, std::endl;
extern bool fin_;

Batalla::Batalla()
{
	for (int i = 0;i < MAX_DISPAROS;i++)
		nDisparos[i] = nullptr;

	for (int i = 0; i < MAX_HECHIZOS; i++)
		nHechizos[i] = nullptr;
}

Batalla::~Batalla()
{
	std::cout << "Limpiando escenario..." << std::endl;

	for (int i = 0; i < MAX_DISPAROS; i++)
		if (nDisparos[i] != nullptr)
		{
			delete nDisparos[i];      //LIBERAR MEMORIA
			nDisparos[i] = nullptr;   //VACIAR
		}

	for (int i = 0; i < MAX_HECHIZOS; i++)
		if (nHechizos[i] != nullptr) {
			delete nHechizos[i];
			nHechizos[i] = nullptr;
		}
}

void Batalla::KeyBatalla(unsigned char key, Personaje& j1, Personaje& j2)
{
	switch (key)
	{
	case ' ': //HUMANOS PELEAN, DISPARAN O HECHIZAN CON EL ESPACIO
		if (j1.return_Tipo() == ARQUERO) {
			lanzarDisparo(j1);
			std::cout << "J1 lleva: " << j1.return_Disparos() << std::endl;
		}
		else if (j1.return_Tipo() == HECHICERO) {
			lanzarHechizo(j1, j2, 0);
			std::cout << "J1 lanza hechizo: " << std::endl;
		}
		else
		{
			pegar(j2, j1);
			std::cout << "J2 pegando... " << std::endl;
		}
		break;
	case 13: //ALIENS PELEAN, DISPARAN O HECHIZAN CON ENTER
		if (j2.return_Tipo() == ARQUERO) {
			lanzarDisparo(j2);
			std::cout << "J2 lleva: " << j2.return_Disparos() << std::endl;
		}
		else if (j2.return_Tipo() == HECHICERO) {
			lanzarHechizo(j2, j1, 0);
			std::cout << "J2 lanza hechizo: " << std::endl;
		}
		else
		{
			pegar(j2, j1);
			std::cout << "J2 pegando... " << std::endl;
		}
		break;
	}

	switch (key)
	{
		//JUGADOR 1
	case 'w': j1.direccion(0, 1);  break;
	case 's': j1.direccion(0, -1); break;
	case 'a': j1.direccion(-1, 0); break;
	case 'd': j1.direccion(1, 0);  break;

		// JUGADOR 2
	case 'i': j2.direccion(0, 1);  break;
	case 'k': j2.direccion(0, -1); break;
	case 'j': j2.direccion(-1, 0); break;
	case 'l': j2.direccion(1, 0);  break;
	}
}

void Batalla::actualizarCombate(Personaje& j1, Personaje& j2, Caja& caja, Obstaculo* lista[5])
{
	////////////////PERSONAJES//////////////////
	j1.moverEnBatalla();
	j2.moverEnBatalla();

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
	//DEMAS CHOQUES
	for (int i = 0; i < MAX_DISPAROS; i++)
	{
		if (nDisparos[i] == nullptr) continue;

		if (nDisparos[i]->return_Activo())
		{
			nDisparos[i]->moverDisparo();
			limites_d(*nDisparos[i], caja); //CON LA CAJA

			for (int k = 0; k < 5; k++) {
				if (lista[k] != nullptr)
					choqueObstaculo(*nDisparos[i], *lista[k]); //CON LOS OBSTACULOS
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
		
	//////////////// HECHIZOS //////////////////
	for (int i = 0; i < MAX_HECHIZOS; i++) {
		if (nHechizos[i] != nullptr) {

			if (nHechizos[i]->return_Activo()) {
				nHechizos[i]->mover();

				Personaje* victima = nHechizos[i]->return_Obj();
				if (victima != nullptr && nHechizos[i]->Impacta(victima->return_X(), victima->return_Y(), 0.05)) {

					std::cout << "Hechizo: impacto detectado" << i << std::endl;

					delete nHechizos[i];
					nHechizos[i] = nullptr;
					continue;
				}
			}
		}
	}

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

void Batalla::lanzarHechizo(Personaje& mago, Personaje& objetivo, int tipo)
{
	if (nHechizos[tipo] != nullptr) delete nHechizos[tipo];

	nHechizos[tipo] = new Hechizo();
	nHechizos[tipo]->configurar((Hechizo::TipoHechizo)tipo);

	nHechizos[tipo]->setObj(&objetivo);

	double dX = objetivo.return_X() - mago.return_X();
	double dY = objetivo.return_Y() - mago.return_Y();

	nHechizos[tipo]->activar(mago.return_X(), mago.return_Y(), dX, dY);
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