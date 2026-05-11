#include "Interfaz.h"
#include <iostream>
#include <cctype>

#include "freeglut.h"
#include "Juego.h"
#include "menu.h"
#include "vista.h"      
#include "MotorGrafico.h"
#include "tablero.h"
#include "Batalla.h"
#include "dibujo_tablero.h"

//los extern son para q los busque en el main, me ha ayudado la IA en esta parte
//basicamente es un: "oye usa el [extern] q declare en el main
extern Estado estado;
extern Menu miMenu;
extern Tablero miTablero;
extern Camara miCamara;
extern MotorGrafico motor;
extern Caja miCaja;
extern Dibujar_tablero dibujo_tablero;
extern Juego juego;
extern Batalla miBatalla;
extern Personaje pj1, pj2;
extern bool fin_;


//HE MOVIDO AQUI LOS CALLBACKSSS MIRADLO PORFII
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (estado == MENU) {
            // Lógica de botones del menú comprimida pa q ver luego si puedo solucionar lo de modo ventana o modo fullscreen
            if (x > 100 && x < 250 && y > 120 && y < 250) exit(0);
            if (x > 270 && x < 530 && y > 290 && y < 510) estado = SELECCION;
            if (x > 550 && x < 700 && y > 120 && y < 250) {
                miMenu.cargar_ranking();
                estado = RANKING;
            }
        }
    }
}

void OnDraw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //he quitado lo q ponia aqui:
    //
    //dibujo_tablero.dibuja();
    //
    switch (estado) { //aqui dentro no he tocando nada
    case MENU:
        miCamara.vistaMenu();
        miMenu.dibuja_menu();
        break;
    case JUEGO:
        miCamara.vistaJuego();
        dibujo_tablero.dibuja();
        fin_ = false;
        break;
    case RANKING:
        miCamara.vistaRanking();
        miMenu.dibuja_ranking();
        break;
    case SELECCION:
        miCamara.vistaMenu();
        miMenu.dibuja_menu();
        miMenu.dibuja_capa_seleccion();
        break;
    case BATALLA:
        miCamara.vistaBatalla();
        motor.dibujarCaja(miCaja);
        motor.dibujarPersonaje(pj1);
        motor.dibujarPersonaje(pj2);
        motor.dibujarBarraVida(pj1, pj2);

        for (int i = 0; i < 20; i++) {
            Disparo* d = miBatalla.return_nDisparos()[i];
            if (d) motor.dibujarDisparo(d);
        }
        for (int b = 0; b < 2; b++)
            for (int i = 0; i < 3; i++) {
                Hechizo* h = miBatalla.return_nHechizos()[b][i];
                if (h != nullptr)
                    motor.dibujarHechizo(h);
            }
        break;
    }
    //no borrar esta linea ni poner nada despues
    glutSwapBuffers();
}

void OnTimer(int value) {
    if (estado == BATALLA) {
        miBatalla.actualizarCombate(pj1, pj2, miCaja, motor.obtenerObstaculos());
        if (fin_) estado = JUEGO;
    }
    glutPostRedisplay();
    
    //Se vuelve a llamar a sí misma cada 20ms (unos 50 FPS)
    glutTimerFunc(20, OnTimer, 0);
}

void OnKeyboardDown(unsigned char key, int x, int y) {
    unsigned char c = std::tolower(key);

    if (key == 27) { // ESC es la 27
        if (estado == MENU) exit(0);
        else estado = MENU;
    }

    if (c == 'r') {
        std::string nombre;
        int puntos;

        //parte de la CMD win
        std::cout << "\n--- REGISTRO DE PUNTUACION ---" << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n'); 
        //fflush(stdin);

        // <---- Limpieza de buffer

        //CMD
        std::cout << "TRES LETRAS: ";
        std::cin >> nombre;
        if (nombre.size() > 3) nombre = nombre.substr(0, 3);//he editado esto
        //ahora lo q hace es q si escribes mas de 3 se queda con las 3 primeras y te jodes

        std::cout << "Puntuacion (solo numeros): ";
        if (!(std::cin >> puntos)) {
            //Si el usuario mete letras en vez de números, evitamos el bucle infinito
             std::cout << "Error: Puntos invalidos." << std::endl;
             std::cin.clear();
             std::cin.ignore(1000, '\n');
             puntos = 0;
        }

        miMenu.actualizar_ranking(nombre, puntos);
        estado = RANKING;
    }

    //Selección de bando
    if (estado == SELECCION) {
        key = tolower(key);
        if (key == 'h') {
           juego.setBandoJugador(Bando_jugador_es_Humano);
           estado = JUEGO;
        }
        else if (key == 'a') {
           juego.setBandoJugador(Bando_jugador_es_Alien);
           estado = JUEGO;
        }
        // Refresco de pantalla para q se pinte
        glutPostRedisplay();
    }


if (key == 'b') {
     std::cout << "[SISTEMA] Abriendo escenario de batalla..." << std::endl;
     if (estado == JUEGO) {
     estado = BATALLA;
     }
    pj1 = Personaje::crearPieza(ARQUERO, HUMANO, 5.0, 7.5);
    pj1.direccion(1.0, 0.0);
    pj2 = Personaje::crearPieza(HECHICERO, ALIEN, 15.0, 7.5);
    pj2.direccion(-1.0, 0.0);
    motor.inicializarBatalla();
    }
        
    if (estado == BATALLA) {
       miBatalla.KeyBatalla(key, pj1, pj2);
    }

    glutPostRedisplay();
}