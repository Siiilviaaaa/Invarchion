#pragma once
#include "ETSIDI.h"
#include <string>
#include <vector>
#include <fstream>

struct EntradaRanking {
    std::string nombre;
    int puntos;
};

class Menu {
private:
    ETSIDI::Sprite _fondo;
    ETSIDI::Sprite _boton_jugar;
    ETSIDI::Sprite _boton_ranking;
    ETSIDI::Sprite _boton_exit;
    ETSIDI::Sprite _seleccion;
    ETSIDI::Sprite _ranking;

    std::vector<std::string> _lineas_ranking;

    // CORRECCIÓN: El vector debe ser un miembro de la clase
    std::vector<EntradaRanking> _lista_puntuaciones;

public:
    Menu();

    void inicializa_menu();
    // Cambia la línea actual por esta en la sección pública de tu clase Menu:
    void dibuja_menu(bool hJugar = false, bool hRanking = false, bool hSalir = false);
    void dibuja_capa_seleccion();

    void dibuja_ranking();
    void cargar_ranking();
    void actualizar_ranking(std::string nombre);
    void dibuja_fin();
};