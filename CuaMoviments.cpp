#include "CuaMoviments.h"

void CuaMoviments::afegeix(const Moviment& moviment) //Afegim un nou moviment al final de la cua
{
	Moviment* nouMoviment = new Moviment(moviment); //Creem un nou Moviment dinamicament

	if (esBuida()) //Si la cua esta buida entrem al if
	{
		m_primer = nouMoviment; //Fem que el nouMoviment sigui el primer element de la llista
		m_ultim = nouMoviment; //Tambe que sigui el ultim
	}
	else //Si la cua no esta buida entrem al else
	{
		m_ultim->setSeguent(nouMoviment); //Fem que l'ultim element de la llista apunti al nouMoviment
		m_ultim = nouMoviment; //El nouMoviment es l'ultim element de la llista
	}
}

void CuaMoviments::treu() //Treiem el primer moviment de la cua
{
	if (!esBuida()) //Entrem al if si la cua no esta buida
	{
		Moviment* eliminar = m_primer; //Fem que el nou apuntador que hem creat apunti al primer element de la llista
		m_primer = m_primer->getSeguent(); //Fem que el segon element de la llista passi a ser el primer

		delete eliminar; //Eliminem l'element a eliminar

		if (m_primer == nullptr) //En el moment que el primer element apunta a res entrem al if
			m_ultim = nullptr; //Llavors vol dir que nomes hi ha un element a la cua i es el primer i l'ultim
	}
}
