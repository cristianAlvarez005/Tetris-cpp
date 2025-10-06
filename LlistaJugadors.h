#include "Jugador.h"

class LlistaJugadors
{
public:
	LlistaJugadors() { m_primer = nullptr; } //Constructor per defecte
	~LlistaJugadors(); //Destructor
	void afegirJugador(const string& nom, int puntuacio); //Afegeix un nou jugador a la llista
	void buidarLlista(); //Buida la llista
	void imprimirLlista() const; //Imprimeix la llista
	void carregarLlista(const string& nomFitxer); //Omple la llista desde un fitxer
	void guardarArxiu(const string& nomFitxer) const; //Guarda la llista en un fitxer
	
private:
	Jugador* m_primer; //Atribut que indica on esta el primer element de la llista

	bool esBuida() const { return m_primer == nullptr; } //Metode que incica si la llista esta buida o no
	void treu(); //Meotde que treu un element de la llista
};