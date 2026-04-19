#include "Cursor.h"


//fichero con las funciones logicas que puede realizar el cursor
//inicializarse en las casillas de abajo del euqipo correspondiente 
//dibujarse a medida que se tocan las teclas
//preguntar quien hay en esa casilla- recorrer un array
//coger o no la pieza
//preuntar si se puede soltar la pieza en base a sus movimientos-recorrer el array
//soltar o no la pieza
//pedir cambio de turno-pedir cambio a la batalla

Cursor::Cursor(int col, int fil)
{
	columna = col;
	fila = fil;
}

void Cursor::dibuja()
{//aqui va toda la parte grafica, se activa siempre que se cmabia la posicion del cursor, cuidado que son atributos privados
}

void Cursor::inicializa(int turno)
{//posicionar las coordenadas del cursor en el inicio base segun turno 
	if (turno == 0)// es el turno de los humanos!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{
		fila = 3;
		columna = 1;
		//Una vez que cmabie esto deberia pintarse la forma del cursor
	}
	if (turno == 1)// es el turno de los humanos!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{
		fila = 3;
		columna = 7;
		//Una vez que cmabie esto deberia pintarse la forma del cursor
	}
}

void Cursor::preguntar_coger()
{
}

void Cursor::preguntar_soltar()
{
}

void Cursor::coger()
{
}

void Cursor::soltar()
{
}
