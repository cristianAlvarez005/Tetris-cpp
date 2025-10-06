#ifndef CUA_H
#define CUA_H

#include "Moviment.h" 

class CuaMoviments
{
public:
	CuaMoviments() { m_primer = nullptr; m_ultim = nullptr; } //Constructor per defecte
	~CuaMoviments() { while (!esBuida()) treu(); } //Destructor
	void afegeix(const Moviment& moviment); //Metode que afegeix un moviment al final de la cua
	void treu(); //Metode que treu el primer element de la cua
	Moviment& getPrimer() const { if (!esBuida()) return *m_primer; } //Metode que retorna el primer element de la cua
	Moviment& getUltim() const { if (!esBuida()) return *m_ultim; } //Metode que retorna el ultim element de la cua
	bool esBuida() const { return m_primer == nullptr; } //Metode que indica si la cua esta buida o no

private:
	Moviment* m_primer; //Atribut que indica quin es el primer element de la cua
	Moviment* m_ultim; //Atribut que indica quin els l'ultim element de la cua
};

#endif
