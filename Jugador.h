#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Jugador
{
public:
    Jugador(const string& nom, int punts) { m_nom = nom; m_puntuacio = punts; m_seguent = nullptr; } //Constructor per parametres d'un Jugador
    Jugador* getSeguent() const { return m_seguent; } //Metode que retorna l'apuntador al seguent jugador
    void setSeguent(Jugador* seguent) { m_seguent = seguent; }  //Metode que estableix on es troba el seguent jugador
    int getPuntuacio() const { return m_puntuacio; } //Retorna la puntuacio 
    string getNom() const { return m_nom; } //Retorna el nom
private:
    string m_nom; //Atribut que guarda el nom del jugador
    int m_puntuacio; //Puntuacio del Jugador
    Jugador* m_seguent; //Apuntador al seguent jugador
};
