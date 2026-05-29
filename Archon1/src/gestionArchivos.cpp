#include "gestionArchivos.h"
#include "Juego.h"
#include <iostream>
#include <fstream>

using std::cout, std::cin, std::endl, std::string, std::ofstream;

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
			archivo << j.figuras[i]->return_Vida() << " ";
			archivo << "\n";
		}
	}

	archivo.close();
	cout << "partida guardada exitosamente" << endl;
}
