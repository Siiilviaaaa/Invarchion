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
		insertar_mensaje("Turno HUMANOS");
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
			insertar_mensaje("Turno ALIENS");
		}
	}
}

void Cursor::mover_humanos(unsigned char key, int turno)
{
	if (turno != 0)
	{
		return;
	}

	int cambioFila = 0;
	int cambioColumna = 0;

	switch (key)
	{
	case 'a':
		cambioColumna = -1;
		break;

	case 'd':
		cambioColumna = 1;
		break;

	case 's':
		cambioFila = -1;
		break;

	case 'w':
		cambioFila = 1;
		break;

	default:
		return;
	}

	movimiento(cambioFila, cambioColumna, "Humano",turno);
}
void Cursor::mover_aliens(int key, int turno)
{
	if (turno != 1)
	{
		return;
	}

	int cambioFila = 0;
	int cambioColumna = 0;

	switch (key)
	{
	case GLUT_KEY_LEFT:
		cambioColumna = -1;
		break;

	case GLUT_KEY_RIGHT:
		cambioColumna = 1;
		break;

	case GLUT_KEY_DOWN:
		cambioFila = -1;
		break;

	case GLUT_KEY_UP:
		cambioFila = 1;
		break;

	default:
		return;
	}

	movimiento(cambioFila, cambioColumna, "Alien",turno);
}
void Cursor::movimiento(int mov_filas, int mov_columnas, const std::string& mensaje, int turno)
{
	int desplazamiento_fila = fila + mov_filas;
	int desplazamiento_columna = columna + mov_columnas;
	InfoCasilla* casillaDestino = miTablero.getInfoCasilla(desplazamiento_fila, desplazamiento_columna);//para que guarde la casilla actual en cada momento

	if (desplazamiento_fila < 0 || desplazamiento_fila > 4 || desplazamiento_columna < 0 || desplazamiento_columna > 6)
	{
		//si nos encontramos en el limite del tablero, salimos de la función
		return;
	}
	if (contador_selecciones == 1)
	{
		if (casillaDestino != nullptr && casillaDestino->getPersonaje() != nullptr)
		{
			Personaje* personajeDestino = casillaDestino->getPersonaje();

			//hay un personaje de nuestro bando, no podemos saltarle
			if (personajeDestino->return_Bando() == turno)
			{
				insertar_mensaje("No puedes pasar por una casilla ocupada por un aliado");
				return;
			}

			//Hay un persoanje del otro equipo, entramos directamente en batalla.
			if (personajeDestino->return_Bando() != turno)
			{
				fila = desplazamiento_fila;
				columna = desplazamiento_columna;

				if (personajeSeleccionado != nullptr)
				{
					personajeSeleccionado->setX(columna);
					personajeSeleccionado->setY(fila);
				}

				atacante = personajeSeleccionado;
				defensor = personajeDestino;

				contador_selecciones = 0;
				movimientos_restantes = 0;
				personajeSeleccionado = nullptr;

				if (ptrJuego != nullptr)
				{
					ptrJuego->cambiarEscenarioABatalla(atacante, defensor);
				}

				return;
			}
		}
	}
	switch (contador_selecciones)
	{
	case 1:
		if (movimientos_restantes > 0)
		{
			fila = desplazamiento_fila;
			columna = desplazamiento_columna;
			movimientos_restantes--;

			// Actualizar visualmente el personaje en cada movimiento
			if (personajeSeleccionado != nullptr)
			{
				personajeSeleccionado->setX(columna);
				personajeSeleccionado->setY(fila);
			}

			insertar_mensaje(
				mensaje + ", te quedan " +
				std::to_string(movimientos_restantes) +
				" movimientos"
			);
		}
		break;

	case 2:
		fila = desplazamiento_fila;
		columna = desplazamiento_columna;
		insertar_mensaje("Selecciona un personaje");
		break;

	default:
		break;
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
			if (key == 'q' && contador_selecciones == 1)
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
					ptrJuego->cambiarEscenarioABatalla(atacante, defensor);
					//llamada a batalla pasandole mi personaje y el personaje actual de la casilla del tablero
					break;
				case 3:
					std::cout << "Sois del mismo equipo, movimiento extra por compasión" << std::endl;
					insertar_mensaje("Movimiento Extra 'por compasion'");
					movimientos_restantes = 1;
				}
			}
			//HECHIZO EN TABLERO HUMANO
			else if (key == 'c' && contador_selecciones == 1)
			{
				Personaje* mago = miTablero.getInfoCasilla(filaAntes, columnaAntes)->getPersonaje();
				aplicarCuracionMasiva(turno, mago);
				std::cout << "Curacion masiva aplicada. Cambio de turno: " << std::endl;
			}
			else
			{
				mover_humanos(key, turno);
			}
		}
	}
	if (turno == 1)
	{
		if (key == 'm' && contador_selecciones == 2)//si equipo humanos presiona "espacio" por primera vez
		{
			int cogerOK = coger(turno);
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
			if (key == 'm' && contador_selecciones == 1)
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
					ptrJuego->cambiarEscenarioABatalla(atacante, defensor);
					//llamada a batalla pasandole mi personaje y el personaje actual de la casilla del tablero
					break;
				}
			}
			//HECHIZO EN TABLERO ALIENS
			else if (key == 'n' && contador_selecciones == 1)
			{
				Personaje* mago = miTablero.getInfoCasilla(filaAntes, columnaAntes)->getPersonaje();
				aplicarCuracionMasiva(turno, mago);
				std::cout << "Curacion masiva aplicada. Cambio de turno: " << std::endl;
			}
			else
			{
				mover_aliens(key,turno);
			}
		}
	}
}
bool Cursor::tieneMovimientoPosible(int turno)
{
	int direcciones[4][2] = {
		{ 1, 0 },   // arriba
		{ -1, 0 },  // abajo
		{ 0, 1 },   // derecha
		{ 0, -1 }   // izquierda
	};

	for (int i = 0; i < 4; i++)
	{
		int nuevaFila = fila + direcciones[i][0];
		int nuevaColumna = columna + direcciones[i][1];

		if (nuevaFila < 0 || nuevaFila > 4 || nuevaColumna < 0 || nuevaColumna > 6)
		{
			continue;
		}

		InfoCasilla* casillaVecina = miTablero.getInfoCasilla(nuevaFila, nuevaColumna);

		if (casillaVecina == nullptr)
		{
			continue;
		}

		Personaje* personajeVecino = casillaVecina->getPersonaje();

		// Si la casilla está vacía, sí puede moverse
		if (personajeVecino == nullptr)
		{
			return true;
		}

		// Si hay enemigo, también puede moverse porque entraría en batalla
		if (personajeVecino->return_Bando() != turno)
		{
			return true;
		}
	}

	// Si todas las casillas válidas están ocupadas por aliados o son bordes, no puede moverse
	return false;
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
	if (infoCasillaActual->personajeEncima->return_Bando() == turno)//comprueba que el personaje es de nuestro bando
	{
		if (!tieneMovimientoPosible(turno))//verificacmos que no sea un movimiento imposible del que no se pueda salir
		{
			insertar_mensaje("Este personaje no tiene por donde escapar...");
			return 0;
		}

		informacion = *infoCasillaActual;//copia la informacion del puntero que apunta al tablero original
		movimientos_restantes = infoCasillaActual->personajeEncima->movimientos;//copiamos los movimientos
		//guarda la informacion de la casilla, por si hay que eliminarla luego de aqui, no eliminamos pq no sbemos is la va a soltar
		personajeSeleccionado = infoCasillaActual->personajeEncima;
		filaAntes = fila;
		columnaAntes = columna;
		
		InfoCasilla* casillaOrigen = miTablero.getInfoCasilla(filaAntes, columnaAntes);

		std::cout << "inicialmente personaje en:" << infoCasillaActual->personajeEncima->x <<"," << infoCasillaActual->personajeEncima->y;
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

	if (casillaAnterior->personajeEncima == nullptr) //esto ya lo tienes en la funcion coger
	{
		return 0;
	}

	// CASO 1: la casilla actual está vacía
	if (casillaActual->personajeEncima == nullptr)
	{
		//modifcamos la posicion del perosnaje para q dibuje (TELETRANSPORTE) donde debe
	/*	casillaAnterior->personajeEncima->setX(columna);
		casillaAnterior->personajeEncima->setY(fila);
		std::cout << "teoricamente personaje en:" << casillaAnterior->personajeEncima->x <<"," <<casillaAnterior->personajeEncima->y;
		casillaActual->personajeEncima = casillaAnterior->personajeEncima;
		casillaAnterior->personajeEncima = nullptr;*/

		Personaje* personajeMovido = casillaAnterior->personajeEncima;

		personajeMovido->setX(columna);
		personajeMovido->setY(fila);

		casillaActual->personajeEncima = personajeMovido;
		casillaAnterior->personajeEncima = nullptr;

		personajeSeleccionado = nullptr;

		return 1;
	}

	// CASO 2: la casilla actual tiene un personaje de mi mismo bando
	if (casillaActual->personajeEncima->bando == turno)
	{
		return 3;
	}

	// CASO 3: la casilla actual tiene un personaje enemigo
	if (casillaActual->personajeEncima->bando != turno)
	{
		//copiamos en perosnaje mio el de la casilla anterior
		atacante = casillaAnterior->personajeEncima;
		//copiamos en prsonaje batalla el de la casilla nueva
		defensor = casillaActual->personajeEncima;
		//y eso son los que se pasan a la batlla, esos punteros
		std::cout << "Atacante: " << atacante->return_Tipo() << " Defensor: " << defensor->return_Tipo() << std::endl;
		return 2;
	}

	return 0;
}

void Cursor::aplicarCuracionMasiva(int turno, Personaje* mago)
{
	if (mago != nullptr && mago->return_Tipo() == HECHICERO) {
		if (mago->return_HechizosRestantes() > 0) {

			//RECORREMOS LOS PERSONAJES BUSCANDO ALIADOS
			for (int i = 0; i < 20; i++) {
				Personaje* aliado = ptrJuego->getPersonaje(i);
				if (aliado != nullptr && aliado->return_Bando() == turno && aliado->return_Vida() > 0) {

					//CURAMOS UN TERCIO DE LA VIDA
					int cura = aliado->return_VidaMax() / 3;
					int nuevaVida = aliado->return_Vida() + cura;

					//SIN SUPERAR EL MAXIMO
					if (nuevaVida > aliado->return_VidaMax()) {
						nuevaVida = aliado->return_VidaMax();
					}
					aliado->setVida(nuevaVida);
				}
			}
			mago->usarHechizo();
			insertar_mensaje("Curacion masiva! Turno finalizado.");

			//RESET CURSOR Y CAMBIO DE TURNO
			contador_selecciones = 0;
			movimientos_restantes = 0;
			if (ptrJuego != nullptr) ptrJuego->cambiarTurno();

		}
	}
}