#include "Batalla.h"
#include "Hechizos.h"
#include <vector>

////VARIABLES GLOBALES
int Personaje::puntuacionHumanos = 0;
int Personaje::puntuacionAliens = 0;

//personaje::personaje(tipo_figura t, bando e, int x, int y)
Personaje::Personaje()
{
	
}

Personaje::~Personaje()
{
	//LIMPIAR MEMORIA DE LOS DISPAROS CUANDO EL PERSOANJE MUERE
	
}

void Personaje::sumarPuntos(int puntos)
{
	if (bando == HUMANO)
		puntuacionHumanos += puntos;
	else
		puntuacionAliens += puntos;
}

Personaje* Personaje::crearPieza(Tipo_figura tipo, int x, int y, Bando bando)
{
	Personaje* pieza = nullptr;

	//DECIDIR CARACTERISTICAS SEGUN EL TIPO DE PIEZA
	switch (tipo)
	{
	case LUCHADOR:
		pieza = new Luchador(x, y, bando); //es un hijo de personajes
		pieza->setVida(100);
		pieza->setVidaMax(100);
		pieza->setDanio(10);
		pieza->setV_base(0.8);

		pieza->setVelocidad(0.8);
		pieza->t_paralisis = 0;
		pieza->t_hiperVelocidad = 0;
		break;
	case ARQUERO:
		pieza = new Arquero(x, y, bando);
		pieza->setVida(80);
		pieza->setVidaMax(80);
		pieza->setDanio(15);
		pieza->setV_base(1.2);

		pieza->setVelocidad(1.2);
		pieza->t_paralisis = 0;
		pieza->t_hiperVelocidad = 0;
		break;
	case VOLADOR:
		pieza = new Volador(x, y, bando);
		pieza->setVida(140);
		pieza->setVidaMax(140);
		pieza->setDanio(8);
		pieza->setV_base(1.5);

		pieza->setVelocidad(1.5);
		pieza->t_paralisis = 0;
		pieza->t_hiperVelocidad = 0;
		break;
	case EXCAVADOR:
		pieza = new Excavador(x, y, bando);
		pieza->setVida(60);
		pieza->setVidaMax(60);
		pieza->setDanio(30);
		pieza->setV_base(1.0);

		pieza->setVelocidad(1.0);
		pieza->t_paralisis = 0;
		pieza->t_hiperVelocidad = 0;
		break;
	case HECHICERO:
		pieza = new Hechicero(x, y, bando);
		pieza->setVida(90);
		pieza->setVidaMax(90);
		pieza->setDanio(25);
		pieza->setV_base(1.3);
		pieza->setVelocidad(1.3);
		break;
	default:
		break;
	}
	if (pieza) pieza->setTipo(tipo);

	return pieza;
}

//void Personaje::lanzarDisparo() //NO HACE FALTA AHORA QUE HAY HIJOS
//{
//	if (tipo != ARQUERO) return;
//
//	for (int i = 0;i < MAX_DISPAROS;i++)
//	{
//		if (nDisparos[i]==nullptr)
//		{
//			nDisparos[i] = new Disparo(); //RESERVA MEMORIA
//
//			nDisparos[i]->setX(x);
//			nDisparos[i]->setY(y);
//			nDisparos[i]->setVX(0.2);
//			nDisparos[i]->setVY(1.0);
//			nDisparos[i]->setActivo(true);
//			break;
//		}
//	}
//}


//ESTO AHORA PASA A SER O DE LA CLASE DISPARO, O DE CADA HIJO--> NO TODAS LAS PIEZAS DISPARAN
//void Personaje::gestionarDisparos(Personaje& enemigo)
//{
//	for (int i = 0;i < MAX_DISPAROS;i++)
//		if (nDisparos[i] != nullptr)
//		{
//			nDisparos[i]->moverDisparo();
//
//			if (nDisparos[i]->Impacto(enemigo, *this) || !nDisparos[i]->return_Activo())
//			{ //SI NO ESTA ACTIVO Y SI IMPACTA
//				delete nDisparos[i]; //LIBERAR MEMORIA
//				nDisparos[i] = nullptr; //DEJAR HUECO LIBRE
//			}
//		}
//}

void Personaje::actualizarEfectos()
{
	if (t_paralisis > 0)
	{
		t_paralisis -= 0.1; //DISMINUIR TIEMPO DE PARALISIS
		if (t_paralisis < 0)
			t_paralisis = 0;
	}

	if (t_hiperVelocidad > 0)
	{
		t_hiperVelocidad -= 0.1; //DISMINUIR TIEMPO DE HIPER VELOCIDAD
		if (t_hiperVelocidad < 0)
			t_hiperVelocidad = 0;
	}

	//RECALCULAR LA VELOCIDAD ACTUAL
	if (t_paralisis > 0)
		setVelocidad(return_Vbase() * 0.5); //PARALISIS REDUCE VELOCIDAD A LA MITAD
	else if (t_hiperVelocidad > 0)
		setVelocidad(return_Vbase() * 1.5); //HIPER VELOCIDAD AUMENTA VELOCIDAD EN UN 50%
	else
		setVelocidad(return_Vbase()); //VELOCIDAD NORMAL
}

// Implementación básica para que el enlazador encuentre el código

void Luchador::ataque() {
	// Por ahora vacío para que compile, luego añades lógica cuerpo a cuerpo
	std::cout << "Luchador atacando cuerpo a cuerpo!" << std::endl;
}

void Volador::ataque() {
	// Lógica para ataque desde el aire
	std::cout << "Volador picando desde las alturas!" << std::endl;
}

void Hechicero::ataque() {
	// Aquí podrías llamar a usar_Hechizo[cite: 3, 10]
	std::cout << "Hechicero lanzando magia!" << std::endl;
}