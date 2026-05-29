#pragma once
#include <string>

class Juego;

class GesionArchivos
{
public: 
	static void guardarPartida(const Juego& j);
	static void ejecutarPartidaGuardada(Juego& juego);
};

