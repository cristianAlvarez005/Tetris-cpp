#include "Tetris.h"

int Tetris::juga(int mode, Screen& pantalla)
{
	int puntuacio = 0; //Inicialitzem la puntuacio a un valor

	if (mode == 1) //Si el mode es 1
		puntuacio = jugaNormal(pantalla);  //Juguem una partida i ens guardem la puntuacio
	else
		jugaFitxer(pantalla); //Si el mode es 2 juguem una partida de mode test i no es retorna la puntuacio ja que no fa falta

	return puntuacio; //retornem la puntuacio
}

int Tetris::jugaNormal(Screen& pantalla)  
{
    m_partida.inicialitza(1,"","",""); //Inicialitzem la partida en mode normal

	PlaySound(TEXT("./data/Games/TetrisPartida"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //Executem la musica

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    do
    {
        //Mostrem la finestra grafica
        pantalla.show();

        LAST = NOW; 
        NOW = SDL_GetPerformanceCounter(); 
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency()); 

        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla.processEvents(); 

		pausa(1, deltaTime); //Cridem a la funcio de pausa que conte l'actualitza

        pantalla.update(); //Actualitzem la pantalla

		acabarTetris(pantalla); //Cridem a la funcio d'acabar tetris

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)); //Executem el bucle fins que es prem ESC

    PlaySound(0, 0, 0); //Quan s'acaba el bucle treiem la musica

	int puntuacio = m_partida.getPuntuacio(); //Obtenim la puntuacio de la partida

	return puntuacio; //Retornem la puntuacio de la partida
}

void Tetris::jugaFitxer(Screen& pantalla)
{
	string partida; //Creem un string per llegir el fitxer de la partida
	string figures; //Creem un string per llegir el fitxer de figures
	string moviments; //Creem un string per llegir el fitxer de moviments

	cout << "Introdueix el fitxer inicial: ";
	cin >> partida; //Llegim el fitxer de partida
	cout << "Introdueix el fitxer de figures: ";
	cin >> figures; //Llegim el fitxer de figures
	cout << "Introdueix el fitxer de moviments: ";
	cin >> moviments; //Llegiim el fitxer de moviments

	string path = "./data/Games/"; //Indiquem on es trobaran els fitxer del mode test

	m_partida.inicialitza(2, path + partida, path + figures, path + moviments); //Inicialitzem la partida em mode test amb el path complert dels fitxers

	PlaySound(TEXT("./data/Games/TetrisPartida"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //Executem la musica

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	do
	{
		//Mostrem la finestra grafica
		pantalla.show();

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

		// Captura tots els events de ratolí i teclat de l'ultim cicle
		pantalla.processEvents();

		pausa(2, deltaTime); //Cridem a la funcio de pausa que conté l'actualitza

		pantalla.update(); //Actualitzem la pantalla

		acabarTetris(pantalla); //Cridem a la funcio d'acabar el tetris

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)); //Ens mantenim en el bucle fins que no es prem ESC

	PlaySound(0, 0, 0); //Apaguem la musica
}

void Tetris::acabarTetris(Screen& pantalla)
{
	if (m_partida.acabarPartida())  //Si la partida esta acabada entrem al if
	{
		do 
		{
			m_partida.acabarPartida(); //Mostrem el missatge d'acabar la partida
			PlaySound(0, 0, 0); //Apaguem la musica

			if (m_partida.getNivell() == 20) //Si el nivell es 20
			{
				pantalla.update(); //Actualitzem la pantalla
				PlaySound(TEXT("./data/Games/Victoria"), NULL, SND_FILENAME | SND_SYNC); //Executem la musica de victoria
				PlaySound(0, 0, 0); //La apaguem un cop executada
				m_partida.setNivell(21); //Forcem que el nivell sigui un diferent del de les condicions
			}
			else if (m_partida.getNivell() < 20) //Si el nivell es menor que 20
			{
				pantalla.update(); //Actualitzem la pantalla
				PlaySound(TEXT("./data/Games/Derrota"), NULL, SND_FILENAME | SND_SYNC);  //Executem la musica de derrota
				PlaySound(0, 0, 0); //Apaguem la musica
				m_partida.setNivell(21); //Forcem el nivell a 21 per que no entri a cap dels if
			}
			pantalla.processEvents(); //Mirem si s'ha presionat alguna tecla
		} while (!Keyboard_GetKeyTrg(KEYBOARD_E) && !Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)); //Ens mantenim en el bucle fins que es prem la E o ESC
	}
}

void Tetris::pausa(int mode, double deltaTime)
{
	if (Keyboard_GetKeyTrg(KEYBOARD_P)) //Si es prem la tecla P entrem al if
	{
		if (!m_pausa) 
			m_pausa = true; //Si m_pausa estava a false passa a true
		else
			m_pausa = false; //Si m_pausa estava a true passa a false
	}

	if (m_pausa) //Si m_pausa == true
	{
		GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false); //Dibuixem el fons del taulell

		string msgPausa = "PAUSA";
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 170, POS_Y_TAULER + 200, 1.20, msgPausa); //Mostra missatge pausa 
		string sortir = "Prem 'ESC' per sortir al menu.";
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 110, POS_Y_TAULER + 500, 0.5, sortir); //Mostrem missatge per acabar partida
		string reprendre = "Prem 'P' per reprendre la partida.";
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 105, POS_Y_TAULER + 525, 0.5, reprendre); //Mostrem missatge per reprendre partida
	}
	else //Si pausa es false continuem jugant
		m_partida.actualitza(mode, deltaTime); //Actualitzem la partida i continuem jugant
}

void Tetris::mostraPuntuacions()  
{
    m_puntuacions.carregarLlista("./data/Games/PuntuacionsHistoriques.txt"); //Posem tots els jugadors a la llista
    m_puntuacions.imprimirLlista(); //Imprimim la llista
	m_puntuacions.buidarLlista(); //Buidem la llista perque quan la tornem a cridar no es duplqui
}

void Tetris::afeigeixPuntuacions(const string& nom, int puntuacions)
{
    m_puntuacions.carregarLlista("./data/Games/PuntuacionsHistoriques.txt"); //Posem tots els jugadors a la llista
    m_puntuacions.afegirJugador(nom, puntuacions); //Afegim el nou jugador a la posicio que li toca en funcio de la puntuacio
    m_puntuacions.guardarArxiu("./data/Games/PuntuacionsHistoriques.txt"); //Actualitzem el arxiu guardant tota la llista
	m_puntuacions.buidarLlista(); //Buidem la llista perque no es dupliqui quan la tornem a carregar
}
