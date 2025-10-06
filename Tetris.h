#ifndef TETRIS_H
#define TETRIS_H

#include "Partida.h"
#include "LlistaJugadors.h"

class Tetris
{
public: 
	Tetris() { m_pausa = false; } //Constructor per defecte

	int juga(int mode, Screen& pantalla); //Metode per jugar en funcio del mode. Es passa la pantalla per referencia per poder jugar mes d'una vegada
	void mostraPuntuacions(); //Metoda que mostra les puntuacions historiques
	void afeigeixPuntuacions(const string& nom, int puntuacions); //Metode que afegeix un nou jugador a la llista de puntuacions historiques
	 
private:
	Partida m_partida; //Atribut que permet gestionar una partida
	LlistaJugadors m_puntuacions; //Atribut que gestiona les puntuacions historiques

	bool m_pausa; //Booleà que idica si la`partida esta pausada o no

	int jugaNormal(Screen& pantalla);  //Metode per jugar normal
	void jugaFitxer(Screen& pantalla);  //Metode pel mode test
	void acabarTetris(Screen& pantalla); //Metode s'acabar el tetris
	void pausa(int mode, double deltaTime); //Metode per pausar la partida
};

#endif
