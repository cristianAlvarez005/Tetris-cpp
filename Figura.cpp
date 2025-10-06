#include "Figura.h" 
Figura::Figura() //Inicialitzem totes les variables privades de Figura a 0.
{
	m_posX = 0;
	m_posY = 0;
	m_color = NO_COLOR;
	m_figura = NO_FIGURA;
	m_amplada = 0;
	m_alcada = 0;

	for (int i = 0; i < MAX_ALCADA; i++)
		for (int j = 0; j < MAX_AMPLADA; j++)
			m_forma[i][j] = NO_COLOR; 
}

int Figura::Aleatori(int num) //Genera sequencies aleatories
{
	int numAleatori; 

	if (num != 0)
		numAleatori = rand() % num + 1; //Quan entrem el num de figures que hi ha ens genera una figura aleatoria
	else
		numAleatori = 2 + rand() % 8; //Si entrem un 0 ens genera una posX aleatoria entre 2 i 8 
									  //perque de cap de les maneres es sorti del taulell
	return numAleatori; //Retorna el numero aleatori
}

void Figura::figuraAleatoria() //Generea figura aleatoria
{
	inicialitza((TipusFigura)Aleatori(N_TIPUS_FIGURES), Aleatori(0), 1, 0); //Fem que la posX de la figura i la figura siguin aleatories

	for (int i = 0; i < Aleatori(N_GIRS_HORARIS); i++) 
		gir(GIR_HORARI); //Fem que els girs de la figura siguin aleatoris
}

void Figura::inicialitza(const TipusFigura& figura, int posX, int posY, int codiGir)
{
	for (int i = 0; i < MAX_ALCADA; i++)
		for (int j = 0; j < MAX_AMPLADA; j++)
			m_forma[i][j] = NO_COLOR; //S'inicializa cada posicio de la figura a NO_COLOR

	m_figura = figura; //S'assigna el tipus de figura que es passa per parametre a la variable privada 
	m_color = (ColorFigura)figura; //S'assigna el color de figura que es passa per parametre a la variable privada 
	m_posX = posX - 1; //S'estableix el punt de referencia de la figura a la posX = 0
	m_posY = posY - 1; //S'estableix el punt de referencia de la figura a la posX = 0

	switch (figura) //S'inicialitza cada figura
	{
	case NO_FIGURA:
		m_alcada = 0;
		m_amplada = 0;
		break;

	case FIGURA_O:
		m_forma[0][0] = COLOR_GROC;
		m_forma[0][1] = COLOR_GROC;
		m_forma[1][0] = COLOR_GROC;
		m_forma[1][1] = COLOR_GROC;

		m_alcada = 2;
		m_amplada = 2;
		break;

	case FIGURA_I:
		m_forma[1][0] = COLOR_BLAUCEL;
		m_forma[1][1] = COLOR_BLAUCEL;
		m_forma[1][2] = COLOR_BLAUCEL;
		m_forma[1][3] = COLOR_BLAUCEL;

		m_alcada = MAX_ALCADA;
		m_amplada = MAX_AMPLADA;

		break;

	case FIGURA_T:
		m_forma[0][1] = COLOR_MAGENTA;
		m_forma[1][0] = COLOR_MAGENTA;
		m_forma[1][1] = COLOR_MAGENTA;
		m_forma[1][2] = COLOR_MAGENTA;

		m_alcada = 3;
		m_amplada = 3;
		break;

	case FIGURA_L:
		m_forma[0][2] = COLOR_TARONJA;
		m_forma[1][0] = COLOR_TARONJA;
		m_forma[1][1] = COLOR_TARONJA;
		m_forma[1][2] = COLOR_TARONJA;

		m_alcada = 3;
		m_amplada = 3;
		break;

	case FIGURA_J:
		m_forma[0][0] = COLOR_BLAUFOSC;
		m_forma[1][0] = COLOR_BLAUFOSC;
		m_forma[1][1] = COLOR_BLAUFOSC;
		m_forma[1][2] = COLOR_BLAUFOSC;

		m_alcada = 3;
		m_amplada = 3;
		break;

	case FIGURA_Z:
		m_forma[0][0] = COLOR_VERMELL;
		m_forma[0][1] = COLOR_VERMELL;
		m_forma[1][1] = COLOR_VERMELL;
		m_forma[1][2] = COLOR_VERMELL;

		m_alcada = 3;
		m_amplada = 3;
		break;

	case FIGURA_S:
		m_forma[0][1] = COLOR_VERD;
		m_forma[0][2] = COLOR_VERD;
		m_forma[1][1] = COLOR_VERD;
		m_forma[1][0] = COLOR_VERD;

		m_alcada = 3;
		m_amplada = 3;
		break;
	}

	for (int i = 0; i < codiGir; i++) 
		gir(GIR_HORARI); //Girem la figura tantes vegades com ens indica codiGir 
}

void Figura::getMatriu(ColorFigura copia[MAX_ALCADA][MAX_AMPLADA]) const //Copia de matriu
{
	for (int i = 0; i < MAX_ALCADA; i++) 
		for (int j = 0; j < MAX_AMPLADA; j++)  
			copia[i][j] = m_forma[i][j]; //copia cada posicio de m_forma a copia
}

void Figura::transposarMatriu(ColorFigura matriu[MAX_ALCADA][MAX_AMPLADA]) const //Intercanvia files per columnes de la matriu matriu
{
	for (int i = 0; i < m_alcada; i++) //Recorrem les files fins a m_alcada
		for (int j = i + 1; j < m_amplada; j++) //Recorrem columnes despres de la diagonal principal
		{
			ColorFigura temp = matriu[i][j]; //Guardem el valor en una variable temporal
			matriu[i][j] = matriu[j][i]; //Assignem la posicio invertida de matriu a la posicio de matriu
			matriu[j][i] = temp; //Guardem el contingut de temp a la posicio [j][i]
		}
}

void Figura::girHorari() //Transposem i despres invertim columnes
{
	transposarMatriu(m_forma); //Transposem la matriu

	for (int i = 0; i < m_alcada; i++) //Recorrem totes les files que ocupa la matriu
		for (int j = 0; j < m_amplada / 2; j++) //Recorrem la meitat de les columnes que ocpa la matriu per poder invertir
		{
			ColorFigura temp = m_forma[i][j];
			m_forma[i][j] = m_forma[i][m_amplada - j - 1];
			m_forma[i][m_amplada - j - 1] = temp; // Fem un swap per invertir les columnes 
		}
}

void Figura::girAntiHorari() //Transposem i despres invertim files
{
	transposarMatriu(m_forma);//Transposem la matriu

	for (int i = 0; i < m_alcada / 2; i++)//Recorrem la meitat de les files per poder invertir
		for (int j = 0; j < m_amplada; j++)//Recorrem totes les columnes que ocupa la matriu
		{
			ColorFigura temp = m_forma[i][j];
			m_forma[i][j] = m_forma[m_alcada - i - 1][j];
			m_forma[m_alcada - i - 1][j] = temp; //Fem un swap per invertir files
		}
}

void Figura::gir(const DireccioGir& direccio) //Girem la figura en el sentit que ens indiqui el pramentre
{
	if (direccio == GIR_HORARI)
		girHorari(); //Si es GIR_HORARI cridem a la funcio de gir horari

	else
		girAntiHorari(); //D'altra banda cridarem a la funcio de gir anti horari
}

void Figura::desplacarHoritzontal(int dirX)
{
	m_posX += dirX; //Movem la figura a esquerra o dreta en funcio de si es 1 o -1
}

void Figura::baixar()
{
	m_posY += 1; //Baixem la figura una posicio
}

void Figura::dibiuxaFigura() const  //Dibuixa una figura
{
	for (int i = 0; i < m_alcada; i++)
		for (int j = 0; j < m_amplada; j++) //Recorrem totes les posicions de la figura 
			if(m_forma[i][j] != NO_COLOR)
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(m_forma[i][j] + 1), //Pintem del color de la figura + 1 perque cuadri amb els establerts a IMAGE_NAME
					POS_X_TAULER + ((m_posX + j) * MIDA_QUADRAT), POS_Y_TAULER + ((m_posY + i) * MIDA_QUADRAT), false); //Especifiquem la posicio on volem que es pinti
} 

void Figura::dibuixaFiguraSeguent() const 
{
	for (int i = 0; i < m_alcada; i++) //Recorrem cada posició que ocupa la figura i la pintem amb el seu color corresponent a la posició corresponent.
		for (int j = 0; j < m_amplada; j++)
			if (m_forma[i][j] != NO_COLOR) 
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(m_forma[i][j] + 1), //Pintem del color de la figura + 1 perque cuadri amb els establerts a IMAGE_NAME
					POS_X_TAULER + ((16 + j) * MIDA_QUADRAT), POS_Y_TAULER + ((i)*MIDA_QUADRAT), false); //La pintem fora del taulell a la posY = 0
}

void Figura::dibuixaFiguraSeguent2() const
{
	for (int i = 0; i < m_alcada; i++) //Recorrem cada posició que ocupa la figura i la pintem amb el seu color corresponent a la posició corresponent.
		for (int j = 0; j < m_amplada; j++)
			if (m_forma[i][j] != NO_COLOR)
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(m_forma[i][j] + 1), //Pintem del color de la figura + 1 perque cuadri amb els establerts a IMAGE_NAME
					POS_X_TAULER + ((16 + j) * MIDA_QUADRAT), POS_Y_TAULER + ((5 + i) * MIDA_QUADRAT), false); //La pintem fora del taulell a la posY = 5 
}

void Figura::dibuixaFiguraSeguent3() const
{
	for (int i = 0; i < m_alcada; i++) //Recorrem cada posició que ocupa la figura i la pintem amb el seu color corresponent a la posició corresponent.
		for (int j = 0; j < m_amplada; j++)
			if (m_forma[i][j] != NO_COLOR)
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(m_forma[i][j] + 1), //Pintem del color de la figura + 1 perque cuadri amb els establerts a IMAGE_NAME
					POS_X_TAULER + ((16 + j) * MIDA_QUADRAT), POS_Y_TAULER + ((10 + i) * MIDA_QUADRAT), false); //La pintem fora del taulell a la posY = 10
}

void Figura::dibuixaFiguraFantasma() const
{
	for (int i = 0; i < m_alcada; i++)
		for (int j = 0; j < m_amplada; j++) //Recorrem totes les posicions de la figura 
			if (m_forma[i][j] != NO_COLOR)
				GraphicManager::getInstance()->drawSprite(GRAFIC_FANTASMA, //Pintem del color que representa la figura fantasma
					POS_X_TAULER + ((m_posX + j) * MIDA_QUADRAT), POS_Y_TAULER + ((m_posY + i) * MIDA_QUADRAT), false); //La pintem respecte les variables privades
}

ifstream& operator>>(ifstream&  input, Figura& figura) //Llegim una figura desde un fitxer
{
	int novaFigura;
	int x, y;
	int codiGir;

	input >> novaFigura >> x >> y >> codiGir; //Llegim el tipus de figura, la posicio i les vegades que esta girada
	TipusFigura codiFigura = (TipusFigura)(novaFigura); //Passem el int del tipus de la figura a TipusFigura
	figura.inicialitza(codiFigura, x, y, codiGir); //Inicialitzem la figura

	return input;
}
