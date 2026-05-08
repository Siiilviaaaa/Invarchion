#pragma once
#include "Personajes.h"
#include "Caja.h"
#include "freeglut.h"
#include "Juego.h"
#include "ETSIDI.h"
#include "Disparos.h"
#include "Hechizos.h"
#include "Obstaculo.h"

/////////INTERFAZ DEL ESCENARIO DE COMBATE/////////////////////

class Batalla
{
	static const int MAX_DISPAROS = 20;
	static const int MAX_HECHIZOS = 3;
	Disparo* nDisparos[MAX_DISPAROS];
	Hechizo* nHechizos[MAX_HECHIZOS];
	
public:
	Batalla();
	~Batalla();
	Disparo* (&return_nDisparos())[20] { return nDisparos; }
	Hechizo* (&return_nHechizos())[3] { return nHechizos; }

	/////////ACTUALIZACIONES//////////////
	void KeyBatalla(unsigned char key, Personaje& j1, Personaje& j2);
	void actualizarCombate(Personaje& j1, Personaje& j2, Caja& caja, Obstaculo* lista[5]);
	int FinCombate(Personaje& humanos, Personaje& aliens);

	/////////DAÑAR AL OPONENTE////////////
	void pegar(Personaje& atacante, Personaje& objetivo);
	void lanzarDisparo(Personaje& aliado);
	void lanzarHechizo(Personaje& mago, Personaje& objetivo, int tipo);

	/////////INTERACCION CON LOS ELEMENTOS////////////
	void entrePersonajes(Personaje& j1, Personaje& j2);
	bool entreDisparos(Disparo& d1, Disparo& d2);
	static bool NoMover(Personaje& j, const Pared& p);
	static bool reboteDisparos(Disparo& d, const Pared& p);
	static bool choqueObstaculo(Personaje& j, const Obstaculo& o);
	static bool choqueObstaculo(Disparo& d, const Obstaculo& o);

	static void limites_d(Disparo& d, Caja& c);
	static void limites_p(Personaje& j, Caja& c);
};