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
	Disparo* nDisparos[MAX_DISPAROS];
public:
	Batalla();
	~Batalla();
	Disparo* (&return_nDisparos())[20] { return nDisparos; }

	/////////ACTUALIZACIONES//////////////
	void KeyBatalla(unsigned char key, Personaje& j1, Personaje& j2);
	int actualizarCombate(Personaje& j1, Personaje& j2, Caja& caja, Obstaculo* lista[5]);
	int FinCombate(Personaje& humanos, Personaje& aliens);

	/////////DAÑAR AL OPONENTE////////////
	void pegar(Personaje& atacante, Personaje& objetivo);
	void lanzarDisparo(Personaje& aliado);
	void eliminarRestos();

	/////////INTERACCION CON LOS ELEMENTOS////////////
	static bool NoMover(Personaje& j, const Pared& p);
	static bool reboteDisparos(Disparo& d, const Pared& p);
	static bool choqueObstaculo(Personaje& j, const Obstaculo& o);
	static bool choqueObstaculo(Disparo& d, const Obstaculo& o);

	static void limites_d(Disparo& d, Caja& c);
	static void limites_p(Personaje& j, Caja& c);
};