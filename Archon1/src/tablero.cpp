#include <vector>
#include "tablero.h"
#include "freeglut.h"
#include"ETSIDI.h"

int matrizArchon[5][7] = {
    {0, 1, 2, 2, 2, 0, 1}, // Fila 0 (Superior)
    {1, 2, 1, 2, 0, 2, 0}, // Fila 1
    {0, 2, 2, 2, 2, 2, 1}, // Fila 2
    {1, 2, 0, 2, 1, 2, 0}, // Fila 3
    {0, 1, 2, 2, 2, 0, 1}, // Fila 4 (Cruz Central)


};
Tablero::Tablero() {
    lado = 2.0f;
    inicializa();//llamamos a q se inicialice la casilla
    turno = 0;
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
            matriz[i][j].configurar(i, j, lado, tipo);
            
        }
    }
}

void Tablero::dibuja() {
    //meter foto de fondo
    glEnable(GL_TEXTURE_2D); // Activamos el uso de texturas
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("Recursos/fondotablero.png").id);
    glDisable(GL_LIGHTING); // Desactivamos luces para que la foto no se vea oscura
    glColor3f(1, 1, 1);    // Color blanco puro para no teñir la foto
    float m = 2.0f;
    float ancho = 7 * lado;
    float alto = 5 * lado;
    glBegin(GL_POLYGON);
    //// Mapeamos la foto (0,0 a 1,1) a los vértices del cuadrado
    //// Usamos Z = -0.1 para que esté físicamente detrás de las casillas
    glTexCoord2d(1, 1); glVertex3f(-m, -m, -0.1f);
    glTexCoord2d(0, 1); glVertex3f(ancho + m, -m, -0.1f);
    glTexCoord2d(0, 0); glVertex3f(ancho + m, alto + m, -0.1f);
    glTexCoord2d(1, 0); glVertex3f(-m, alto + m, -0.1f);
    glEnd();

    glDisable(GL_TEXTURE_2D); // ¡IMPORTANTE! Apagamos texturas para que no afecten a las casillas
    glEnable(GL_LIGHTING);    // Reactivamos luces si las usas

    glPushMatrix();
    //para el fondo del tablero cambie de color segun turno
    if (turno == 0)
        glColor3f(0.0f, 0.3f, 0.6f);
    else
        glColor3f(0.6f, 0.0f, 0.0f);


    float anchoTotal = 7 * lado;
    float altoTotal = 5 * lado;
    glLineWidth(7.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0.05f);
    glVertex3f(anchoTotal, 0, 0.05f);
    glVertex3f(anchoTotal, altoTotal, 0.05f);
    glVertex3f(0, altoTotal, 0.05f);
    glEnd();

    glPopMatrix();

    //dibujar el tablero llamando a las casillas, iterando sobre la matriz
    glDisable(GL_LIGHTING);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            matriz[i][j].dibuja(); // Cada casilla ya sabe dónde está y su color
        }
    }
    glEnable(GL_LIGHTING);
}

//le devuelvo a sofia una casilla con todos sus atributos para que los compare
Casilla Tablero::datos_casilla(int x, int y)
{
    Casilla casilla_ = matriz[x][y];
    return casilla_;
}

void Tablero::vacia_casilla(int x, int y)
{
    matriz[x][y].ocupada = 0;
}

void Tablero::rellena_casilla(int x, int y, Casilla nueva)
{
    nueva = matriz[x][y]; //pensar si hace copia o borra lo q habia 
}






//INICIALIZAR POSICIONES PIEZAS
//void Tablero::inicializarPiezas() 
// {
// 
// CREAR PIEZAS Y POSICONARLAS [][] --> COORDENADAS
// pieza [][] = Personajes_carac::craerPieza(SOLDADO);
// pieza [][] = Personajes_carac::craerPieza(ARQUERO);
// pieza [][] = Personajes_carac::craerPieza(VOLADOR);
// pieza [][] = Personajes_carac::craerPieza(EXCAVADOR);
// pieza [][] = Personajes_carac::craerPieza(HECHICERO);
// }
