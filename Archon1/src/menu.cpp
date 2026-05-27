#include "Menu.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include <iostream>
#include <algorithm>

Menu::Menu() :
    _fondo("extra/fondo_menu.png"),
    _boton_exit("extra/menu_boton_exit.png"),
    _boton_jugar("extra/menu_boton_jugar.png"),
    _boton_ranking("extra/menu_boton_ranking.png"),
    _seleccion("extra/menu_seleccion.png"),
    _ranking("extra/ranking_fondo.png")
{
    // Una vez inicializados los objetos, llamamos a la configuración de tamaño/posición
    inicializa_menu();
}

//Variable global externa
extern int puntuacion_actual;
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

void Menu::dibuja_menu(bool hJugar, bool hRanking, bool hSalir) {
    glDisable(GL_LIGHTING);

    glPushMatrix();
    // Traslación base del menú (fija)
    glTranslatef(39.8f, 41.0f, 0.0f);

    // 1. Dibujar el fondo estático primero sin ninguna alteración
    _fondo.draw();

    // Capa ligeramente al frente para evitar Z-fighting
    glTranslatef(0.0f, 0.0f, 0.5f);

    // 2. BOTÓN EXIT
    glPushMatrix();
    if (hSalir) {
        // Centro local: pos_x + (width/2) = 2 + 2.5 = 4.5f | pos_y + (height/2) = 9 + 2.25 = 11.25f
        glTranslatef(4.5f, 11.25f, 0.0f);
        glScalef(1.1f, 1.1f, 1.0f);
        glTranslatef(-4.5f, -11.25f, 0.0f);
    }
    _boton_exit.draw();
    glPopMatrix();

    // 3. BOTÓN JUGAR (Selección)
    glPushMatrix();
    if (hJugar) {
        // Centro local: 6.25 + 3.5 = 9.75f | 2.9 + 3.25 = 6.15f
        glTranslatef(9.75f, 6.15f, 0.0f);
        glScalef(1.1f, 1.1f, 1.0f);
        glTranslatef(-9.75f, -6.15f, 0.0f);
    }
    _boton_jugar.draw();
    glPopMatrix();

    // 4. BOTÓN RANKING
    glPushMatrix();
    if (hRanking) {
        // Centro local: 12.5 + 2.5 = 15.0f | 9 + 2.25 = 11.25f
        glTranslatef(15.0f, 11.25f, 0.0f);
        glScalef(1.1f, 1.1f, 1.0f);
        glTranslatef(-15.0f, -11.25f, 0.0f);
    }
    _boton_ranking.draw();
    glPopMatrix();

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

void Menu::dibuja_ranking()
{
    glDisable(GL_LIGHTING);
    glPushMatrix();

    //Posición aislada del Ranking
    glTranslatef(200.0f, 200.0f, 1.0f);

    glBegin(GL_POLYGON);
    //Arriba Izquierda: Rojo Neón Oscuro 
    glColor3f(0.35f, 0.0f, 0.0f);
    glVertex3f(-15.0f, 9.0f, -0.1f);

    //Arriba Derecha: Negro 
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(15.0f, 9.0f, -0.1f);

    //Abajo Derecha: Negro Total
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(15.0f, -9.0f, -0.1f);

    //Abajo Izquierda: Negro con rojo
    glColor3f(0.1f, 0.0f, 0.0f);
    glVertex3f(-15.0f, -9.0f, -0.1f);
    glEnd();

    //Reset de color para no teñir la textura
    glColor3f(1.0f, 1.0f, 1.0f);

    //Dibujo del ranking
    _ranking.setPos(-8.0f, -8.0f);
    _ranking.setSize(15, 15);
    _ranking.draw();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    //TEXTO DEL RANKING
    glColor3f(1.0f, 1.0f, 1.0f);

    float offset_y = 3.15f; //posicion de inicio de la lista en el eje Y

    for (const auto& linea : _lineas_ranking) {
        
        glRasterPos3f(-1.5f, offset_y, 0.2f); //posicion de inicio de la lista en el eje X

        for (char c : linea) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); //la impresion
        }

        offset_y -= 1.1f;//interlineado entre saltos de linea
    }

    //IGNORAR NO TOCAR, FUNCIONES PARA EL ACTUALIZADO
    glEnable(GL_TEXTURE_2D); 
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void Menu::cargar_ranking() {
    //ESTA FUNCIONALIDAD ES PARA Q EL RANKING SE CARGUE DEL FICHERO DE TXT

    _lineas_ranking.clear();
    std::ifstream archivo("extra/ranking.txt");
    std::string linea;

    if (archivo.is_open())  ////////abro lectura del archivo
    {
        int contador = 0;
        // Leemos mientras haya líneas y no hayamos llegado a 10 \n
        while (std::getline(archivo, linea) && contador < 10) {
            if (!linea.empty()) 
            {
                _lineas_ranking.push_back(linea); //Evita guardar líneas en blanco
                contador++;
            }
        }
        archivo.close();   ////////cierro lectura del archivo

        std::cout << "[SISTEMA] Ranking cargado: " << _lineas_ranking.size() << " entradas." << std::endl; //comentarios de debug
    }
    else 
    {
        _lineas_ranking.push_back("Error: extra/ranking.txt no encontrado");//caso de ausencia de fichero contemplado
    }
}

void Menu::actualizar_ranking(std::string nombre) {

    //LIMPIEZA Y APERTURA DEL FICHERO
    //Vacio el contenedor en memoria para cargar la lista desde cero sin duplicados
    _lista_puntuaciones.clear();
    std::ifstream lectura("extra/ranking.txt");
    std::string linea;

    //LECTURA Y PARSEO (EXTRACCIÓN DE DATOS)
    if (lectura.is_open())
    {
        //Leo el archivo línea por línea
        while (std::getline(lectura, linea)) {
            if (linea.empty()) continue; // Si la línea está vacía, saltamos a la siguiente

            //localizo los delimitadores del formato ("1. NOMBRE - PUNTOS")
            size_t pos_guion = linea.find(" - ");
            size_t pos_espacio_inicial = linea.find(" ");

            //Si se encuentran ambos delimitadores, procesamos la línea
            if (pos_guion != std::string::npos && pos_espacio_inicial != std::string::npos)
            {
                //Extraemos el sub原始texto correspondiente al nombre del jugador
                std::string n = linea.substr(pos_espacio_inicial + 1, pos_guion - pos_espacio_inicial - 1);
                try
                {
                    //Extraemos la puntuación y la convertimos de texto (string) a entero (int)
                    int p = std::stoi(linea.substr(pos_guion + 3));

                    //Guardamos la estructura (Nombre, Puntos) en el vector en memoria
                    _lista_puntuaciones.push_back({ n, p });
                }
                //Si el formato numérico está corrupto, capturamos la excepción y evitamos que el juego crashee
                catch (...) { continue; }
            }
        }
        lectura.close(); //Cerramos el flujo de lectura
    }

    //INSERCIÓN DEL NUEVO REGISTRO
    // Añadimos al vector la nueva partida usando el nombre recibido y la puntuación de la variable global
    _lista_puntuaciones.push_back({ nombre, puntuacion_actual });

    //Ordenamos el vector de mayor a menor puntuación utilizando el algoritmo std::sort
    //Mediante una función lambda comparamos el campo 'puntos' de cada estructura
    std::sort(_lista_puntuaciones.begin(), _lista_puntuaciones.end(),
        [](const EntradaRanking& a, const EntradaRanking& b) {
            return a.puntos > b.puntos;
        });

    //TRUNCADO (LÍMITE DE CAPACIDAD)
    //Si al añadir el nuevo récord superamos el tamaño permitido del Top, recortamos el vector a 9 elementos
    if (_lista_puntuaciones.size() > 9) {
        _lista_puntuaciones.resize(9);
    }

    //PERSISTENCIA (ESCRITURA EN DISCO)
    //Abro el fichero en modo escritura (sobrescribe el archivo anterior por completo)
    std::ofstream escritura("extra/ranking.txt");
    if (escritura.is_open())
    {
        //Vuelco el vector ordenado aplicando el formato indexado: "Posición. Nombre - Puntos"
        for (int i = 0; i < _lista_puntuaciones.size(); i++)
        {
            escritura << i + 1 << ". " << _lista_puntuaciones[i].nombre
                << " - " << _lista_puntuaciones[i].puntos << std::endl;
        }
        escritura.close(); //Cerramos el flujo de escritura
    }

    //Fuerzo la recarga de las strings en el buffer del menú para que el cambio se refleje inmediatamente en pantalla
    cargar_ranking();
}

void Menu::dibuja_fin() {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    // 1. FORZAR MATRIZ PROPIA EN 2D (Aislamiento total de cámaras)
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); // Plano de 800x600 píxeles reales

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 2. DIBUJAR EL FONDO NEGRO (Ajustado a coordenadas de pantalla completa)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(800.0f, 0.0f);
    glVertex2f(800.0f, 600.0f);
    glVertex2f(0.0f, 600.0f);
    glEnd();

    // 3. DIBUJAR EL TEXTO EN COORDENADAS DE PANTALLA REALES (X, Y)
    ETSIDI::setTextColor(1.0f, 1.0f, 0.0f); // Amarillo
    ETSIDI::setFont("fuentes/Bitwise.ttf", 24); // Tamaño un poco más grande para debug

    //300 píxeles de la izquierda y 400 píxeles desde abajo.
    ETSIDI::printxy("ENHORABUENA", 210.0f, 400.0f);

    ETSIDI::setFont("fuentes/Bitwise.ttf", 14);
    ETSIDI::printxy("HAS GANADO", 300.0f, 250.0f); // VE A LA CMD PARA DEJAR TU NOMBRE GRABADO EN LA HISTORIA
    ETSIDI::printxy(" PRESIONA ENTER Y", 200.0f, 120.0f);
    ETSIDI::printxy(" VE A LA CMD PARA DEJAR TU NOMBRE GRABADO EN LA HISTORIA", 50.0f, 100.0f);

    // 4. RESTAURAR MATRICES ORIGINALES (Para no romper el resto del juego)
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}