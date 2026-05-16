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

//variables globales
float tiempoMensajeSelecciondeBando = 0.0f;
std::string textoBando = "";
bool mostrandoInstruccionesTablero = false;
float tiempoInstruccionesTablero = 0.0f;


//HE MOVIDO AQUI LOS CALLBACKSSS MIRADLO PORFII
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //Obtener dimensiones actuales de la ventana
        float width = glutGet(GLUT_WINDOW_WIDTH);
        float height = glutGet(GLUT_WINDOW_HEIGHT);

        //Convertir clic a coordenadas normalizadas (0.0 a 1.0)
        float nx = x / width;
        float ny = y / height;

        if (estado == MENU) {
            // Botón Salir (Originalmente x:100-250, y:120-250)
            if (nx > 0.125f && nx < 0.312f && ny > 0.2f && ny < 0.416f) {
                exit(0);
            }

            // Botón Selección (Originalmente x:270-530, y:290-510)
            if (nx > 0.337f && nx < 0.662f && ny > 0.483f && ny < 0.85f) {
                estado = SELECCION;
            }

            // Botón Ranking (Originalmente x:550-700, y:120-250)
            if (nx > 0.687f && nx < 0.875f && ny > 0.2f && ny < 0.416f) {
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

    
    switch (estado) { //aqui dentro no he tocando nada
    case MENU:
        miCamara.vistaMenu();
        miMenu.dibuja_menu();
        break;
    case JUEGO:
        miCamara.vistaJuego();
        dibujo_tablero.dibuja();
        for (int i = 0; i < MAX_PERSONAJES; i++) {
            Personaje* p = juego.getPersonaje(i);
            if (p != nullptr && p->return_Vida() > 0) {
                motor.dibujarPersonaje(*p);
            }
        }
        fin_ = false;

        // 1. Dibuja el mensaje del bando seleccionado usando el motor gráfico
        if (tiempoMensajeSelecciondeBando > 0) {
            motor.dibujarMensajeBando(textoBando);
        }

        // 2. Dibuja la pantalla de instrucciones usando el motor gráfico
        if (mostrandoInstruccionesTablero) {
            motor.dibujarInstruccionesTablero();
        }
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
    // 1. Reducir tiempo de las instrucciones primero (para que no se quede congelado el reloj)
    if (mostrandoInstruccionesTablero && tiempoInstruccionesTablero > 0) {
        tiempoInstruccionesTablero -= 20.0f;
        if (tiempoInstruccionesTablero <= 0) {
            mostrandoInstruccionesTablero = false;
            tiempoMensajeSelecciondeBando = 0.0f; // Limpiamos también el bando si expira el tiempo
        }
    }

    // 2. CONGELACIÓN DEL JUEGO: Si siguen activas, frena el resto de la lógica
    if (estado == JUEGO && mostrandoInstruccionesTablero) {
        glutPostRedisplay();
        glutTimerFunc(20, OnTimer, 0);
        return;
    }

    // 3. Lógica normal del juego (solo se ejecuta si no hay instrucciones en pantalla)
    if (estado == BATALLA) {
        miBatalla.actualizarCombate(pj1, pj2, miCaja, motor.obtenerObstaculos());
        if (fin_) estado = JUEGO;
    }
    glutPostRedisplay();

    // Reducir tiempo del mensaje de bando cuando el juego ya está corriendo
    if (tiempoMensajeSelecciondeBando > 0) {
        tiempoMensajeSelecciondeBando -= 20.0f;
    }

    glutTimerFunc(20, OnTimer, 0);
}

void OnKeyboardDown(unsigned char key, int x, int y) {
    unsigned char c = std::tolower(key);

    // NUEVO BLOQUE: Control estricto de entrada durante las instrucciones
    if (estado == JUEGO && mostrandoInstruccionesTablero) {
        if (key == ' ') { // Solo el ESPACIO quita los carteles y descongela
            mostrandoInstruccionesTablero = false;
            tiempoInstruccionesTablero = 0.0f;
            tiempoMensajeSelecciondeBando = 0.0f;
            glutPostRedisplay();
        }
        return; // BLOQUEO: Cualquier otra tecla ('b', WASD, etc.) se ignora por completo
    }

    if (key == 27) { // ESC es la 27
        if (estado == MENU) exit(0);
        else estado = MENU;
    }

    if (c == 'r') {
        std::string nombre;
        int puntos;

        std::cout << "\n--- REGISTRO DE PUNTUACION ---" << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');

        std::cout << "TRES LETRAS: ";
        std::cin >> nombre;
        if (nombre.size() > 3) nombre = nombre.substr(0, 3);

        std::cout << "Puntuacion (solo numeros): ";
        if (!(std::cin >> puntos)) {
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
        if (key == 'h' || key == 'a') {
            if (key == 'h') {
                juego.setBandoJugador(Bando_jugador_es_Humano);
                textoBando = "Jugador 1: Humanos";
            }
            else {
                juego.setBandoJugador(Bando_jugador_es_Alien);
                textoBando = "Jugador 1: Aliens";
            }
            estado = JUEGO;

            // Sincronización de tiempos a 15 segundos
            tiempoMensajeSelecciondeBando = 15000.0f;
            mostrandoInstruccionesTablero = true;
            tiempoInstruccionesTablero = 15000.0f;
        }
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