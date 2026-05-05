#include "Cursor.h"
#include "Casilla.h"
#include "freeglut.h"
#include <iostream>

//extern MATRIZ_GLOBAL;
//de momento se coge esta
Casilla matriz_global[5][7];//esta realmente es una matriz global externa del main que guarda toda la informacion del juego actualizado

void Cursor::inicializar_tablero(int turno)
{
	if (turno == 0)//turno de los humanos
	{
		fila = 4;
		columna = 0;
		contador_selecciones = 2;
		informacion = nullptr;
	}
	else 
	{
		if (turno == 1)//turno de los aliens
		{
			fila = 4;
			columna = 6;
			contador_selecciones = 2;
			informacion = nullptr;
		}
	}
}

void Cursor::mover_cursor_tablero(unsigned char key,int turno)
{
	//movimiento exclusivo del cursor 
	if (turno == 0)//turno de humanos
	{
		//si presionamos tecla y no estamos en el limite...
		if ((key == 'a') && (columna > 0))
		{
			switch (contador_selecciones)
			{
			case 1:
			{
				if (informacion->personajeEncima->movimientos > 0)
				{
					columna - +1;
					informacion->personajeEncima->movimientos -= 1;
				}
				break;
			}
			case 2:  columna -= 1;
				break;//estamos buscando casilla a coger
			defalut: break;
			}
		}
		if ((key == 'd') && (columna < 6)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (informacion->personajeEncima->movimientos > 0)
				{
					columna +=1;
					informacion->personajeEncima->movimientos -= 1;
				}
				break;
			}
			case 2:  columna += 1;
				break;//estamos buscando casilla a coger
			defalut: break;
			}
		}

		if ((key == 'w') && (fila > 0)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (informacion->personajeEncima->movimientos > 0)
				{
					fila -=1;
					informacion->personajeEncima->movimientos -= 1;
				}
				break;
			}
			case 2:  fila -= 1;
				break;//estamos buscando casilla a coger
			defalut: break;
			}
		}
		if ((key == 's') && (fila < 4)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (informacion->personajeEncima->movimientos > 0)
				{
					fila +=1;
					informacion->personajeEncima->movimientos -= 1;
				}
				break;
			}
			case 2:  fila += 1;
				break;//estamos buscando casilla a coger
			defalut: break;
			}
		}
	}
	if (turno == 1)//turno de aliens
	{
		//si presionamos tecla y no estamos en el limite...
		if ((key == 'j') && (columna > 0))
		{
			switch (contador_selecciones)
			{
			case 1:
			{
				if (informacion->personajeEncima->movimientos > 0)
				{
					columna - +1;
					informacion->personajeEncima->movimientos -= 1;
				}
				break;
			}
			case 2:  columna -= 1;
				break;//estamos buscando casilla a coger
			defalut: break;
			}
		}
		if ((key == 'l') && (columna < 6)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (informacion->personajeEncima->movimientos > 0)
				{
					columna += 1;
					informacion->personajeEncima->movimientos -= 1;
				}
				break;
			}
			case 2:  columna += 1;
				break;//estamos buscando casilla a coger
			defalut: break;
			}
		}

		if ((key == 'i') && (fila > 0)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (informacion->personajeEncima->movimientos > 0)
				{
					fila -= 1;
					informacion->personajeEncima->movimientos -= 1;
				}
				break;
			}
			case 2:  fila -= 1;
				break;//estamos buscando casilla a coger
			defalut: break;
			}
		}
		if ((key == 'k') && (fila < 4)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (informacion->personajeEncima->movimientos > 0)
				{
					fila += 1;
					informacion->personajeEncima->movimientos -= 1;
				}
				break;
			}
			case 2:  fila += 1;
				break;//estamos buscando casilla a coger
			defalut: break;
			}
		}
	}
}

void Cursor::seleccion_personaje_tablero(unsigned char key, int turno)
{
	if (turno == 0)
	{
		if (key == 'q'&& contador_selecciones==2)//si equipo humanos presiona "espacio" por primera vez
		{
			int ok = coger(turno);
			//llamar a la funcion coger que se encarga de verificar si el perosnaje es valido y guardarselo
			if (ok == 1)//significa que ha cogido al personaje y le tenemos guardado
			{
				contador_selecciones -= 1;
			}
			// si coger nos devuelve un ok, le restamos uno a contador_selecciones
			//A PARTIR DE AHORA HAY QUE CONTAR MOVIMIENTOS!
		}
		else
		{
			if (key == 'e' && contador_selecciones == 1)
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
				mover_cursor_tablero(key, turno);
			}
		}
	}
	if (turno == 1)
	{
		if (key == 'u' && contador_selecciones == 2)//si equipo humanos presiona "espacio" por primera vez
		{
			int cogerOK = soltar();
			switch (cogerOK)
			{
			case 0: std::cout << "no tengo nada que soltar" << std::endl;
			case 1:
			{
				std::cout << "habia uno de nosotros- le hemos cogido" << std::endl;
				contador_selecciones -= 1;
			}
			}
			// si coger nos devuelve un ok, le restamos uno a contador_selecciones
			//A PARTIR DE AHORA HAY QUE CONTAR MOVIMIENTOS!
		}
		else
		{
			if (key == 'o' && contador_selecciones == 1)
			{
				int soltarOK=soltar();
				switch (soltarOK)
				{
				case 0: std::cout << "no tengo nada que soltar" << std::endl;
				case 1: std::cout << "casilla libre_nos hemos movido ahi" << std::endl;
				case 2: std::cout << "hay un enemigo, avisamos a batalla" << std::endl;
				}
			}
			else
			{
				mover_cursor_tablero(key, turno);
			}
		}
	}
}

int Cursor::coger(int turno)
{
	InfoCasilla* infoCasillaActual = matriz_global[fila][columna].info;//copiamos el valor de la matriz

	if (infoCasillaActual == nullptr)//comprobar que la casilla tiene informacion-evitar fallos del programa
	{
		return 0;
	}

	if (infoCasillaActual->personajeEncima == nullptr)//comprueba si hay personaje en la casilla o esta libre
	{
		return 0;
	}
	if (infoCasillaActual->personajeEncima->bando == turno)//comprueba que el personaje es de nuestro bando
	{
		informacion = infoCasillaActual;//asignamos informacion
		//guarda la informacion de la casilla, por si hay que eliminarla luego de aqui, no eliminamos pq no sbemos is la va a soltar
		filaAntes = fila;
		columnaAntes = columna;
		return 1;
	}
	return 0;
}

int Cursor::soltar()
{
	if (informacion == nullptr)//si no hemosguardado nada no suleta nada
	{
		return 0;
	}
	if (informacion->personajeEncima == nullptr)//si hay error al guardar y no hay nada, no soltamos nada
	{
		return 0;
	}
	//punteros que modifican directamente
	InfoCasilla* infoAhora = matriz_global[fila][columna].info;
	InfoCasilla* infoAntes = matriz_global[filaAntes][columnaAntes].info;

	if (infoAhora == nullptr || infoAntes == nullptr)//si alguna casilla esta vacia, no soltamos nada
	{
		return 0;
	}

	if (infoAhora->personajeEncima == nullptr)//si esta libre la casilla
	{
		infoAhora->personajeEncima = informacion->personajeEncima;
		infoAntes->personajeEncima = nullptr;//borramos de antes

		informacion = nullptr;

		return 1;
	}

	if (infoAhora->personajeEncima->bando == informacion->personajeEncima->bando)//hay alguien de mi bando
	{
		// No se puede soltar encima de uno de mi equipo
		return 0;
	}

	if (infoAhora->personajeEncima->bando != informacion->personajeEncima->bando)//hay un enemigo
	{
		// Avisamos de que hay que empezar batalla
		return 2;
	}

	return 0;
}