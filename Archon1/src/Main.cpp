#include <iostream>
#include "freeglut.h"
#include "MotorGrafico.h"
#include "tablero.h"
#include "Batalla.h"
#include "Juego.h"
#include "casilla.h"
#include "menu.h"
#include "dibujo_tablero.h"
#include <cctype>
#include "vista.h"

//er
using std::cout, std::cin, std::endl;

//IMPORTANTE AÑADIR LOS ENUM Q HAGAN FALTA
enum Estado { MENU, SELECCION, JUEGO, RANKING, BATALLA };
Estado estado = MENU;
//variable global que devuelve el bando del jugador y ese empieza primero

//
//RECORDAD QUE YO SIEMPRE PONGO MENSAJES EN EL SHELL PARA SABER Q ESTAMOS HACIENDO Y SI LA FUNCIONALIDAD VA Y LO Q ME FALLA SON LOS GRÁFICOS
//

//PARA QUE NO SE RESTAURE LA VIDA DE LOS PERSONAJES AL ACABAR LA BATALLA SOLO USAR CREARPIEZA 1 VEZ AL INICIO

Menu miMenu;
Tablero miTablero;
Camara miCamara;
Dibujar_tablero dibujo_tablero(&miTablero, 2.0f);
Juego juego(&miTablero); // <--- ESTO ES LO QUE FALTA

void mouse(int button, int state, int x, int y) //esta funcion detecta los clicks en el menú
{ //esto no debería de ir en una funcion por separado?
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (estado == MENU) {
            //BOTÓN EXIT (Centro: 178, 182)
            if (x > 100 && x < 250 && y > 120 && y < 250) {
                std::cout << "[CLICK] Saliendo del juego..." << std::endl;
                exit(0);
            }
            //BOTÓN JUGAR (Centro: 399, 399)
            if (x > 270 && x < 530 && y > 290 && y < 510) {
                std::cout << "[CLICK] ¡A JUGAR!" << std::endl;
                estado = SELECCION;
            }
            //BOTÓN RANKING (Centro: 622, 183)
            if (x > 550 && x < 700 && y > 120 && y < 250) {
                std::cout << "[CLICK] Abriendo Ranking..." << std::endl;
                estado = RANKING;
            }
        }
        else if (estado == SELECCION)
        {
            //aqui no hay nada para q si estamos en seleccion no se hagan el listo y le puedan dar a exit
        }

    }
    
}

void OnDraw(void) //aqui dentro está el switch al que hay q añadir el estado de batalla con su respectiva camara, creo q es de Elena eso
                  //también he conservado la posición original del tablero y he movido yo mi menú para q no hubiera problemas
{
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    dibujo_tablero.dibuja();
 
  switch (estado) {
    case MENU:
        //primero camara
        miCamara.vistaMenu();
        //despues dibujar
        miMenu.dibuja_menu();
        break;
    case JUEGO:
        miCamara.vistaJuego();
        dibujo_tablero.dibuja();
        break;
    case RANKING:
        //pantallaRanking.draw();
        break;
    case SELECCION:
        // Mantenengo la misma cámara que el menú para que se siga vienda debajo que queda bien
        miCamara.vistaMenu();

        // Dibujo el menú de fondo (para que no desaparezca)
        miMenu.dibuja_menu();
        // Dibujo la capa de selección encima
        miMenu.dibuja_capa_seleccion();
        break;
    case BATALLA:
        miCamara.vistaBatalla();
        break;

    }
    //no borrar esta linea ni poner nada despues
    glutSwapBuffers();   
}

void OnTimer(int value) //no tengo 100% claro si es estrictamente necesaria pero yo la he añadido pq me facilitaba la vida
{
    glutPostRedisplay();
    // Se vuelve a llamar a sí misma cada 20ms (unos 50 FPS)
    glutTimerFunc(20, OnTimer, 0);
}

void OnKeyboardDown(unsigned char key, int x, int y) {
    // Solo procesamos estas teclas si estamos en la pantalla de bando para q no se solape con el movimiento de las fichas luego, ok??
    if (estado == SELECCION) {

        key = tolower(key); //el tolower es TO  LOWER  CASE, por si alguna lo necesita usar es para no poner 'a'||'A'

        if (key == 'h') {
            std::cout << "[SISTEMA] Has elegido: HUMANOS. Iniciando despliegue..." << std::endl;
            juego.setBandoJugador(Bando_jugador_es_Humano);
            estado = JUEGO;
        }
        else if (key == 'a') {
            std::cout << "[SISTEMA] Has elegido: ALIENS. Iniciando invasión..." << std::endl;
            juego.setBandoJugador(Bando_jugador_es_Alien);
            estado = JUEGO;
        }


        // Refresco de pantalla para q se pinte
        glutPostRedisplay();
    }
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
    
    miMenu.inicializa_menu();
    miTablero.inicializa(); // Configuramos las vistas de Elena y Diego que son las hechas hasta ahora

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

    //esto todo habrá q modificarlo si quereis distintas musicas en las distintas pantallas, prioridad de ajuste fino, dejar para el final
    cout << "Reproduciendo..." << std::endl;
    // Asegraros de que el nombre del archivo y la carpeta coincidan letra por letra
    ETSIDI::play("extra/mi_musica.mp3");

//aqui he añadido alguna mia
    glutMouseFunc(mouse);
    glutTimerFunc(20, OnTimer, 0);
    glutDisplayFunc(OnDraw);
    glutKeyboardFunc(OnKeyboardDown);
    glutMainLoop();
    
    return 0;

}