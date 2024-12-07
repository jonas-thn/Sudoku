#include "generator.h"

//static variablem müssen in der c datei definiert werden
static const int BREITE = 9;
static const int HÖHE = 9;
static const int QUADRAT = 3;

static char* sudoku = NULL; //sudoku buffer für algorithmus

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
	for (int i = 0; i < BREITE * HÖHE; i++)
	{
		sudoku[i] = '.';
	}
}

int sudokuGenerieren(int schwierigkeit) //schwierigkeit 1-5
{
	zufälligGefülltesSudokuGenerieren();

	char* tempBuffer1 = (char*)malloc(BREITE * HÖHE * sizeof(char)); //temp1 zum zurücksetzen falls es lösbar ist (auf version mit entfernten elementen)
	char* tempBuffer2 = (char*)malloc(BREITE * HÖHE * sizeof(char)); //temp2 zum kompletten zurücksetzen falls es nicht lösbar ist (auf volle version)

	for (int i = 0; i < BREITE * HÖHE; i++) //tempBuffer2 speichern
	{
		tempBuffer2[i] = sudoku[i];
	}

	//10 * schwierigkeit (1-5) elemente aus dem sudoku entfernen
	//Bedingung für Eindeutige Lösbarkeit
	//bei weniger als 17 von 81 ausgefüllten Feldern gibt es immer mehrere Lösungen
	//ab ~38 ausgefüllten Feldern ist das Sudoku in der Regel eindeutig Lösbar
	int entfernen = 10 * schwierigkeit; 
	int lösbar = 0;

	while (!lösbar)
	{
		for (int i = 0; i < BREITE * HÖHE; i++) //tempBuffer2 laden
		{
			sudoku[i] = tempBuffer2[i];
		}

		for (int i = 0; i < entfernen;) //anzahl an zufälligen elementen entfenren
		{
			int x = zahlVon1Bis9() - 1; //zufälliger x index
			int y = zahlVon1Bis9() - 1; //zufälliger y index
			if (getGeneratorElement(x, y) != '.')
			{
				setGeneratorElement(x, y, '.'); //element entfernen
				i++;
			}
		}

		for (int i = 0; i < BREITE * HÖHE; i++) //tempBuffer1 speichern
		{
			tempBuffer1[i] = sudoku[i];
		}

		lösbar = sudokuLösen(); //testen ob sudoku lösbar ist (löst sudoku auch, deshalb tempBuffer1 nötig)

		if(lösbar) //testen ob lösbar um eine komplette kopie zu spaaren 
		{
			for (int i = 0; i < BREITE * HÖHE; i++) //tempBuffer1 laden
			{
				sudoku[i] = tempBuffer1[i];
			}
		}
	}

	free(tempBuffer1);
	free(tempBuffer2);
}

void zufälligGefülltesSudokuGenerieren()
{
	int maxVersuche = 45; //höhere Zahl erhöht Zufall, aber macht programm deutlich langsamer (30-60)
	int erfolgreich = 0;

	while (!erfolgreich)
	{
		generatorSudokuLeeren();

		for (int i = 0; i < maxVersuche; i++)
		{
			char element = charVon1Bis9();
			int x = zahlVon1Bis9() - 1;
			int y = zahlVon1Bis9() - 1;

			if (platzierenMöglich(x, y, element))
			{
				setGeneratorElement(x, y, element);
			}
		}

		erfolgreich = sudokuLösen();
	}
}

void printGeneriertesSudoku()
{
	for (int y = 0; y < HÖHE; y++) //!!!!!! erst zeilen(spalte für spalte) füllen, dann spalten füllen -> sonst transponiert
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

	int test = löserInitialisieren("Sudokus/Generiert.txt");

	if (test == -1)
	{
		return -1;
	}

	sudoku = getLöserSudokuBuffer();

	return 0;
}

void generatorBeenden()
{
	löserBeenden();
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


