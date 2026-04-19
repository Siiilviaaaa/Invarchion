#include "Cursor.h"


//fichero con las funciones logicas que puede realizar el cursor
//inicializarse en las casillas de abajo del euqipo correspondiente 
//dibujarse a medida que se tocan las teclas
//preguntar quien hay en esa casilla- recorrer un array
//coger o no la pieza
//preuntar si se puede soltar la pieza en base a sus movimientos-recorrer el array
//soltar o no la pieza
//pedir cambio de turno-pedir cambio a la batalla

Cursor::Cursor()
{
	fila = 0;
	columna = 0;
}

void Cursor::dibuja()
{//aqui va toda la parte grafica, se activa siempre que se cmabia la posicion del cursor, cuidado que son atributos privados
}

void Cursor::inicializa(int turno)
{//posicionar las coordenadas del cursor en el inicio base segun turno 
	if (turno == 0)// es el turno de los humanos!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{
		filaEstoy = 3;
		columnaEstoy = 1;
		//Una vez que cambie esto deberia pintarse la forma del cursor
	}
	if (turno == 1)// es el turno de los humanos!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{
		filaEstoy = 3;
		columnaEstoy = 7;
		//Una vez que cambie esto deberia pintarse la forma del cursor
	}
}

void Cursor::preguntar_coger(Matriz m, int turno, Cursor cursor)
{
	if (m[cursor.columnaEstoy][cursor.filaEstoy].hay_pieza == 1)//de la matriz que nos han pasado, mediante una funcion de la propia matriz, detecta que hay una pieza en la zona entarra aqui
	{
		if (m[cursor.columnaEstoy][cursor.filaEstoy].bando == turno)
		{
			persona = m[cursor.columnaEstoy][cursor.filaEstoy].personaje;//a la persona del cursor le asigno la persona que hay en la matriz
			//nos copiamos la celda de la matriz en la que estoy para acordarno luego por si hay que retroceder
			filaVengo = filaEstoy;
			columnaVengo = columnaEstoy;
			m[cursor.columnaEstoy][cursor.filaEstoy].personaje.borrar();//para que se borre el perosnaje de la pantalla
		}
	}
}

void Cursor::preguntar_soltar(Matriz m, int turno, Cursor cursor)
{
	if (m[cursor.columnaEstoy][cursor.filaEstoy].hay_pieza == 0)//si la casilla esta vacia
	{
		coger();

	}
}

void Cursor::coger()
{
}

void Cursor::soltar()
{
}
