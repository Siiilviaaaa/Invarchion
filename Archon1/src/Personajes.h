#pragma once

class Disparo;

enum Tipo_figura { LUCHADOR, ARQUERO, VOLADOR, EXCAVADOR, HECHICERO };
enum Bando { HUMANO, ALIEN };

class Personaje
{
	friend class MotorGrafico;

	Tipo_figura tipo;
	Bando bando;
	int vida, vida_max; //VARIABLE PARA COMPROBAR SU USAR POCION
	int danio;
	double v;
	double vel_base;
	double x, y;

	//DIRECCION
	double dirX, dirY;

	//HECHIZOS
	double t_paralisis;
	double t_hiperVelocidad;

public:
	//void sumarPuntos(int puntos);   METER EN JUEGO.H
	static Personaje crearPieza(Tipo_figura tipo, Bando b, double posX, double posY);
	void direccion(double dx, double dy);
	void actualizarEfectos();

	//////////METODOS//////////////
	Tipo_figura return_Tipo() const { return tipo; }
	Bando return_Bando()const { return bando; }
	int return_Vida() const { return vida; }
	int return_Danio() const { return danio; }
	double return_X() const { return x; }
	double return_Y() const { return y; }
	double return_Vbase() const { return vel_base; }
	int return_VidaMax() const { return vida_max; }
	double return_dirX() const { return dirX; }
	double return_dirY() const { return dirY; }

	///////////SETTERS/////////////////
	void setTipo(Tipo_figura nuevoTipo) { tipo = nuevoTipo; }
	void setVida(int nuevaVida) { vida = nuevaVida; }
	void setDanio(int nuevoDanio) { danio = nuevoDanio; }
	void setVelocidad(double V) { v = V;}
	void setV_base(double nuevaVBase) { vel_base = nuevaVBase; }
	void setX(double nuevaX) { x = nuevaX; }
	void setY(double nuevaY) { y = nuevaY; }
	void set_paralisis(double nuevoTiempo) { t_paralisis = nuevoTiempo; }
	void set_hiperVelocidad(double nuevoTiempo) { t_hiperVelocidad = nuevoTiempo; }
	void setVidaMax(int nuevaVidaMax) { vida_max = nuevaVidaMax; }
	void setBando(Bando nuevo) { bando = nuevo; }
};