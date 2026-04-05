#pragma once
#include "ETSIDI.h"


class Menu {
private:
    ETSIDI::Sprite _fondo;

    ETSIDI::Sprite _boton_jugar;
    ETSIDI::Sprite _boton_ranking;
    ETSIDI::Sprite _boton_exit;
    ETSIDI::Sprite _seleccion;

    // Aquí podríais añadir más Sprites para el menú si quereis, no lo haría la verdad

public:
    Menu();

    // Funciones principales del menú
    void inicializa_menu();
    void dibuja_menu();
    void dibuja_capa_seleccion();
};