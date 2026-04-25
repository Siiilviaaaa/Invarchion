#pragma once

class Cursor {
	int fila,columna;//ver si hay .h de posicion 
	//QUIZA EL CURSOR DEBERIA TENER UN ATRIBUTO QUE ES UN PERSONAJE PARA QU EAL COGER Y SOLTAR NO SE PIERDA
public:
	Cursor(int fi, int col);//constructor
	void dibuja();
	void inicializa(int turno);
	void preguntar_coger();
	void preguntar_soltar();
	void coger();
	void soltar();
};