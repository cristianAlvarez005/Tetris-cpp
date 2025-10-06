#include "Partida.h"

Partida::Partida() 
{
    m_temps = 0;
    m_puntuacio = 0;
    m_nivell = 1; //Comencem la partida al nivell 1 
    m_velocitat = 1.0; //La figura baixara cada segon al nivell 1

    srand(time(NULL)); //Creem una llavor per partida perque no es repeteixin les sequencies de figures
} 

void Partida::inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)//int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
    m_puntuacio = 0; //Independentment del mode establim puntuacio a 0;
    m_nivell = 1; //Independentment del mode establim el nivell a 1

    m_joc.noFantasmaNoSeguent(); //Treiem les figures seguents i la fantasma de la pantalla

    if (mode == 1)
        m_joc.inicialitza(); //Inicialitzem una partida en mode normal
    else
        inicialitzaFitxer(fitxerInicial, fitxerFigures, fitxerMoviments); //Inicialitzem una partida en mode test
} 

void Partida::inicialitzaFitxer(const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
    m_joc.inicialitzaFitxerInicial(fitxerInicial); //Inicialitzem l'estat inicial d'una partida
    m_joc.inicialitzaFitxerFigures(fitxerFigures);  //Inicialitzem la cua de figures
    inicialitzaFitxerMoviments(fitxerMoviments); //Inicialitzem la cua de moviments
}

void Partida::inicialitzaFitxerMoviments(const string& fitxerMoviments)
{
    while (!m_moviments.esBuida())
        m_moviments.treu(); //Treiem elements fins que la cua estigui buida per si hem acabat la partida abans que la cua de moviments

    int numMoviment;

    ifstream fitxer;
    fitxer.open(fitxerMoviments); //Obrim el fitxer
    if (fitxer.is_open()) // Mirem si el fitxer esta obert
    {
        while (fitxer >> numMoviment) //Mentres que es pugui llegir el moviment per fitxer entrem al while
        { 
            TipusMoviment codiMoviment = (TipusMoviment)(numMoviment); //Convertim el int a TipusMoviment
            Moviment moviment(codiMoviment); //Cridem al constructor per parametres de Moviment
            m_moviments.afegeix(moviment); //Afegim el moviment a la cua
        }
        fitxer.close(); //Tanquem el fitxer
    }
}
 
void Partida::jugaModeTest(double deltaTime) 
{
    int nFilesEliminades; // Comptador de files eliminades 
    if (m_joc.acabarJoc()) //Si el joc s'ha acabat entrem al if
        acabarPartida(); //Acabem la partida
    else
    {
        m_joc.dibuixa(); // Dibuixa la partida 

        m_temps += deltaTime;
        if (m_temps > 1.0) //Cada moviment es realitza cada segon
        {
            if (!m_moviments.esBuida()) //Jugeum mentres la cua de moviments no estigui buida
            {
                TipusMoviment movimentActual = m_moviments.getPrimer().getMoviment(); //Obtenim el primer moviment de la cua

                switch (movimentActual) //Mirem quina codificacio te
                {
                case MOVIMENT_BAIXA_FINAL:
                    nFilesEliminades = m_joc.baixaFiguraDeCop(2); //Baixem la figura de cop (mode 2) i ens guardem el num de files eliminades
                    puntuacio(nFilesEliminades); //Cridem a la funcio de puntuacio i li passem el numero de files eliminades
                    break;

                case MOVIMENT_DRETA: 
                    m_joc.mouFigura(1); // Mou la figura cap a la dreta (1)
                    break;

                case MOVIMENT_ESQUERRA:
                    m_joc.mouFigura(-1); // Mou la figura cap a l'esquerra (-1)
                    break;

                case MOVIMENT_GIR_HORARI: 
                    m_joc.giraFigura(GIR_HORARI); // Gira la figura en sentit horari
                    break;

                case MOVIMENT_GIR_ANTIHORARI: 
                    m_joc.giraFigura(GIR_ANTI_HORARI); // Gira la figura en sentit antihorari
                    break;

                case MOVIMENT_BAIXA: 
                    nFilesEliminades = m_joc.baixaFigura(2); // Baixa la figura (mode 2) i ens guardem el numero de files eliminades
                    if (m_joc.getPosY() == 0) //Mirem si s'ha generat una figura a la posicio superiro
                        puntuacio(nFilesEliminades); //Si es aixi sumem per haber colocat la figura mes el numero de files elimiades
                    break;

                default:
                    break;
                }

                m_moviments.treu(); //Treiem el moviment executat
            }

            m_temps = 0.0; //Resetejem el temps en cada moviment
        }

        string msg = "Nivell: " + to_string(m_nivell) + "   Puntuacio: " + to_string(m_puntuacio);
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_TAULER, POS_Y_TAULER - 65, 0.75, msg); //Mostra la puntuacio i el nivell en color verd
    }
}

void Partida::jugaModeNormal(double deltaTime)
{
    int nFilesEliminades; //Comptador de files eliminades
    if (m_joc.acabarJoc()) //Entrem al if si el joc s'ha acabat i llavors no fem el actualitza
        acabarPartida(); //Mostrem el missatge al acabar el joc
    else
    {
        m_joc.dibuixa(); //Dibuixa la partida

        m_temps += deltaTime; 
        if (m_temps > m_velocitat) //Condicio perque la figura baixi automaticament
        {
            nFilesEliminades = m_joc.baixaFigura(1); //Baixa la figura (mode 1) i guarda el numero de files eliminades
            if (m_joc.getPosY() == 0) //En el moment en que es genera una nova figura s'entra al if
                puntuacio(nFilesEliminades); //Es suma la puntuacio per colocar una figura de manera automatica amb el plus de files eliminades
            m_temps = 0.0; //Es reseteja el temps a 0
        }

        if (Keyboard_GetKeyTrg(KEYBOARD_SPACE)) //Entra al if si es prem l'espai del teclat
        {
            nFilesEliminades = m_joc.baixaFiguraDeCop(1); //Guarda les files eliminades despres de baixar la figura de cop
            puntuacio(nFilesEliminades); //Es suma la puntuacio per colocar una figura de manera automatica amb el plus de files eliminades
        }

        if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT)) //Entra al if si es prem la fletxa dreta del teclat
        {
            m_joc.mouFigura(1); //Mou la figura cap a la dreta
            m_joc.baixaFantasma(); //Actualitzem la posicio de la figura fantasma
        }

        if (Keyboard_GetKeyTrg(KEYBOARD_LEFT)) //Entra al if si es prem la fletxa esquerra del teclat
        {
            m_joc.mouFigura(-1); //Mou la figura cap a l'esquerra
            m_joc.baixaFantasma(); //Actualitzem la posicio de la figura fantasma
        }

        if (Keyboard_GetKeyTrg(KEYBOARD_UP)) //Entra al if si em prem la fletxa amunt del teclat
        {
            //Entra al if si es prem la fletxa amunt del teclat
            m_joc.giraFigura(GIR_HORARI); //Gira la figura en sentit horari
            m_joc.baixaFantasma(); //Actualitzem la posicio de la figura fantasma
        }
            

        if (Keyboard_GetKeyTrg(KEYBOARD_DOWN)) //Entra al if si es pres la fletxa avall del teclat
        {
            m_joc.giraFigura(GIR_ANTI_HORARI); //Gira la figura en sentit anti-horari
            m_joc.baixaFantasma(); //Actualitzem la posicio de la figura fantasma
        }

        if (Keyboard_GetKeyTrg(KEYBOARD_W)) //Entra al if si es prem la W del teclat
        {
            nFilesEliminades = m_joc.baixaFigura(1); //Baixem la figura una posicio i ens guardem el numero de files eliminades
            if (m_joc.getPosY() == 0) //Mirem si s'ha generat una figura a la part superior del taulell
                puntuacio(nFilesEliminades); //Es suma la puntuacio per colocar una figura de manera automatica amb el plus de files eliminades
        }

        string msg = "Nivell: " + to_string(m_nivell) + "   Puntuacio: " + to_string(m_puntuacio);
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_TAULER, POS_Y_TAULER - 65, 0.75, msg); //Mostra la puntuacio i el nivell en color verd
    }
}

void Partida::puntuacio(int nElim) //Porta el recompte de punts, el nivell i la velocitat de la partida
{
    switch (nElim)
    {
    case 0:
        m_puntuacio += 10; //Sumem 10 punts quan es col·loca la figura de manera automatica
        break;
    case 1:
        m_puntuacio += 110; //Sumem 110 punts quan es col·loca la figura de manera automatica i s'elimina 1 fila
        break;
    case 2:
        m_puntuacio += 160; //Sumem 160 punts quan es col·loca la figura de manera automatica i s'elimina 2 files
        break;
    case 3:
        m_puntuacio += 185; //Sumem 185 punts quan es col·loca la figura de manera automatica i s'elimina 3 files
        break;
    case 4:
        m_puntuacio += 210; //Sumem 210 punts quan es col·loca la figura de manera automatica i s'elimina 4 files
        break;
    }

    //En aquests if else if cada 1000 punts s'augmenta de nivell i es disminueix la velocitat 0.05 fins al nivell maxim, el nivell 20 on la velocitat es de 0.05
    if (m_puntuacio < 1000)
    {
        m_nivell = 1;
    }
    else if (m_puntuacio < 2000)
    {
        m_nivell = 2;
        m_velocitat = 0.95;
    }
    else if (m_puntuacio < 3000)
    {
        m_nivell = 3;
        m_velocitat = 0.90;
    }
    else if (m_puntuacio < 4000)
    {
        m_nivell = 4;
        m_velocitat = 0.85;
    }
    else if (m_puntuacio < 5000)
    {
        m_nivell = 5;
        m_velocitat = 0.80;
    }
    else if (m_puntuacio < 6000)
    {
        m_nivell = 6;
        m_velocitat = 0.75;
    }
    else if (m_puntuacio < 7000)
    {
        m_nivell = 7;
        m_velocitat = 0.70;
    }
    else if (m_puntuacio < 8000)
    {
        m_nivell = 8;
        m_velocitat = 0.65;
    }
    else if (m_puntuacio < 9000)
    {
        m_nivell = 9;
        m_velocitat = 0.60;
    }
    else if (m_puntuacio < 10000)
    {
        m_nivell = 10;
        m_velocitat = 0.55;
    }
    else if (m_puntuacio < 11000)
    {
        m_nivell = 11;
        m_velocitat = 0.50;
    }
    else if (m_puntuacio < 12000)
    {
        m_nivell = 12;
        m_velocitat = 0.45;
    }
    else if (m_puntuacio < 13000)
    {
        m_nivell = 13;
        m_velocitat = 0.40;
    }
    else if (m_puntuacio < 14000)
    {
        m_nivell = 14;
        m_velocitat = 0.35;
    }
    else if (m_puntuacio < 15000)
    {
        m_nivell = 15;
        m_velocitat = 0.30;
    }
    else if (m_puntuacio < 16000)
    {
        m_nivell = 16;
        m_velocitat = 0.25;
    }
    else if (m_puntuacio < 17000)
    {
        m_nivell = 17;
        m_velocitat = 0.20;
    }
    else if (m_puntuacio < 18000)
    {
        m_nivell = 18;
        m_velocitat = 0.15;
    }
    else if (m_puntuacio < 19000)
    {
        m_nivell = 19;
        m_velocitat = 0.10;
    }
    else
    {
        m_nivell = 20;
        m_velocitat = 0.05;
    }
}

bool Partida::acabarPartida() //Mostra el misstage final d'acabar la partida
{
    bool acabar = m_joc.acabarJoc(); //Ens guardem si el joc s'ha acabat o no

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false); //Dibuixem el fons del taulell
    
    if (m_nivell == 20)
    {
        string msgFinal = "NIVELL MAXIM: HAS GUANYAT!!";
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_TAULER - 42, POS_Y_TAULER + 200, 1.20, msgFinal); //Mostra missatge perdedor 
        string puntuacio = "Puntuacio final: " + to_string(m_puntuacio); 
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 120, POS_Y_TAULER + 250, 0.8, puntuacio); //Mostra puntuacio final
        string sortir = "Prem 'ESC' per sortir al menu.";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 120, POS_Y_TAULER + 500, 0.5, sortir); //Missatge per sortir
        string taulell = "Prem 'E' per veure el taulell.";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 126, POS_Y_TAULER + 525, 0.5, taulell); //Missatge per veure el tauell

    }
    else
    {
        string msgFinal = "TAULER PLE: HAS PERDUT!!";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER - 20, POS_Y_TAULER + 200, 1.20, msgFinal); //Mostra missatge guanyador 
        string puntuacio = "Puntuacio final: " + to_string(m_puntuacio); 
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 115, POS_Y_TAULER + 250, 0.8, puntuacio); //Mostra la puntuacio final
        string sortir = "Prem 'ESC' per sortir al menu.";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 120, POS_Y_TAULER + 500, 0.5, sortir); //Missatge per sortir
        string taulell = "Prem 'E' per veure el taulell.";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 126, POS_Y_TAULER + 525, 0.5, taulell); //Missatge per veure el tauelell
    } 
    
    return acabar; //Retorna si s'ha acabat el joc o no
}

void Partida::actualitza(int mode, double deltaTime) //Actualitza la partida en funcio del mode i de deltaTime
{
    if (mode == 1) //Si el mode es 1 es juga normal
        jugaModeNormal(deltaTime); //Crida a la funcio de jugar normal i li passa per parametre deltaTime
    else //Mode == 2
        jugaModeTest(deltaTime); //Crida a la funcio del mode test i li passa per parametre deltaTime
}
