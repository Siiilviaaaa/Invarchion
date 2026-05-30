#include "gestionArchivos.h"
#include "Juego.h"
#include <iostream>
#include <fstream>

using std::cout, std::cin, std::endl, std::string, std::ofstream, std::ifstream;

void GesionArchivos::guardarPartida(const Juego& j) 
{
	//pedir nombre de la partida
	string nombrePartida;
	cout << "Ingrese el nombre de la partida" << endl;
	cin >> nombrePartida;
	nombrePartida += ".txt";

	//crea el fichero y confirmar que se haya abierto
	ofstream archivo(nombrePartida); 
	if (!archivo.is_open()) {
		cout << "error al abrir el fichero de la partida" << endl;
		return;
	}

	//guardar turno partida actual 
	Turno turnoActual = j.turnoActual;
	archivo << (int)turnoActual;
	archivo << "\n";

	//guardar datos de todos los personajes: tipo, bando, x, y, vida. ej: 2 1 8 7 125 
	for (int i = 0;i < MAX_PERSONAJES;i++) {
		if (j.figuras[i] != nullptr) {
			archivo << j.figuras[i]->return_Tipo() << " ";
			archivo << j.figuras[i]->return_Bando() << " ";
			archivo << j.figuras[i]->return_X() << " ";
			archivo << j.figuras[i]->return_Y() << " ";
			archivo << j.figuras[i]->return_Vida() << " "; //por si en el futuro se cambia a que no se recupera la vida despues de la batalla
			archivo << "\n";
		}
	}

	archivo.close();
	cout << "partida guardada exitosamente" << endl;
}

void GesionArchivos::ejecutarPartidaGuardada(Juego& juego)
{
	string nombrePartidaAbrir;
	cout << "introduzca el nombre de la partida que quiera reanudar" << endl;
	cin >> nombrePartidaAbrir;
	nombrePartidaAbrir += ".txt";

	ifstream archivo(nombrePartidaAbrir);

	if (!archivo.is_open()) {
		cout << "no se encontro el archivo que intenta abrir" << endl;

	}

	//se puede borrar el actual y o bien crear un nuevo, o reemplazar los datos. El inconveniente de lo primero es los memory leaks, y del segundo es que 
	//si algo ocurre durante el reemplazo, te quedas sin ninguna partida. He decidido hacerlo reemplazando porque no creo que pueda gestionar la memoria
	//bien al 100%

	juego.~Juego(); //borra tablero y vector figuras

	int turnoLeido;
	archivo >> turnoLeido;
	cout << "turno leido: " << turnoLeido << endl;
	juego.turnoActual = (Turno)turnoLeido;

	for (int i = 0; i < MAX_PERSONAJES; i++) {
		int tipo, bando, vida;
		double x, y;

		archivo >> tipo;
		archivo >> bando;
		archivo >> x;
		archivo >> y;
		archivo >> vida;
		cout << "guardados datos del personaje " << i << tipo << bando << x << y << vida << endl;

		//metemos las figuras nuevas en el array que borramos antes
		juego.figuras[i] = Personaje::crearPieza((Tipo_figura)tipo, (Bando)bando, x, y);
		juego.figuras[i]->setVida(vida);

		// Las colocamos en el tablero
		juego.ptrTablero->setInfoCasilla((int)y, (int)x, juego.figuras[i]);
	}

}
