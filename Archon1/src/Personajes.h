#pragma once
#include <iostream>

class Disparo;

enum Tipo_figura { LUCHADOR, ARQUERO, VOLADOR, EXCAVADOR, HECHICERO };
enum Bando { HUMANO, ALIEN };

class Personaje
{
	friend class MotorGrafico;
	friend class Cursor;
	friend class Juego;
	friend class Batalla;

protected:
	Tipo_figura tipo;
	Bando bando;
	int movimientos;
	int vida, vida_max;
	int danio;
	double v;
	double vel_base;
	double x, y;
	bool moviendose{ false };
	int temporizadorAtaque{ 0 };
	double dirX, dirY; //DIRECCION
	
	double t_paralisis;

public:
	Personaje() = default;
	Personaje(Tipo_figura t, Bando b, double posX, double posY);
	virtual ~Personaje();

	//crearPieza tiene que devolver un puntero por polimorfismo
	static Personaje* crearPieza(Tipo_figura tipo, Bando b, double posX, double posY);
	void direccion(double dx, double dy);
	void moverEnBatalla();

	//CONTROL DE ATAQUES
	virtual void activarAtaque();
	virtual bool estaAtacando() const;

	//CONTROL DE LOS HECHIZOS
	virtual bool actualizarEfectos();

	virtual void resetTrasBatalla(){}//lo dejo vacio pq ninigun personaje tiene que hacer nada excepto el arquero
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
	double return_paralisis() const { return t_paralisis; }

	void setTipo(Tipo_figura nuevoTipo) { tipo = nuevoTipo; }
	void setMovimientos(int mov) { movimientos = mov; }
	void setVida(int nuevaVida) { vida = nuevaVida; }
	void setDanio(int nuevoDanio) { danio = nuevoDanio; }
	void setVelocidad(double V) { v = V;}
	void setV_base(double nuevaVBase) { vel_base = nuevaVBase; }
	void setX(double nuevaX) 
	{
		//double ladoCasilla = 1.95;//esto imagino que debería de usar la variable que ya se hayadefinido, solo que no la encuentro
		//double offsetTableroX = nuevaX* ladoCasilla + 0.2;
		//x = offsetTableroX;
		x = nuevaX;
	}
	void setY(double nuevaY)
	{ 
		//double ladoCasilla = 1.95;//esto imagino que debería de usar la variable que ya se hayadefinido, solo que no la encuentro
		//double offsetTableroY = ladoCasilla * (4 - nuevaY) + 0.2; //creo que las coordenadas empiezan abajo, ashora lo veo, y ns que son filas y que columans
		//y = offsetTableroY;
		y = nuevaY;
	}
	double getY(void) const//para solucionar el prblema de espejo en las y
	{
		double ladoCasilla = 1.95f;
		double yCorregidaMirror = (4.2f * ladoCasilla) - y;
		return yCorregidaMirror;
	}
	
	void setVidaMax(int nuevaVidaMax) { vida_max = nuevaVidaMax; }
	void setBando(Bando nuevo) { bando = nuevo; }
	void set_paralisis(double tiempo) { t_paralisis = tiempo; }

};

class Luchador : public Personaje {
public:
	Luchador(Bando b, double posX, double posY);
};

class Arquero : public Personaje {
	int disparosRealizados{ 0 }; //CONTADOR DE DISPAROS
	double t_recarga{ 0.0 };
public:
	Arquero(Bando b, double posX, double posY);
	void resetMunicion() { disparosRealizados = 0; }
	void sumarDisparo() { disparosRealizados++; }
	int return_Disparos() { return disparosRealizados; }
	bool gestionRecarga();
	void resetTrasBatalla() override;
};

class Volador : public Personaje {
public:
	Volador(Bando b, double posX, double posY);
};

class Excavador : public Personaje {
	int temporizadorExcavacion{ 0 };
public:
	Excavador(Bando b, double posX, double posY);
	void activarAtaque() override;
	bool actualizarEfectos() override;
	bool estaBajoTierra() const;
	int getFaseExcavacion()const;
};

class Hechicero : public Personaje {
	int hechizoUtilizado = 0;
	int hechizosRestantes = 3;
public:
	Hechicero(Bando b, double posX, double posY);
	int return_HechizosRestantes() { return hechizosRestantes; }
	void usarHechizo() { hechizosRestantes--; }
	int HechizoUtilizado() { return hechizoUtilizado; }
	void siguienteHechizo() {
		hechizoUtilizado++;
		if (hechizoUtilizado > 2) hechizoUtilizado = 0;
	}

};