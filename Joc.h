#ifndef JOC_H
#define JOC_H
#include "Tauler.h"	
#include "CuaFigures.h"
#include "CuaMoviments.h"


using namespace std;

class Joc
{
public:
	void inicialitzaFitxerInicial(const string& fitxerInicial); //Inicialitzem la partida desde un fitxer
	void inicialitzaFitxerFigures(const string& fitxerFigures); //Inicialitzem les figures de la partida desde un fitxer
	void inicialitza(); //inicialitza per jugar en mode normal

	bool acabarJoc(); //Mira si el joc s'ha acabat
	bool giraFigura(DireccioGir direccio); //gira la figura si es posible
	bool mouFigura(int dirX); //desplaça la figura horitzontalment si es possible
	int baixaFigura(int mode); //baixa la figura si es possible i elimina les files completes
	int baixaFiguraDeCop(int mode); //baixa la figura de cop fins que colisiona amb alguna cosa en el taulell i elimina les files completes
	void baixaFantasma(); //Cada vegada que es mou m_figura, m_fantasma baixa fins que colisiona
	void noFantasmaNoSeguent(); //Buidem el taulell treient les figures seguents i la figura fantasma

	void dibuixa(); //Funcio que dibuixa el taulell i la figura que esta caient, les seguents i la fantasma

	int getPosX() { return m_figura.getPosX(); } //Recuperem la posX de la figura amb un getter d'un getter
	int getPosY() { return m_figura.getPosY(); } //Recuperem la posY de la figura amb un getter d'un getter
	void setPosX(int x) { m_figura.setPosX(x); } //Establim la posX de la figura amb un setter d'un setter
	void setPosY(int y) { m_figura.setPosY(y); } //Establim la posY de la figura amb un setter d'un setter
	int getAmplada() { return m_figura.getAmplada(); } //Recuperem l'amplada de la figura amb un getter d'un getter
	int getAlcada() { return m_figura.getAlcada(); } //Recuperem l'alcada de la figura amb un getter d'un getter
	ColorFigura getFigura(int i, int j) { return m_figura.getPosicioFigura(i, j); } //Recuperem el color en una determinada posicio de la matriu amb un getter d'un getter

private:
	Tauler m_tauler; //El taulell sobre el que jugare
	Figura m_figura; //La figura que anira caient

	Figura m_figuraSeguent; //Figura que caura despres de la actual
	Figura m_figuraSeguent2; //Figura que caura despres de figuraSeguent
	Figura m_figuraSeguent3; //Figura que caura despres de figuraSeguent2

	Figura m_fantasma; //Figura que marca on caura m_figura

	CuaFigures m_figures; //Guarda les figures llegides pel mode test

	void afegirFigura(); //afegir una figura al taulell
	void generarFigures(int mode); //Genera les figures depenent del mode en el que esta

};
#endif
