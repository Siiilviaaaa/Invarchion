#include "Cursor.h"
#include "Casilla.h"
#include "freeglut.h"

//extern MATRIZ_GLOBAL;
//de momento se coge esta
Casilla matriz_global[5][7];//esta realmente es una matriz global externa del main que guarda toda la informacion del juego actualizado

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
			int ok = coger(turno);
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
				case 0: //no se puede soltar nada pq somos del mismo equiipo- eliminar personaje del CURSOR
				case 1: //soltamos y esta vacia- actualizamos la matriz_global
				case 2: //soltamos y entramos en batalla- a la espera de ver quien ganaa
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
			int ok = coger(turno);
			//llamar a la funcion coger que se encarga de verificar si el perosnaje es valido y guardarselo
			if (ok == 1)//significa que ha cogido al personaje y le tenemos guardado
			{
				contador_selecciones - 1;
			}
			else
			{
				mover_cursor(key, turno);//PERO ESTA YA NO ES LA MISMA KEY?!!?!??!??
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
				case 0: //no se puede soltar nada pq somos del mismo equiipo- eliminar personaje del CURSOR
				case 1: //soltamos y esta vacia- actualizamos la matriz_global
				case 2: //soltamos y entramos en batalla- a la espera de ver quien ganaa
				}
			}
			else
			{
				mover_cursor(key, turno);
			}
		}
	}
}
int Cursor::coger(int turno)
{
	//aqui tengo que consultar con una matriz externa global que este actualizada y lleve la informacion de todas las casillas
	//preuntar si el bando de la matriz es el mismo que nuestro turno
		//si lo es: cogerlo 
	if (matriz_global[columna][fila].info->personajeEncima->bando == turno)//perosnaje elegido de nuetsro bando
	{
		informacion->personajeEncima = matriz_global[columna][fila].info->personajeEncima;//nos copiamos el personaje
		return 1;
	}
	else return 0;//para avisar a la funcion de mover 
}

int Cursor::soltar()
{

}
