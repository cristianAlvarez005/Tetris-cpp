#include "Joc.h"

void Joc::inicialitza() //Inicialitzem una nova figura perque vagi caient
{
	for (int i = 0; i < N_FILES_TAULER; i++)
		for (int j = 0; j < N_COL_TAULER; j++)
			m_tauler.setTauler(i, j, COLOR_NEGRE); //Inicialitzem tot el taulell de COLOR_NEGRE

	m_figura.figuraAleatoria(); //Generem una figura perque vagi caient un cop la anterior ja s'ha colocat al taulell
	m_figuraSeguent.figuraAleatoria(); //Generem una figura que sera la seguent que caura
	m_figuraSeguent2.figuraAleatoria(); //generem la figura seguent2
	m_figuraSeguent3.figuraAleatoria(); //Generem la figura seguent3
	baixaFantasma(); //Fem que la fantasma estigui a la ultima fila ja que el taulell esta buit
}

void Joc::inicialitzaFitxerInicial(const string& fitxerInicial)  //Inicialitzem l'estat inicial de la partida
{

	ifstream fitxer;
	fitxer.open(fitxerInicial); //Obrim el fitxer
	if (fitxer.is_open()) //Mirem si el fitxer esta obert
	{
		fitxer >> m_figura; //Llegim la informacio d'una figura
		fitxer >> m_tauler; //Llegim la informacio del taulell
	}
	fitxer.close(); //Tanquem el fitxer
}

void Joc::inicialitzaFitxerFigures(const string& fitxerFigures)
{
	while (!m_figures.esBuida())
		m_figures.treu(); //Treiem elements fins que estigui buida per si hem acabat la partida abans de que s'acabin les figures

	int codi, fila, columna, gir;

	ifstream fitxer;
	fitxer.open(fitxerFigures); //Obrim el fitxer
	if (fitxer.is_open()) //Mirem si el fitxer esta obert
	{
		while (fitxer >> codi >> fila >> columna >> gir) //Llegim mentres es pugui llegir del fitxer la informacio d'una figura
		{
			TipusFigura codiFig = (TipusFigura)(codi); //Passem el int a TipusFigura
			TestFigures figura(codiFig, fila + 1, columna + 1, gir); //Creem la figura i sumem 1 a la fila i columna per colocarla a la posicio correcte
			m_figures.afegeix(figura); //La afegim a la cua
		}
		fitxer.close(); //Tanquem el fitxer
	}
}

void Joc::noFantasmaNoSeguent() //Treiem les figures seguents i la fantasma de la pantalla
{
	//Inicialitzem les figures seguents i la figura fantasma a NO_FIGURA i a la posicio 0 amb gir 0
	m_figuraSeguent.inicialitza(NO_FIGURA, 0, 0, 0); 
	m_figuraSeguent2.inicialitza(NO_FIGURA, 0, 0, 0); 
	m_figuraSeguent3.inicialitza(NO_FIGURA, 0, 0, 0);
	m_fantasma.inicialitza(NO_FIGURA, 0, 0, 0); 
}

bool Joc::acabarJoc() //Comprova si el joc s'ha acabat
{
	bool acabar = m_tauler.taulerComplet(m_figura); //Mira si el valor que retorna la funcio es true o false

	if (acabar) //Si es true
		m_figura.inicialitza(NO_FIGURA, 0, 0, 0); //Inicialitzem la figura que esta caient a 0

	return acabar; //Retornem si s'ha acabat el joc o no
}

void Joc::afegirFigura() //Afegim la figura al taulell
{
	int posXFigura = m_figura.getPosX(); //Recuperem la posX de la figura
	int posYFigura = m_figura.getPosY(); //Recuperem la posY de la figura

	//Recorrem cada posicio de la figura
	for (int i = 0; i < MAX_ALCADA; i++)
		for (int j = 0; j < MAX_AMPLADA; j++)
			if (m_figura.getPosicioFigura(i, j) != NO_COLOR) //Mirem si en aquella posicio de la figura no hi ha NO_COLOR
				m_tauler.setTauler(posYFigura + i, posXFigura + j, m_figura.getPosicioFigura(i, j)); //Establim aquella posicio de la figura al taulell
}

void Joc::generarFigures(int mode)
{
	if (mode == 1) //Si el mode es 1 estem en mode normal
	{
		m_figura = m_figuraSeguent; //La figura seguent passa a la actual ja que la actual ja s'ha colocat
		m_figuraSeguent = m_figuraSeguent2; //La figura seguent 2 pasa a la seguent
		m_figuraSeguent2 = m_figuraSeguent3; //La figura seguent 3 passa a la seguent 2
		m_figuraSeguent3.figuraAleatoria(); //La figura seguent 3 queda buida aixi que generem una nova figura aleatoria
		baixaFantasma(); //Actualitzem la posicio de la figura fantasma al generar una figura
	}
	else //Estem en mode test
	{
		if (!m_figures.esBuida()) //Mirem si la cua de figures esta buida i sino ho esta entrem al if 
		{
			TestFigures figura = m_figures.getPrimer(); //Obtenim el primer element de la cua
			m_figura.inicialitza(figura.getFigura(), figura.getColumna(), figura.getFila(), figura.getGir());  //Inicialitzem la figura
			m_figures.treu(); //La treiem de la cua
		}
		else //Si la cua esta buida
			m_figura.inicialitza(NO_FIGURA, 0, 0, 0); //Inicialitzem una figura buida
	}
}

bool Joc::giraFigura(DireccioGir direccio) //Gira una figura si es pot
{
	bool girValid; //Bolea que determina si el gir es valid
	Figura copia = m_figura; //Es fa una copia de la figura
	copia.gir(direccio); //Es gira la copia
	girValid = m_tauler.movimentEsValid(copia, m_figura.getPosX(), m_figura.getPosY()); //Es comproba si la copia es pot girar ja que retorna true o false

	if (girValid) //Si es true s'entra al if
		m_figura.gir(direccio); //Si la copia es pot girar, es gira la figura real

	return girValid; //Es retorna true o false en funcio de si la figura s'ha pogut girar o no
}

bool Joc::mouFigura(int dirX)
{
	int posXFigura = m_figura.getPosX(); //Recuperem posX de la figura
	int posYFigura = m_figura.getPosY(); //Recuperem posY de la figura

	Figura copia = m_figura; //Fem una copia de la figura
	copia.desplacarHoritzontal(dirX); //Movem la copia de la figura en la direccio que indica el parametre
	bool movimentValid = false; //Establim que en un principi no es pot moure la figura

	if (m_tauler.movimentEsValid(copia, posXFigura + dirX, posYFigura)) //Entrem al if si la copia es pot moure   
	{
		m_figura.desplacarHoritzontal(dirX); //Actualitzem la figura real movent-la en la direccio que indica el parametre
		movimentValid = true; //Establim que el moviment es valid
	}

	return movimentValid; //Retornem si el moviment es valid o no amb true o false
}

int Joc::baixaFigura(int mode)
{
	int filesEliminades = 0; //Comptador de files eliminades
	Figura copia = m_figura; //Realitza una copia de la figura
	bool valid = m_tauler.movimentEsValid(copia, m_figura.getPosX(), m_figura.getPosY() + 1); //Es comprova si la copia es pot baixar o no

	if (valid) //Si es pot baixar entrem al if
		m_figura.baixar(); //Baixem la figura real
	else //En el moment que no es pot baixar entrem al else
	{
		afegirFigura(); //Col·loquem la figura al taulell en la posicio que colisiona
		filesEliminades = m_tauler.eliminarFilesCompletes(); //Mirem quantes files s'han eliminat un cop la figura esta col·locada
		generarFigures(mode); //Generem les figures depenent del mode en el que estem
	}

	return filesEliminades; //Retornem el numero de files que s'ha eliminat al baixar la figura
}

int Joc::baixaFiguraDeCop(int mode)
{
	int posYFigura = m_figura.getPosY(); //Recuperem la posY de la figura
	int filesEliminades = 0; //Contador de files eliminades
	bool baixar = true; //Esta a true si la figura es pot baixar
	Figura copia = m_figura; //Fem una copia de la figura que volem baixar

	while (posYFigura < N_FILES_TAULER && (baixar)) //Iterarem les files sempre que la posY sigui menor a l'alçada del taulell i es pugui baixar
	{
		baixar = m_tauler.movimentEsValid(copia, m_figura.getPosX(), posYFigura + 1); //Mirem si la copia de la figura es pot baixar
		copia.baixar(); //Baixem la copia de la figura
		if(baixar) //Si es pot baixar entrem al if
			posYFigura++; //Augmentem la posY de la figura real
	}

	m_figura.setPosY(posYFigura); //Establim la nova posY despres de baixar de cop
	afegirFigura(); //La afegim al taulell un cop no es pot moure mes
	filesEliminades = m_tauler.eliminarFilesCompletes(); //Un cop afegida mirem quantes files s'han eliminat
	generarFigures(mode); //Generem les figures depenent del mode en el que estem

	return filesEliminades; //Retornem el numero de files que s'han eliminat despres de baixar de cop
}

void Joc::baixaFantasma()
{
	m_fantasma = m_figura; //Assignem la figura que esta caient a la figura fantasma
	int posYFigura = m_fantasma.getPosY(); //Recuperem la posY de la figura fantasma
	bool baixar = true; //Esta a true si la figura es pot baixar
	Figura copia = m_fantasma; //Fem una copia de la figura fantasma

	while (posYFigura < N_FILES_TAULER && (baixar)) //Iterarem les files sempre que la posY sigui menor a l'alçada del taulell i es pugui baixar
	{
		baixar = m_tauler.movimentEsValid(copia, m_fantasma.getPosX(), posYFigura + 1); //Mirem si la copia de la figura fantasma es pot baixar
		copia.baixar(); //Baixem la copia de la figura
		if (baixar) //Si es pot baixar entrem al if
			posYFigura++; //Augmentem la posY de la figura fantasma
	}

	m_fantasma.setPosY(posYFigura); //Actualitzem la posY de la figura fantasma un cop baixada
	m_fantasma.setColor(COLOR_FANTASMA); //Establim el color de la figura fantasma al seu color ja que abans era de m_figura
}

void Joc::dibuixa() //Funcio que dibuixa el joc
{
	m_tauler.dibuixaTauler(); //Dibuixem el taullel amb les peces o en negre depenent de l'estat en el que es troba
	m_fantasma.dibuixaFiguraFantasma();  //Dibuixem la figura fantasma abans de la figura perque la figura pugui tapar la fantasma
	m_figura.dibiuxaFigura(); //Dibuixem la figura que es troba caient
	//Dibuixem les figures seguents
	m_figuraSeguent.dibuixaFiguraSeguent(); 
	m_figuraSeguent2.dibuixaFiguraSeguent2(); 
	m_figuraSeguent3.dibuixaFiguraSeguent3();
}
