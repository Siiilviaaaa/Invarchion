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
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslated(personaje.x,personaje.y, 0.5);
	if (personaje.bando == HUMANO) glColor3ub(0, 0, 255);
	else glColor3ub(255, 0, 0);
	glutSolidSphere(0.5, 20, 20);
	glEnable(GL_LIGHTING);
	glPopMatrix();
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