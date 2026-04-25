#pragma once
#include "freeglut.h"
//para cambiar la vista y la perspectiva cuando entramos en batalla o en otras situaciones
class Camara {
	bool modoBatalla;
public:
	Camara() {
		modoBatalla = false;
	}
	void vistaMenu() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(50.0, 50.0, 20.0,
			50.0, 50.0, 0.0,
			0.0, 1.0, 0.0);
	}
	void vistaJuego() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(7.0, 5.0, 20.0,
			7.0, 5.0, 0.0,
			0.0, 1.0, 0.0);
	}
	void vistaBatalla() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(7.0, -5.0, 15.0,
			7.0, 5.0, 0.0,
			0.0, 1.0, 0.0);
	}
	

};