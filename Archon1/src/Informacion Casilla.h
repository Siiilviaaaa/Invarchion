#pragma once
#include "Personajes.h"
enum Tipocasilla{blanca, negra, lila, punto_poder};

class InfoCasilla 
{
	friend class Cursor;
	Tipocasilla tipo_color;
	Personaje* personajeEncima;
	bool puntoPoder;
public:
	InfoCasilla(Tipocasilla color = blanca):tipo_color(color), personajeEncima (nullptr), puntoPoder(false) {}

	Tipocasilla getColor() const { return tipo_color; }
	Personaje* getPersonaje() const { return personajeEncima; }
	bool estaOcupada() const { return personajeEncima != nullptr; }

	void setPersonaje(Personaje* p) { personajeEncima = p; }
	void setColor(Tipocasilla c) { tipo_color = c; }

	bool getPuntoPoder() const { return puntoPoder; }
	void setPuntoPoder(bool p) { puntoPoder = p; }
};
