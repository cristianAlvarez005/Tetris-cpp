#ifndef CUAFIGURES_H
#define CUAFIGURES_H

#include "TestFigures.h"

class CuaFigures
{
public:
	CuaFigures() { m_primer = nullptr; m_ultim = nullptr; } //Constructor per defecte
	~CuaFigures() { while (!esBuida()) treu(); } //Destructor per defecte
	void afegeix(const TestFigures& figura); //Metode que afegeix una figura al final de la cua
	void treu(); //Metode que treu la primera figura de la cua
	TestFigures& getPrimer() const { if (!esBuida()) return *m_primer; } //Metode que retorna el primer element de la cua
	TestFigures& getUltim() const { if (!esBuida()) return *m_ultim; } //Metode que retorna l'ultim element de la cua
	bool esBuida() const { return m_primer == nullptr; } //Metode que indica si la cua esta buida o no
private:
	TestFigures* m_primer; //Atribut que indica on esta el primer element de la cua
	TestFigures* m_ultim; //Atribut que indica quin es l'ultim element de la cua
};

#endif
