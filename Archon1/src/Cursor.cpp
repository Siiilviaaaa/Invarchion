#include "Cursor.h"
#include "freeglut.h"

void Cursor::inicializar(int turno)
{
	if (turno == 0)//turno de los humanos
	{
		fila = 5;
		columna = 1;
		contador_selecciones = 2;
	}
	if (turno == 0)//turno de los aliens
	{
		fila = 5;
		columna = 7;
		contador_selecciones = 2;
	}
}

void Cursor::dibuja()
{
}

void Cursor::mueve(unsigned char key,int turno)
{
	//movimiento exclusivo del cursor 
	if (turno == 0)//turno de humanos
	{
		//si presionamos tecla y no estamos en el limite...
		if ((key == 'a') && (columna >1)) columna -= 1;
		if ((key == 'd') && (columna <7)) columna += 1;

		if ((key == 's') && (fila < 5)) fila -= 1;
		if ((key == 'w') && (fila > 1)) fila += 1;
	}
	if (turno == 1)//turno de aliens
	{
		if ((key == GLUT_KEY_LEFT) && (columna > 1)) columna -= 1;
		if ((key == GLUT_KEY_RIGHT) && (columna < 7)) columna += 1;

		if ((key ==GLUT_KEY_UP ) && (fila > 1)) fila += 1;
		if ((key == GLUT_KEY_DOWN) && (fila < 5)) fila -= 1;
	}
}

void Cursor::coger()
{
}

void Cursor::soltar()
{
}
