#pragma once

class Disparo;

enum Tipo_figura { LUCHADOR, ARQUERO, VOLADOR, EXCAVADOR, HECHICERO };
enum Bando { HUMANO, ALIEN };

class Personaje
{
	friend class MotorGrafico;
	friend class Cursor;

	Tipo_figura tipo;
	Bando bando;
	int movimientos;
	int vida, vida_max;
	int danio;
	double v;
	double vel_base;
	double x, y;
	double dirX, dirY; //DIRECCION

	int disparosRealizados; //CONTADOR DE DISPAROS
	int hechizoUtilizado = 0;
	int hechizosRestantes = 3;
	double t_paralisis;


public:
	Personaje() { this->disparosRealizados = 0; }
	static Personaje crearPieza(Tipo_figura tipo, Bando b, double posX, double posY);
	void direccion(double dx, double dy);
	void moverEnBatalla();

	//CONTROL DE LOS DISPAROS
	void resetMunicion() { disparosRealizados = 0; }
	void sumarDisparo() { disparosRealizados++; }
	int return_Disparos() { return disparosRealizados; }

	//CONTROL DE LOS HECHIZOS
	int return_HechizosRestantes() { return hechizosRestantes; }
	void usarHechizo() { hechizosRestantes--; }
	int HechizoUtilizado() { return hechizoUtilizado; }
	void siguienteHechizo() {
		hechizoUtilizado++;
		if (hechizoUtilizado > 2) hechizoUtilizado = 0;
	}
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
	double return_paralisis() const { return t_paralisis; }

	void setTipo(Tipo_figura nuevoTipo) { tipo = nuevoTipo; }
	void setVida(int nuevaVida) { vida = nuevaVida; }
	void setDanio(int nuevoDanio) { danio = nuevoDanio; }
	void setVelocidad(double V) { v = V;}
	void setV_base(double nuevaVBase) { vel_base = nuevaVBase; }
	void setX(double nuevaX) { x = nuevaX; }
	void setY(double nuevaY) { y = nuevaY; }
	void setVidaMax(int nuevaVidaMax) { vida_max = nuevaVidaMax; }
	void setBando(Bando nuevo) { bando = nuevo; }
	void set_paralisis(double tiempo) { t_paralisis = tiempo; }
};