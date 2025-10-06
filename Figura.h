#ifndef FIGURA_H
#define FIGURA_H

#include <iostream>
#include <fstream>
#include "InfoJoc.h"
#include "GraphicManager.h" 
#include <stdlib.h>
#include <time.h> 
#include <Windows.h> 
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

using namespace std;

class Figura
{
public:
    Figura();

    TipusFigura getTipusFigura() const { return m_figura; } //Retorna la figura que es
    ColorFigura getPosicioFigura(int fila, int columna) const { return m_forma[fila][columna]; } //Retrona el color de la fig en una posicio concreta
    void setColor(const ColorFigura& color) { m_color = color; } //Establim el color de la figura al passat per parametre
    int getPosX() const { return m_posX; } //Retorna la posX de referencia
    int getPosY() const { return m_posY; } //Retorna la posY de referencia
    void setPosX(int x) { m_posX = x; } //S'estableix la posX de referencia
    void setPosY(int y) { m_posY = y; } //S'estableix la posY de referencia
    int getAlcada() const { return m_alcada; } //Retorna l'alçada de la figura
    int getAmplada() const { return m_amplada; } //Retorna l'alçada de la figura
    void getMatriu(ColorFigura copia[MAX_ALCADA][MAX_AMPLADA]) const; // Fa una copia de m_forma a copia 

    void figuraAleatoria(); //Genera una figura aleatoria
    void inicialitza(const TipusFigura& figura, int posX, int posY, int codiGir); //Inicialitza la figura amb la info pasada per parametre
    void gir(const DireccioGir& direccio); //Gira la figura en un sentit o un altre en funcio del parametre
    void desplacarHoritzontal(int dirX); //Desplaça la figura a la dreta o esquerre en funcio del parametre
    void baixar(); //Baixa la figura una posicio

    void dibiuxaFigura() const; //Dibuixa una figura
    void dibuixaFiguraSeguent() const; //Dibuixa la figura seguent
    void dibuixaFiguraSeguent2() const; //Dibuixa la figura seguent 2
    void dibuixaFiguraSeguent3() const; //Dibuixa la figura seguent 3
    void dibuixaFiguraFantasma() const; //Dibuixa la figura fantasma

private:
    TipusFigura m_figura; //Ens indica quina figura es
    ColorFigura m_color; //ENs indica el color de la figura
    ColorFigura m_forma[MAX_ALCADA][MAX_AMPLADA]; //La forma respresentada en una matriu segons ColorFigura
    int m_posX;//punt superior a l'esquerre de la matriu m_forma dins del tauler (x)
    int m_posY;//punt superior a l'esquerre de la matriu m_forma dins del tauler (y)
    int m_alcada;//alçada de la matriu que ocupa la figura
    int m_amplada;//amplada de la matriu que ocupa la figura

    void girHorari(); //Fa el gir horari
    void girAntiHorari(); //Fa el gir anti horari 
    void transposarMatriu(ColorFigura matriu[MAX_ALCADA][MAX_AMPLADA]) const; //Transposa la matriu m_forma
    int Aleatori(int num); //Genera un numero aleatori
};

ifstream& operator>>(ifstream& input, Figura& figura); //Sobrecarrega de lectura de figura per fitxer

#endif
