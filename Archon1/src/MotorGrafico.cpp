#include "MotorGrafico.h"
#include <ctime>
#include <cstdlib>

MotorGrafico::MotorGrafico() :
	numObstaculos(5),
	luchador("Recursos/luchador.png"), 	
	soldado("Recursos/soldado.png"),	
	volador("Recursos/volador.png"),
	minero("Recursos/minero.png"),	
	hechicero("Recursos/hechicero.png"),

	golem("Recursos/golem.png"),	
	arquero("Recursos/arquero.png"),
	murcielago("Recursos/murcielago.png"),
	gusano("Recursos/gusano.png"),
	mago("Recursos/mago.png"),

	barraVida("Recursos/barra.png"),
	calavera("Recursos/calavera.png"),
	Flecha("Recursos/flecha.png"),
	Paralisis("Recursos/hechizo1.png"),
	Velocidad("Recursos/hechizo2.png"),
	Pocion("Recursos/pocion.png")
{
	//DIMENSIONES
	luchador.setSize(2.0, 2.0);
	golem.setSize(2.0, 2.0);
	soldado.setSize(2.0, 2.0);
	arquero.setSize(2.0, 2.0);
	volador.setSize(2.0, 2.0);
	murcielago.setSize(2.0, 2.0);
	minero.setSize(2.0, 2.0);
	gusano.setSize(2.0, 2.0);
	hechicero.setSize(2.0, 2.0);
	mago.setSize(2.0, 2.0);

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

void MotorGrafico::dibujarPersonaje(const Personaje& personaje)
{
	//HACER ANIMACION!!!!!!!!!!!!!!!!
	switch (personaje.tipo)
	{
	case Tipo_figura::LUCHADOR:
		if (personaje.bando == HUMANO)
		{
			luchador.setPos(personaje.x, personaje.y);
			luchador.draw();
		}else
		{
			golem.setPos(personaje.x, personaje.y);
			golem.draw();
		}
		break;
	case Tipo_figura::ARQUERO:
		if (personaje.bando == HUMANO)
		{
			soldado.setPos(personaje.x, personaje.y);
			soldado.draw();
		}
		else
		{
			arquero.setPos(personaje.x, personaje.y);
			arquero.draw();
		}
		break;
	case Tipo_figura::VOLADOR:
		if (personaje.bando == HUMANO)
		{
			volador.setPos(personaje.x, personaje.y);
			volador.draw();
		}
		else
		{
			murcielago.setPos(personaje.x, personaje.y);
			murcielago.draw();
		}
		break;
	case Tipo_figura::EXCAVADOR:
		if (personaje.bando == HUMANO)
		{
			minero.setPos(personaje.x, personaje.y);
			minero.draw();
		}
		else
		{
			gusano.setPos(personaje.x, personaje.y);
			gusano.draw();
		}
		break;
	case Tipo_figura::HECHICERO:
		if (personaje.bando == HUMANO)
		{
			hechicero.setPos(personaje.x, personaje.y);
			hechicero.draw();
		}
		else
		{
			mago.setPos(personaje.x, personaje.y);
			mago.draw();
		}
		break;
	default:
		break;
	}
}

void MotorGrafico::dibujarDisparo(const Disparo& disparo)
{
	if (disparo.activo)
	{
		Flecha.setPos(disparo.x, disparo.y);
		Flecha.draw();
	}
}

void MotorGrafico::dibujarHechizo(const Hechizo& hechizo)
{
	if (hechizo.activo)
	{
		if (hechizo.tipo == Hechizo::PARALISIS)
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
