#include <iostream>
#include "freeglut.h"    
#include "Interfaz.h"
#include "menu.h"        
#include "vista.h"       
#include "MotorGrafico.h"    
#include "Batalla.h"      

//ESTADO GLOBAL DEL JUEGO E INSTANCIAS DE MÓDULOS//
Estado estado = MENU; //Mquina de estados principal (MENU, JUEGO, BATALLA, etc.)
Menu miMenu; //Gestion de pantallas de meno, selección y -persistencia de ranking
Tablero miTablero; 
Camara miCamara; //control de perspectivas
MotorGrafico motor;// Subsistema de  dibujo
Caja miCaja;
Juego juego(&miTablero);
Cursor micursor;
Batalla miBatalla;
Personaje pj1, pj2;

int main(int argc, char** argv) {

    // --- CONFIGURACIÓN E INICIALIZACIÓN DE WINDOWS Y FREEGLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600); //dimension inicial nativa de la ventana (relación 4:3)
    glutCreateWindow("Invarchion");

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //Color de fondo por defecto (gris oscuro)
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, 800.0 / 600.0, 0.1, 150); //vista plana en 2D

    ////////  INICIALIZACIÓN DE OBJETOS //////
    miMenu.inicializa_menu(); //carga de texturas
    miTablero.inicializa();  //Configuramos las vistas de Elena y Diego que son las hechas hasta ahora
    motor.setTablero(&miTablero);
    juego.inicializarPartida();
    micursor.inicializar_tablero(juego.getTurno());//iniciliza colores y sitios del cursor
    micursor.setJuego(&juego);//actualiza de quien es el turno

    //// REGISTRO DE CALLBACKS ////
    //Estas funciones las he puesto en Interfaz.cpp tras el commit de limpieza de main
   
    //las de raton
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(mousePassive);
    
    //redimensionado de pantalla
    glutReshapeFunc(redimensionar);

    //temporizador
    glutTimerFunc(20, OnTimer, 0);
    //OnDraw, Keyboard y teclas especiales
    glutDisplayFunc(OnDraw);
    glutKeyboardFunc(OnKeyboardDown);
    glutSpecialFunc(OnSpecialKeyboardDown);

    glutMainLoop(); // Cede el control a FreeGLUT. Bloquea el retorno hasta el cierre del juego

    return 0;
}