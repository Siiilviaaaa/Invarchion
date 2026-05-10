//////////  TODAS LAS DECLARACIONES, PUEDE QUE SOBRE ALGUNA  ///////////

#include <iostream>
#include "freeglut.h"
#include "ETSIDI.h"      


#include "Interfaz.h"
#include "menu.h"        
#include "vista.h"       
#include "MotorGrafico.h"
#include "tablero.h"     
#include "Batalla.h"     
#include "Juego.h"   
#include "dibujo_tablero.h"

//cuidado he quitado el using std::

///////////////////  TODAS LAS INICIALIZACIONES  ///////////////////////////////
Estado estado = MENU;
Menu miMenu;
Tablero miTablero;
Camara miCamara;
MotorGrafico motor;
Caja miCaja;
Dibujar_tablero dibujo_tablero(&miTablero, 2.0f);
Juego juego(&miTablero);

//PRUEBAS
Batalla miBatalla;
Personaje pj1, pj2;
bool fin_ = false;

//////////  SOLO EL MAIN COMO ME TOCABA LIMPIARLO LO HE LIMPIADO  /////////////////
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Invarchion"); //le cambié el nombre

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, 800.0 / 600.0, 0.1, 150);

    ////////  INICIALIZACIÓN DE OBJETOS //////
    //he movido esto aqui abajo para q este lo otro todo juntito
    miMenu.inicializa_menu();
    miTablero.inicializa();  // Configuramos las vistas de Elena y Diego que son las hechas hasta ahora

    //esto todo habrá q modificarlo si quereis distintas musicas en las distintas pantallas, prioridad de ajuste fino, dejar para el final
    cout << "Reproduciendo..." << std::endl;
    // Asegraros de que el nombre del archivo y la carpeta coincidan letra por letra
    //ETSIDI::play("extra/mi_musica.mp3");

    // --- REGISTRO DE CALLBACKS ---
    // Estas funciones las he puesto en Interfaz.cpp
    glutMouseFunc(mouse);
    glutTimerFunc(20, OnTimer, 0);
    glutDisplayFunc(OnDraw);
    glutKeyboardFunc(OnKeyboardDown);

    glutMainLoop();

    return 0;
}