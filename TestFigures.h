#ifndef TESTFIGURA_H
#define TESTFIGURA_H

#include "InfoJoc.h"

class TestFigures
{
public:
	TestFigures() { m_figura = NO_FIGURA; m_fila = 0; m_columna = 0; m_gir = 0; m_seguent = nullptr; } //Constructor per defecte
	TestFigures(const TipusFigura& figura, int fila, int columna, int gir) { m_figura = figura; m_fila = fila; m_columna = columna; m_gir = gir; m_seguent = nullptr; } //Constructor per parametres
	TipusFigura getFigura() const { return m_figura; } //Mètode que retorna el tipus de figura
	int getFila() const { return m_fila; } //Metode que retorna la fila on es troba la figura
	int getColumna() const { return m_columna; } //Metode que retorna la columna on es troba la figura
	int getGir() const { return m_gir; } //Metode que retorna el num de girs horaris de la figura
	TestFigures* getSeguent() const { return m_seguent; } //Metode que retorna on esta la figura seguent
	void setSeguent(TestFigures* seguent) { m_seguent = seguent; } //Metode que estableix on apunta la seguent figura

private:
	TipusFigura m_figura; //Atribut que indica el tpus de figura que es 
	int m_fila; //Atribut que indica la fila en la que es troba la figura
	int m_columna; //Atribut que indica la columna en la que es troba la figura
	int m_gir; //Atribut que indica quantes vegades esta girada la figura
	TestFigures* m_seguent; //Atribut que apunta al seguent Jugador
};

#endif
