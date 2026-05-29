#pragma once
#include <string>

class Juego;

class GesionArchivos
{
public: 
	static void guardarPartida(const Juego& j);
	void ejecutarPartidaGuardada();
};

