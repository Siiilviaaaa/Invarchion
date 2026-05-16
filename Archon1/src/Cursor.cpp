#include "Cursor.h"
#include "Casilla.h"
#include "freeglut.h"
#include "tablero.h"
#include <iostream>

void Cursor::inicializar_tablero(int turno)
{
	if (turno == 0)//turno de los humanos
	{
		fila = 4;
		columna = 0;
		contador_selecciones = 2;
		movimientos_restantes = 0;
	}
	else 
	{
		if (turno == 1)//turno de los aliens
		{
			fila = 4;
			columna = 6;
			contador_selecciones = 2;
			movimientos_restantes = 0;
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
				if (movimientos_restantes > 0)
				{
					columna -=1;
					movimientos_restantes -= 1;
				}
				break;
			}
			case 2:  columna -= 1;
				break;//estamos buscando casilla a coger
			default: break;
			}
		}
		if ((key == 'd') && (columna < 6)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (movimientos_restantes > 0)
				{
					columna +=1;
					movimientos_restantes -= 1;
				}
				break;
			}
			case 2:  columna += 1;
				break;//estamos buscando casilla a coger
			default: break;
			}
		}

		if ((key == 'w') && (fila > 0)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (movimientos_restantes > 0)
				{
					fila -=1;
					movimientos_restantes -= 1;
				}
				break;
			}
			case 2:  fila -= 1;
				break;//estamos buscando casilla a coger
			default: break;
			}
		}
		if ((key == 's') && (fila < 4)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (movimientos_restantes > 0)
				{
					fila +=1;
					movimientos_restantes -= 1;
					//print te qyuedan x movimientos DIEGOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
				}
				break;
			}
			case 2:  fila += 1;
				break;//estamos buscando casilla a coger
			default: break;
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
				if (movimientos_restantes > 0)
				{
					columna -=1;
					movimientos_restantes -= 1;
				}
				break;
			}
			case 2:  columna -= 1;
				break;//estamos buscando casilla a coger
			default: break;
			}
		}
		if ((key == 'l') && (columna < 6)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (movimientos_restantes > 0)
				{
					columna += 1;
					movimientos_restantes -= 1;
				}
				break;
			}
			case 2:  columna += 1;
				break;//estamos buscando casilla a coger
			default: break;
			}
		}

		if ((key == 'i') && (fila > 0)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (movimientos_restantes > 0)
				{
					fila -= 1;
					movimientos_restantes -= 1;
				}
				break;
			}
			case 2:  fila -= 1;
				break;//estamos buscando casilla a coger
			default: break;
			}
		}
		if ((key == 'k') && (fila < 4)) {
			switch (contador_selecciones)
			{
			case 1:
			{
				if (movimientos_restantes > 0)
				{
					fila += 1;
					movimientos_restantes -= 1;
				}
				break;
			}
			case 2:  fila += 1;
				break;//estamos buscando casilla a coger
			default: break;
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
			int cogerOK = coger(turno);
			switch (cogerOK)
			{
			case 0: std::cout << "no se ha podido coger" << std::endl;break;
			case 1:
			{
				std::cout << "habia uno de nosotros- le hemos cogido" << std::endl;
				contador_selecciones -= 1;
			}break;
			}
			 //si coger nos devuelve un ok, le restamos uno a contador_selecciones
			//A PARTIR DE AHORA HAY QUE CONTAR MOVIMIENTOS!
		}
		else
		{
			if (key == 'e' && contador_selecciones == 1)
			{
				int soltarOK = soltar();
				switch (soltarOK)
				{
				case 0: std::cout << "no se ha podido soltar" << std::endl;break;
				case 1: std::cout << "casilla libre_nos hemos movido ahi" << std::endl;break;
				case 2: std::cout << "hay un enemigo, avisamos a batalla" << std::endl; break;
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
			int cogerOK = coger(turno);
			switch (cogerOK)
			{
			case 0: std::cout << "no se ha podido coger" << std::endl; break;
			case 1:
			{
				std::cout << "habia uno de nosotros- le hemos cogido" << std::endl;
				contador_selecciones -= 1;
			}break;
			}
			///// si coger nos devuelve un ok, le restamos uno a contador_selecciones
			//A PARTIR DE AHORA HAY QUE CONTAR MOVIMIENTOS!
		}
		else
		{
			if (key == 'o' && contador_selecciones == 1)
			{
				int soltarOK=soltar();
				switch (soltarOK)
				{
				case 0: std::cout << "no se ha podido soltar" << std::endl; break;
				case 1: { 
					std::cout << "casilla libre_nos hemos movido ahi" << std::endl; 
					contador_selecciones -= 1;//le restamos ara que no pueda entrar en nada mas
					//AVISAR AL CAMMBIO DE TURNO 
					break; 
				}
				case 2: std::cout << "hay un enemigo, avisamos a batalla" << std::endl; break;//meter una variable externa y moifica el main
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
	//crear variable que llame a elena: tablero.h get y modificar casilla
	const InfoCasilla* infoCasillaActual = miTablero.getInfoCasilla(fila,columna);//copiamos el valor de la matriz global

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
		informacion = *infoCasillaActual;//copia la informacion del puntero que apunta al tablero original
		movimientos_restantes = infoCasillaActual->personajeEncima->movimientos;//copiamos los movimientos
		//guarda la informacion de la casilla, por si hay que eliminarla luego de aqui, no eliminamos pq no sbemos is la va a soltar
		filaAntes = fila;
		columnaAntes = columna;
		return 1;
	}
	return 0;
}

int Cursor::soltar()
{
	
	if (informacion.personajeEncima == nullptr)//si no hemos guardado ningun perosnaje no lo podremos soltar nunca
	{
		return 0;
	}
	//punteros que modifican directamente
	InfoCasilla* infoAhora = miTablero.getInfoCasilla(fila,columna);//le retorna lo qu ehay en la casilla que queremos soltar

	if (infoAhora == nullptr)//si la casilla esta vacia, no soltamos nada
	{
		return 0;
	}

	if (infoAhora->personajeEncima == nullptr)//si esta libre la casilla
	{
		miTablero.setInfoCasilla(fila, columna, informacion.personajeEncima);//le hemos dicho a la casilla del tablero que se rellene con lo que teniamos guardado
		miTablero.setInfoCasilla(filaAntes, columnaAntes, nullptr);
		return 1;
	}

	if (infoAhora->personajeEncima->bando == informacion.personajeEncima->bando)//hay alguien de mi bando
	{
		// No se puede soltar encima de uno de mi equipo
		return 0;
	}

	if (infoAhora->personajeEncima->bando != informacion.personajeEncima->bando)//hay un enemigo
	{
		// Avisamos de que hay que empezar batalla
		return 2;
	}

	return 0;
}