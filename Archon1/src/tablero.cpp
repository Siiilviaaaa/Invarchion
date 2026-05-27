#include <vector>
#include "tablero.h"
#include "freeglut.h"
#include "Juego.h"
#include "ETSIDI.h"

//declaracion matriz, constructor y funciones
int matrizArchon[5][7] = {
    {0, 1, 2, 2, 2, 0, 1}, // Fila 0 (Superior)
    {1, 2, 1, 2, 0, 2, 0}, // Fila 1
    {0, 2, 2, 2, 2, 2, 1}, // Fila 2
    {1, 2, 0, 2, 1, 2, 0}, // Fila 3
    {0, 1, 2, 2, 2, 0, 1}, // Fila 4 (Cruz Central)

};

Tablero::Tablero() {
  
    inicializa();//llamamos a q se inicialice la casilla
}

void Tablero::inicializa() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            Tipocasilla tipo;
            int valor = matrizArchon[i][j];
            switch (valor) {
            case 0: tipo = negra; break;
            case 1: tipo = blanca; break;
            case 2: tipo = lila; break;
            default: tipo = blanca;
            }
            datos[i][j] = InfoCasilla(tipo);
            matriz[i][j] = Casilla(i, j, &datos[i][j]);
                        
        }
    }
}

int Tablero::getTurno(Juego* juego) const
{
   if (juego != nullptr) {
       return juego->getTurno();
   }
   return 0;
}


////le devuelvo a sofia una casilla con todos sus atributos para que los compare
//Casilla Tablero::datos_casilla(int x, int y)
//{
//    Casilla casilla_ = matriz[x][y];
//    return casilla_;
//}
//
//void Tablero::vacia_casilla(int x, int y)
//{
//    matriz[x][y].ocupada = 0;
//}
//
//void Tablero::rellena_casilla(int x, int y, Casilla nueva)
//{
//    nueva = matriz[x][y]; //pensar si hace copia o borra lo q habia 
//}