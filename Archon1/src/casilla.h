#pragma once
using byte = unsigned char;
enum bando { HUMANO, ALIEN, NEUTRAL };
enum Tipocasilla { blanca, negra, lila };
class Casilla
{
	//variables para la posicion
	int fila_, columna_; //posicion en el espacio
	float lado; //valor lado cubo
	//estado de la logica
	bool ocupada; //hay pieza??

	bando tipo_bando;//de que bando es la pieza???
	Tipocasilla tipo_color;//color tablero

public:
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

	//funciones logica del cursor con sofia
};