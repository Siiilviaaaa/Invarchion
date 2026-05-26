#pragma once
#include "Informacion Casilla.h"
//definicion del tipo de casilla y todos sus atributos

class Casilla
{
	friend class Cursor;
	friend class Juego;
	//variables para la posicion
	int fila, columna; //posicion en el espacio
	InfoCasilla* info;
public:
	Casilla(): fila(0), columna(0), info(nullptr){}
	Casilla(int f_, int c_, InfoCasilla* info_):fila(f_), columna(c_), info(info_){}

	
	int getfila()const { return fila; }
	int getcolumna()const { return columna; }
	InfoCasilla* getInfo() const { return info; }

	//void configurar(int f, int c, float l, Tipocasilla color_);
	//void dibuja();
	
	//void x(double x) { x_= x; }
	//double x() const{ return x_; }
	//void y(double y) { y_ = y; }
	//double y()const { return y_; }
	//void posicion(double ix, double iy);

	
};