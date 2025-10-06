#include "CuaFigures.h"

void CuaFigures::afegeix(const TestFigures& figura) //Afegim una nova figura al final de la cua
{
	TestFigures* novaFigura = new TestFigures(figura); //Creem una nova Figura dinamicament

	if (esBuida()) //Si la cua esta buida entrem al if
	{
		m_primer = novaFigura; //Fem que la novaFigura sigui el primer element de la llista
		m_ultim = novaFigura; //Tambe que sigui el ultim
	}
	else //Si la cua no esta buida entrem al else
	{
		m_ultim->setSeguent(novaFigura); //Fem que l'ultim element de la llista apunti al novaFigura
		m_ultim = novaFigura; //El nouMoviment es l'ultim element de la llista
	}
}

void CuaFigures::treu() //Treiem el pirmer element de la cua
{
	if (!esBuida()) //Entrem al if si la cua no esta buida
	{
		TestFigures* eliminar = m_primer; //Fem que el nou apuntador que hem creat apunti al primer element de la llista
		m_primer = m_primer->getSeguent(); //Fem que el segon element de la llista passi a ser el primer

		delete eliminar; //Eliminem l'element a eliminar

		if (m_primer == nullptr) //En el moment que el primer element apunta a res entrem al if
			m_ultim = nullptr; //Llavors vol dir que nomes hi ha un element a la cua i es el primer i l'ultim
	}
}