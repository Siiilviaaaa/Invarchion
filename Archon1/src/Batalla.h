#pragma once
#include "Personajes.h"
#include "freeglut.h"
#include "ETSIDI.h"

//VARIABLES GLOBALES DEFINIDAS EN BATALLA.CPP
extern bool usoPocion;

//CABECERAS DE FUNCIONES
void KeyBatalla(unsigned char key, Personajes_carac& j1, Personajes_carac& j2,
				double x1, double y1, double x2, double y2);
void start_combat(Personajes_carac& humanos, Personajes_carac& aliens);
void pegar(Personajes_carac& atacante, Personajes_carac& objetivo,
			double x1, double y1, double x2, double y2);
void actualizarCombate(Personajes_carac& j1, Personajes_carac& j2);

////////CLASES//////
class Disparo
{
	double x, y; // POSICION
	double velo_x, velo_y; // VELOCIDAD
	int danio; // DAÑO QUE CAUSA
	bool activo; // SI ESTA O NO EN PANTALLA

	ETSIDI::Sprite _flecha;
	
public:
	//////////GETTERS Y SETTERS///////////
	double return_X() const { return x; }
	double return_Y() const { return y; }
	double return_VX() const { return velo_x; }
	double return_VY() const { return velo_y; }
	void setX(double nuevoX) { x = nuevoX; }
	void setY(double nuevoY) { y = nuevoY; }
	void setVX(double nuevoVX) { velo_x = nuevoVX; }
	void setVY(double nuevoVY) { velo_y = nuevoVY; }

	////////////////METODOS///////////////
	Disparo(); //CONSTRUCTOR
	void dibujarDisparo();
	void crearDisparo(double posX, double posY);
	void actualizarDisparos(Personajes_carac& j1, Personajes_carac& j2);
};

class Hechizo
{
	int usos_max;
	int usos_restantes;
	bool activo; // "HECHIZO LANZADO DE MANERA VISUAL"
	double posX, posY; // POSICION DEL HECHIZO EN PANTALLA

	double t_recarga; // TIEMPO TOTAL DE RECARGA
	double t_restante; // TIEMPO RESTANTE PARA USAR DE NUEVO

	ETSIDI::Sprite _hechizo1;
	ETSIDI::Sprite _hechizo2;
	ETSIDI::Sprite _pocion;

public:
	//////////GETTERS Y SETTERS///////////
	double return_RECARGA() const { return t_recarga; }
	double return_RESTANTE() const { return t_restante; }
	bool return_Activo() const { return activo; }
	double return_PosX() const { return posX; }
	double return_PosY() const { return posY; }
	void setRECARGA(Tipo nuevoTiempo) { t_recarga = nuevoTiempo; }
	void setRESTANTE(double nuevoTiempo) { t_restante = nuevoTiempo; }
	void setActivo(bool nuevoActivo) { activo = nuevoActivo; }
	void setPosX(double nuevoPosX) { posX = nuevoPosX; }
	void setPosY(double nuevoPosY) { posY = nuevoPosY; }

	////////////////METODOS///////////////
	Hechizo(); //CONSTRUCTOR
	void conf_Hechizos(); //DIFERENCIAR TIPOS DE HECHIZOS
	void usar_Hechizo(int tipoHechizo, Personajes_carac& objetivo);
	void usar_Pocion(Personajes_carac& aliado);
	void actualizarTiempos(double Time);  //ACTUALIZA TIEMPOS DE RECARGA
};