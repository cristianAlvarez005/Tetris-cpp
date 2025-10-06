#include "Tauler.h"

Tauler::Tauler()
{
    //Recorrem totes les posicions del taulell
    for (int i = 0; i < N_FILES_TAULER; i++)
        for (int j = 0; j < N_COL_TAULER; j++) 
            m_tauler[i][j] = COLOR_NEGRE; //Inicialitzem la posicio del taulell a COLOR_NEGRE
}

bool Tauler::filaCompleta(int fila) const //Mirem si la fila es troba completa
{
    int j = 1; //Comences despres de la primera columna que es un borde
    int incompleta = true; //boolea que ens marca si no esta completa

    while (j < N_COL_TAULER && incompleta) //Recorrem totes les columnes mentres que es compleixi la condicio
    {
        if (m_tauler[fila][j] == COLOR_NEGRE) //Si alguna columna de la fila es troba de color negre entrem al if
            incompleta = false; //Vol dir que queda alguna columna per estar plena
        j++; //Incrementem les columnes per mirar si la seguent es de COLOR_NEGRE o no
    }
    return incompleta; //Retornem el boolea
}

void Tauler::eliminarFila(int fila)
{
    if (fila < 0 || fila >= N_FILES_TAULER) //Mirem si la fila que rebem per parametre es troba fora dels limits
        return; 

    for (int i = fila; i > 0; i--) //Recorrem totes les posicions desde la fila especificada fins a 1
        for (int j = 0; j < N_COL_TAULER; j++) //Recorrem totes les columnes de cada fila
            m_tauler[i][j] = m_tauler[i - 1][j]; //La fila superior la baixem 

    for (int j = 0; j < N_COL_TAULER; j++)
        m_tauler[0][j] = COLOR_NEGRE; //Establim cada columna de la fila a COLOR_NEGRE
}

int Tauler::eliminarFilesCompletes() //Eliminem totes les files eliminades
{
    int filesEliminades = 0; //Contador que marca el num de files eliminades

    for (int i = 0; i < N_FILES_TAULER; i++) //Recorra totes les files del taulell
        if (filaCompleta(i)) //Mirem si la fila que estem iterant esta completa
        {
            eliminarFila(i); //Eliminem la fila que estem iterant
            filesEliminades++; //Sumem 1 al contador
        }
    return filesEliminades; //Retornem el num de files eliminades
}

bool Tauler::girValid(const Figura& figura, const DireccioGir& direccio) const
{
    Figura figTemp = figura; //Creem una figura temporal per comprovar si el gir es valid
    figTemp.gir(direccio); //Girem la figura temporal en el sentit que marca el valor passat per parametre

    int posXFigura = figTemp.getPosX(); //Recuperem la posX de la figura temporal
    int posYFigura = figTemp.getPosY(); //Recuperem la posY de la figura temporal

    bool valid = true; //Bolea que marca si es pot fer el gir
    int i = 0; //iterador de files

    while (i < figTemp.getAlcada() && valid) //Mentres la i sigui menor a la alçada de la figura i el gir sigui valid iterem les files
    {
        int j = 0; //Iterador de les columnes de cada fila
        while (j < figTemp.getAmplada() && valid)//Mentres la j sigui menor a la amplada de la figura i el gir sigui valid iterem les columnes
        { 
            if (figTemp.getPosicioFigura(i, j) != NO_COLOR) //Entrem al if si hi ha un color diferent de NO_COLOR a la posicio que estem mirant
            {
                if (posXFigura + j >= N_COL_TAULER || posXFigura + j < 0 || posYFigura + i < 0 || posYFigura + i >= N_FILES_TAULER) //Si la figura un cop girada es surt dels limits entrem al if
                    valid = false; //El gir no es pot fer
                else if (m_tauler[posYFigura + i][posXFigura + j] != COLOR_NEGRE) //Si la figura un cop girada colisiona amb una figura ja colocada al taulell entrem al if
                    valid = false; //El gir no es pot fer
            }
            j++; //Incrementem l'iterador de les columnes 
        }
        i++; //Incrementem l'iterador de les files
    }

    return valid; //Retornem si el gir es pot fer o no amb true o false;
}

bool Tauler::movimentEsValid(const Figura& figura, int posX, int posY) const //Mira si el moviment es valid
{
    bool valid = true; //Bolea que esta a true si el moviment es pot fer
    int i = 0; //Iterador de files
    while (i < figura.getAlcada() && valid) //Mentres la i sigui menor a la alçada de la figura i el moviment sigui valid iterem les files
    {
        int j = 0; //Iterador de les columnes de cada fila
        while (j < figura.getAmplada() && valid) //Mentres la j sigui menor a la amplada de la figura i el moviment sigui valid iterem les columnes
        {
            if (figura.getPosicioFigura(i, j) != NO_COLOR) //Entrem al if si hi ha un color diferent de NO_COLOR a la posicio que estem mirant
                if (posX + j >= N_COL_TAULER || posX + j - 1 < 0 || posY + i < 0 || posY + i >= N_FILES_TAULER || m_tauler[posY + i][posX + j] != COLOR_NEGRE)
                    valid = false;
                    //El moviment no es valid si la figura excedeix els limits del taulell o colisiona amb una figura ja colocada al taulell. Fiquem -1 pq no accedeixi al limit lateral esquerra.
            j++; //Incrementem l'iterador de les columnes 
        }
        i++; //Incrementem l'iterador de les files 
    }
    return valid; //Retornem si el moviment es pot fer o no amb true o false
}

bool Tauler::taulerComplet(const Figura& figura) const
{
    bool ple = false; //Valor que retornarem per saber si col·lisiona.

    ColorFigura copiaFigura[MAX_ALCADA][MAX_AMPLADA]; //Creem una copia de la figura que "simular" els moviments i realitzar-los si són possibles. 
    figura.getMatriu(copiaFigura); //Compiem la matriu pasada per parametre a copiaFigura
    int posXFigura = figura.getPosX(); //Obtenim la posX de la figura
    int posYFigura = figura.getPosY(); //obtenim la posY de la figura
    int amplada = figura.getAmplada(); //Obtenim quantes columnes ocupa
    int alcada = figura.getAlcada(); //Obtenim quantes files ocupa
    
    int i = 0; //Iterador de files a 0

    while ((i < amplada) && (!ple)) //Recorrem mentres no arribem a la fila maxima o el tauler estigui ple
    {
        int j = 0; //Iterador de columnes a 0

        while ((j < alcada) && (!ple)) //Recorrem mentres no arribem a la columna maxima o el tauler estigui ple
        {
            if ((copiaFigura[i][j] != NO_COLOR) && (m_tauler[i + posYFigura][j + posXFigura] != COLOR_NEGRE)) //Si una posició de la figura i la posició del tauler que ocupa aquesta mateixa posició de la figura no són de color negre, hi ha colisió.
                ple = true; //Establim que esta ple
            else
                j++; //Sino incrementem les columnes
        }
        i++; //Quan s'han mirat totes les columnes de la fila incrementem la fila
    }

    return ple; //Retornem si el tauler esta ple o no
}

void Tauler::dibuixaTauler() //Dibuixem el taulell i les figures ja colocades
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false); //Dibuixem el fons del taulell
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false); //Dibuixem els bordes del taulell

    //Recorrem cada posicio del taulell 
    for (int i = 0; i < N_FILES_TAULER; i++)                       
        for (int j = 1; j < N_COL_TAULER; j++)
            if(m_tauler[i][j] != COLOR_NEGRE) //Entrem al if si la posicio no es de COLOR_NEGRE
                GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(m_tauler[i][j] + 1), 
                    POS_X_TAULER + (j * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
                    //Pintem cada posicio del taulell diferent de color negre
}

ifstream& operator>>(ifstream& input, Tauler& tauler)
{
    int color;
    //Recorrem totes les posicions del taulell
    for (int i = 0; i < N_FILES_TAULER; i++)
        for (int j = 1; j < N_COL_TAULER; j++)
        {
            input >> color; //Llegim el color del fitxer
            tauler.setTauler(i, j, (ColorFigura)color); //Establim el color llegit a la posicio que estem iterant del taulell
        }

    return input;
}
