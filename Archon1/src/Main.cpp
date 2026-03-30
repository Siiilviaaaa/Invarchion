#include <iostream>
#include "freeglut.h"
#include "ETSIDI.h"

//porfavor no toqueis rutas de carpetas q me ha costado mucho y lloro, el archivo gitgnore igual
//llevo un par de horas para guardar temas de la carpeta de extra, confirmadme si se escucha
//hoy no se si me da tiempo a terminar de configurar el main, de ahi en adelante con todo
//si quereis configurarlo vosotras recordad q es copiar las funciones de freeglut del lab
//como se rompa lloro
int main() {
    std::cout << "Reproduciendo..." << std::endl;

    // Asegraros de que el nombre del archivo y la carpeta coincidan letra por letra
    ETSIDI::play("extra/mi_musica.mp3");

    std::cout << "Presiona Enter para salir y parar la musica..." << std::endl;
    getchar(); // Esto mantiene el programa vivo para q de tiempo a escuchar
    return 0;
}