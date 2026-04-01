#include <iostream>
#include "freeglut.h"
#include "ETSIDI.h"
#include "tablero.h"
#include "Batalla.h"

using std::cout, std::cin, std::endl;

//porfavor no toqueis rutas de carpetas q me ha costado mucho y lloro, el archivo gitgnore igual
//llevo un par de horas para guardar temas de la carpeta de extra, confirmadme si se escucha
//hoy no se si me da tiempo a terminar de configurar el main, de ahi en adelante con todo
//si quereis configurarlo vosotras recordad q es copiar las funciones de freeglut del lab
//como se rompa lloro

Tablero miTablero;

void OnDraw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


	///IDENTIFICAR SI SE DIBUJA EL TABLERO O LA BATALLA
    ///CUANDO "ESTADO" ESTE BIEN DEFINIDO QUITAR COMENTARIOS
   // if (estadoActual==ESTADO_TABLERO)
    miTablero.dibujar(); // Llamamos al dibujo de nuestra clase
   // else if (estadoActual==ESTADO_BATALLA)
   // {
	//	batalla.dibujar(); ///SIN HACER
	//  start_combat(humanos, aliens);
	// }
    
    glutSwapBuffers();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tablero");
    //se pude hacer una funcion con esta para cmabiar el color en funcion del turno
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Fondo de ventana gris
    miTablero.inicializarCamara();       // Configuramos la vista

    
    std::cout << "Reproduciendo..." << std::endl;

    // Asegraros de que el nombre del archivo y la carpeta coincidan letra por letra
    ETSIDI::play("extra/mi_musica.mp3");

    std::cout << "Presiona Enter para salir y parar la musica..." << std::endl;
    glutDisplayFunc(OnDraw);
    glutMainLoop();
    getchar(); // Esto mantiene el programa vivo para q de tiempo a escuchar
    
    return 0;

}