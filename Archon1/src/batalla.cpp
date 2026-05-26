#include <iostream>
#include <cmath>
#include "Batalla.h"

using std::cout, std::cin, std::endl;
extern bool fin_;
extern int puntuacion_actual;

Batalla::Batalla()
{
	for (int i = 0;i < MAX_DISPAROS;i++)
		nDisparos[i] = nullptr;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			nHechizos[i][j] = nullptr;
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

	for (int b = 0; b < 2; b++) {        //RECORRE 2 BANDOS
		for (int i = 0; i < 3; i++) {    //RECORRE 3 HECHIZOS
			if (nHechizos[b][i] != nullptr) {
				delete nHechizos[b][i];
				nHechizos[b][i] = nullptr;
			}
		}
	}
}

void Batalla::KeyBatalla(unsigned char key, Personaje& j1, Personaje& j2)
{
	switch (key)
	{
	///////////////HUMANOS////////////////
	//MOVIMIENTO
	case 'w': j1.direccion(0, 1);  j1.moverEnBatalla(); break;
	case 's': j1.direccion(0, -1); j1.moverEnBatalla(); break;
	case 'a': j1.direccion(-1, 0); j1.moverEnBatalla(); break;
	case 'd': j1.direccion(1, 0);  j1.moverEnBatalla(); break;

	case ' ': //PELEAN/DISPARAN
		if (j1.return_Tipo() == ARQUERO) {
			lanzarDisparo(j1);
			std::cout << "J1 lleva: " << j1.return_Disparos() << std::endl;
		}
		else
		{
			pegar(j1, j2);
			std::cout << "J1 pegando... " << std::endl;
		}
		break;
	case 'c': //HECHIZAN
		if (j1.return_Tipo() == HECHICERO) {
			lanzarHechizo(j1, j2, j1.HechizoUtilizado(), j1.return_Bando());
			j1.siguienteHechizo();
			std::cout << "J1 lanza hechizo: " << std::endl;
		}
		break;

	///////////////ALIENS////////////////
	////MOVIMIENTO EN CON TECLA ESPECIAL (FLECHAS)

	case 13: //PELEAN/DISPARAN
		if (j2.return_Tipo() == ARQUERO) {
			lanzarDisparo(j2);
			std::cout << "J2 lleva: " << j2.return_Disparos() << std::endl;
		}
		else
		{
			pegar(j2, j1);
			std::cout << "J2 pegando... " << std::endl;
		}
		break;
	case'n': //HECHIZAN
		if (j2.return_Tipo() == HECHICERO) {
			lanzarHechizo(j2, j1, j2.HechizoUtilizado(), j2.return_Bando());
			j2.siguienteHechizo();
			std::cout << "J2 lanza hechizo: " << std::endl;
		}
		break;
	}
}

void Batalla::tecla_especial(int key, Personaje& alien)
{
	switch (key)
	{
		case GLUT_KEY_UP: alien.direccion(0, 1);  alien.moverEnBatalla(); break;
		case GLUT_KEY_DOWN: alien.direccion(0, -1); alien.moverEnBatalla(); break;
		case GLUT_KEY_LEFT: alien.direccion(-1, 0); alien.moverEnBatalla(); break;
		case GLUT_KEY_RIGHT: alien.direccion(1, 0);  alien.moverEnBatalla(); break;
	}
}

void Batalla::actualizarCombate(Personaje& j1, Personaje& j2, Caja& caja, Obstaculo* lista[5])
{
	////////////////PERSONAJES//////////////////
	limites(j1, caja);
	limites(j2, caja);

	entrePersonajes(j1, j2);

	j1.actualizarEfectos();
	j2.actualizarEfectos();

	j1.gestionRecarga();
	j2.gestionRecarga();

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
			limites(*nDisparos[i], caja); //CON LA CAJA

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
	for (int b = 0; b < 2; b++) {
		for (int i = 0; i < 3; i++) {

			if (nHechizos[b][i] != nullptr) {
				nHechizos[b][i]->mover();

				Personaje* victima = nHechizos[b][i]->return_Obj();

				if (victima != nullptr && nHechizos[b][i]->Impacta(victima->return_X(), victima->return_Y(), 0.1)) {

					//IDENTIFICAMOS EL TIPO
					int tipo = nHechizos[b][i]->return_Tipo();

					switch (tipo) {
					case 0: { //PARALISIS
						std::cout << "Efecto: Personaje congelado" << std::endl;
						victima->setVelocidad(0);
						victima->set_paralisis(5.0);
						break;
					}
					case 1://DAÑO EXTRA
						std::cout << "Efecto: Mitad de la vida" << std::endl;
						victima->setVida(victima->return_Vida() / 2);
						break;
					case 2: {//TELETRANSPORTE
						std::cout << "Efecto: Teletransporte aleatorio" << std::endl;
						double nuevaX = 1.5f + (float)(rand() % 170) / 10.0f;
						double nuevaY = 1.5f + (float)(rand() % 120) / 10.0f;

						victima->x =nuevaX;
						victima->y =nuevaY;
						break;
						}
					}

					delete nHechizos[b][i];
					nHechizos[b][i] = nullptr;
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
		std::cout << "Sin municion espera a la recarga" << std::endl;
		return;
	}
	std::cout << "Disparando..." << std::endl;

	bool hueco = false; //PARA VER SI HAY CAPACIDAD EN EL ARRAY
	for (int i = 0; i < MAX_DISPAROS; i++)
	{
		if (nDisparos[i] == nullptr)
		{
			nDisparos[i] = new Disparo();
			aliado.sumarDisparo();
			nDisparos[i]->setBando(aliado.return_Bando());

			double dX = aliado.return_dirX();
			double dY = aliado.return_dirY();

			if (dX == 0 && dY == 0) {
				dX = (aliado.return_Bando() == HUMANO) ? 1.0 : -1.0;
			}

			double margen = 1.2;
			nDisparos[i]->setX(aliado.return_X() + dX * margen);
			nDisparos[i]->setY(aliado.return_Y() + dY * margen);

			nDisparos[i]->setVX(dX * 0.1);
			nDisparos[i]->setVY(dY * 0.1);
			nDisparos[i]->setActivo(true);

			hueco = true;
			break;
		}
	}
	if (!hueco) {
		std::cout << "Maximo de disparos alcanzado" << std::endl;
	}
}

void Batalla::lanzarHechizo(Personaje& mago, Personaje& objetivo, int tipo, int equipo)
{
	if (equipo < 0 || equipo > 1) return;

	if (mago.return_HechizosRestantes() <= 0) {
		std::cout << "No te quedan hechizos en esta ronda" << std::endl;
		return;
	}

	bool hueco = false;
	for (int i = 0; i < 3; i++)
	{
		if (nHechizos[equipo][i] == nullptr) {
			nHechizos[equipo][i] = new Hechizo((Hechizo::TipoHechizo)tipo, mago.return_Bando());

			nHechizos[equipo][i]->setObj(&objetivo);

			double dX = objetivo.return_X() - mago.return_X();
			double dY = objetivo.return_Y() - mago.return_Y();

			nHechizos[equipo][i]->activar(mago.return_X(), mago.return_Y(), dX, dY);

			mago.usarHechizo();

			hueco = true;
            break; 
        }
    }
	if (!hueco) {
		std::cout << "Maximo de hechizos alcanzado" << std::endl;
	}
}

void Batalla::entrePersonajes(Personaje& j1, Personaje& j2)
{
	double dx = j1.return_X() - j2.return_X();
	double dy = j1.return_Y() - j2.return_Y();
	double dist = sqrt(dx * dx + dy * dy);
	double radioChoque = 0.7;

	
	if (dist > 0.0 && dist < radioChoque)
	{
		double juntos = radioChoque - dist;
		double normalx = dx / dist;
		double normaly = dy / dist;

		j1.x += normalx * (juntos / 2);
		j1.y += normaly * (juntos / 2);

		j2.x -= normalx * (juntos / 2);
		j2.y -= normaly * (juntos / 2);
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
	double radioSuma = (o.return_Radio() * 0.75)+0.3;

	if (dist < radioSuma)
	{
		double juntos = radioSuma - dist;
		double normalx = dx / dist;
		double normaly = dy / dist;

		//POSICIONAMIENTO
		j.x += normalx * juntos;
		j.y += normaly * juntos;

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

void Batalla::limites(Disparo& d, Caja& c)
{
	reboteDisparos(d, c.return_suelo());
	reboteDisparos(d, c.return_techo());
	reboteDisparos(d, c.return_izq());
	reboteDisparos(d, c.return_dcha());
}

void Batalla::limites(Personaje& j, Caja& c)
{
	double radio = 1.0;

	//COMPROBAR CADA PARED
	//SI NOMOVER ES TRUE, LIMITE
	j.x = NoMover(j, c.return_izq()) ? radio : j.x;
	j.x = NoMover(j, c.return_dcha()) ? 20.0 - radio : j.x;
	j.y = NoMover(j, c.return_suelo()) ? radio : j.y;
	j.y = NoMover(j, c.return_techo()) ? 15.0 - radio : j.y;

}