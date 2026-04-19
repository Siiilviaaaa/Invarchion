#pragma once
#include "ETSIDI.h"

class Personaje; //DECLARACION ANTICIPADA

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
	void usar_Hechizo(int tipoHechizo, Personaje& objetivo);
	void usar_Pocion(Personaje& aliado);
	void actualizarTiempos(double Time);  //ACTUALIZA TIEMPOS DE RECARGA
};

//////VARIABLES GLOBALES DEFINIDAS EN HECHIZOS.CPP
extern Hechizo hechizos[3];
extern bool usoPocion;