#pragma once
#include "Personajes.h"
#include "freeglut.h"
#include "ETSIDI.h"

//VARIABLES GLOBALES DEFINIDAS EN BATALLA.CPP
extern bool usoPocion;

//CABECERAS DE FUNCIONES
void KeyBatalla(unsigned char key, Personajes_carac& j1, Personajes_carac& j2,
				double x1, double y1, double x2, double y2);
int FinalBatalla(Personajes_carac& humanos, Personajes_carac& aliens);
void actualizarCombate(Personajes_carac& j1, Personajes_carac& j2);
void pegar(Personajes_carac& atacante, Personajes_carac& objetivo,
			double x1, double y1, double x2, double y2);

////////CLASES//////
class Disparo
{
	double x, y; // POSICION
	double velo_x, velo_y; // VELOCIDAD
	int danio; // DAÑO QUE CAUSA
	bool activo; // SI ESTA O NO EN PANTALLA

	ETSIDI::Sprite flecha;
	
public:
	//////////GETTERS Y SETTERS///////////
	bool return_Activo() const { return activo; }
	void setX(double nuevoX) { x = nuevoX; }
	void setY(double nuevoY) { y = nuevoY; }
	void setVX(double nuevoVX) { velo_x = nuevoVX; }
	void setVY(double nuevoVY) { velo_y = nuevoVY; }
	void setActivo(bool nuevoActivo) { activo = nuevoActivo; }

	////////////////METODOS///////////////
	Disparo();//COSNTRUCTOR
	void dibujarDisparo();
	void moverDisparo();
	bool Impacto(Personajes_carac& objetivo);
	
};

class Hechizo
{
public:
	enum TipoHechizo : int { PARALISIS, HIPERVELOCIDAD, POCION };
private:
	TipoHechizo tipo;
	int usos_restantes;
	bool activo; // "HECHIZO LANZADO DE MANERA VISUAL"
	double posX, posY; // POSICION DEL HECHIZO EN PANTALLA

	double t_recarga; // TIEMPO TOTAL DE RECARGA
	double t_restante; // TIEMPO RESTANTE PARA USAR DE NUEVO

	ETSIDI::Sprite mis_hechizos; //GRAFICO DEL HECHIZO

public:
	double return_RESTANTE() const { return t_restante; }
	
	Hechizo(); //CONSTRUCTOR 
	void configurar(TipoHechizo t);
	void dibujarHechizo();
	void usar_Hechizo(int tipoHechizo, Personajes_carac& objetivo);
	//void usar_Pocion(Personajes_carac& aliado);
	void actualizarTiempos(double Time);  //ACTUALIZA TIEMPOS DE RECARGA
};