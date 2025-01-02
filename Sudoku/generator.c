#include "generator.h"

//static variablem muessen in der c datei definiert werden
static const int BREITE = 9;
static const int HOEHE = 9;
static const int QUADRAT = 3;

static char* sudoku = NULL; //sudoku buffer fuer algorithmus

int generatorInitialisieren() //sudoku generator initialisieren
{
	srand(time(NULL)); //zufallsgenerator initialisieren (Seed = time)

	//loeser mit leerer datei initialisieren
	//aufgrund der struktur des loesers wird leere datei benoetigt
	int test = loeserInitialisieren("Sudokus/Generiert.txt"); 

	if (test == -1) //wenn loeser fehlschlaegt, dann auch generator
	{
		return -1;
	}

	//WICHTIG:
	//sudoku buffer im generator zeigt auf gleichen buffer wie loeser (pointer referenz)
	//man arbeitet als eigendlich die ganze zeit mit dem loeser buffer
	//hin- und herkopieren von verschiedenen arrays gespaart
	sudoku = getLoeserSudokuBuffer(); 

	return 0; 
}

void setGeneratorElement(int x, int y, char element) //generator element setter
{
	sudoku[BREITE * y + x] = element;
}

char getGeneratorElement(int x, int y) //generator element getter
{
	return sudoku[BREITE * y + x];
}

void generatorSudokuLeeren() //gesamtes sudoku leeren
{
	for (int i = 0; i < BREITE * HOEHE; i++)
	{
		sudoku[i] = '.';
	}
}

char* getGeneriertesSudoku() //gibt generator sudoku buffer zurueck (pointer referenz)
{
	return sudoku;
}

//setzt / ueberschreibt datein falls neues sudoku generiert wird 
int generatorDateiManager(char* originalPfad, char* dateiPfad, char* zahlen)
{
	FILE* datei; //file pointer

	datei = fopen(originalPfad, "w"); //ORIGINAL datei oeffnen

	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei oeffnen null error");
		return -1;
	}

	for (int i = 0; i < BREITE*HOEHE; i++) //fuer array laenge (81 zeichen) loop
	{
		if (i % 9 == 0) //nach jedem 9. zeichen ein zeilenumbruch fuer lesbarkeit
		{
			fputc('\n', datei); //zeilenumbruch einfuegen
		}

		fputc(zahlen[i], datei); //char von zahlen array in datei schreiben
	}

	fclose(datei); //datei schliessen

	//------------------------------------------------------------------------------

	datei = fopen(dateiPfad, "w"); //SPEICHER datei oeffnen

	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei oeffnen null error");
		return -1;
	}

	for (int i = 0; i < BREITE * HOEHE; i++) //fuer array laenge (81 zeichen) loop
	{
		if (i % 9 == 0) //nach jedem neunten zeichen ein zeilenumbruch fuer lesbarkeit
		{
			fputc('\n', datei); //zeilenumbruch
		}

		fputc(zahlen[i], datei); //char von zahlen array in datei schreiben
	}

	fclose(datei); //datei schliessen

	return 0; //alles gut
}

/* ALGORITHMUS ZUSAMMENFASSUNG :
-zuerst ein pseudo zufaelliges vollstaendig ausgefuelltes sudoku generieren (30-60 wirklich zufaellige felder)
-von diesem garantiert loesbaren ausgefuellten sudoku bis zu 50 felder loeschen (je nach schwierigkeit)
-wenn man sich von beiden "seiten" an eine loesung annaehert erhaelt man eine gute balance zwischen zufaelligkeit, loesbarkeit und geschwindigkeit
(nach jeder generierten zahl zu testen, ob das sudoku noch loesbar ist, waere nicht performant, da der loesungs-algorithmus zu oft ausgefuehrt werden muesste)
-deshalb naehert sich der algorithmus "konstanten" zahlen an, die eine hohe warscheinlichekeit haben erfolgreich zu sein
-so muss der loesbarkeits-test nur moeglichst selten durchgefuehrt werden 
*/

int sudokuGenerieren(int schwierigkeit) //schwierigkeit 1-5
{
	zufaelligGefuelltesSudokuGenerieren(); //sudoku komplett mit zufaelligen moeglichen werten faellen (aber loesbar/geloest)

	char* tempBuffer1 = (char*)malloc(BREITE * HOEHE * sizeof(char)); //temp1 zum zuruecksetzen falls es loesbar ist (auf version mit entfernten elementen)
	char* tempBuffer2 = (char*)malloc(BREITE * HOEHE * sizeof(char)); //temp2 zum kompletten zuruecksetzen falls es nicht loesbar ist (auf volle version)

	for (int i = 0; i < BREITE * HOEHE; i++) //tempBuffer2 speichern
	{
		tempBuffer2[i] = sudoku[i];
	}

	//10 * schwierigkeit (1-5) elemente aus dem sudoku entfernen
	//Bedingung fuer Eindeutige Loesbarkeit
	//bei weniger als 17 von 81 ausgefuellten Feldern gibt es immer mehrere Loesungen
	//ab ~38 ausgefuellten Feldern ist das Sudoku in der Regel eindeutig Loesbar
	int entfernen = 10 * schwierigkeit; 
	int loesbar = 0;

	while (!loesbar)
	{
		for (int i = 0; i < BREITE * HOEHE; i++) //tempBuffer2 laden
		{
			sudoku[i] = tempBuffer2[i];
		}

		for (int i = 0; i < entfernen;) //anzahl an zufuelligen elementen entfenren
		{
			int x = zahlVon1Bis9() - 1; //zufaelliger x index
			int y = zahlVon1Bis9() - 1; //zufaelliger y index
			if (getGeneratorElement(x, y) != '.')
			{
				setGeneratorElement(x, y, '.'); //element entfernen
				i++;
			}
		}

		for (int i = 0; i < BREITE * HOEHE; i++) //tempBuffer1 speichern
		{
			tempBuffer1[i] = sudoku[i];
		}

		loesbar = sudokuLoesen(); //testen ob sudoku loesbar ist (loest sudoku auch, deshalb tempBuffer1 noetig)

		if(loesbar) //testen ob loesbar um eine komplette kopie zu spaaren 
		{
			for (int i = 0; i < BREITE * HOEHE; i++) //tempBuffer1 laden
			{
				sudoku[i] = tempBuffer1[i];
			}
		}
	}

	//heap speicher freigeben
	free(tempBuffer1);
	free(tempBuffer2);
}

void zufaelligGefuelltesSudokuGenerieren()
{
	int maxVersuche = 45; //hoehere Zahl erhoeht Zufall, aber macht programm langsamer (30-60)
	int erfolgreich = 0; //schauen ob aktuelle generierung moeglich/loesbar/voll ist

	while (!erfolgreich) //solange wiederhohlen bis moegliches/loesbares/volles sudoku erreicht
	{
		generatorSudokuLeeren(); //komplettes sudoku leeren/zuruecksetzen

		for (int i = 0; i < maxVersuche; i++) //zufaellige felder setzen
		{
			char element = charVon1Bis9(); //zufaelliges element generieren
			int x = zahlVon1Bis9() - 1; //xIndex generieren
			int y = zahlVon1Bis9() - 1; //yIndex generieren

			if (platzierenMoeglich(x, y, element)) //wenn platzieren moeglich (also spalte, zeile und quadrat frei von elemet ist)
			{
				setGeneratorElement(x, y, element); //element setzen
			}
		}

		erfolgreich = sudokuLoesen(); //sudoku loesen -> alle freien felder auffuellen
	}
}

void printGeneriertesSudoku()
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
			printf("%c ", getGeneratorElement(x, y)); //element an x und y printen
		}
		printf("|\n"); //am ende eine letzte vertikale linie
	}
	printf("+ - - - + - - - + - - - +\n"); //am ende eine letzte horizonatle linie 
}

void generatorBeenden() //dynamischen speicher freigeben
{
	loeserBeenden();
}

int zahlVon1Bis9() //zufaelligen int zwischen 1-9 generieren
{
	int random = (rand() % 9) + 1; //von 1-9

	return random;
}

char charVon1Bis9() //zufaelligen char zsichen 1-9 generieren
{
	int random = (rand() % 9) + 1; //von 1-9
	char zahlZuChar = (char)(random + 48); //in char konvertieren

	return zahlZuChar;
}


