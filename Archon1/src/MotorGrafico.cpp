#include "MotorGrafico.h"

MotorGrafico::MotorGrafico() :
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
}

void MotorGrafico::dibujarPared(const Pared& p)
{
	glDisable(GL_LIGHTING);
	glColor3ub(p.r, p.g, p.b);
	glBegin(GL_POLYGON);
	glVertex3f(p.x1, p.y1, 10);
	glVertex3f(p.x2, p.y2, 10);
	glVertex3f(p.x2, p.y2, -10);
	glVertex3f(p.x1, p.y1, -10);
	glEnd(); //
	glEnable(GL_LIGHTING);
}

void MotorGrafico::dibujarCaja(const Caja& c)
{
	dibujarPared(c.suelo);
	dibujarPared(c.techo);
	dibujarPared(c.izq);
	dibujarPared(c.dcha);

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
		Flecha.setPos(disparo.x, disparo.x);
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