#pragma once

class Personaje;

class Hechizo
{
	friend class MotorGrafico;

public:
	enum TipoHechizo : int { PARALISIS, HIPERVELOCIDAD, POCION };
private:
	TipoHechizo tipo;
	bool activo;
	double posX, posY;
	double vx, vy;
	Personaje* objetivo;

	int usos_restantes;
	double t_recarga;
	double t_restante;

public:
	Hechizo(); //CONSTRUCTOR 
	void activar(double x, double y, double dirX, double dirY);
	void mover();
	bool Impacta(double Obx, double Oby, double Obr);

	void configurar(TipoHechizo t);
	void efectos(Personaje& objetivo);

	/////////METODOS///////////////
	bool return_Activo() const { return activo; }
	double return_X() const { return posX; }
	double return_Y() const { return posY; }
	Personaje* return_Obj() const { return objetivo; }

	void setActivo(bool estado) { activo = estado; }
	void setX(double nuevaX) { posX = nuevaX; }
	void setY(double nuevaY) { posY = nuevaY; }
	void setObj(Personaje* obj) { objetivo = obj; }
};