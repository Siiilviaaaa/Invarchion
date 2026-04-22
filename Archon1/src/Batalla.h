#pragma once
#include "Personajes.h"
#include "Caja.h"
#include "freeglut.h"
#include "Juego.h"
#include "ETSIDI.h"
#include "Disparos.h"
#include "Hechizos.h"

/////////INTERFAZ DEL ESCENARIO DE COMBATE/////////////////////

class Batalla
{
public:
	/////////ACTUALIZACIONES//////////////
	void actualizarCombate(Personaje& j1, Personaje& j2);
	int FinCombate(Personaje& humanos, Personaje& aliens);

	/////////DAÑAR AL OPONENTE////////////
	void pegar(Personaje& atacante, Personaje& objetivo, double x1, double y1, double x2, double y2);
	void KeyBatalla(unsigned char key, Personaje& j1, Personaje& j2,double x1, double y1, double x2, double y2);
	
	/////////INTERACCION CON LOS ELEMENTOS////////////
	static bool rebotePersonaje(Personaje& j, const Pared& p);
	static bool reboteDisparo(Disparo& j, const Pared& p);

	static void limitesDisparo(Disparo& d, Caja& c);
	static void limitesPersonaje(Personaje& j, Caja& c);
};