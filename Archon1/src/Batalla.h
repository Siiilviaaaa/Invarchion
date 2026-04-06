#pragma once
#include "Personajes.h"
#include "freeglut.h"

//VARIABLES GLOBALES DEFINIDAS EN BATALLA.CPP
extern bool usoPocion;

//CABECERAS DE FUNCIONES
void KeyBatalla(unsigned char key, Personajes_carac& j1, Personajes_carac& j2,
				double x1, double y1, double x2, double y2, GLuint flecha);
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
	GLuint flecha; // IMAGEN

public:
	Disparo(); //CONSTRUCTOR
	void crearDisparo(double posX, double posY, GLuint png);
	void actualizarDisparos(Personajes_carac& j1, Personajes_carac& j2);
};

class Hechizo
{
	GLuint imagen;
	int usos_max;
	int usos_restantes;
	bool activo; // "HECHIZO LANZADO DE MANERA VISUAL"
	double posX, posY; // POSICION DEL HECHIZO EN PANTALLA

	double t_recarga; // TIEMPO TOTAL DE RECARGA
	double t_restante; // TIEMPO RESTANTE PARA USAR DE NUEVO

public:
	//////////GETTERS Y SETTERS///////////
	double return_RECARGA() const { return t_recarga; }
	double return_RESTANTE() const { return t_restante; }
	bool return_Activo() const { return activo; }
	void setRECARGA(Tipo nuevoTiempo) { t_recarga = nuevoTiempo; }
	void setRESTANTE(double nuevoTiempo) { t_restante = nuevoTiempo; }
	void setActivo(bool nuevoActivo) { activo = nuevoActivo; }

	////////////////METODOS///////////////
	Hechizo(); //CONSTRUCTOR
	void conf_Hechizos(); //DIFERENCIAR TIPOS DE HECHIZOS
	void usar_Hechizo(int tipoHechizo, Personajes_carac& objetivo);
	void usar_Pocion(Personajes_carac& aliado);
	void actualizarTiempos(double Time);  //ACTUALIZA TIEMPOS DE RECARGA
};