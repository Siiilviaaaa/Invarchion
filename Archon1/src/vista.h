#pragma once
#include "freeglut.h"
//para cambiar la vista y la perspectiva cuando entramos en batalla o en otras situaciones
class Camara {
	
public:
	Camara() {
		
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
		gluLookAt(9.0, 9.0, 35.0,
			9.0, 9.0, 0.0,
			0.0, 1.0, 0.0);
	}
	void vistaBatalla() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(10.0, 7.5, 23.0,
			10.0, 7.5, 0.0,
			0.0, 1.0, 0.0);
	}
	void vistaRanking() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(200.0, 200.0, 20.0,
			200.0, 200.0, 0.0,
			0.0, 1.0, 0.0);
	}
	

};