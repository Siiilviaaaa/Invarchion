#pragma once
//declaracion del tablero a partir de las casillas
#include "casilla.h"



//ELENA CREO QUE ESTO VA AQUI, LO DEJO TODO COMENTADO POR SI ACASO, SOY SILVIA ;)
//#include "Personajes.h" //PARA PODER POSICIONAR LAS PIEZAS

class Tablero {
private:
    InfoCasilla datos[5][7]; //para la informacion
    Casilla matriz[5][7]; 
    
    int turno; //por ejemplo 0 para humanos y 1 para aliens


public:
    // Constructor
    Tablero();
    void inicializa();
    const Casilla* getCasilla(int f, int c) const {
        return &matriz[f][c];
    }
    Casilla* casillaModificable(int f, int c) {
        return &matriz[f][c];
    }
    void cambiarTurno() { turno = (turno == 0) ? 1 : 0; }
    int getTurno() const { return turno; }
    //INCIALIZAR POSICIONES PIEZAS
	//void inicializarPiezas();


    //funciones logica del cursor con sofia
    Casilla datos_casilla(int x, int y);
    void vacia_casilla(int x, int y);
    void rellena_casilla(int x, int y, Casilla nueva); //procesar si tiene sentido lo q hace en casilla
    

};
