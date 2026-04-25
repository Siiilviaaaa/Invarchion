#include "Cursor.h"

void Cursor::inicializar(int turno)
{
	if (turno == 0)//turno de los humanos
	{
		fila = 5;
		columna = 1;
	}
	if (turno == 0)//turno de los aliens
	{
		fila = 5;
		columna = 7;
	}
}

void Cursor::dibuja()
{
}

void Cursor::mueve(unsigned char key)
{
}

void Cursor::coger()
{
}

void Cursor::soltar()
{
}
