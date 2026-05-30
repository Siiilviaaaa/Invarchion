#include "Interfaz.h"
#include <iostream>
#include <cctype>
#include "freeglut.h"
#include "menu.h"
#include "vista.h"      
#include "MotorGrafico.h"
#include "gestionArchivos.h"

//los extern son para q los busque en el main, me ha ayudado la IA en esta parte
//basicamente es un: "oye usa el [extern] q declare en el main
// --- ENLACE DE INSTANCIAS EXTERNAS (DEFINIDAS EN MAIN.CPP) ---
extern Estado estado;
extern Menu miMenu;
extern Tablero miTablero;
extern Camara miCamara;
extern MotorGrafico motor;
extern Caja miCaja;
extern Juego juego;
extern Batalla miBatalla;
extern Cursor micursor;
extern Personaje pj1, pj2;

//variables globales
float tiempoMensajeSelecciondeBando = 0.0f; // Temporizador para el banner informativo de facción elegida
std::string textoBando = "";                 // Cadena de texto del bando seleccionado
bool mostrandoInstruccionesTablero = false;  // Flag de bloqueo/congelación por lectura de controles
float tiempoInstruccionesTablero = 0.0f;     // Duración de la pantalla de ayuda técnica (15 segundos)
bool hoverSalir = false;                     // Estado hover: Botón de cierre
bool hoverSeleccion = false;                 // Estado hover: Botón de inicio/selección
bool hoverRanking = false;                   // Estado hover: Botón de clasificaciones
bool fin_ = false;                           // Flag de sincronización síncrona que decreta la muerte en combate
int puntuacion_actual = 0;                   // Puntuación de la partida activa traspasada al gestor de persistencia
int puntuacion_humanos = 0;                  // Registro acumulado de daño/bajas de la facción Terran
int puntuacion_aliens = 0;                   // Registro acumulado de daño/bajas de la facción Alienígena

// Mapea las coordenadas físicas del puntero en píxeles a regiones normalizadas de pantalla para interactuar con la GUI del menú
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

//callback de ondraw movido y la musica para sincronizar con el dinujado
void OnDraw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Interruptores para controlar que la música se dispare una sola vez por estado
    static bool ini_menu = false;
    static bool ini_juego = false;
    static bool ini_batalla = false;
    static bool ini_ranking = false;
    static bool ini_fin = false;

    switch (estado) { 
    case FIN_PARTIDA:
        if (!ini_fin) {
            ETSIDI::stopMusica();
            ETSIDI::playMusica("extra/musica_fin.mp3", false);
            ini_fin = true;
            ini_menu = false;
            ini_juego = false;
            ini_batalla = false;
            ini_ranking = false;
        }
        miCamara.vistaRanking();
        miMenu.dibuja_fin();
        juego.reiniciarJuego(&juego);
        break;
    
    case MENU:
        if (!ini_menu) {
            ETSIDI::stopMusica();
            ETSIDI::playMusica("extra/mi_musica.mp3", true);
            ini_menu = true;
            ini_juego = false;
            ini_batalla = false;
            ini_ranking = false;
            ini_fin = false;
        }
        miCamara.vistaMenu();
        // Mapeamos las variables en orden: hJugar (hoverSeleccion), hRanking (hoverRanking), hSalir (hoverSalir)
        miMenu.dibuja_menu(hoverSeleccion, hoverRanking, hoverSalir);
        break;
    case JUEGO:
    {
        miCamara.vistaJuego();
        motor.dibujarTablero();

        if (!ini_juego) {
            ETSIDI::stopMusica();
            ETSIDI::playMusica("extra/Tablero.mp3", true);
            ini_juego = true;
            ini_menu = false;
            ini_batalla = false;
            ini_ranking = false;
            ini_fin = false;
        }

        for (int f = 0; f < 9; f++) {
            for (int c = 0; c < 9; c++) {
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

        motor.dibujarMensajesTablero(micursor.obt_mensaje());//imprime los mensajes de seleccion y turno en el tablero              

        if (tiempoMensajeSelecciondeBando > 0) {//dibuja mensaje de bando
            motor.dibujarMensajeBando(textoBando);
        }

        if (mostrandoInstruccionesTablero) {//dibuja las instrucciones del tablero
            motor.dibujarInstruccionesTablero();
        }

        motor.dibujarPuntuaciones(puntuacion_humanos, puntuacion_aliens); //PUNTUACIONES EN TABLERO
       
        break;
    }
    case RANKING:

        if (!ini_ranking) {
            ETSIDI::stopMusica();
            ETSIDI::playMusica("extra/Ranking.mp3", true);
            ini_ranking = true;
            ini_menu = false;
            ini_juego = false;
            ini_batalla = false;
            ini_fin = false;
        }

        miCamara.vistaRanking();
        miMenu.dibuja_ranking();
        //RESET DE PUNTUACIONES PARA NUEVA PARTIDA
        puntuacion_actual = 0;
        puntuacion_aliens = 0;
        puntuacion_humanos = 0;
        break;
    case SELECCION:
        miCamara.vistaMenu();
        miMenu.dibuja_menu(hoverSeleccion, hoverRanking, hoverSalir);
        miMenu.dibuja_capa_seleccion();
        break;
    case BATALLA:
        
        if (!ini_batalla) {
            ETSIDI::stopMusica();
            ETSIDI::playMusica("extra/Batalla.mp3", true);
            ini_batalla = true;
            ini_juego = false;
            ini_menu = false;
            ini_ranking = false;
            ini_fin = false;
        }

        miCamara.vistaBatalla();
        motor.dibujarCaja(miCaja, miBatalla);

		//DIBUJAR PERSONAJES, DISPAROS, HECHIZOS, BARRA DE VIDA Y MENSAJES DE BATALLA
        Personaje* atacante = juego.getAtacanteBatalla();
        Personaje* defensor = juego.getDefensorBatalla();

        if (atacante != nullptr && defensor != nullptr) {
            motor.dibujarPersonaje(*atacante);
            motor.dibujarPersonaje(*defensor);
            miBatalla.actualizarCombate(*atacante, *defensor, miCaja, miBatalla.obtenerObstaculos());
            motor.dibujarBarraVida(*atacante, *defensor);
        }

		for (int i = 0; i < 20; i++) { //RECORREMOS LA LISTA DE DISPAROS Y LOS DIBUJAMOS SI ESTAN ACTIVOS
            Disparo* d = miBatalla.return_nDisparos()[i];
            if (d) motor.dibujarDisparo(d);
        }
		for (int b = 0; b < 2; b++) //RECORREMOS LA MATRIZ DE HECHIZOS Y LOS DIBUJAMOS SI ESTAN ACTIVOS
            for (int i = 0; i < 3; i++) {
                Hechizo* h = miBatalla.return_nHechizos()[b][i];
                if (h != nullptr)
                    motor.dibujarHechizo(h);
            }

		motor.dibujarMensajesBatalla(miBatalla.getMensaje(),miBatalla.getMensajeBonus());
        motor.dibujarPuntuaciones(puntuacion_humanos, puntuacion_aliens);

        break;
    }
    //no borrar esta linea ni poner nada despues
    glutSwapBuffers();
}

// Procesa temporizadores, subrutinas de colisión y transiciones críticas basadas en condiciones de victoria
void OnTimer(int value) {
    //ir restando tiempo de las instrucciones primero (para que no se quede congelado el reloj)
    if (mostrandoInstruccionesTablero && tiempoInstruccionesTablero > 0) {
        tiempoInstruccionesTablero -= 20.0f;
        if (tiempoInstruccionesTablero <= 0) {
            mostrandoInstruccionesTablero = false;
            tiempoMensajeSelecciondeBando = 0.0f; // Limpiamos también el bando si expira el tiempo
        }
    }

    // CONGELACIÓN DEL JUEGO: Si siguen activas, frena el resto de la lógica, ayuda de IA
    if (estado == JUEGO && mostrandoInstruccionesTablero) {
        glutPostRedisplay();
        glutTimerFunc(20, OnTimer, 0);
        return;
    }

    //Lógica normal del juego (solo se ejecuta si no hay instrucciones en pantalla)
    if (estado == BATALLA) {
        Personaje* atacante = juego.getAtacanteBatalla();
        Personaje* defensor = juego.getDefensorBatalla();

		if (atacante != nullptr && defensor != nullptr) //VERIFICAMOS QUE LOS PERSONAJES EXISTAN ANTES DE ACTUALIZAR
            miBatalla.actualizarCombate(*atacante, *defensor, miCaja, miBatalla.obtenerObstaculos());
  
        if (fin_) {
            juego.finalizarBatalla();
            miTablero.reseteoColores();//reseta los colores de la casillas posibles 

            //DETERMINAR QUIEN HA GANADO
			HanGanado estado_fin = juego.DeterminarSiJuegoHaTerminado();
            HanGanado estado_fin2 = juego.victoriaPuntosPoder();
           //GUARDAR LA PUNTUACION DEL GANADOR PARA EL RANKING
            if (estado_fin == GanaronHumanos||estado_fin2==GanaronHumanos) {
                puntuacion_actual = puntuacion_humanos;
                estado = FIN_PARTIDA;
            }
            else if (estado_fin == GanaronAliens||estado_fin2==GanaronAliens) {
                puntuacion_actual = puntuacion_aliens;
                estado = FIN_PARTIDA;
            }
            else { //SI NO PUES, SE SIGUE LA PARTIDA
                juego.cambiarTurno();
                micursor.inicializar_tablero(juego.getTurno());
                estado = JUEGO;
            }
            glutPostRedisplay();
        }
    }
    if (estado == JUEGO) {
        HanGanado estado_fin3 = juego.victoriaPuntosPoder();
        if (estado_fin3 == GanaronHumanos) {
            puntuacion_actual = puntuacion_humanos;
            estado = FIN_PARTIDA;
        }
        else if (estado_fin3 == GanaronAliens) {
            puntuacion_actual = puntuacion_aliens;
            estado = FIN_PARTIDA;
        }
        glutPostRedisplay();
    }
    glutPostRedisplay();

    //Reducir tiempo del mensaje de bando cuando el juego ya está corriendo
    if (tiempoMensajeSelecciondeBando > 0) {
        tiempoMensajeSelecciondeBando -= 20.0f;
    }

    glutTimerFunc(20, OnTimer, 0);
}

//callback de teclado estandar
void OnKeyboardDown(unsigned char key, int x, int y)
{
    unsigned char c = std::tolower(key);

    if (estado == JUEGO && mostrandoInstruccionesTablero) {
        if (key == ' ') { //Solo el ESPACIO quita los carteles y descongela
            mostrandoInstruccionesTablero = false;
            tiempoInstruccionesTablero = 0.0f;
            tiempoMensajeSelecciondeBando = 0.0f;
            glutPostRedisplay();
        }
        return; // BLOQUEO: Cualquier otra tecla ('b', WASD, etc.) se ignora por completo
    }

    if (key == 27) { //ESC es la 27
        if (estado == MENU) exit(0);
        else estado = MENU;
    }



    if (c == 'r' && estado != FIN_PARTIDA) {
        estado = FIN_PARTIDA;
        glutPostRedisplay(); //Fuerza a OnDraw() a pintar la pantalla negra de dibuja_fin()
        return;
    }

    if (estado == FIN_PARTIDA) {
        std::string nombre;
        int puntos;

        std::cout << "\n--- REGISTRO DE PUNTUACION ---" << std::endl;
        std::cin.clear();

        std::cout << "TRES LETRAS: ";
        std::cin >> nombre;
        if (nombre.size() > 3) nombre = nombre.substr(0, 3);

        miMenu.actualizar_ranking(nombre);
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
            //Sincronización de tiempos a 15 segundos
            tiempoMensajeSelecciondeBando = 15000.0f;
            mostrandoInstruccionesTablero = true;
            tiempoInstruccionesTablero = 15000.0f;
        }
        glutPostRedisplay();
    }

    if (estado == JUEGO)
    {
        if (key == 'g') { //guardar partida
            GesionArchivos::guardarPartida(juego);
        }
        if (key == 'p') { //abrir partida guardada
            GesionArchivos::ejecutarPartidaGuardada(juego);
        }
           
        micursor.seleccion_personaje_tablero(c, juego.getTurno());
        
        if (micursor.obt_contador_selecciones() == 0) {
            micursor.inicializar_tablero(juego.getTurno());
        }
    }


    if (estado == BATALLA) {
       
        Personaje* p1 = juego.getAtacanteBatalla();
        Personaje* p2 = juego.getDefensorBatalla();

        if (p1 != nullptr && p2 != nullptr) { //VERIFICAMOS QUE LOS PERSONAJES EXISTAN
            Personaje* humano = nullptr; //IDENTIFICAR JUGADOR ACTUAL SI ES HUMANO

            if (p1->return_Bando() == HUMANO) //SI ERES HUMANO CON AWSD, V Y C, IMDEPENDIENTEMENTE DEL JUGADOR
            {
                humano = p1;
                miBatalla.KeyBatalla(key, *p1, *p2);
            }
            else if (p2 && p2->return_Bando() == HUMANO) {
                humano = p2;
                miBatalla.KeyBatalla(key, *p2, *p1);
            }
        }
    }
    glutPostRedisplay();
}

//callbac de teclado especial
void OnSpecialKeyboardDown(int key, int x, int y)
{
    //HACEMOS LO MISMO PARA LOS ALIENS

    if (estado == BATALLA) {

        Personaje* p1 = juego.getAtacanteBatalla();
        Personaje* p2 = juego.getDefensorBatalla();

        if (p1 != nullptr && p2 != nullptr) {//VERIFICAMOS QUE LOS PERSONAJES EXISTAN
            Personaje* alien = nullptr;

            if (p1->return_Bando() == ALIEN) alien = p1;
            else if (p2->return_Bando() == ALIEN) alien = p2;

            if (alien != nullptr)
                miBatalla.tecla_especial(key, *alien);
        }
    }

    if (estado == JUEGO )
    {
        micursor.mover_aliens(key, juego.getTurno());

        if (micursor.obt_contador_selecciones() == 0) {
            micursor.inicializar_tablero(juego.getTurno());
        }
    }
    glutPostRedisplay();
}

//Evalúa continuamente las regiones normalizadas de la ventana sin requerir pulsaciones para conmutar las flags de hover
void mousePassive(int x, int y) {
    float width = glutGet(GLUT_WINDOW_WIDTH);
    float height = glutGet(GLUT_WINDOW_HEIGHT);

    float nx = x / width;
    float ny = y / height;

    if (estado == MENU) {
        //Resetear estados
        hoverSalir = false;
        hoverSeleccion = false;
        hoverRanking = false;

        //Bot Salir
        if (nx > 0.125f && nx < 0.312f && ny > 0.2f && ny < 0.416f) hoverSalir = true;

        //Bot Selección
        if (nx > 0.337f && nx < 0.662f && ny > 0.483f && ny < 0.85f) hoverSeleccion = true;

        //Bot Ranking
        if (nx > 0.687f && nx < 0.875f && ny > 0.2f && ny < 0.416f) hoverRanking = true;

        glutPostRedisplay(); // Forzar redibujado para ver el cambio de color
    }
}

//Implementa de relación de aspecto rígido de 4:3. Genera barras grises simétricas para evitar estiramientos de texturas
void redimensionar(int width, int height) {
    float aspect_deseado = 800.0f / 600.0f;
    float aspect_actual = (float)width / (float)height;

    int vp_x = 0, vp_y = 0;
    int vp_width = width;
    int vp_height = height;

    //calcula las barras negras según la deformación de la ventana
    if (aspect_actual >= aspect_deseado) {
        vp_width = (int)(height * aspect_deseado);
        vp_x = (width - vp_width) / 2;
    }
    else {
        vp_height = (int)(width / aspect_deseado);
        vp_y = (height - vp_height) / 2;
    }

    // a'plica el Viewport protegido para no deformar nada
    glViewport(vp_x, vp_y, vp_width, vp_height);

    //NO fuerza gluOrtho2D aquí. Dejamos que OnDraw aplique la vista necesaria IA
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Dejamos la perspectiva por defecto del Main como base inicial
    gluPerspective(40.0, aspect_deseado, 0.1, 150);

    glMatrixMode(GL_MODELVIEW);
}