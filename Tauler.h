#ifndef TAULER_H
#define TAULER_H

#include "Figura.h"

class Tauler
{
public:
	Tauler(); //Inicialitzem tot el taullel a color negre

	void setTauler(int i, int j, const ColorFigura& color) { m_tauler[i][j] = color; } //Establim el color passat per parametre en una determinada posicio del taulell
	ColorFigura getTauler(int i, int j) const { return m_tauler[i][j]; } //Retornem el color del taulell en una determminada poscio

	int eliminarFilesCompletes(); //eliminar totes les completes      
	bool girValid(const Figura& figura, const DireccioGir& direccio) const;  //mirar si el gir es valid
	bool movimentEsValid(const Figura& figura, int posX, int posY) const; //mirar si es pot moure horitzontalment o de manera vertical o no
	bool taulerComplet(const Figura& figura) const; //Comprovem si el tauler esta complet

	void dibuixaTauler(); //Dibuixem el taulell
private:
	ColorFigura m_tauler[N_FILES_TAULER][N_COL_TAULER]; //matriu que representa el taulell

	bool filaCompleta(int fila) const; //mirar si la fila esta completa
	void eliminarFila(int fila); //eliminar una fila
};

ifstream& operator>>(ifstream& input, Tauler& tauler); //Sobrecarrega per llegir el taulell per fitxer

#endif  
