#include "löser.h"

int löserInitialisieren(const char* original)
{
	sudoku = (char*)malloc(sizeof(char) * BREITE * HÖHE); //speicher für zahlen array

	if (sudoku == NULL) //test ob malloc funktioniert hat
	{
		fprintf(stderr, "zahlen malloc null error (im löser)");
		return -1;
	}

	FILE* datei; //file pointer
	char temp; //temp char speichern
	int n = 0; //char nummer (in arrays)

	datei = fopen(original, "r"); //datei in read mode öffen


	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei öffnen null error");
		return -1;
	}

	while ((temp = fgetc(datei)) != EOF) //solange char lesen und in temp speichern, bin end of file erreicht
	{
		if (temp != '\n') //'\n' nicht speichern
		{
			sudoku[n] = temp; //zahlen array beladen
			n++; //nächster char(in arrays)
		}
	}

	fclose(datei); //datei schließen
}

void setSudokuElement(int x, int y, char element)
{
	sudoku[BREITE * y + x] = element;
}

char getSudokuElement(int x, int y)
{
	return sudoku[BREITE * y + x];
}

int zahlInZeile(int zeile, char zahl)
{
	for (int x = 0; x < BREITE; x++)
	{
		if (zahl == getSudokuElement(x, zeile))
		{
			return TRUE;
		}
	}

	return FALSE;
}

int zahlInSpalte(int spalte, char zahl)
{
	for (int y = 0; y < HÖHE; y++)
	{
		if (zahl == getSudokuElement(spalte, y))
		{
			return TRUE;
		}
	}

	return FALSE;
}

int zahlInQuadrat(int x, int y, char zahl) //x und y als index(0-8)
{
	int xQuadrat = x / (int)QUADRAT; //quadreat x index (0-2)
	int yQuadrat = y / (int)QUADRAT; //quadrat y index (0-2)

	int xStart = xQuadrat * QUADRAT;
	int yStart = yQuadrat * QUADRAT;

	for (int y = 0; y < QUADRAT; y++)
	{
		for (int x = 0; x < QUADRAT; x++)
		{
			char element = getSudokuElement(xStart + x, yStart + y);

			if (element == zahl)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

int platzierenMöglich(int x, int y, char zahl)
{
	int zeileTest = !zahlInZeile(y, zahl);
	int spalteTest = !zahlInSpalte(x, zahl);
	int quadratTest = !zahlInQuadrat(x, y, zahl);

	return (zeileTest && spalteTest && quadratTest);
}

int leereFelderFinden()
{
	testFeldIndex = -1;

	for (int y = 0; y < HÖHE; y++)
	{
		for (int x = 0; x < BREITE; x++)
		{
			if (getSudokuElement(x, y) == '.')
			{
				leeresFeld tempFeld = { .x = x, .y = y, .zahl = '.', .startZahl=1};
				testFeldIndex++;
				leereFelder[testFeldIndex] = tempFeld;
			}
		}
	}

	return testFeldIndex + 1;
}

int sudokuLösen()
{
	int leereFelderZumTesten = leereFelderFinden();

	testFeldIndex = 0;

	while (testFeldIndex >= 0 && testFeldIndex < leereFelderZumTesten)
	{
		leeresFeld feldTemp = leereFelder[testFeldIndex];

		int startZahlTemp = feldTemp.startZahl;
		int gefunden = FALSE;

		for (int testZahl = feldTemp.startZahl; testZahl <= 9; testZahl++)
		{
			printf("INDEX: %d, START: %d, TEST: %d, GEFUNDEN: %d\n", testFeldIndex, feldTemp.startZahl, testZahl, gefunden);

			char zahlZuChar = (char)(testZahl + 48);
			if (platzierenMöglich(feldTemp.x, feldTemp.y, zahlZuChar))
			{
				setSudokuElement(feldTemp.x, feldTemp.y, zahlZuChar);

				leeresFeld neuesFeld = { .x = feldTemp.x, .y = feldTemp.y, .zahl = zahlZuChar, .startZahl = testZahl + 1 };
				leereFelder[testFeldIndex] = neuesFeld;

				testFeldIndex++;
				gefunden = TRUE;
				break;
			}
		}

		if(!gefunden)
		{
			setSudokuElement(feldTemp.x, feldTemp.y, '.');
			leeresFeld feldRückgängig = { .x = feldTemp.x, .y = feldTemp.y, .zahl = '.', .startZahl = 1};
			leereFelder[testFeldIndex] = feldRückgängig;

			testFeldIndex--;
		}

	}

	if (testFeldIndex >= leereFelderZumTesten)
	{
		return 1; 
	}
	else
	{
		return 0;
	}

}

void printGelöstesSudoku() //sudoku mit zahlen in console rpinten 
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
			printf("%s%c%s ", FARBE_GRÜN, getSudokuElement(x, y), FARBE_ZURÜCKSETZEN); //x und y getauscht, sonst transformiert 
		}
		printf("|\n"); //am ende eine letzte vertikale linie
	}
	printf("+ - - - + - - - + - - - +\n"); //am ende eine letzte horizonatle linie 
}

int löserBeenden()
{
	free(sudoku);
}

