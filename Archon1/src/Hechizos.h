#pragma once
#include "Personajes.h"

class Hechizo
{
	friend class MotorGrafico;

public:
	enum TipoHechizo : int { PARALISIS, DANIO, TELETRANSPORTE };
private:
	TipoHechizo tipo;
	bool activo;
	double posX, posY;
	double vx, vy;
	Personaje* objetivo;
	Bando bando;

public:
	Hechizo(TipoHechizo tipo_recibido, Bando bando_recibido); //CONSTRUCTOR 
	void activar(double x, double y, double dirX, double dirY);
	void mover();
	bool Impacta(double Obx, double Oby, double Obr);

	/////////METODOS///////////////
	TipoHechizo return_Tipo() const { return tipo; }
	bool return_Activo() const { return activo; }
	double return_X() const { return posX; }
	double return_Y() const { return posY; }
	Personaje* return_Obj() const { return objetivo; }
	Bando return_Bando() const { return bando; }

	void setActivo(bool estado) { activo = estado; }
	void setX(double nuevaX) { posX = nuevaX; }
	void setY(double nuevaY) { posY = nuevaY; }
	void setObj(Personaje* obj) { objetivo = obj; }
	void setBando(Bando b) { bando = b; }
};