#include "MotorGrafico.h"
#include "freeglut.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

MotorGrafico::MotorGrafico() :
	numObstaculos(5),
	luchador("Recursos/pruebacolor.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	soldado("Recursos/pruebacolor.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	volador("Recursos/pruebacolor.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	minero("Recursos/pruebacolor.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	hechicero("Recursos/pruebacolor.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),

	golem("Recursos/golem.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	arquero("Recursos/arquero.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	murcielago("Recursos/murcielago.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	gusano("Recursos/gusano.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),
	mago("Recursos/mago.png", numColumnasSpritePersonaje, numFilasSpritePersonaje),

	barraVida("Recursos/barra.png"),
	calavera("Recursos/calavera.png"),
	Paralisis("Recursos/hechizo1.png"),
	Velocidad("Recursos/hechizo2.png"),
	Pocion("Recursos/pocion.png")
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
void MotorGrafico::dibujarCursor(Cursor cursor)
{
	float ancho=1.0;//lo que mide cada lado del cuadraro-tablero
	//se añade en el motor grafico la funcion de que el cursor se dibuje, para que cuando se modifiquen las corrdenadas se repinte
	glLineWidth(0.2f); //grosor del delineado de 0.2, que se vea pero no excesivo 
	glColor3ub(255, 128, 0);//color naranja llamativo
	glBegin(GL_LINE_LOOP);
	glVertex2f(cursor.obt_columna(), cursor.obt_fila());
	glVertex2f(cursor.obt_columna() + ancho, cursor.obt_fila());
	glVertex2f(cursor.obt_columna() + ancho, cursor.obt_fila() + ancho);
	glVertex2f(cursor.obt_columna(), cursor.obt_fila() + ancho);
	glEnd();
	glLineWidth(1.0f); // volver al grosor normal
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

	return;

}

void MotorGrafico::dibujarDisparo(Disparo* disparo)
{
	if (disparo == nullptr)return;

	glPushMatrix();
	glTranslated(disparo->x, disparo->y, 0.5);
	glDisable(GL_LIGHTING);
	glColor3ub(255, 255, 0);
	glutSolidSphere(0.4, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void MotorGrafico::dibujarHechizo(const Hechizo& hechizo)
{
	if (hechizo.activo)
	{
		if (hechizo.tipo == Hechizo::PARALISIS) //esto mejor con un swithc no?
		{
			Paralisis.setPos(hechizo.posX, hechizo.posY);
			Paralisis.draw();
		}
		else if(hechizo.tipo == Hechizo::HIPERVELOCIDAD)
		{
			Velocidad.setPos(hechizo.posX, hechizo.posY);
			Velocidad.draw();
		}
		else if(hechizo.tipo == Hechizo::POCION)
		{
			Pocion.setPos(hechizo.posX, hechizo.posY);
			Pocion.draw();
		}
	}
}

void MotorGrafico::dibujarVida_Muerte(const Personaje& humano, const Personaje& alien)
{
	//BARRA HUMANOS (IZQ)
	float porcentaje_h = (float)humano.vida / humano.vida_max;
	int frame = 10; //NO SE MUY BIEN COMO AJUSTAR LOS FRAMES

	barraVida.setPos(5.0, 18.0);
	barraVida.draw();

	//BARRA ALIENS (DCH)
	float porcentaje_a = (float)alien.vida / alien.vida_max;

	barraVida.setPos(15.0, 18.0);
	barraVida.draw();

	if (humano.vida <= 0) //SI MUERE, DIBUJAR CALAVERA
	{
		calavera.setPos(humano.x, humano.y + 1.2); //DIBUJAR CALAVERA ENCIMA DEL PERSONAJE
		calavera.draw();
	}

	if (alien.vida <= 0)
	{
		calavera.setPos(alien.x, alien.y + 1.2);
		calavera.draw();
	}
}
