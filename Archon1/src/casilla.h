#pragma once
//definicion del tipo de casilla y todos sus atributos
using byte = unsigned char;
enum bando { HUMANO, ALIEN, NEUTRAL };
enum personaje{humano1, humano2, humano3, humano4, hmano5, humano6, alien1, alien2, alien3, alien4, alien5, alien6};
enum Tipocasilla { blanca, negra, lila };
class Casilla
{
public:
	//variables para la posicion
	int fila_, columna_; //posicion en el espacio
	float lado; //valor lado cubo
	//estado de la logica
	bool ocupada; //hay pieza??

	bando tipo_bando;//de que bando es la pieza???
	personaje tipo_personaje;
	Tipocasilla tipo_color;//color tablero

//public:
	Casilla();
	void configurar(int f, int c, float l, Tipocasilla color_);
	void dibuja();
	void fila(int f) { fila_ = f; }
	int fila()const { return fila_; }
	void columna(int c) { columna_ = c; }
	int columna()const { return columna_; }
	//void x(double x) { x_= x; }
	//double x() const{ return x_; }
	//void y(double y) { y_ = y; }
	//double y()const { return y_; }
	//void posicion(double ix, double iy);

	
};