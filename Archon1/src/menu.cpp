#include "Menu.h"
#include "ETSIDI.h"
#include "freeglut.h"

Menu::Menu() :
    _fondo("extra/fondo_menu.png"),
    _boton_exit("extra/menu_boton_exit.png"),
    _boton_jugar("extra/menu_boton_jugar.png"),
    _boton_ranking("extra/menu_boton_ranking.png"),
    _seleccion("extra/menu_seleccion.png")
{
    // Una vez inicializados los objetos, llamamos a la configuración de tamaño/posición
    inicializa_menu();
}

void Menu::inicializa_menu() {

    _fondo.setPos(0, 0);
    _fondo.setSize(19.5, 16);

    // EXIT: En la parte superior izquierda
    _boton_exit.setPos(2, 9);
    _boton_exit.setSize(5, 4.5);

    // RANKING: En la parte superior derecha (Simetría: 19.5 - 2 - 5 = 12.5)
    _boton_ranking.setPos(12.5, 9);
    _boton_ranking.setSize(5, 4.5);

    // JUGAR: Centrado abajo (Simetría: (19.5 - 7) / 2 = 6.25)
    _boton_jugar.setPos(6.25, 2.9);
    _boton_jugar.setSize(7, 6.5);

    //SELECCION DE EQUIPO 1er TURNO: 
    // En inicializa_menu()
    _seleccion.setSize(10, 8); 
    _seleccion.setPos(4.6, 4.6); 

}

void Menu::dibuja_menu() {
    glDisable(GL_LIGHTING);

    glPushMatrix();
    // Nos movemos al "espacio vacío" 4.8, 8 porfavor construir lo demas en otros espacios
    //glTranslatef(4.8f, 8.0f, 0.0f);
    glTranslatef(39.8f, 41.0f, 0.0f);

    _fondo.draw();

    glTranslatef(0.0f, 0.0f, 0.5f);
    _boton_exit.draw();
    _boton_jugar.draw();
    _boton_ranking.draw();

    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void Menu::dibuja_capa_seleccion()
{

    glPushMatrix();

    //traslado igual que el menú para que coincidan los ejes
    glTranslatef(39.8f, 41.0f, 10.0f);

    _seleccion.draw();

    glPopMatrix();

    
}

