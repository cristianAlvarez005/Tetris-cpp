#ifndef NODE_H
#define NODE_H

#include "InfoJoc.h"
#include <iostream>
#include <fstream>

using namespace std;

class Moviment
{
public:
	Moviment() { m_moviment = NO_MOVIMENT; m_seguent = nullptr; } //Constructor per defecte
	Moviment(const TipusMoviment& moviment) { m_moviment = moviment; m_seguent = nullptr; } //COnstructor per parametres

	TipusMoviment getMoviment() const { return m_moviment; } //Metode que retorna el moviment
	Moviment* getSeguent() const { return m_seguent; } //Metode que retorna l'apuntador al seguent moviment
	void setSeguent(Moviment* seguent) { m_seguent = seguent; } //Metode que estableix on es troba el seguent moviment
private:
	TipusMoviment m_moviment; //Atribut que indica quin es el moviment
	Moviment* m_seguent; //Atribut que indica on es troba el seguent Moviment
};  

#endif