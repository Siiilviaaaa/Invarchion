#pragma once
#include "Personajes.h"
#include "Caja.h"
#include "freeglut.h"
#include "Juego.h"
#include "Disparos.h"
#include "Hechizos.h"
#include "Obstaculo.h"

/////////INTERFAZ DEL ESCENARIO DE COMBATE/////////////////////

class Batalla
{
	friend class MotorGrafico;
	friend class Juego;

	static const int MAX_DISPAROS = 20;
	Disparo* nDisparos[MAX_DISPAROS]; //LISTA DE DISPAROS, SE INICIALIZA EN EL CONSTRUCTOR Y LO LLENAMOS EN LANZAR DISPARO
	Hechizo* nHechizos[2][3]; //EL PRIMER INDICE ES PARA EL BANDO, EL SEGUNDO PARA EL TIPO DE HECHIZO

	Obstaculo* listaObstaculos[7]; //LISTA DE OBSTACULOS, SE INICIALIZA EN EL CONSTRUCTOR Y LO LLENAMOS EN INICIALIZAR_BATALLA
	int numObstaculos;

	std::string mensaje_batalla = "PREPARADOS... LUCHAD!"; //INICIALIZADO CON UNMENSAJE POR DEFECTO PARA QUE NO APAREZCA BASURA EN PANTALLA
	std::string mensaje_bonus = " ";
	
public:
	Batalla();
	~Batalla();
	Disparo* (&return_nDisparos())[20] { return nDisparos; }
	Hechizo* (&return_nHechizos())[2][3] { return nHechizos; }

	///////MENSAJES///////
	std::string getMensaje() const { return mensaje_batalla; }
	std::string getMensajeBonus()const { return mensaje_bonus; }
	void setMensaje(std::string nuevoMensaje) {	mensaje_batalla = nuevoMensaje;	}
	void setMensajeBonus(std::string MensajeBonus) { mensaje_bonus = MensajeBonus; }

	/////////ACTUALIZACIONES//////////////
	void inicializarBatalla();
	void KeyBatalla(unsigned char key, Personaje& j1, Personaje& j2);
	void tecla_especial(int key, Personaje& alien);
	void actualizarCombate(Personaje& j1, Personaje& j2, Caja& caja, Obstaculo* lista[5]);
	HanGanado FinCombate(Personaje& humanos, Personaje& aliens);

	/////////DAÑAR AL OPONENTE////////////
	void pegar(Personaje& atacante, Personaje& objetivo);
	void lanzarDisparo(Personaje& aliado);
	void lanzarHechizo(Personaje& mago, Personaje& objetivo, int tipo, int equipo);

	/////////INTERACCION CON LOS ELEMENTOS////////////
	void entrePersonajes(Personaje& j1, Personaje& j2);
	bool entreDisparos(Disparo& d1, Disparo& d2);
	static bool NoMover(Personaje& j, const Pared& p);
	static bool reboteDisparos(Disparo& d, const Pared& p);
	static bool choqueObstaculo(Personaje& j, const Obstaculo& o);
	static bool choqueObstaculo(Disparo& d, const Obstaculo& o);

	static void limites(Disparo& d, Caja& c);
	static void limites(Personaje& j, Caja& c);

	//DIRECCION QUE APUNTA A OTRA DIRECCION
	Obstaculo* (&obtenerObstaculos())[7] {return listaObstaculos;}
};