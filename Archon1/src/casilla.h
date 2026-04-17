#pragma once
#include <Personajes.h> //he quitado en lo que definias los tipos de personajes, que ya estaba en personajes.h
//definicion del tipo de casilla y todos sus atributos
using byte = unsigned char;

enum Tipocasilla { blanca, negra, lila};
class Casilla
{
public:
	//variables para la posicion
	int fila_, columna_; //posicion en el espacio
	float lado; //valor lado cubo
	//estado de la logica
	bool ocupada; //hay pieza??

	Bando tipo_bando;//de que bando es la pieza
	Tipo_figura tipo_personaje; 
	Tipocasilla tipo_color;//color tablero
	

//public:
	Casilla();
	void configurar(int f, int c, float l, Tipocasilla color_);
	void dibuja();
	void fila(int f) { fila_ = f; }
	int fila()const { return fila_; }
	void columna(int c) { columna_ = c; }
	int columna()const { return columna_; }

	Bando ComprobarSiHayPiezaEncima(int x, int y);//develveme personaje.bando, asi yo se q si es null no hay nada y si no, que pieza hay, gracias
	//void x(double x) { x_= x; }
	//double x() const{ return x_; }
	//void y(double y) { y_ = y; }
	//double y()const { return y_; }
	//void posicion(double ix, double iy);

	
};