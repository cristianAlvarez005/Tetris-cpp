//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <windows.h> 
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Partida.h"
#include "./InfoJoc.h"
#include "Tetris.h"


int main(int argc, const char* argv[]) 
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
 
    Tetris tetris; //Creem una variable tetris
    int opcio = 0; //Creem una variable per llegir la opcio del menu
    int puntuacio = 0; //Creem una variable per guardar la puntuacio de les partides
    string nom; //Creem una variable per llegir el nom del jugador

    while (opcio != 6) //Executem el menu mentres no es premi la opcio de sortir
    {
        cout << "MENU PRINCIPAL" << endl;
        cout << "--------------" << endl;
        cout << "--------------" << endl;
        cout << endl;
        cout << endl;
        cout << "1. Joc en mode normal" << endl;
        cout << "2. Joc en mode test" << endl;
        cout << "3. Mostrar puntuacions historiques" << endl;
        cout << "4. Mostrar instruccions" << endl;
        cout << "5. Mostrar sistema de puntuacio" << endl;
        cout << "6. Sortir" << endl;
        cout << endl;
        cout << "Introdueix la opcio: ";
        cin >> opcio; ///Llegim quina opcio es vol mostrar

        switch (opcio)
        {
        case 1:
            system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            puntuacio = tetris.juga(1, pantalla); //Juga una partida del tetris en mode normal i es guarda la puntuacio
            cout << "JOC EN MODE NORMAL" << endl;
            cout << endl;
            cout << "Has acabat la partida :)" << endl;
            cout << "Introdueix les teves inicials: ";
            cin >> nom; //Llegeix el nom de l'usuari
            tetris.afeigeixPuntuacions(nom, puntuacio); //L'afegeix a la llista de puntuacions historiques
            cout << endl;
            cout << "Introdueix qualsevol numero i prem l'enter per tornar al menu: ";
            cin >> opcio; //Llegeix el numero introduit
            system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            break;

        case 2:
            system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            tetris.juga(2, pantalla); //Juga una partida en mode test
            system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            cout << "JOC EN MODE TEST" << endl;
            cout << endl;
            cout << "El mode test ha finalitzat :)" << endl;
            cout << endl;
            cout << "Introdueix qualsevol numero i prem l'enter per tornar al menu: ";
            cin >> opcio; //Llegeix el numero introduit
            system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            break;

        case 3:
            system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            cout << "LLISTAT DE PUNTUACIONS HISTORIQUES" << endl;
            cout << endl;
            tetris.mostraPuntuacions(); //Mostra les puntuacions historiques
            cout << endl;
            cout << "Introdueix qualsevol numero i prem l'enter per tornar al menu: ";
            cin >> opcio; //Llegeix el numero introduit
            system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            break;

        case 4:
            system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            cout << "INSTRUCCIONS" << endl;
            cout << endl;
            cout << "Moure a la dreta --> Fletxa dreta" << endl;
            cout << "Moure a l'esquerra --> Fletxa esquerra" << endl;
            cout << "Gir horari --> Fletxa amunt" << endl;
            cout << "Gir anti horari --> Fletxa avall" << endl;
            cout << "Baixar --> W" << endl;
            cout << "Baixar de cop --> Espai" << endl;
            cout << "Mostrar taulell al acabar partida --> E" << endl;
            cout << "Pausar partida --> P" << endl;
            cout << "Acabar partida --> ESC" << endl;
            cout << endl;
            cout << "Introdueix qualsevol numero i prem l'enter per tornar al menu: ";
            cin >> opcio; //Llegeix el numero introduit
            system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            break;

        case 5:
            system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            cout << "SISTEMA DE PUNTUACIO" << endl;
            cout << endl;
            cout << "Colocar figura al baixar/baixar de cop --> 10p" << endl;
            cout << "Eliminar 1 fila --> 100p" << endl;
            cout << "Eliminar 2 files --> 150p" << endl;
            cout << "Eliminar 3 files --> 175p" << endl;
            cout << "Eliminar 4 files --> 200p" << endl;
            cout << endl;
            cout << "Comences al nivell 1 i cada 1000p augmentes de nivell." << endl;
            cout << "Si acabes la partida al nivell 20 guanyes (nivell maxim)." << endl;
            cout << endl;
            cout << "Introdueix qualsevol numero i prem l'enter per tornar al menu: ";
            cin >> opcio; //Llegeix el numero introduit
            system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            break; 

        default:
            if (opcio < 1 || opcio > 6) //Es mostra si la opcio insertada no esta dins del menu
            {
                system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
                cout << "El numero indicat no esta dins de les opcions del menu" << endl;
                cout << "Introdueix qualsevol numero i prem l'enter per tornar al menu: ";
                cin >> opcio; //Llegeix el numero introduit
                system("cls"); //Treiem tots els missatges que estaven mostrats a la terminal
            }
            break;
        }
    } 

    SDL_Quit(); //Alliberem la memoria grafica al tancar la terminal
    return 0;
}
