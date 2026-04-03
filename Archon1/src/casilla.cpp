#include "casilla.h"
#include "tablero.h"
#include "freeglut.h"
//declaracion de las casillas y sus funciones
Casilla::Casilla() {
    fila_ = 0;
    columna_ = 0;
    lado = 1.0f;
    tipo_color = blanca;
    ocupada = false;
    tipo_bando = NEUTRAL;
}
void Casilla::configurar(int f, int c, float l, Tipocasilla color_)
{
    fila_ = f;
    columna_ = c;
    lado = l;
    tipo_color = color_;

}

void Casilla::dibuja() {

    glPushMatrix();
    float x = columna_ * lado;
    float y = fila_ * lado;
    //glTranslatef(fila_ + lado / 2.0f, -lado / 2.0f, columna_ + lado / 2.0f);
    switch (tipo_color) {
    case blanca:      glColor3f(1.0f, 1.0f, 1.0f); break;
    case negra:       glColor3f(0.1f, 0.1f, 0.1f); break;
    case lila:        glColor3f(0.5f, 0.0f, 0.5f); break;
    }
    if (tipo_color != lila) {
        glBegin(GL_QUADS);
        glVertex3f(x, y, 0.0f);
        glVertex3f(x + lado, y, 0.0f);
        glVertex3f(x + lado, y + lado, 0.0f);
        glVertex3f(x, y + lado, 0.0f);
        glEnd();
    }

    //glutSolidCube(lado);//cubo
    glColor3f(0.2f, 0.2f, 0.2f);//delineado color
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(x, y, 0.005f); // Elevamos 0.005 para evitar parpadeo (Z-fighting)
    glVertex3f(x + lado, y, 0.005f);
    glVertex3f(x + lado, y + lado, 0.005f);
    glVertex3f(x, y + lado, 0.005f);
    glEnd();
    //glutWireCube(lado + 0.01f);//dibujo delineado
    glPopMatrix();
}


