#ifndef INFO_JOC_H
#define INFO_JOC_H

//Typedef per saber quina tecla es presiona
typedef enum
{
    TECLA_ESQUERRA,
    TECLA_DRETA,
    TECLA_AMUNT,
    TECLA_ABAIX,
    TECLA_ESPAI,
    TECLA_ESCAPE,
    NO_TECLA
} TipusTecla;

//Typedef per determinar el tipus de moviment que hem llegit del fitxer de mode test.
typedef enum 
{
    MOVIMENT_ESQUERRA = 0,
    MOVIMENT_DRETA,
    MOVIMENT_GIR_HORARI,
    MOVIMENT_GIR_ANTIHORARI,
    MOVIMENT_BAIXA,
    MOVIMENT_BAIXA_FINAL,
    NO_MOVIMENT,
}TipusMoviment; 

//Constant que marca el nº de figures diferents
const int N_TIPUS_FIGURES = 7;

//Constant que marca el nº de girs horaris
const int N_GIRS_HORARIS = 3;

//Typedef que marca els diferents colors per a cada figura
typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    COLOR_FANTASMA,
    NO_COLOR
} ColorFigura;

//Typedef que ens indica les formes de les figures
typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S
} TipusFigura;

//Typedef per determinar el sentit en el que gira la figura
typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

// Tamany de la pantalla gràfica
const int SCREEN_SIZE_X = 700; //Passem de 600 a 700 per posar les seguents figures
const int SCREEN_SIZE_Y = 700;

// Mida dels quadrats que formen el tauler
const int MIDA_QUADRAT = 26;

// Tamany del tauler
const int N_FILES_TAULER = 21;
const int N_COL_TAULER = 12;

//Tamany de la figura
const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

// Posició del tauler a la pantalla
const int POS_X_TAULER = 120;
const int POS_Y_TAULER = 100;

#endif
