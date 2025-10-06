#include "LlistaJugadors.h"

LlistaJugadors::~LlistaJugadors()
{
    Jugador* actual = m_primer; //Inicialitzem un punter que apunta al primer element de la llista
    while (actual != nullptr) //Iterem mentres actual no apunti a nullptr
    {
        Jugador* seguent = actual->getSeguent(); //Guardem l'apuntador al seguent element de la llista
        delete actual; //Eliminem el jugador actual
        actual = seguent; //Actualitzem actual perque apunti al seguent
    }
}

void LlistaJugadors::afegirJugador(const string& nom, int puntuacio) //Afegim un jugador a la llista
{
    Jugador* nouJugador = new Jugador(nom, puntuacio); //Creem un nou objecte dinamic del tipus Jugador

    if ((m_primer == nullptr) || ((m_primer->getPuntuacio()) < puntuacio)) //Entrem al if si la llista esta buida o si la puntuacio del primer es menor que la puntuacio a afegir
    {
        nouJugador->setSeguent(m_primer); //Fem que el nou jugador apunti al primer
        m_primer = nouJugador; //Fem que el primer jugador sigui el que acabem d'afegir
    }
    else
    {
        Jugador* actual = m_primer; //Inicialitzem un apuntador que apunta al primer element de la llista
        while ((actual->getSeguent()) && ((actual->getSeguent()->getPuntuacio()) >= puntuacio)) //Iterem fins trobar en quina posicio ha d'anar ja que esta ordenat desdendentment
            actual = actual->getSeguent(); //Fem que el jugador seguent sigui l'actual

        nouJugador->setSeguent(actual->getSeguent()); //El nou jugador apunta al apuntador seguent de actual
        actual->setSeguent(nouJugador); //Actual apunta al nou Jugador
    }
}

void LlistaJugadors::treu()  //Elimina el primer element de la llista
{
    if (!esBuida()) //Si la llista no esta buida eliminem el primer element
    {
        Jugador* eliminar = m_primer; //Creem un apuntador on apunta el primer element de la llista
        m_primer = m_primer->getSeguent(); //Fem que el segon element de la llista sigui el primer

        delete eliminar; //Eliminem eliminar que es el primer element
    }
}

void LlistaJugadors::buidarLlista() //Elimina tots els elements de la llista
{
    while (!esBuida()) //Itera mentres la llista no estigui buida
        treu(); //Elimina el primer element de la llista
}

void LlistaJugadors::imprimirLlista() const //Imprimeix la llista
{
    Jugador* actual = m_primer; //Fem que el jugador actua apunti al primer element de la llista
    while (actual != nullptr) //Iterem mentres actual no apunti a res

    {
        cout << actual->getNom() << " " << actual->getPuntuacio() << endl; //Imrimim el no i la puntuacio del actual
        actual = actual->getSeguent(); //Fem que el seguent sigui el actual
    } 
}

void LlistaJugadors::carregarLlista(const string& nomFitxer) //Carreguem la llista des del fitxer
{
    ifstream fitxer(nomFitxer); //Obrim el fitxer
    if (fitxer.is_open()) //Entrem al if si el fitxer esta obert
    {
        string nom; //Creem un string per llegir el nom
        int puntuacio; //Creem un int per llegir la puntuacio
        while (fitxer >> nom >> puntuacio) //Iterem mentres poguem llegir un nom i una puntuacio des del fitxer
            afegirJugador(nom, puntuacio); //Afegim el jugador a la llista

        fitxer.close(); //Tanquem el fitxer quan hem acabat de iterar
    }
}

void LlistaJugadors::guardarArxiu(const string& nomFitxer) const //Passem els jugadors de la llista a l'arxiu
{
    ofstream fitxer(nomFitxer); //Obrim el fitxer
    if (fitxer.is_open()) //Entrem al if si el fitxer esta obert
    {
        Jugador* actual = m_primer; //Fem que actual apunti al primer element de la llista
        while (actual != nullptr) //Iterem mentres actual no apunti a res
        {
            fitxer << actual->getNom() << " " << actual->getPuntuacio() << endl; //Anem guardant al fitxer el nom i la puntuacio
            actual = actual->getSeguent();  //Fem que el seguent element de la llista sigui el actual
        }
        fitxer.close(); //Tanquem el fitxer
    }
}