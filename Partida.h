#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "Joc.h" 

using namespace std;

class Partida 
{
public:
    Partida(); //Inicialitza els atributs
    void inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments); //Inicialitzem la partida depenent del mode
    void actualitza(int mode, double deltaTime); //Metode que actualitza la partida cada vegada en funcio de deltaTime
    bool acabarPartida(); //Mostra el missatge final  

    int getPuntuacio() const { return m_puntuacio; } //Retorna la puntuacio
    int getNivell() const { return m_nivell; } //Retorna el nivell
    void setNivell(int nivell) { m_nivell = nivell; } //Establim el nivell al passat per parametre
    
private:
    double m_temps; //Variable que emmmagatzema el temps per baixar automaticament
    Joc m_joc; //Variable que conte tota la informacio per jugar
    int m_puntuacio; //Punts de la partida
    int m_nivell; //Nivell en el que estem de la partida
    float m_velocitat; //Velocitat a la qque baixa la figura automaticament
    CuaMoviments m_moviments; //Cua que gestiona els moviments durant el mode test

    void inicialitzaFitxer(const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments); //Inicialitza el mode test
    void inicialitzaFitxerMoviments(const string& fitxerMoviments);  //Inicialitza els moviments llegits per fitxer
    void jugaModeTest(double deltaTime); //Es l'actualitza del mode test
    void jugaModeNormal(double deltaTime); //Es l'actualitza del mode normal
    void puntuacio(int nElim); //Punts que rebem per cada figura que coloquem i actualitzacio del nivell i la velocitat
};

#endif 
