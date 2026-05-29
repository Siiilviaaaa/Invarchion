#include <iostream>
#include <cmath>
#include <string>
#include "Batalla.h"

using std::cout, std::cin, std::endl;

//VARIABLES DEFINIDAS EN INTERFACE.CPP
extern bool fin_;
extern int puntuacion_humanos;
extern int puntuacion_aliens;

Batalla::Batalla():numObstaculos(5)
{
	//INICIALIZAR PARA EVITAR QUE SEAN BASURA

	for (int i = 0;i < MAX_DISPAROS;i++)
		nDisparos[i] = nullptr;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			nHechizos[i][j] = nullptr;

	for (int i = 0; i < 5; i++)
		listaObstaculos[i] = nullptr;
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

	for (int b = 0; b < 2; b++)        //RECORRE 2 BANDOS
		for (int i = 0; i < 3; i++)    //RECORRE 3 HECHIZOS
			if (nHechizos[b][i] != nullptr) {
				delete nHechizos[b][i];
				nHechizos[b][i] = nullptr;
			}
}

void Batalla::inicializarBatalla()
{
	srand((unsigned int)time(NULL));
	int aceptados = 0;
	for (int i = 0; i < numObstaculos; i++) {
		if (listaObstaculos[i]) delete listaObstaculos[i];
		listaObstaculos[i] = nullptr;
	}
	double r = 1.3;
	const double limite_max_x = 20.0;
	const double limite_max_y = 15.0;
	const double margen_pared = 1.0;
	const double margen_personaje = 3.5;
	const float dist_min = 3.5f;
	double p1x = 5.0, p1y = 7.5, p2x = 15.0, p2y = 7.5;
	int intentos = 0;
	while (aceptados < numObstaculos && intentos < 1000) {
		intentos++;

		double rx = (margen_pared + r) + ((double)rand() / RAND_MAX) * (limite_max_x - 2 * (margen_pared + r));
		double ry = (margen_pared + r) + ((double)rand() / RAND_MAX) * (limite_max_y - 2 * (margen_pared + r));
		bool colision = false;
		//posciones iniciales de los personajes en batalla
		double distP1 = sqrt(pow(rx - p1x, 2) + pow(ry - p1y, 2));
		double distP2 = sqrt(pow(rx - p2x, 2) + pow(ry - p2y, 2));
		if (distP1 < margen_personaje || distP2 < margen_personaje) {
			colision = true;
		}
		if (!colision) {
			for (int j = 0; j < aceptados; j++) {
				Obstaculo* existente = listaObstaculos[j];
				float dx = (float)(rx - existente->return_X());
				float dy = (float)(ry - existente->return_Y());
				float distancia = sqrtf(powf(dx, 2) + powf(dy, 2));
				if (distancia < (r * dist_min)) {
					colision = true;
					break;
				}
			}
		}

		if (!colision) {
			listaObstaculos[aceptados] = new Obstaculo(rx, ry, r);
			aceptados++;
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

	case 'v': //PELEAN/DISPARAN
		if (j1.return_Tipo() == ARQUERO) {
			Arquero* arq = dynamic_cast<Arquero*>(&j1);
			if (arq != nullptr) {
				lanzarDisparo(j1);
				std::cout << "J1 lleva: " << j1.return_Disparos() << std::endl;
				setMensaje("Humanos llevan " + std::to_string(j1.return_Disparos()) + " disparos");
			}
			
		}
		else
		{
			pegar(j1, j2);
			std::cout << "J1 pegando... " << std::endl;
		}
		j1.activarAtaque();
		break;
	case 'c': //HECHIZAN
		if (j1.return_Tipo() == HECHICERO) {
			Hechicero* hech1 = dynamic_cast<Hechicero*>(&j1);
			if (hech1 != nullptr) {
				lanzarHechizo(*hech1, j2, hech1->HechizoUtilizado(), j1.return_Bando());
				hech1->siguienteHechizo();
				std::cout << "J1 lanza hechizo: " << std::endl;
			}
			
		}
		break;

	///////////////ALIENS////////////////
	////MOVIMIENTO EN CON TECLA ESPECIAL (FLECHAS)

	case 'm': //PELEAN/DISPARAN
		if (j2.return_Tipo() == ARQUERO) {
			lanzarDisparo(j2);
			std::cout << "J2 lleva: " << j2.return_Disparos() << std::endl;
			setMensaje("Aliens llevan " + std::to_string(j2.return_Disparos()) + " disparos");
		}
		else
		{
			pegar(j2, j1);
			std::cout << "J2 pegando... " << std::endl;
		}
		j2.activarAtaque();
		break;
	case'n': //HECHIZAN
		if (j2.return_Tipo() == HECHICERO) {
			Hechicero* hech2 = dynamic_cast<Hechicero*>(&j1);
			if (hech2 != nullptr) {
				lanzarHechizo(*hech2, j2, hech2->HechizoUtilizado(), j1.return_Bando());
				hech2->siguienteHechizo();
				std::cout << "J2 lanza hechizo: " << std::endl;
			}
			
		}
		break;
	}
}

void Batalla::tecla_especial(int key, Personaje& alien)
{
	//DEFINIDA EN EL ONSPECIALKEYDOWN DE INTERFAZ-> SOLO SE LLAMA CUANDO EL ALIEN ESTA EN BATALLA
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

	//DEVUELVE TRUE SI SE DESCONGELA Y SI SE ACABA LA MUNICION -> ESCRIBE EL MENSAJE POR PANTALLA DE JUEGO
	if (j1.actualizarEfectos())
		setMensaje("Humano DESCONGELADO");

	if (j2.actualizarEfectos())
		setMensaje("Alien DESCONGELADO");

	if (j1.gestionRecarga())
		setMensaje("Humanos: Municion recargada");

	if (j2.gestionRecarga())
		setMensaje("Aliens: Municion recargada");

	for (int k = 0; k < 5; k++) //PARA EVITAR ARRAYS VACIOS
		if (lista[k] != nullptr) {
			choqueObstaculo(j1, *lista[k]);
			choqueObstaculo(j2, *lista[k]);
		}

	//////////////// DISPAROS //////////////////
	//CHOQUE ENTRE DISPAROS:
	for (int i = 0; i < MAX_DISPAROS; i++) {
		if (nDisparos[i] == nullptr || !nDisparos[i]->return_Activo()) continue; //PARA EVITAR ARRAYS VACIOS
			for (int j = i + 1; j < MAX_DISPAROS; j++)
				if (nDisparos[j] != nullptr && nDisparos[j]->return_Activo()) //PARA EVITAR ARRAYS VACIOS
					entreDisparos(*nDisparos[i], *nDisparos[j]); //AMBOS JUGADORES
	}

	//RESTO DE CHOQUES
	for (int i = 0; i < MAX_DISPAROS; i++)
	{
		if (nDisparos[i] == nullptr) continue; //PARA EVITAR ARRAYS VACIOS

		if (nDisparos[i]->return_Activo())
		{
			nDisparos[i]->moverDisparo();
			limites(*nDisparos[i], caja); //CON LA CAJA

			for (int k = 0; k < 5; k++)
				if (lista[k] != nullptr) //PARA EVITAR ARRAYS VACIOS
					choqueObstaculo(*nDisparos[i], *lista[k]); //CON LOS OBSTACULOS

		//ASEGURARSE DE QUE SE DEFINEN BIEN EN BATALLA
			bool j1_enemigo = (nDisparos[i]->return_Bando() != j1.return_Bando());
			bool j2_enemigo = (nDisparos[i]->return_Bando() != j2.return_Bando());

			nDisparos[i]->Impacto(j1, j1_enemigo);
			nDisparos[i]->Impacto(j2, j2_enemigo);
		}
  
		if (!nDisparos[i]->return_Activo()) //BORRAR DISPAROS INACTIVOS
		{
			delete nDisparos[i];
			nDisparos[i] = nullptr;
		}
	}

	//////////////// HECHIZOS //////////////////		
	for (int b = 0; b < 2; b++) {
		for (int i = 0; i < 3; i++) {

			if (nHechizos[b][i] != nullptr) { //PARA EVITAR ARRAYS VACIOS
				nHechizos[b][i]->mover();

				Personaje* victima = nHechizos[b][i]->return_Obj(); //OBTENER OBJETIVO DEL HECHIZO

				if (victima != nullptr && nHechizos[b][i]->Impacta(victima->return_X(), victima->return_Y(), 0.1)) {

					int puntosHechizo = 20;

					//IDENTIFICAMOS EL TIPO
					int tipo = nHechizos[b][i]->return_Tipo();

					switch (tipo) {
					case 0: { //PARALISIS
						std::cout << "Efecto: Personaje congelado" << std::endl;
						setMensaje("Efecto: Personaje congelado");
						victima->setVelocidad(0);
						victima->set_paralisis(10.0);
						break;
					}
					case 1: //DAÑO EXTRA
						std::cout << "Efecto: Mitad de la vida" << std::endl;
						setMensaje("Efecto: Mitad de la vida");
						victima->setVida(victima->return_Vida() / 2);
						break;
					case 2: { //TELETRANSPORTE
						std::cout << "Efecto: Teletransporte aleatorio" << std::endl;
						setMensaje("Efecto: Teletransporte aleatorio");
						double nuevaX = 1.5f + (float)(rand() % 170) / 10.0f;
						double nuevaY = 1.5f + (float)(rand() % 120) / 10.0f;

						victima->x =nuevaX;
						victima->y =nuevaY;
						break;
						}
					}

					//BONUS POR KILL
					if (victima->return_Vida() <= 0)
						puntosHechizo += 50;

					//SUMAR PUNTOS AL ATACANTE
					if (nHechizos[b][i]->return_Bando() == HUMANO)
						puntuacion_humanos += puntosHechizo;
					else
						puntuacion_aliens += puntosHechizo;

					delete nHechizos[b][i]; //BORRAR HECHIZO
					nHechizos[b][i] = nullptr;
				}
			}
		}
	}

	////////////////FINAL//////////////////
	int resultado = FinCombate(j1, j2);
	if (resultado != 0) {
		j1.resetMunicion(); //PA QUE SE VUELVA A CERO AL INICIO DE BATALLA
		j2.resetMunicion();

		this->~Batalla();
		fin_ = true; //INDICAMOS QUE SE HA TERMINADO LA BATALLA PARA QEL PASO AL TABLERO
	}
}

HanGanado Batalla::FinCombate(Personaje& humanos, Personaje& aliens)
{
	//RETORNA 0 SI SIGUEN PELEANDO
	//RETORNA 1 SI HUMANOS GANAN
	//RETORNA 2 SI ALIENS GANAN

	if (aliens.return_Vida() <= 0)
	{
		cout << "HUMANS WIN!" << endl;
		setMensaje("HUMANS WIN");
		return GanaronHumanos;
	}
	else if (humanos.return_Vida() <= 0)
	{
		cout << "ALIENS WIN!" << endl;
		setMensaje("ALIENS WIN");
		return GanaronAliens;
	}

	return AunEnCurso;
}

void Batalla::pegar(Personaje& atacante, Personaje& objetivo)
{
	if (objetivo.return_Tipo() == EXCAVADOR) {
		Excavador* exc = dynamic_cast<Excavador*>(&objetivo);
		if (exc != nullptr && exc->estaBajoTierra()) {
			std::cout << "el objetivo esta bajo tierra" << std::endl;
			return;
		}
	}
	double dx = atacante.return_X() - objetivo.return_X();
	double dy = atacante.return_Y() - objetivo.return_Y();

	if (atacante.return_Tipo() == ARQUERO) //EL ARQUERO NO PEGA, SOLO DISPARA
		return;

	if (sqrt(dx * dx + dy * dy) > 1.5) //NO SE CONSIDERA GOLPE
		return;

	int danio = atacante.return_Danio();
	int nuevaVida = objetivo.return_Vida() - danio;
	int vidaAntes = objetivo.return_Vida();

	//VIDA NO NEGATIVA
	if (nuevaVida < 0)
		nuevaVida = 0;

	////////PUNTOS///////
	int puntosGanados = 10;
	if (nuevaVida <= 0) puntosGanados += 50; //BONUS POR KILL

	if (atacante.return_Bando() == HUMANO) puntuacion_humanos += puntosGanados;
	else puntuacion_aliens += puntosGanados;

	std::cout << "Vida antes =" << vidaAntes << " | Nueva =" << nuevaVida << std::endl;

	objetivo.setVida(nuevaVida);

	std::cout << "[COMBATE] " << (atacante.return_Bando() == 0 ? "HUMANO" : "ALIEN") << " golpea ";
}

void Batalla::lanzarDisparo(Personaje& aliado)
{
	//COMPROBAR QUE NO SE HA ALCANZADO EL MAXIMO DE DISPAROS
	if (aliado.return_Disparos() >= 10) {
		std::cout << "Sin municion" << std::endl;
		setMensaje("SIN MUNUCION. Espera a la recarga");
		return;
	}
	std::cout << "Disparando..." << std::endl;

	bool hueco = false; //PARA VER SI HAY CAPACIDAD EN EL ARRAY
	for (int i = 0; i < MAX_DISPAROS; i++)
	{
		if (nDisparos[i] == nullptr) //PARA EVITAR ARRAYS VACIOS
		{
			nDisparos[i] = new Disparo();
			aliado.sumarDisparo();
			nDisparos[i]->setBando(aliado.return_Bando());

			double dX = aliado.return_dirX();
			double dY = aliado.return_dirY();

			//SI NO SE HA MOVIDO, DISPARA HACIA LA DERECHA SI ES HUMANO O HACIA LA IZQUIERDA SI ES ALIEN
			if (dX == 0 && dY == 0) {
				dX = (aliado.return_Bando() == HUMANO) ? 1.0 : -1.0;
			}

			//EVITAR EL SUICIDIO POR IMPACTO INTERNO, PORQUE SALE DEL INTERIOR DEL PERSONAJE
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
	if (equipo < 0 || equipo > 1) return; //VALIDAR EQUIPO

	//COMPROBAR QUE EL MAGO TIENE HECHIZOS DISPONIBLES
	Hechicero* hech = dynamic_cast<Hechicero*>(&mago);
	if (hech != nullptr) {
		if (hech->return_HechizosRestantes() <= 0) {
				std::cout << "No te quedan hechizos en esta ronda" << std::endl;
				setMensaje("Sin hechizos para esta ronda");
				return;
			}
		bool hueco = false;
		for (int i = 0; i < 3; i++)
		{
			if (nHechizos[equipo][i] == nullptr) { //PARA EVITAR ARRAYS VACIOS
				nHechizos[equipo][i] = new Hechizo((Hechizo::TipoHechizo)tipo, mago.return_Bando());

				//EL HECHIZO PERSIGUE AL OBJETIVO, AUNQUE ESTE SE MUEVA -> NO TIENE ESCAPATORIA
				nHechizos[equipo][i]->setObj(&objetivo);

				double dX = objetivo.return_X() - mago.return_X();
				double dY = objetivo.return_Y() - mago.return_Y();

				nHechizos[equipo][i]->activar(mago.return_X(), mago.return_Y(), dX, dY); //SE ACTIVA EL HECHIZO CON LA DIRECCION HACIA EL OBJETIVO

				hech->usarHechizo();

				hueco = true;
				break;
			}
		}
		if (!hueco) {
			std::cout << "Maximo de hechizos alcanzado" << std::endl;
		}

	}
	
	return;
	
}

void Batalla::entrePersonajes(Personaje& j1, Personaje& j2) //COLISION ENTRE PERSONAJES
{
	double dx = j1.return_X() - j2.return_X();
	double dy = j1.return_Y() - j2.return_Y();
	double dist = sqrt(dx * dx + dy * dy);
	double radioChoque = 0.7;

	//PARA QUE NO SE METAN EL UNO DENTRO DEL OTRO, SE SEPARAN EN LA DIRECCION NORMAL AL CHOQUE
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

bool Batalla::entreDisparos(Disparo& d1, Disparo& d2) //COLISION ENTRE DISPAROS
{
	//SI SON DEL MISMO BANDO, NO PASA NADA
	if (d1.return_Bando() == d2.return_Bando()) return false;

	double dx = d1.return_X() - d2.return_X();
	double dy = d1.return_Y() - d2.return_Y();
	double dist = sqrt(dx * dx + dy * dy);

	//SI SE CHOCAN, SE DESACTIVAN AMBOS DISPAROS Y SE ELIMINAN
	if (dist < 0.3)
	{
		d1.setActivo(false);
		d2.setActivo(false);
		std::cout << "[SISTEMA] Choque entre aliado y enemigo" << std::endl;
		return true;
	}
	return false;
}

bool Batalla::NoMover(Personaje& j, const Pared& p) //TRUE SI EL PERSONAJE ESTA A MENOS DE 1 DE LA PARED, Y POR TANTO NO LO ATRAVIESA
{
	if (p.distancia(j.return_X(), j.return_Y()) < 1.0)
		return true; //CHOCA
	return false;
}

bool Batalla::reboteDisparos(Disparo& d, const Pared& p) //TRUE SI HAY REBOTE, Y SE REALIZA EL REBOTE
{
	if (p.distancia(d.return_X(), d.return_Y()) < 0.5)
	{
		//SI y1 == y2 -> SUELO O TECHO
		if (std::abs(p.return_Y1() - p.return_Y2()) < 0.1)
			d.setVY(-d.return_VY()); //REBOTE VERTICAL
		//SI x1 == x2 -> DCH O IZQ
		else if (std::abs(p.return_X1() - p.return_X2()) < 0.1)
			d.setVX(-d.return_VX()); //REBOTE HORIZONTAL

		//MAX 2 REBOTES, AL TERCERO SE ANULA
		d.setRebotes(d.return_Rebotes() + 1);
		std::cout << "Rebote (caja). TOTAL: " << d.return_Rebotes() << "/2" << std::endl;

		if (d.return_Rebotes() > 2) {
			d.setActivo(false);
			std::cout << "[SISTEMA] Disparo agotado (caja)" << std::endl;

		}
		//PA QUE NO SE QUEDE PEGADO A LA PARED, LO MOVEMOS UN POCO EN LA DIRECCION DEL REBOTE
		d.setX(d.return_X() + d.return_VX() * 2);
		d.setY(d.return_Y() + d.return_VY() * 2);

		return true;
	}
	return false;
}

bool Batalla::choqueObstaculo(Personaje& j, const Obstaculo& o) //TRUE SI HAY CHOQUE
{
	double dx = j.return_X() - o.return_X();
	double dy = j.return_Y() - o.return_Y();
	double dist = sqrt(dx * dx + dy * dy);

	//AJUSTAR PA QUE EL RADIO DE IMPACTO DEL OBTACULO NO SE META DENTRO DEL PERSONAJE
	double radioSuma = (o.return_Radio() * 0.75)+0.3;

	if (dist < radioSuma)
	{
		double juntos = radioSuma - dist;
		double normalx = dx / dist;
		double normaly = dy / dist;

		//POSICIONAMIENTO DEL PERSONAJE FUERA DEL RADIO DE IMPACTO
		j.x += normalx * juntos;
		j.y += normaly * juntos;

		std::cout << "CHOQUE" << std::endl;

		return true;
	}
	return false;
}

bool Batalla::choqueObstaculo(Disparo& d, const Obstaculo& o) //TRUE SI HAY CHOQUE
{
	if (!d.return_Activo()) return false; //SI EL DISPARO ESTA INACTIVO-> NO HAY CHOQUE

    double dx = d.return_X() - o.return_X();
    double dy = d.return_Y() - o.return_Y();
    double dist = sqrt(dx * dx + dy * dy);

	if (dist < o.return_Radio() * 0.5) //RADIO DE IMPACTO AJUSTADO PARA QUE NO SE META DENTRO DEL DISPARO, COMO CON LOS PERSONAJES
    {
        if (std::abs(dx) > std::abs(dy)) d.setVX(-d.return_VX());
        else d.setVY(-d.return_VY());

        d.setRebotes(d.return_Rebotes() + 1);
		std::cout << "Rebote (obtaculo). TOTAL: " << d.return_Rebotes() << "/2" << std::endl;

        if (d.return_Rebotes() >= 2) {
			std::cout << "[SISTEMA] Disparo agotado (obtaculo)" << std::endl;
            d.setActivo(false);
        }

		//PA QUE NO SE QUEDE PEGADO AL OBSTACULO, LO MOVEMOS UN POCO EN LA DIRECCION DEL REBOTE
        d.setX(d.return_X() + d.return_VX() * 2);
        d.setY(d.return_Y() + d.return_VY() * 2);
        return true;
    }
    return false;
}

void Batalla::limites(Disparo& d, Caja& c)
{
	//REBOTE CON LAS CUATRO PAREDES DE LA CAJA
	reboteDisparos(d, c.return_suelo());
	reboteDisparos(d, c.return_techo());
	reboteDisparos(d, c.return_izq());
	reboteDisparos(d, c.return_dcha());
}

void Batalla::limites(Personaje& j, Caja& c)
{
	double radio = 1.0;

	//COMPROBAR LAS CUATRO PAREDES DE LA CAJA
	j.x = NoMover(j, c.return_izq()) ? radio : j.x;
	j.x = NoMover(j, c.return_dcha()) ? 20.0 - radio : j.x;
	j.y = NoMover(j, c.return_suelo()) ? radio : j.y;
	j.y = NoMover(j, c.return_techo()) ? 15.0 - radio : j.y;
}