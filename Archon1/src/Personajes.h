#pragma once
#include <vector>
#include <iostream>

class Disparo;

enum Tipo_figura { LUCHADOR, ARQUERO, VOLADOR, EXCAVADOR, HECHICERO };
enum Bando { HUMANO, ALIEN };

class Personaje
{
protected: //asi pueden ver estas variables los hijos
	friend class MotorGrafico;

	Tipo_figura tipo;
	Bando bando;
	int vida;
	int danio;
	double velocidad;
	double vel_base;
	double x, y;

	//DISPAROS TENGO QEU CAMBIARLOOOO
	static const int MAX_DISPAROS = 10;
	//std::vector<Disparo*> disparos;
	//Disparo* nDisparos[MAX_DISPAROS];

	//HECHIZOS
	double t_paralisis;
	double t_hiperVelocidad;
	int vida_max; //VARIABLE PARA COMPROBAR SU USAR POCION

public:
	static int puntuacionHumanos;
	static int puntuacionAliens;
	
	//Personaje(Tipo_figura t, Bando e, int x, int y);
	
	//////////METODOS//////////////							   
	Personaje();
	virtual ~Personaje();

	void sumarPuntos(int puntos);
	static Personaje* crearPieza(Tipo_figura tipo, int x, int y, Bando bando);
	void actualizarEfectos();
	void gestionarDisparos(Personaje& enemigo);
	void lanzarDisparo();
	virtual void ataque() = 0; //esto es para que cada hijo defina su propiio método

	////////////GETTERS/////////////////
	Tipo_figura return_Tipo() const { return tipo; }
	Bando return_Bando()const { return bando; }
	int return_Vida() const { return vida; }
	int return_Danio() const { return danio; }
	double return_X() const { return x; }
	double return_Y() const { return y; }
	double return_Vbase() const { return vel_base; }
	int return_VidaMax() const { return vida_max; }

	//std::vector<Disparo*>& getDisparos() { return disparos; }
	//Disparo* (&return_Disparos())[10] { return nDisparos; }

	///////////SETTERS/////////////////
	void setTipo(Tipo_figura nuevoTipo) { tipo = nuevoTipo; }
	void setVida(int nuevaVida) { vida = nuevaVida; }
	void setDanio(int nuevoDanio) { danio = nuevoDanio; }
	void setVelocidad(double nuevaVelocidad) { velocidad = nuevaVelocidad; }
	void setV_base(double nuevaVBase) { vel_base = nuevaVBase; }
	void setX(double nuevaX) { x = nuevaX; }
	void setY(double nuevaY) { y = nuevaY; }
	void set_paralisis(double nuevoTiempo) { t_paralisis = nuevoTiempo; }
	void set_hiperVelocidad(double nuevoTiempo) { t_hiperVelocidad = nuevoTiempo; }
	void setVidaMax(int nuevaVidaMax) { vida_max = nuevaVidaMax; }
};

//hago HIJOS, para que cada personaje tenga habilidades distintas

class Luchador : public Personaje {
public: 
	Luchador(int _x, int _y, Bando _bando) : Personaje() {}

	void ataque(); //asi se puede tener atauqes distintos para cada personaje
};

class Arquero : public Personaje {
private: 
public:
	Arquero(int _x, int _y, Bando _bando) : Personaje() {}

	void ataque() override { //asi se puede tener atauqes distintos para cada personaje
	}
};

class Volador : public Personaje {
public:
	Volador(int _x, int _y, Bando _bando) : Personaje() {}

	void ataque(); //asi se puede tener atauqes distintos para cada personaje
};

class Excavador : public Personaje {
private: 
	bool estaBajoTierra{ false };
public:
	Excavador(int _x, int _y, Bando _bando) : Personaje() {}

	void ataque() override{}
	void cambiarSiEstaBajoTierra() {
		if (!estaBajoTierra) estaBajoTierra = true;
		else estaBajoTierra = false;
	}
};

class Hechicero : public Personaje {
public:
	Hechicero(int _x, int _y, Bando _bando) : Personaje() {}

	void ataque();
};
