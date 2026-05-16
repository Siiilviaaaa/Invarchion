#include "freeglut.h"
#include <iostream>
#include "Cursor.h"
#include "Casilla.h"
#include "tablero.h"
#include "Juego.h"
#include "ETSIDI.h"

void Cursor::inicializar_tablero(int turno)
{
	if (turno == 0)//turno de los humanos
	{
		fila = 4;
		columna = 0;
		contador_selecciones = 2;
		movimientos_restantes = 0;
		color_r = 0;//color verde para humanos
		color_v = 250;
		color_a = 154;
	}
	else 
	{
		if (turno == 1)//turno de los aliens
		{
			fila = 4;
			columna = 6;
			contador_selecciones = 2;
			movimientos_restantes = 0;
			color_r = 255;//color galaxia para alines
			color_v = 106;
			color_a = 180;
			
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
				if (movimientos_restantes > 0)
				{
					columna -= 1;
					movimientos_restantes -= 1;
					insertar_mensaje("Humano, te quedan " + std::to_string(movimientos_restantes)+ " movimientos");
				}
				break;

			case 2:  
				columna -= 1;
				insertar_mensaje("Selecciona un personaje");
				break;

			default: break;
			}
		}
		if ((key == 'd') && (columna < 6)) {
			switch (contador_selecciones)
			{
			case 1:
				if (movimientos_restantes > 0)
				{
					columna += 1;
					movimientos_restantes -= 1;
					insertar_mensaje("Humano, te quedan " + std::to_string(movimientos_restantes) + " movimientos");
				}
				break;
			
			case 2:  columna += 1;
				insertar_mensaje("Selecciona un personaje");
				break;

			default: break;
			}
		}

		if ((key == 's') && (fila > 0)) {
			switch (contador_selecciones)
			{
			case 1:			
				if (movimientos_restantes > 0)
				{
					fila -=1;
					movimientos_restantes -= 1;
					insertar_mensaje("Humano, te quedan " + std::to_string(movimientos_restantes) + " movimientos");
				}
				break;
			
			case 2:  fila -= 1;
				insertar_mensaje("Selecciona un personaje");
				break;

			default: break;
			}
		}
		if ((key == 'w') && (fila < 4)) {
			switch (contador_selecciones)
			{
			case 1:
				if (movimientos_restantes > 0)
				{
					fila += 1;
					movimientos_restantes -= 1;
					insertar_mensaje("Humano, te quedan " + std::to_string(movimientos_restantes) + " movimientos");
				} 
				break;

			case 2:  fila += 1;
				insertar_mensaje("Selecciona un personaje");
				break;

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
				if (movimientos_restantes > 0)
				{
					columna -=1;
					movimientos_restantes -= 1;
					insertar_mensaje("Alien, te quedan " + std::to_string(movimientos_restantes) + " movimientos");
				}
				break;
			
			case 2:  columna -= 1;
				insertar_mensaje("Selecciona un personaje");
				break;

			default: break;
			}
		}
		if ((key == 'l') && (columna < 6)) {
			switch (contador_selecciones)
			{
			case 1:
				if (movimientos_restantes > 0)
				{
					columna += 1;
					movimientos_restantes -= 1;
					insertar_mensaje("Alien, te quedan " + std::to_string(movimientos_restantes) + " movimientos");
				}
				break;
	
			case 2:  columna += 1;
				insertar_mensaje("Selecciona un personaje");
				break;

			default: break;
			}
		}

		if ((key == 'k') && (fila > 0)) {
			switch (contador_selecciones)
			{
			case 1:
			
				if (movimientos_restantes > 0)
				{
					fila -= 1;
					movimientos_restantes -= 1;
					insertar_mensaje("Alien, te quedan " + std::to_string(movimientos_restantes) + " movimientos");
				}
				break;
			
			case 2:  fila -= 1;
				insertar_mensaje("Selecciona un personaje");
				break;

			default: break;
			}
		}
		if ((key == 'i') && (fila < 4)) {
			switch (contador_selecciones)
			{
			case 1:
			
				if (movimientos_restantes > 0)
				{
					fila += 1;
					movimientos_restantes -= 1;
					insertar_mensaje("Alien, te quedan " + std::to_string(movimientos_restantes) + " movimientos");
				}
				break;
	
			case 2:  fila += 1;
				insertar_mensaje("Selecciona un personaje");
				break;

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
			case 1:
			{
				std::cout << "habia uno de nosotros- le hemos cogido" << std::endl;
				insertar_mensaje("Personaje seleccionado. Movimientos limitados a: " + std::to_string(movimientos_restantes));
				contador_selecciones = 1;
			}break;
			default: break;
			
			}
		}
		else
		{
			if (key == 'e' && contador_selecciones == 1)
			{
				int soltarOK = soltar(turno);
				switch (soltarOK)
				{
				case 0: 
					std::cout << "no se ha podido soltar" << std::endl;break;
				case 1:
					std::cout << "casilla libre_nos hemos movido ahi" << std::endl;
					contador_selecciones = 0;//para no poder volver a entrar ni a soltar ni cogr si no cambia el turno
					movimientos_restantes = 0;//para no poder movernos
				
					if (ptrJuego != nullptr) {
						ptrJuego->cambiarTurno();//cambaimos el turno de la partida
					}

					break;
				case 2:
					std::cout << "hay un enemigo, avisamos a batalla" << std::endl;
					contador_selecciones = 0;
					movimientos_restantes = 0;
					//llamada a batalla pasandole mi personaje y el personaje actual de la casilla del tablero
					break;
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
			insertar_mensaje("U num de selecciones: " + std::to_string(contador_selecciones));//PRUEBAS
			switch (cogerOK)
			{
			case 1:
			{
				std::cout << "habia uno de nosotros- le hemos cogido" << std::endl;
				insertar_mensaje("SELECCIONASTE Movimientos: " + std::to_string(movimientos_restantes));
				contador_selecciones = 1;
			}break;
			default:  
				break;
			}
		}
		else
		{
			if (key == 'o' && contador_selecciones == 1)
			{
				int soltarOK=soltar(turno);
				switch (soltarOK)
				{
				case 0: std::cout << "no se ha podido soltar" << std::endl; break;
				case 1: { 
					std::cout << "casilla libre_nos hemos movido ahi" << std::endl; 
					contador_selecciones = 0;
					movimientos_restantes = 0;
					
					if (ptrJuego != nullptr) {
						ptrJuego->cambiarTurno();
					}

					break; 
				}
				case 2: std::cout << "hay un enemigo, avisamos a batalla" << std::endl;
					contador_selecciones = 0;
					movimientos_restantes = 0;
					//llamada a batalla pasandole mi personaje y el personaje actual de la casilla del tablero
					break;
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
		std::cout << "CASILLA VACIA" << std::endl;
		return 0;
	}
	if (infoCasillaActual->personajeEncima == nullptr)//comprueba si hay personaje en la casilla o esta libre
	{
		std::cout << "CASILLA SIN PERSONAJE" << std::endl;
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

int Cursor::soltar(int turno)
{
	InfoCasilla* casillaAnterior = miTablero.getInfoCasilla(filaAntes, columnaAntes);
	InfoCasilla* casillaActual = miTablero.getInfoCasilla(fila, columna);

	if (casillaAnterior == nullptr || casillaActual == nullptr)
	{
		return 0;
	}

	if (casillaAnterior->personajeEncima == nullptr)
	{
		return 0;
	}

	// CASO 1: la casilla actual está vacía
	if (casillaActual->personajeEncima == nullptr)
	{
		//modifcamos la posicion del perosnaje para q dibuje (TELETRANSPORTE) donde debe
		casillaAnterior->personajeEncima->setX(filaAntes);
		casillaAnterior->personajeEncima->setY(columnaAntes);

		casillaActual->personajeEncima = casillaAnterior->personajeEncima;
		casillaAnterior->personajeEncima = nullptr;
		return 1;
	}

	// CASO 2: la casilla actual tiene un personaje de mi mismo bando
	if (casillaActual->personajeEncima->bando == turno)
	{
		return 0;
	}

	// CASO 3: la casilla actual tiene un personaje enemigo
	if (casillaActual->personajeEncima->bando != turno)
	{
		//copiamos en perosnaje mio el de la casilla anterior
		atacante = casillaAnterior->personajeEncima;
		//copiamos en prsonaje batalla el de la casilla nueva
		defensor = casillaActual->personajeEncima;
		//y eso son los que se pasan a la batlla, esos punteros

		return 2;
	}

	return 0;
}