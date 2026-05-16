#include "MotorGrafico.h"
#include "freeglut.h"
#include <ctime>
#include <cstdlib>
#include <iostream>


MotorGrafico::MotorGrafico() :
	numObstaculos(5),
	luchador("Recursos/arquero.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	soldado("Recursos/arquero.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	volador("Recursos/arquero.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	minero("Recursos/arquero.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	hechicero("Recursos/arquero.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),

	golem("Recursos/golem.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	arquero("Recursos/arquero.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	murcielago("Recursos/murcielago.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	gusano("Recursos/gusano.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	mago("Recursos/mago.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),

	barraVida("Recursos/barra.png")
	/*calavera("Recursos/calavera.png"),
	Paralisis("Recursos/hechizo1.png"),
	Velocidad("Recursos/hechizo2.png"),
	Pocion("Recursos/pocion.png")*/

{
	for (int i = 0; i < 5; i++) {
		listaObstaculos[i] = nullptr;
	}
}

void MotorGrafico::inicializarBatalla()
{
	srand((unsigned int)time(NULL));
	int aceptados = 0;
	for (int i = 0; i < numObstaculos; i++) {
		if (listaObstaculos[i]) delete listaObstaculos[i];
		listaObstaculos[i] = nullptr;
	}
	double r = 1.0;
	const float dist_min = 3.5f;
	while (aceptados < numObstaculos) {
		double rx = r + ((double)rand()/RAND_MAX) *(20 - 2 * r);
		double ry = r + ((double)rand() / RAND_MAX) * (10 - 2 * r);
		bool colision = false;
		for (int j = 0; j < aceptados; j++) {
			Obstaculo* existente = listaObstaculos[j];
			float dx = (float)(rx - existente->return_X());
			float dy = (float)(ry - existente->return_Y());
			float distancia = sqrtf(powf(dx, 2) + powf(dy, 2));
			if (distancia < dist_min) {
				colision = true;
				break;
			}
		}
		if (!colision) {
			listaObstaculos[aceptados] = new Obstaculo(rx, ry, r);
			aceptados++;
		}
	}
}

void MotorGrafico::dibujarPared(const Pared& p)
{
	glDisable(GL_LIGHTING);
	glColor3ub(p.r, p.g, p.b);
	glBegin(GL_POLYGON);
	glVertex3f(p.x1, p.y1, 2);
	glVertex3f(p.x2, p.y2, 2);
	glVertex3f(p.x2, p.y2, -2);
	glVertex3f(p.x1, p.y1, -2);
	glEnd();
	glEnable(GL_LIGHTING);
}

void MotorGrafico::dibujarCaja(const Caja& c)
{
	dibujarPared(c.suelo);
	dibujarPared(c.techo);
	dibujarPared(c.izq);
	dibujarPared(c.dcha);
	//para dibujar fondo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("Recursos/batalla3.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2d(-0, 0);
	glTexCoord2d(1, 1); glVertex2d(20, 0);
	glTexCoord2d(1, 0); glVertex2d(20, 15);
	glTexCoord2d(0, 0); glVertex2d(0, 15);
	glEnd();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("Recursos/obstaculo3.png").id);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);
	for (int i = 0; i < numObstaculos; i++) {
		if (listaObstaculos[i] != nullptr) {
			double x = listaObstaculos[i]->return_X();
			double y = listaObstaculos[i]->return_Y();
			double r = listaObstaculos[i]->return_Radio();
			//glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
			glBegin(GL_QUADS);
			glTexCoord2d(0, 1); glVertex3d(x - r, y - r, 0.1);
			glTexCoord2d(1, 1); glVertex3d(x + r, y - r, 0.1);
			glTexCoord2d(1, 0); glVertex3d(x + r, y + r, 0.1);
			glTexCoord2d(0, 0); glVertex3d(x - r, y + r, 0.1);
			glEnd();
		}
	}
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void MotorGrafico::dibujarCursor(Cursor cursor) const
{

	float x = cursor.obt_columna() * lado;
	float y = cursor.obt_fila() * lado;

	glDisable(GL_LIGHTING);

	glLineWidth(5.0f);
	glColor3ub(cursor.obt_color_r(), cursor.obt_color_v(), cursor.obt_color_a());

	glBegin(GL_LINE_LOOP);
	glVertex3f(x, y, 0.1f);
	glVertex3f(x + lado, y, 0.1f);
	glVertex3f(x + lado, y + lado, 0.1f);
	glVertex3f(x, y + lado, 0.1f);
	glEnd();

	glLineWidth(1.0f);

	glEnable(GL_LIGHTING);
}

void MotorGrafico::dibujarPersonaje(const Personaje& personaje)
{
	ETSIDI::SpriteSequence* SpriteActual = nullptr;
	switch (personaje.tipo) {
	case LUCHADOR:
		SpriteActual = (personaje.bando == HUMANO) ? &luchador : &golem;
		break;
	case ARQUERO:
		SpriteActual = (personaje.bando == HUMANO) ? &soldado : &arquero;
		break;
	case VOLADOR:
		SpriteActual = (personaje.bando == HUMANO) ? &volador : &murcielago;
		break;
	case EXCAVADOR:
		SpriteActual = (personaje.bando == HUMANO) ? &minero : &gusano;
		break;
	case HECHICERO:
		SpriteActual = (personaje.bando == HUMANO) ? &hechicero : &mago;
		break;
	default:
		break;
	}

	if (SpriteActual) {//si existe un sprite
		glPushMatrix();
		glDisable(GL_LIGHTING);//la luz para q no haga sombra
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//para la transparencia
		glTranslated(personaje.x, personaje.y, 0.5);
		//SpriteActual->setPos(personaje.x, personaje.y);
		SpriteActual->setCenter(0, 0);
		SpriteActual->setSize(1.8, 1.8);
		if (personaje.bando == ALIEN) {

			SpriteActual->flip(true, false); //así miran a la izq
			glTranslated(1.95, 0, 0);
		}
		if (personaje.moviendose) {
			///SpriteActual -> setState(1, false);
			//SpriteActual->loop();

		}
		else {
			SpriteActual->setState(0);
		}
		SpriteActual->draw();
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}

void MotorGrafico::dibujarDisparo(Disparo* disparo)
{
	if (disparo == nullptr)return;

	glPushMatrix();
	glTranslated(disparo->x, disparo->y, 0.5);
	glDisable(GL_LIGHTING);
	if (disparo->bando == HUMANO) glColor3ub(255, 255, 255);
	else glColor3ub(0, 255, 0);
	glutSolidSphere(0.2, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void MotorGrafico::dibujarHechizo(Hechizo* hechizo)
{
	if (hechizo == nullptr)return;

	glPushMatrix();
	glTranslated(hechizo->posX, hechizo->posY, 0.5);
	glDisable(GL_LIGHTING);
	switch (hechizo->tipo) {
	case 0: glColor3f(0.0f, 1.0f, 1.0f); break; //PARALISIS
	case 1: glColor3f(1.0f, 0.0f, 1.0f); break; //DANIO
	case 2: glColor3f(0.0f, 1.0f, 0.0f); break; //TELETRANSPORTE
	}
	glutSolidSphere(0.2, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void MotorGrafico::dibujarBarraVida(Personaje& j1, Personaje& j2)
{
	float porcentaje1 = (float)j1.return_Vida() / (float)j1.return_VidaMax();
	float porcentaje2 = (float)j2.return_Vida() / (float)j2.return_VidaMax();
	recortarBarra(porcentaje1, 1.0f, 1.0f, 4.5f, 0.8f);
	recortarBarra(porcentaje2, 14.5f, 1.0f, 4.5f, 0.8f);
}

void MotorGrafico::recortarBarra(float porcentaje, float x, float y, float ancho, float alto)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("Recursos/barra.png").id);
	if (porcentaje < 0) porcentaje = 0;
	if (porcentaje > 1) porcentaje = 1;
	int indice = (int)((1.0f - porcentaje) * 9.0f);
	if (indice > 9) indice = 9;
	float paso = 1.0f/10.0f;
	float vSup = (float)indice * paso;
	float vInf = vSup + 0.1f;

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, vSup); glVertex2f(x, y + alto);        
		glTexCoord2f(1.0f, vSup); glVertex2f(x + ancho, y + alto); 
		glTexCoord2f(1.0f, vInf); glVertex2f(x + ancho, y);        
		glTexCoord2f(0.0f, vInf); glVertex2f(x, y);               
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

void MotorGrafico::dibujaTablero() {
	// SEGURIDAD: Si no hay tablero, no intentamos leer datos (evita el crash)
	if (tablero == nullptr) return;

	dibujarFondo();
	dibujarBordeTurno();

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			const Casilla* c = tablero->getCasilla(i, j);
			dibujarCasilla(c);
		}
	}
}

void MotorGrafico::dibujarFondo() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("Recursos/fondotablero.png").id);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);

	float m = 2.0f;
	float ancho = 7 * lado;
	float alto = 5 * lado;

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-m, -m, -0.1f);
	glTexCoord2d(0, 1); glVertex3f(ancho + m, -m, -0.1f);
	glTexCoord2d(0, 0); glVertex3f(ancho + m, alto + m, -0.1f);
	glTexCoord2d(1, 0); glVertex3f(-m, alto + m, -0.1f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void MotorGrafico::dibujarBordeTurno() {
	// Usamos el tablero guardado para saber el turno
	if (tablero->getTurno() == 0)
		glColor3f(0.0f, 0.3f, 0.6f);
	else
		glColor3f(0.6f, 0.0f, 0.0f);

	float anchoTotal = 7 * lado;
	float altoTotal = 5 * lado;
	glLineWidth(7.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0.05f);
	glVertex3f(anchoTotal, 0, 0.05f);
	glVertex3f(anchoTotal, altoTotal, 0.05f);
	glVertex3f(0, altoTotal, 0.05f);
	glEnd();
}

void MotorGrafico::dibujarCasilla(const Casilla* c) {
	if (c == nullptr) return;

	float x = c->getcolumna() * lado;
	float y = c->getfila() * lado;

	switch (c->getInfo()->getColor()) {
	case blanca: glColor3f(1.0f, 1.0f, 1.0f); break;
	case negra:  glColor3f(0.1f, 0.1f, 0.1f); break;
	case lila:   glColor3f(0.5f, 0.0f, 0.5f); break;
	}

	if (c->getInfo()->getColor() != lila) {
		glBegin(GL_QUADS);
		glVertex3f(x, y, 0.0f);
		glVertex3f(x + lado, y, 0.0f);
		glVertex3f(x + lado, y + lado, 0.0f);
		glVertex3f(x, y + lado, 0.0f);
		glEnd();
	}

	glColor3f(0.2f, 0.2f, 0.2f);
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(x, y, 0.005f);
	glVertex3f(x + lado, y, 0.005f);
	glVertex3f(x + lado, y + lado, 0.005f);
	glVertex3f(x, y + lado, 0.005f);
	glEnd();
}
