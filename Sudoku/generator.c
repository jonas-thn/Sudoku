#include "generator.h"

//static variablem m�ssen in der c datei definiert werden
static const int BREITE = 9;
static const int H�HE = 9;
static const int QUADRAT = 3;

static char* sudoku = NULL; //sudoku buffer f�r algorithmus

void setGeneratorElement(int x, int y, char element)
{
	sudoku[BREITE * y + x] = element;
}

char getGeneratorElement(int x, int y)
{
	return sudoku[BREITE * y + x];
}

void generatorSudokuLeeren()
{
	for (int i = 0; i < BREITE * H�HE; i++)
	{
		sudoku[i] = '.';
	}
}

int sudokuGenerieren(int schwierigkeit) //schwierigkeit 1-5
{
	zuf�lligGef�lltesSudokuGenerieren();

	char* tempBuffer1 = (char*)malloc(BREITE * H�HE * sizeof(char)); //temp1 zum zur�cksetzen falls es l�sbar ist (auf version mit entfernten elementen)
	char* tempBuffer2 = (char*)malloc(BREITE * H�HE * sizeof(char)); //temp2 zum kompletten zur�cksetzen falls es nicht l�sbar ist (auf volle version)

	for (int i = 0; i < BREITE * H�HE; i++) //tempBuffer2 speichern
	{
		tempBuffer2[i] = sudoku[i];
	}

	//10 * schwierigkeit (1-5) elemente aus dem sudoku entfernen
	//Bedingung f�r Eindeutige L�sbarkeit
	//bei weniger als 17 von 81 ausgef�llten Feldern gibt es immer mehrere L�sungen
	//ab ~38 ausgef�llten Feldern ist das Sudoku in der Regel eindeutig L�sbar
	int entfernen = 10 * schwierigkeit; 
	int l�sbar = 0;

	while (!l�sbar)
	{
		for (int i = 0; i < BREITE * H�HE; i++) //tempBuffer2 laden
		{
			sudoku[i] = tempBuffer2[i];
		}

		for (int i = 0; i < entfernen;) //anzahl an zuf�lligen elementen entfenren
		{
			int x = zahlVon1Bis9() - 1; //zuf�lliger x index
			int y = zahlVon1Bis9() - 1; //zuf�lliger y index
			if (getGeneratorElement(x, y) != '.')
			{
				setGeneratorElement(x, y, '.'); //element entfernen
				i++;
			}
		}

		for (int i = 0; i < BREITE * H�HE; i++) //tempBuffer1 speichern
		{
			tempBuffer1[i] = sudoku[i];
		}

		l�sbar = sudokuL�sen(); //testen ob sudoku l�sbar ist (l�st sudoku auch, deshalb tempBuffer1 n�tig)

		if(l�sbar) //testen ob l�sbar um eine komplette kopie zu spaaren 
		{
			for (int i = 0; i < BREITE * H�HE; i++) //tempBuffer1 laden
			{
				sudoku[i] = tempBuffer1[i];
			}
		}
	}

	free(tempBuffer1);
	free(tempBuffer2);
}

void zuf�lligGef�lltesSudokuGenerieren()
{
	int maxVersuche = 45; //h�here Zahl erh�ht Zufall, aber macht programm deutlich langsamer (30-60)
	int erfolgreich = 0;

	while (!erfolgreich)
	{
		generatorSudokuLeeren();

		for (int i = 0; i < maxVersuche; i++)
		{
			char element = charVon1Bis9();
			int x = zahlVon1Bis9() - 1;
			int y = zahlVon1Bis9() - 1;

			if (platzierenM�glich(x, y, element))
			{
				setGeneratorElement(x, y, element);
			}
		}

		erfolgreich = sudokuL�sen();
	}
}

void printGeneriertesSudoku()
{
	for (int y = 0; y < H�HE; y++) //!!!!!! erst zeilen(spalte f�r spalte) f�llen, dann spalten f�llen -> sonst transponiert
	{
		if (y % QUADRAT == 0) //nach jedem Quadrat horizontale linie
		{
			printf("+ - - - + - - - + - - - +\n");
		}

		for (int x = 0; x < BREITE; x++)
		{
			if (x % QUADRAT == 0)
			{
				printf("| "); //nach jedem Quadrat vertikale Linie
			}
			printf("%c ", getGeneratorElement(x, y)); //x und y getauscht, sonst transformiert 
		}
		printf("|\n"); //am ende eine letzte vertikale linie
	}
	printf("+ - - - + - - - + - - - +\n"); //am ende eine letzte horizonatle linie 
}

int generatorInitialisieren()
{
	srand(time(NULL));

	int test = l�serInitialisieren("Sudokus/Generiert.txt");

	if (test == -1)
	{
		return -1;
	}

	sudoku = getL�serSudokuBuffer();

	return 0;
}

void generatorBeenden()
{
	l�serBeenden();
}

int zahlVon1Bis9()
{
	int random = (rand() % 9) + 1; //von 1-9

	return random;
}

char charVon1Bis9()
{
	int random = (rand() % 9) + 1; //von 1-9
	char zahlZuChar = (char)(random + 48);

	return zahlZuChar;
}


