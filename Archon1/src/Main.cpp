#include <iostream>
#include "freeglut.h"
#include "ETSIDI.h"
#include "tablero.h"
#include "Batalla.h"
#include "Juego.h"
#include "casilla.h"

using std::cout, std::cin, std::endl;

//porfavor no toqueis rutas de carpetas q me ha costado mucho y lloro, el archivo gitgnore igual
//llevo un par de horas para guardar temas de la carpeta de extra, confirmadme si se escucha
//hoy no se si me da tiempo a terminar de configurar el main, de ahi en adelante con todo
//si quereis configurarlo vosotras recordad q es copiar las funciones de freeglut del lab
//como se rompa lloro


//TIPOS DE HECHIZOS:  CREACION EN PROCESO
//- REDUCIR VELOCIDAD ENEMIGO hechizos[0]--> 2 VECES POR TURNO
//- AUMENTAR VELOCIDAD ALIADO hechizos[1]--> 2 VECES POR TURNO
//- RESTAURAR PARTE DE LA VIDA ALIADO hechizo[2]--> ACTIVO EN TABLERO --> 1 VEZ POR TURNO Y SE PIERDE TURNO

Juego juego; // <--- ESTO ES LO QUE FALTA
Tablero miTablero;
void OnDraw(void);
void OnDraw(void) {
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(7.0, 5.0, 20.0,
        7.0, 5.0, 0.0,
        0.0, 1.0, 0.0);

    miTablero.dibuja();
  
        //no borrar esta linea ni poner nada despues
    glutSwapBuffers();


	///IDENTIFICAR SI SE DIBUJA EL TABLERO O LA BATALLA
    ///CUANDO "ESTADO" ESTE BIEN DEFINIDO QUITAR COMENTARIOS
   // if (estadoActual==ESTADO_TABLERO)
   
   // else if (estadoActual==ESTADO_BATALLA)
   // {
	//	batalla.dibujar(); ///SIN HACER
	//  start_combat(humanos, aliens);
	// }
    
}
int main(int argc, char** argv) {
    //INICIAR JUEGO
   // Invarchion.IniciarJuego(); //esto cambia el valor del bool ejecutandose a 1, por lo que podeis poner las funciones como la de dibujar el tablero en basse a esto


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tablero");
    //se pude hacer una funcion con esta para cmabiar el color en funcion del turno
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Fondo de ventana gris
    miTablero.inicializa();       // Configuramos la vista

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

    cout << "Reproduciendo..." << std::endl;

    // Asegraros de que el nombre del archivo y la carpeta coincidan letra por letra
    ETSIDI::play("extra/mi_musica.mp3");

    cout << "Presiona Enter para salir y parar la musica..." << std::endl;
    glutDisplayFunc(OnDraw);
    glutMainLoop();
    getchar(); // Esto mantiene el programa vivo para q de tiempo a escuchar
    
    return 0;

}