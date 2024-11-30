#include "löser.h"

int löserInitialisieren(const char* original)
{
	sudoku = (char*)malloc(sizeof(char) * BREITE * HÖHE); //speicher für zahlen buffer in sudoku

	if (sudoku == NULL) //test ob malloc funktioniert hat
	{
		fprintf(stderr, "zahlen malloc null error (im löser)");
		return -1;
	}

	//laden von datein seperat in "löser" implementiert um abhängigkeit zu "dateiarbeit.h" (von bibliotheken untereinander) zu vermeiden

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
			sudoku[n] = temp; //zahlen in sudoku buffer laden
			n++; //nächster char(in arrays)
		}
	}

	fclose(datei); //datei schließen
}

void setSudokuElement(int x, int y, char element) //sudoku element setter
{
	sudoku[BREITE * y + x] = element;
}

char getSudokuElement(int x, int y) //sudoku element getter
{
	return sudoku[BREITE * y + x];
}

int zahlInZeile(int zeile, char zahl) //test ob zahl bereits in zeile vorhanden ist
{
	for (int x = 0; x < BREITE; x++)
	{
		if (zahl == getSudokuElement(x, zeile)) //zeile ist y!!!
		{
			return TRUE; //vorhanden
		}
	}

	return FALSE; //nicht vorhanden
}

int zahlInSpalte(int spalte, char zahl) //test ob zahl bereits in spalte vorhanden ist
{
	for (int y = 0; y < HÖHE; y++)
	{
		if (zahl == getSudokuElement(spalte, y)) //spalte == x
		{
			return TRUE; //vorhanden
		}
	}

	return FALSE; //nicht vorhanden
}

//test ob zahl bereits in quadrat vorhanden ist
int zahlInQuadrat(int x, int y, char zahl) //x und y als index(0-8)
{
	int xQuadrat = x / (int)QUADRAT; //quadrat x index (0-2)
	int yQuadrat = y / (int)QUADRAT; //quadrat y index (0-2)

	int xStart = xQuadrat * QUADRAT; //erstes element von quadrat mit index erhalten x
	int yStart = yQuadrat * QUADRAT; //erstes element von quadrat mit index erhalten y

	for (int y = 0; y < QUADRAT; y++)
	{
		for (int x = 0; x < QUADRAT; x++)
		{
			char element = getSudokuElement(xStart + x, yStart + y);	// x und y offset vom ersten (oben links) element des ausgewählten quadrats
																		
			if (element == zahl) //test ob zahl vorhanden							
			{															
				return TRUE; //vorhanden
			}
		}
	}

	return FALSE; //nicht vorhanden
}

int platzierenMöglich(int x, int y, char zahl) //logische kombination von "zahlenInZeile", "zahlenInSpalte" und "zahlenInQuadrat" -> kann man element in feld platzieren 
{
	int zeileTest = !zahlInZeile(y, zahl); //zeile frei
	int spalteTest = !zahlInSpalte(x, zahl); //spalte frei
	int quadratTest = !zahlInQuadrat(x, y, zahl); //quadrat frei

	return (zeileTest && spalteTest && quadratTest); //rückgabe, ob alle 3 fälle frei sind
}

int leereFelderFinden() //alle leeren / relevanten felder für den lösungs algorithmus finden
{
	testFeldIndex = -1; //index startet ausßerhalb

	for (int y = 0; y < HÖHE; y++) //!!!!!! erst zeilen(spalte für spalte) loopen, dann spalten loopen -> sonst transponiert
	{
		for (int x = 0; x < BREITE; x++)
		{
			if (getSudokuElement(x, y) == '.') //testen ob element ein punkt / frei / bearbeitbar ist
			{
				leeresFeld tempFeld = { .x = x, .y = y, .zahl = '.', .startZahl=1}; //leeres feld struktur bauen
				testFeldIndex++; //Index erhöhen
				leereFelder[testFeldIndex] = tempFeld; //feld speichern in leereFelder array (enthät alle relevanten felder für den algorithmus)
			}
		}
	}

	return testFeldIndex + 1; //länge von "leereFelder" array = anzahl der felder, die der algorithmus lösen muss
}

/*
sudoku lösungs-algorithmus:
-finde zuerst alle leeren / bearbeitbaren / relevanten felder in sudoku
-gehe felder stück für sück durch & teste ob zahlen 1-9 möglich
-erster treffer wird gesetzt und nächtes element wird betrachtet
-sobald bei einem element keine der zahlen 1-9 funktionieren geht man zurück zum vorherigen element
 und versucht dort fortzusetzen (bei letzter funktionierenden zahl + 1)

-> wenn sudoku lösbar, endet schleife mit ausgefülltem sudoku (index >= felder)
->wenn sudoku nicht lösbar, endet schleife mit leerem sudoku (index < 0)
*/
void sudokuLösen() 
{
	int leereFelderZumTesten = leereFelderFinden(); //alle bearbeitbaren felder finden & "leereFelder" array füllen

	testFeldIndex = 0; //index auf 0 (erstes Feld) setzen

	while (testFeldIndex >= 0 && testFeldIndex < leereFelderZumTesten) //solange loopen, bis -1 (unlösbar) oder leereFelder anzahl erreicht (lösbar)
	{
		leeresFeld feldTemp = leereFelder[testFeldIndex]; //feld an index bekommen

		int startZahlTemp = feldTemp.startZahl; //start zahl bekommen (z.B. 5 -> suche geht von 5-9)
		int gefunden = FALSE; //test ob for loop ohne funde durchgeht oder ob etwas gefunden wurde

		for (int testZahl = feldTemp.startZahl; testZahl <= 9; testZahl++) //for loop testet zahlen von start bis 9
		{
			//printf("INDEX: %d, START: %d, TEST: %d, GEFUNDEN: %d\n", testFeldIndex, feldTemp.startZahl, testZahl, gefunden);

			char zahlZuChar = (char)(testZahl + 48); //vonj zahl zu ASCII character konvertieren (weil sudoku mit chars als einträge arbeitet)
			if (platzierenMöglich(feldTemp.x, feldTemp.y, zahlZuChar)) //testen ob aktuelle zahl platzierbar ist
			{
				setSudokuElement(feldTemp.x, feldTemp.y, zahlZuChar); //wenn ja, dann in sudoku platzieren

				//änderung an aktuellem feld speichern
				//startZahl = testZahl + 1 !!! WICHTIG -> es wird gespeichert, an welcher zahl die suche aufgehört hat
				//falls der alorithmus zurück geht, wird die suche wiederhohlt (erstes valides feld gesucht)
				//damit nicht wieder das gleiche feld gefunden wird, setzt der algorithmus die start zahl von der (eventuellen) zukünftigen suche auf die aktuell gefundene zahl + 1
				//außerdem spaart man daurch so viele berechungen / vergleiche wie möglich
				leeresFeld neuesFeld = { .x = feldTemp.x, .y = feldTemp.y, .zahl = zahlZuChar, .startZahl = testZahl + 1}; 
				leereFelder[testFeldIndex] = neuesFeld; //in felder array setzten

				testFeldIndex++; //index inkrementieren (zu nächstem feld gehen)
				gefunden = TRUE; //funden auf true setzen
				break; //aus for loop ausbrechen
			}
		}

		if(!gefunden) //wenn in gesamter suche kein feld gefunden, geht der algorithmus zurück
		{
			setSudokuElement(feldTemp.x, feldTemp.y, '.'); //aktuelles feld zurücksetzen ( '.' = leer )
			leeresFeld feldRückgängig = { .x = feldTemp.x, .y = feldTemp.y, .zahl = '.', .startZahl = 1}; //start zahl wider auf 1 (suchbedingung für anderen zweig zurücksetzen)
			leereFelder[testFeldIndex] = feldRückgängig; //in felder array setzen

			testFeldIndex--; //index dekrementieren (zu vorherigem feld gehen)
		}
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

int löserBeenden() //sudoku löser beenden (free)
{
	free(sudoku);
}

