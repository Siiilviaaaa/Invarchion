#include "freeglut.h"
#include <iostream>
#include "Cursor.h"
#include "Casilla.h"
#include "tablero.h"
#include "Juego.h"
#include "ETSIDI.h"
#include "Hechizos.h"

void Cursor::inicializar_tablero(int turno)
{
	if (turno == 0)//turno de los humanos
	{
		//inicializar la posicion del cursor en la esquina superior izq
		fila = 8;
		columna = 0;
		contador_selecciones = 2;//para contabilizar las veces que se presiona la tecla de coger
		movimientos_restantes = 0;
		color_r = 0;//color verde para humanos
		color_v = 250;
		color_a = 154;
		insertar_mensaje("HUMANOS");
	}
	else 
	{
		if (turno == 1)//turno de los aliens
		{
			//inicializar la posicion del cursor en la esquina superior dch
			fila = 8;
			columna = 8;
			contador_selecciones = 2;//para contabilizar las veces que se presiona la tecla de coger
			movimientos_restantes = 0;
			color_r = 255;//color rosa para aliens
			color_v = 106;
			color_a = 180;
			insertar_mensaje("ALIENS");
		}
	}
}

void Cursor::mover_humanos(unsigned char key, int turno)
{
	if (turno != 0)//siempre que sea el turno de los humanos
	{
		return;
	}
	//variables qu indican cuanto debe varias la fila o la columna dependiendo de la tecla presionada
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

	movimiento(cambioFila, cambioColumna, "HUMANO",turno);//llamamos a la funcion generalizada para mover
}
void Cursor::mover_aliens(int key, int turno)
{
	if (turno != 1)
	{
		return;
	}
	//variables para indicar si hay que cmabiar fila o columna dependiendo de las teclas 
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

	movimiento(cambioFila, cambioColumna, "ALIEN",turno);//llamamos a la funcion generalizada de movimiento
}
void Cursor::movimiento(int mov_filas, int mov_columnas, const std::string& mensaje, int turno)
{
	//variables que indican la posicion final del cursor tras presionar las teclas (la posicion en la que etsabamos y el cambio agregado por la tecla)
	int fila_final = fila + mov_filas;
	int columna_final = columna + mov_columnas;
	//puntero a la casilla del tablero a la que vamos 
	InfoCasilla* casillaDestino = miTablero.getInfoCasilla(fila_final, columna_final);//para que guarde la casilla actual en cada momento

	if (fila_final < 0 || fila_final > 8 || columna_final < 0 || columna_final > 8)
	{
		//si nos encontramos en el limite del tablero, salimos de la función
		return;
	}
	if (contador_selecciones == 1)//si se selecciona 1 vez hay que ir restando movimientos si se puede
	{
		if (casillaDestino != nullptr && casillaDestino->getPersonaje() != nullptr)//si la casilla guarda informacion correcta de persoanje (para comprobar que lo seleccionado es un persoanje de nuestro bando)
		{
			//puntero al personaje de la casilla destino
			Personaje* personajeDestino = casillaDestino->getPersonaje();

			if (personajeDestino->return_Bando() == turno)//si es de nuestro equipo
			{
				if(personajeSeleccionado->return_Tipo() != VOLADOR)//si no soy un volador, no puedo moverme
				{ 
					insertar_mensaje("Casilla ocupada por un aliado");
					return;
				}
				if (personajeSeleccionado->return_Tipo() == VOLADOR && movimientos_restantes-1 <= 0)//si soy un volador, que cuando me mueva y resten un movimiento, sean 0 los que me queden, no puedo moverme ahi pq no tendre escapatoria
				{
					insertar_mensaje("Casilla ocupada por un aliado");
					return;
				}
				if (!tieneMovimientoPosible(fila_final, columna_final, turno, movimientos_restantes-1))//si n esa casilla no va a tener un camino valido, no puede caer ahi
				{
					insertar_mensaje("Camino bloqueado");
					return;
				}
				//si el personaje no ha netrado en ningun if, es que es un volador que puede seguir circulando por el tablero pq le quedan recorridos validos
			}
			else//Hay un persoanje del otro equipo, entramos directamente en batalla.
			{
				//actualizamos la posicion del cursor
				fila = fila_final;
				columna = columna_final;

				if (personajeSeleccionado != nullptr)//si el personaje seleccionado existe le modificamos la posicion
				{
					personajeSeleccionado->setX(columna);
					personajeSeleccionado->setY(fila);
				}
				//declaramos quien ataca y quien defiende
				atacante = personajeSeleccionado;
				defensor = personajeDestino;
				//restablecemos las variables del cursor
				contador_selecciones = 0;
				movimientos_restantes = 0;
				personajeSeleccionado = nullptr;//quitamos el personaje seleccionado

				if (ptrJuego != nullptr)
				{//si el juego existe, entramos en batalla con esos persoanjes
					ptrJuego->cambiarEscenarioABatalla(atacante, defensor);
				}
			}
		}
	}
	switch (contador_selecciones)
	{
	case 1://se ha pulsado la tecla de coger, hay que ir restando movimientos
		if (movimientos_restantes > 0)
		{
			fila = fila_final;
			columna = columna_final;
			movimientos_restantes--;

			//Actualizar el personaje de forma grafica modificando sus propias coordenadas
			if (personajeSeleccionado != nullptr)
			{
				personajeSeleccionado->setX(columna);
				personajeSeleccionado->setY(fila);
			}

			insertar_mensaje(mensaje + " Movilidad: " +	std::to_string(movimientos_restantes));//indica en cada momento cuantos movs le quedan 
		}
		break;

	case 2://no se ha pulsado la tecla de coger 
		fila = fila_final;
		columna = columna_final;
		break;

	default:
		break;
	}
}

void Cursor::seleccion_personaje_tablero(unsigned char key, int turno)
{
	if (turno == TurnoHumanos)//si somos humanos
	{
		if (key == 'v'&& contador_selecciones==2)//pulsamos v y no hemos cogido antes
		{
			int cogerOK = coger(turno);//llamamos a la funcion coger
			switch (cogerOK)
			{
			case 1://hemos cogido un personaje de nuestro bando
			{
				std::cout << "habia uno de nosotros- le hemos cogido" << std::endl;
				insertar_mensaje("HUMANO Movilidad: " + std::to_string(movimientos_restantes));
				contador_selecciones = 1;//indicamos que la accion de coger la hicimos ya
			}break;
			default: break;
			}
		}
		else
		{
			if (key == 'v' && contador_selecciones == 1)//pulsamos v y ya habiamos cogido, toca soltar
			{
				int soltarOK = soltar(turno);//llamamos a la funcion soltar
				switch (soltarOK)
				{
				case 0: //no se pudo soltar por imposibilidad
					std::cout << "no se ha podido soltar" << std::endl;break;
				case 1://no habia nadie asiq ocupamos esa casilla vacia
					std::cout << "casilla libre_nos hemos movido ahi" << std::endl;
					contador_selecciones = 0;//para no poder volver a entrar ni a soltar ni cogr si no cambia el turno
					movimientos_restantes = 0;//para no poder movernos
				
					if (ptrJuego != nullptr) {
						ptrJuego->cambiarTurno();//cambaimos el turno de la partida
					}

					break;
				default: break;
				}
			}
			//HECHIZO EN TABLERO HUMANO
			else if (key == 'c' && contador_selecciones == 1)
			{
				Personaje* p1 = miTablero.getInfoCasilla(filaAntes, columnaAntes)->getPersonaje(); //OBTENER PERSONAJE SELCCIONADO
				if (p1 != nullptr && p1->return_Tipo() == HECHICERO) {
					Hechicero* mago1 = dynamic_cast<Hechicero*>(p1);
					if (mago1 != nullptr) {
						Hechizo::aplicarCuracionMasiva(turno, mago1, ptrJuego);
						std::cout << "Curacion masiva aplicada. Cambio de turno: " << std::endl;
						insertar_mensaje("HUMANO CURACION MASIVA");
					}
				}
				
			}
			else
			{
				mover_humanos(key, turno);//si no se pulsa la v, se mueve normal 
			}
		}
	}
	if (turno == TurnoAliens)//siendo el turno de aliens
	{
		if (key == 'm' && contador_selecciones == 2)//si se pulsa m y no hemos cogido 
		{
			int cogerOK = coger(turno);//llamamos a coger
			switch (cogerOK)
			{
			case 1://hemos cogido a uno de nuetsro equipo
			{
				std::cout << "habia uno de nosotros- le hemos cogido" << std::endl;
				insertar_mensaje("ALIEN Movilidad: " + std::to_string(movimientos_restantes));
				contador_selecciones = 1;
			}break;
			default:  
				break;
			}
		}
		else
		{
			if (key == 'm' && contador_selecciones == 1)//si se pulsa m y ya habiamos cogido antes
			{
				int soltarOK=soltar(turno);//llamamos a soltar
				switch (soltarOK)
				{
				case 0: std::cout << "no se ha podido soltar" << std::endl; break;//imposibilidad de soltar
				case 1://casilla vacia asiq se ocupa
				{ 
					std::cout << "casilla libre_nos hemos movido ahi" << std::endl; 
					contador_selecciones = 0;
					movimientos_restantes = 0;
					
					if (ptrJuego != nullptr) {//avisamos a que se cambie de turno
						ptrJuego->cambiarTurno();
					}
					break; 
				}
				default: break;
				}
			}
			//HECHIZO EN TABLERO ALIENS
			else if (key == 'n' && contador_selecciones == 1)
			{
				Personaje* p2 = miTablero.getInfoCasilla(filaAntes, columnaAntes)->getPersonaje(); //OBTENER PERSONAJE SELCCIONADO
				if (p2 != nullptr && p2->return_Tipo() == HECHICERO) {
					Hechicero* mago2 = dynamic_cast<Hechicero*>(p2);
					if (mago2 != nullptr) {
						Hechizo::aplicarCuracionMasiva(turno, mago2, ptrJuego);
						std::cout << "Curacion masiva aplicada. Cambio de turno: " << std::endl;
						insertar_mensaje("ALIENS CURACION MASIVA");
					}
				}
				
			}
			else
			{
				mover_aliens(key,turno);//si no se pulso la m, se juega con las otras teclas normal 
			}
		}
	}
}
bool Cursor::tieneMovimientoPosible(int filaOrigen, int columnaOrigen, int turno, int movimientos) const
{
	for (int diferencia_filas = -movimientos; diferencia_filas <=movimientos; diferencia_filas++)//para evaluar la cantidad de filas a las que puede llegar con esos movimientos 
	{
		for (int diferencia_columnas=-movimientos; diferencia_columnas<=movimientos;diferencia_columnas++)//para evaluar la cantidad de columans a las que puede llegar con esos movimientos
		{
			int movimientos_requeridos = abs(diferencia_filas) + abs(diferencia_columnas);//calcula para la casilla que se esta evaluando cuantos moviminetos necesitaria
			if (movimientos_requeridos == 0 || movimientos_requeridos > movimientos)continue;//si son 0 o mas de los qu eme puedo permitir, siguiente iteracion


			//las variables que deciden que casilla evaluar en cada movimiento, desde el origen en el que se encuentra 
			int nuevaFila = filaOrigen + diferencia_filas;
			int nuevaColumna = columnaOrigen + diferencia_columnas;

			if (nuevaFila < 0 || nuevaFila > 8 || nuevaColumna < 0 || nuevaColumna > 8)//si no nos encontramos en los limites del tablero
			{
				continue;//como esa casilla no es valida, salta directo a la siguiente iteracion
			}
			//puntero a una casilla vecina que se evlaua en esta iteracion
			InfoCasilla* casillaVecina = miTablero.getInfoCasilla(nuevaFila, nuevaColumna);

			if (casillaVecina == nullptr)//la casilla no guarda informacion
			{
				continue;//como esa casilla no es valida, salta directo a la siguiente iteracion
			}
			//piuntero perosnaje de dicha casilla vecina 
			Personaje* personajeVecino = casillaVecina->getPersonaje();

			if (personajeVecino == nullptr)//Casilla vacia, hay un camino posible de alternativa de juego 
			{
				return true;
			}

			if (personajeVecino->return_Bando() != turno)//Casilla con enemigo, hay una alternativa de juego 
				return true;
		}
	}
	//Si no hay casillas vacias o para entrar a batalla, no puede moverse, debera seleccionar otro personaje
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
		if (infoCasillaActual->personajeEncima->tipo == VOLADOR)
		{
			//verificamos que EXISTE alguna casilla posible a la que el volador con sus moivimientos sea capaz de llegar 
			if (!tieneMovimientoPosible(fila,columna,turno, infoCasillaActual->personajeEncima->movimientos))//le pasamos los movimientos del personaje volador
			{//si no puede, no se podra seleccionar nunca
				insertar_mensaje("Camino bloqueado");
				return 0;
			}
		}
		else
		{
		//aqui se verifica solo las casillas de los alrededores, puesto que los perosanjes SOLO andan (exceptuando el volador)
			if (!tieneMovimientoPosible(fila,columna,turno,1))//le pasamos solo 1 movimiento, pq auqnue el perosnaj etenga mas, como solo puede andar se evalua SOLO el movimiento inmediato que va a realizar 
			{//verificacmos que no sea un movimiento imposible del que no se pueda salir
				insertar_mensaje("Camino bloqueado");
				return 0;
			}
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
		Personaje* personajeMovido = casillaAnterior->personajeEncima;

		personajeMovido->setX(columna);
		personajeMovido->setY(fila);

		casillaActual->personajeEncima = personajeMovido;
		casillaAnterior->personajeEncima = nullptr;


		personajeSeleccionado = nullptr;

		return 1;
	}
	casillaAnterior->setPersonaje(nullptr); //no estaba borrando bien la posicion del personaje antes
	return 2;
}

