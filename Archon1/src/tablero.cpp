#include <vector>
#include "tablero.h"
#include "freeglut.h"
#include "Juego.h"
#include "ETSIDI.h"

//declaracion matriz, constructor y funciones
int matrizArchon[9][9] = {
    {0, 1, 0,2, 2, 2, 1, 0,1}, // Fila 0 (Superior)
    {1, 0, 2,1, 2, 0, 2, 1,0}, // Fila 1
    {0, 2, 1,0, 2, 1, 0, 2,1}, // Fila 2
    {2, 1, 0, 1,2, 0, 1, 0,2}, // Fila 3
    {1, 2, 2, 2,2, 2, 2, 2,0}, // Fila 4 (Cruz Central)
    {2, 1, 0, 1,2, 0, 1, 0,2}, // Fila 5 
    {0, 2, 1, 0,2, 1, 0, 2,1}, // Fila 6 
    {1, 0, 2, 1,2, 0, 2, 2,0}, // Fila 7 
    {0, 1, 0, 2,2, 2, 1, 0,1}, // Fila 8 
};

Tablero::Tablero() {
  
    inicializa();//llamamos a q se inicialice la casilla
}

void Tablero::inicializa() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            Tipocasilla tipo;
            int valor = matrizArchon[i][j];
            switch (valor) {
            case 0: tipo = negra; break;
            case 1: tipo = blanca; break;
            case 2: tipo = lila; break;
            default: tipo = lila;
            }
            datos[i][j] = InfoCasilla(tipo);
            matriz[i][j] = Casilla(i, j, &datos[i][j]);
            //defino las coordenadas de los puntos de poder
            if ((i == 4 && j == 4) || (i == 0 && j == 4) || (i == 8 && j == 4) || (i == 4 && j == 0) || (i == 4 && j == 8)) {
                datos[i][j].setPuntoPoder(true);
            }
        }
    }
}
void Tablero::reseteoColores()
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            datos[i][j].setSeleccion(false);
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