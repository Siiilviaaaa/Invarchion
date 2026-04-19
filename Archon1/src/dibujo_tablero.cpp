#include "dibujo_tablero.h"
#include "ETSIDI.h"
#include "tablero.h"

Dibujar_tablero::Dibujar_tablero(Tablero* t, float l) : tablero(t), lado(l){}

void Dibujar_tablero::dibuja()
{
	dibujarFondo();
	dibujarBordeTurno();
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            const Casilla* c = tablero->getCasilla(i, j);
            dibujarCasilla(c);
        }
    }

}

void Dibujar_tablero::dibujarFondo()
{
    //meter foto de fondo
    glEnable(GL_TEXTURE_2D); // Activamos el uso de texturas
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("Recursos/fondotablero.png").id);
    glDisable(GL_LIGHTING); // Desactivamos luces para que la foto no se vea oscura
    glColor3f(1, 1, 1);    // Color blanco puro para no teñir la foto
    float m = 2.0f;
    float ancho = 7 * lado;
    float alto = 5 * lado;
    glBegin(GL_POLYGON);

    glTexCoord2d(1, 1); glVertex3f(-m, -m, -0.1f);
    glTexCoord2d(0, 1); glVertex3f(ancho + m, -m, -0.1f);
    glTexCoord2d(0, 0); glVertex3f(ancho + m, alto + m, -0.1f);
    glTexCoord2d(1, 0); glVertex3f(-m, alto + m, -0.1f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void Dibujar_tablero::dibujarBordeTurno()
{
    glPushMatrix();
    //para el fondo del tablero cambie de color segun turno
    if (tablero->getTurno() == 0)
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
}

void Dibujar_tablero::dibujarCasilla(const Casilla* c)
{
    float x = c->getcolumna() * lado; // j (columna) es X en pantalla
    float y = c->getfila() * lado; // i (fila) es Y en pantalla

    switch (c->getInfo()->getColor()) {
    case blanca: glColor3f(1.0f, 1.0f, 1.0f); break;
    case negra:  glColor3f(0.1f, 0.1f, 0.1f); break;
    case lila:   glColor3f(0.5f, 0.0f, 0.5f); break;
    }
    if (c->getInfo()->getColor() != lila) {
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


