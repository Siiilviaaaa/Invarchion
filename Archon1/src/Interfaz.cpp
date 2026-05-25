#include "Interfaz.h"
#include <iostream>
#include <cctype>
#include "ETSIDI.h"
#include "freeglut.h"
#include "Juego.h"
#include "menu.h"
#include "vista.h"      
#include "MotorGrafico.h"
#include "tablero.h"
#include "Batalla.h"
#include "Cursor.h"



//los extern son para q los busque en el main, me ha ayudado la IA en esta parte
//basicamente es un: "oye usa el [extern] q declare en el main
extern Estado estado;
extern Menu miMenu;
extern Tablero miTablero;
extern Camara miCamara;
extern MotorGrafico motor;
extern Caja miCaja;
extern Juego juego;
extern Batalla miBatalla;
extern Personaje pj1, pj2;
extern bool fin_;
extern Cursor micursor;

//variables globales
float tiempoMensajeSelecciondeBando = 0.0f;
std::string textoBando = "";
bool mostrandoInstruccionesTablero = false;
float tiempoInstruccionesTablero = 0.0f;

//Variables globales para controlar el hover
bool hoverSalir = false;
bool hoverSeleccion = false;
bool hoverRanking = false;

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
        // Mapeamos las variables en orden: hJugar (hoverSeleccion), hRanking (hoverRanking), hSalir (hoverSalir)
        miMenu.dibuja_menu(hoverSeleccion, hoverRanking, hoverSalir);
        break;
    case JUEGO:
    {
        miCamara.vistaJuego();
        motor.dibujarTablero();

        for (int f = 0; f < 5; f++) {
            for (int c = 0; c < 7; c++) {
                InfoCasilla* info = miTablero.getInfoCasilla(f, c);

                if (info != nullptr && info->getPersonaje() != nullptr) {
                    if (info->getPersonaje()->return_Vida() > 0) {
                        motor.dibujarPersonaje(*(info->getPersonaje()));
                    }
                }
            }
        }

        fin_ = false;
        motor.dibujarCursor(micursor);

        //dibujar mensajes
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        // 1. Guardamos la perspectiva 3D actual en una mochila para no romper el tablero
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        // Creamos un plano fijo que mide exactamente 800x600 píxeles (el tamaño de tu ventana)
        gluOrtho2D(0, 800, 0, 600);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        // 2. Color de la letra (Blanco puro)
        glColor3ub(153, 50, 204);

        std::string mensajeTablero = micursor.obt_mensaje();//varia en funcion de la situacion del tablero actual
      
        // 3. ¡ESTA ES LA SUSTITUCIÓN REAL! 
        // Coloca el texto a 220 píxeles desde la izquierda y a 35 píxeles desde el suelo de la ventana
        glRasterPos2i(220, 45);

        // Imprimimos el texto letra a letra (estilo ranking)
        for (char c : mensajeTablero) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }

        // 4. Sacamos la perspectiva 3D de la mochila para que el tablero se siga viendo bien
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
              
        /////Menu integracion merge
        // 1. Dibuja el mensaje del bando seleccionado usando el motor gráfico
        if (tiempoMensajeSelecciondeBando > 0) {
            motor.dibujarMensajeBando(textoBando);
        }

        // 2. Dibuja la pantalla de instrucciones usando el motor gráfico
        if (mostrandoInstruccionesTablero) {
            motor.dibujarInstruccionesTablero();
        }
        break;
    }
    case RANKING:
        miCamara.vistaRanking();
        miMenu.dibuja_ranking();
        break;
    case SELECCION:
        miCamara.vistaMenu();
        miMenu.dibuja_menu(hoverSeleccion, hoverRanking, hoverSalir);
        miMenu.dibuja_capa_seleccion();
        break;
    case BATALLA:
        miCamara.vistaBatalla();
        motor.dibujarCaja(miCaja);

        Personaje* atacante = juego.getAtacanteBatalla();
        Personaje* defensor = juego.getDefensorBatalla();

        if (atacante != nullptr && defensor != nullptr) {
            motor.dibujarPersonaje(*atacante);   
            std::cout << atacante->return_X();
            std::cout << atacante->return_Y();
            motor.dibujarPersonaje(*defensor);
            miBatalla.actualizarCombate(*atacante, *defensor, miCaja, motor.obtenerObstaculos());
        }

        //motor.dibujarBarraVida(pj1, pj2);

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
        Personaje* atacante = juego.getAtacanteBatalla();
        Personaje* defensor = juego.getDefensorBatalla();

        if (atacante != nullptr && defensor != nullptr) {
            miBatalla.actualizarCombate(*atacante, *defensor, miCaja, motor.obtenerObstaculos());

        }
        if (fin_) {
            estado = JUEGO;
            juego.finalizarBatalla();
        }
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
                micursor.inicializar_tablero(juego.getTurno());//de esta forma siempre actualizara el cursor, cuando se seleccione

            }
            else {
                juego.setBandoJugador(Bando_jugador_es_Alien);
                textoBando = "Jugador 1: Aliens";
                micursor.inicializar_tablero(juego.getTurno());
            }
            estado = JUEGO;
            motor.juego = &juego;
            // Sincronización de tiempos a 15 segundos
            tiempoMensajeSelecciondeBando = 15000.0f;
            mostrandoInstruccionesTablero = true;
            tiempoInstruccionesTablero = 15000.0f;
        }
        glutPostRedisplay();
    }

    if (estado == JUEGO)
    {
        micursor.seleccion_personaje_tablero(c, juego.getTurno());
        
        if (micursor.obt_contador_selecciones() == 0) {
            micursor.inicializar_tablero(juego.getTurno());
        }
    }

    /*if (key == 'b') {
        std::cout << "[SISTEMA] Abriendo escenario de batalla..." << std::endl;
        if (estado == JUEGO) {
        estado = BATALLA;
        }
        pj1 = Personaje::crearPieza(ARQUERO, HUMANO, 5.0, 7.5);
        pj1.direccion(1.0, 0.0);
        pj2 = Personaje::crearPieza(HECHICERO, ALIEN, 15.0, 7.5);
        pj2.direccion(-1.0, 0.0);
        motor.inicializarBatalla();
    }*/

        /*if (estado == BATALLA) {
            miBatalla.KeyBatalla(key, pj1, pj2);
        }*/

    glutPostRedisplay();
}

void OnSpecialKeyboardDown(int key, int x, int y) {

    if (estado == BATALLA) {
        miBatalla.tecla_especial(key, pj2);
    }
    if (estado == JUEGO && juego.getTurno() == 1)
    {
        micursor.mover_aliens(key);

        if (micursor.obt_contador_selecciones() == 0) {
            micursor.inicializar_tablero(juego.getTurno());
        }
    }
    glutPostRedisplay();
}

void mousePassive(int x, int y) {
    float width = glutGet(GLUT_WINDOW_WIDTH);
    float height = glutGet(GLUT_WINDOW_HEIGHT);

    float nx = x / width;
    float ny = y / height;

    if (estado == MENU) {
        // Resetear estados
        hoverSalir = false;
        hoverSeleccion = false;
        hoverRanking = false;

        // Botón Salir
        if (nx > 0.125f && nx < 0.312f && ny > 0.2f && ny < 0.416f) hoverSalir = true;

        // Botón Selección
        if (nx > 0.337f && nx < 0.662f && ny > 0.483f && ny < 0.85f) hoverSeleccion = true;

        // Botón Ranking
        if (nx > 0.687f && nx < 0.875f && ny > 0.2f && ny < 0.416f) hoverRanking = true;

        glutPostRedisplay(); // Forzar redibujado para ver el cambio de color
    }
}

void redimensionar(int width, int height) {
    float aspect_deseado = 800.0f / 600.0f;
    float aspect_actual = (float)width / (float)height;

    int vp_x = 0, vp_y = 0;
    int vp_width = width;
    int vp_height = height;

    // 1. Calculamos las barras negras según la deformación de la ventana
    if (aspect_actual >= aspect_deseado) {
        vp_width = (int)(height * aspect_deseado);
        vp_x = (width - vp_width) / 2;
    }
    else {
        vp_height = (int)(width / aspect_deseado);
        vp_y = (height - vp_height) / 2;
    }

    // 2. Aplicamos el Viewport protegido para no deformar nada
    glViewport(vp_x, vp_y, vp_width, vp_height);

    // 3. NO forzamos gluOrtho2D aquí. Dejamos que OnDraw aplique la vista necesaria
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Dejamos la perspectiva por defecto del Main como base inicial
    gluPerspective(40.0, aspect_deseado, 0.1, 150);

    glMatrixMode(GL_MODELVIEW);
}