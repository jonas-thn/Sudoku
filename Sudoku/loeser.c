#include "loeser.h"

//static variablem muessen in der c datei definiert werden
static const int BREITE = 9;
static const int HOEHE = 9;
static const int QUADRAT = 3;

#define MAX_LEERE_FLDER 81
static leeresFeld leereFelder[81]; //array enthaelt zu bearbeitende felder (funktioniert wie stack)
static int testFeldIndex = -1; //index, auf welchem feld sich der algorithmus grade befindet

static char* sudoku = NULL; //sudoku buffer fuer algorithmus

int loeserInitialisieren(const char* original)
{
	sudoku = (char*)malloc(sizeof(char) * BREITE * HOEHE); //speicher fuer zahlen buffer in sudoku

	if (sudoku == NULL) //test ob malloc funktioniert hat
	{
		fprintf(stderr, "zahlen malloc null error (im loeser)");
		return -1;
	}

	//laden von datein seperat in "loeser" implementiert um abhaengigkeit zu "dateiarbeit.h" (von bibliotheken untereinander) zu vermeiden

	FILE* datei; //file pointer
	char temp; //temp char speichern
	int n = 0; //char nummer (in arrays)

	datei = fopen(original, "r"); //datei in read mode oeffnen


	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei oeffnen null error");
		return -1;
	}

	while ((temp = fgetc(datei)) != EOF) //solange char lesen und in temp speichern, bin end of file erreicht
	{
		if (temp != '\n') //'\n' nicht speichern
		{
			sudoku[n] = temp; //zahlen in sudoku buffer laden
			n++; //naechster char(in arrays)
		}
	}

	fclose(datei); //datei schliessen
}

void setLoeserElement(int x, int y, char element) //sudoku element setter
{
	sudoku[BREITE * y + x] = element;
}

char getLoeserElement(int x, int y) //sudoku element getter
{
	return sudoku[BREITE * y + x];
}

char* getLoeserSudokuBuffer() //sudoku pointer zurueckgeben (pointer referenz)
{
	return sudoku;
}

int zahlInZeile(int zeile, char zahl) //test ob zahl bereits in zeile vorhanden ist
{
	for (int x = 0; x < BREITE; x++)
	{
		if (zahl == getLoeserElement(x, zeile)) //zeile ist y!!!
		{
			return TRUE; //vorhanden
		}
	}

	return FALSE; //nicht vorhanden
}

int zahlInSpalte(int spalte, char zahl) //test ob zahl bereits in spalte vorhanden ist
{
	for (int y = 0; y < HOEHE; y++)
	{
		if (zahl == getLoeserElement(spalte, y)) //spalte == x
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
			char element = getLoeserElement(xStart + x, yStart + y);	// x und y offset vom ersten (oben links) element des ausgewaehlten quadrats
																		
			if (element == zahl) //test ob zahl vorhanden							
			{															
				return TRUE; //vorhanden
			}
		}
	}

	return FALSE; //nicht vorhanden
}

int platzierenMoeglich(int x, int y, char zahl) //logische kombination von "zahlenInZeile", "zahlenInSpalte" und "zahlenInQuadrat" -> kann man element in feld platzieren 
{
	int zeileTest = !zahlInZeile(y, zahl); //zeile frei
	int spalteTest = !zahlInSpalte(x, zahl); //spalte frei
	int quadratTest = !zahlInQuadrat(x, y, zahl); //quadrat frei

	return (zeileTest && spalteTest && quadratTest); //rueckgabe, ob alle 3 faelle frei sind
}

int leereFelderFinden() //alle leeren / relevanten felder fuer den loesungs algorithmus finden
{
	testFeldIndex = -1; //index startet ausserhalb

	for (int y = 0; y < HOEHE; y++) //!!!!!! erst zeilen(spalte fuer spalte) loopen, dann spalten loopen -> sonst transponiert
	{
		for (int x = 0; x < BREITE; x++)
		{
			if (getLoeserElement(x, y) == '.') //testen ob element ein punkt / frei / bearbeitbar ist
			{
				leeresFeld tempFeld = { .x = x, .y = y, .zahl = '.', .startZahl=1}; //leeres feld struktur bauen
				testFeldIndex++; //Index erhoehen
				leereFelder[testFeldIndex] = tempFeld; //feld speichern in leereFelder array (enthaet alle relevanten felder fuer den algorithmus)
			}
		}
	}

	return testFeldIndex + 1; //laenge von "leereFelder" array = anzahl der felder, die der algorithmus loesen muss
}

/*
sudoku loesungs-algorithmus:
-finde zuerst alle leeren / bearbeitbaren / relevanten felder in sudoku
-gehe felder stueck fuer sueck durch & teste ob zahlen 1-9 moeglich
-erster treffer wird gesetzt und naechstes element wird betrachtet
-sobald bei einem element keine der zahlen 1-9 funktionieren geht man zurueck zum vorherigen element
 und versucht dort fortzusetzen (bei letzter funktionierenden zahl + 1)

-> wenn sudoku loesbar, endet schleife mit ausgefuelltem sudoku (index >= felder)
->wenn sudoku nicht loesbar, endet schleife mit leerem sudoku (index < 0)
*/
int sudokuLoesen() 
{
	int leereFelderZumTesten = leereFelderFinden(); //alle bearbeitbaren felder finden & "leereFelder" array fuellen

	testFeldIndex = 0; //index auf 0 (erstes Feld) setzen

	while (testFeldIndex >= 0 && testFeldIndex < leereFelderZumTesten) //solange loopen, bis -1 (unloesbar) oder leereFelder anzahl erreicht (loesbar)
	{
		leeresFeld feldTemp = leereFelder[testFeldIndex]; //feld an index bekommen

		int startZahlTemp = feldTemp.startZahl; //start zahl bekommen (z.B. 5 -> suche geht von 5-9)
		int gefunden = FALSE; //test ob for loop ohne funde durchgeht oder ob etwas gefunden wurde

		for (int testZahl = feldTemp.startZahl; testZahl <= 9; testZahl++) //for loop testet zahlen von start bis 9
		{
			//printf("INDEX: %d, START: %d, TEST: %d, GEFUNDEN: %d\n", testFeldIndex, feldTemp.startZahl, testZahl, gefunden);

			char zahlZuChar = (char)(testZahl + 48); //vonj zahl zu ASCII character konvertieren (weil sudoku mit chars als eintraege arbeitet)
			if (platzierenMoeglich(feldTemp.x, feldTemp.y, zahlZuChar)) //testen ob aktuelle zahl platzierbar ist
			{
				setLoeserElement(feldTemp.x, feldTemp.y, zahlZuChar); //wenn ja, dann in sudoku platzieren

				//aenderung an aktuellem feld speichern
				//startZahl = testZahl + 1 !!! WICHTIG -> es wird gespeichert, an welcher zahl die suche aufgehoert hat
				//falls der alorithmus zurueck geht, wird die suche wiederhohlt (erstes valides feld gesucht)
				//damit nicht wieder das gleiche feld gefunden wird, setzt der algorithmus die start zahl von der (eventuellen) zukuenftigen suche auf die aktuell gefundene zahl + 1
				//ausserdem spaart man daurch so viele berechungen / vergleiche wie moeglich
				leeresFeld neuesFeld = { .x = feldTemp.x, .y = feldTemp.y, .zahl = zahlZuChar, .startZahl = testZahl + 1}; 
				leereFelder[testFeldIndex] = neuesFeld; //in felder array setzten

				testFeldIndex++; //index inkrementieren (zu naechstem feld gehen)
				gefunden = TRUE; //funden auf true setzen
				break; //aus for loop ausbrechen
			}
		}

		if(!gefunden) //wenn in gesamter suche kein feld gefunden, geht der algorithmus zurueck
		{
			setLoeserElement(feldTemp.x, feldTemp.y, '.'); //aktuelles feld zuruecksetzen ( '.' = leer )
			leeresFeld feldRueckgaengig = { .x = feldTemp.x, .y = feldTemp.y, .zahl = '.', .startZahl = 1}; //start zahl wider auf 1 (suchbedingung fuer anderen zweig zuruecksetzen)
			leereFelder[testFeldIndex] = feldRueckgaengig; //in felder array setzen

			testFeldIndex--; //index dekrementieren (zu vorherigem feld gehen)
		}

	}

	//Wenn testfeldindex -1, dann unloesbar, sonst loesbar
	return (testFeldIndex < 0 ? FALSE : TRUE);

}

void printGeloestesSudoku() //sudoku mit zahlen in console rpinten 
{
	for (int y = 0; y < HOEHE; y++) //!!!!!! erst zeilen(spalte fuer spalte) fuellen, dann spalten fuellen -> sonst transponiert
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
			printf("%s%c%s ", FARBE_GRUEN, getLoeserElement(x, y), FARBE_ZURUECKSETZEN); //element an x und y printen
		}
		printf("|\n"); //am ende eine letzte vertikale linie
	}
	printf("+ - - - + - - - + - - - +\n"); //am ende eine letzte horizonatle linie 
}

void loeserBeenden() //sudoku loeser beenden - heap speicher freigeben
{
	free(sudoku);
}

