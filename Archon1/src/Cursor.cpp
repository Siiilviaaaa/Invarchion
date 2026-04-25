#include "Cursor.h"
#include "freeglut.h"

//extern MATRIZ_GLOBAL;

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

void Cursor::mover_cursor(unsigned char key,int turno)
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
void Cursor::mover(unsigned char key, int turno)
{
	if (turno == 0)
	{
		if (key == 'q'&& contador_selecciones==2)//si equipo humanos presiona "espacio" por primera vez
		{
			int ok = coger();
			//llamar a la funcion coger que se encarga de verificar si el perosnaje es valido y guardarselo
			if (ok == 1)//significa que ha cogido al personaje y le tenemos guardado
			{
				contador_selecciones - 1;
			}
			
			// si coger nos devuelve un ok, le restamos uno a contador_selecciones
			//A PARTIR DE AHORA HAY QUE CONTAR MOVIMIENTOS!
		}
		else
		{
			if (key == 'd' && contador_selecciones == 1)
			{
				int siguiente_movimiento = soltar();
				//llamar a la funcion soltar que se encarga de verificar si se suelta perssona o si se manda a batalla
				switch (siguiente_movimiento)
				{
				case 0: //no se puede soltar nada pq somos del mismo equiipo
				case 1: //soltamos y esta vacia
				case 2: //soltamos y entramos en batalla
				}
			}
			else
			{
				mover_cursor(key, turno);
			}
		}
	}
	if (turno == 1)
	{
		if (key == 'l' && contador_selecciones == 2)//si equipo humanos presiona "espacio" por primera vez
		{
			int ok = coger();
			//llamar a la funcion coger que se encarga de verificar si el perosnaje es valido y guardarselo
			if (ok == 1)//significa que ha cogido al personaje y le tenemos guardado
			{
				contador_selecciones - 1;
			}

			// si coger nos devuelve un ok, le restamos uno a contador_selecciones
			//A PARTIR DE AHORA HAY QUE CONTAR MOVIMIENTOS!
		}
		else
		{
			if (key == 'm' && contador_selecciones == 1)
			{

				int siguiente_movimiento = soltar();
				//llamar a la funcion soltar que se encarga de verificar si se suelta perssona o si se manda a batalla
				switch (siguiente_movimiento)
				{
				case 0: //no se puede soltar nada pq somos del mismo equiipo
				case 1: //soltamos y esta vacia
				case 2: //soltamos y entramos en batalla
				}
			}
			else

			{
				mover_cursor(key, turno);
			}
		}
	}
}
int Cursor::coger()
{
	//aqui tengo que consultar con una matriz externa global que este actualizada y lleve la informacion de todas las casillas

}

int Cursor::soltar()
{
}
