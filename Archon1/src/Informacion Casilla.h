#pragma once
#include "Personajes.h"
enum Tipocasilla{blanca, negra, lila};

class InfoCasilla {
	Tipocasilla tipo_color;
	Personajes_carac* personajeEncima;
public:
	InfoCasilla(Tipocasilla color = blanca):tipo_color(color), personajeEncima (nullptr){}

	Tipocasilla getColor() const { return tipo_color; }
	Personajes_carac* getPersonaje() const { return personajeEncima; }
	bool estaOcupada() const { return personajeEncima != nullptr; }

	void setPersonaje(Personajes_carac* p) { personajeEncima = p; }
	void setColor(Tipocasilla c) { tipo_color = c; }
};
