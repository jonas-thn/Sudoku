#include "generator.h"

//static variablem müssen in der c datei definiert werden
static const int BREITE = 9;
static const int HÖHE = 9;
static const int QUADRAT = 3;

static char* sudoku = NULL; //sudoku buffer für algorithmus

int generatorInitialisieren() //sudoku generator initialisieren
{
	srand(time(NULL)); //zufallsgenerator initialisieren (Seed = time)

	//löser mit leerer datei initialisieren
	//aufgrund der struktur des lösers wird leere datei benötigt
	int test = löserInitialisieren("Sudokus/Generiert.txt"); 

	if (test == -1) //wenn löser fehlschlägt, dann auch generator
	{
		return -1;
	}

	//WICHTIG:
	//sudoku buffer im generator zeigt auf gleichen buffer wie löser (pointer referenz)
	//man arbeitet als eigendlich die ganze zeit mit dem löser buffer
	//hin- und herkopieren von verschiedenen arrays gespaart
	sudoku = getLöserSudokuBuffer(); 

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
	for (int i = 0; i < BREITE * HÖHE; i++)
	{
		sudoku[i] = '.';
	}
}

char* getGeneriertesSudoku() //gibt generator sudoku buffer zurück (pointer referenz)
{
	return sudoku;
}

//setzt / überschreibt datein falls neues sudoku generiert wird 
int generatorDateiManager(char* originalPfad, char* dateiPfad, char* zahlen)
{
	FILE* datei; //file pointer

	datei = fopen(originalPfad, "w"); //ORIGINAL datei öffnen

	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei öffnen null error");
		return -1;
	}

	for (int i = 0; i < BREITE*HÖHE; i++) //für array länge (81 zeichen) loop
	{
		if (i % 9 == 0) //nach jedem 9. zeichen ein zeilenumbruch für lesbarkeit
		{
			fputc('\n', datei); //zeilenumbruch einfügen
		}

		fputc(zahlen[i], datei); //char von zahlen array in datei schreiben
	}

	fclose(datei); //datei schließen

	//------------------------------------------------------------------------------

	datei = fopen(dateiPfad, "w"); //SPEICHER datei öffnen

	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei öffnen null error");
		return -1;
	}

	for (int i = 0; i < BREITE * HÖHE; i++) //für array länge (81 zeichen) loop
	{
		if (i % 9 == 0) //nach jedem neunten zeichen ein zeilenumbruch für lesbarkeit
		{
			fputc('\n', datei); //zeilenumbruch
		}

		fputc(zahlen[i], datei); //char von zahlen array in datei schreiben
	}

	fclose(datei); //datei schließen

	return 0; //alles gut
}

/* ALGORITHMUS ZUSAMMENFASSUNG :
-zuerst ein pseudo zufälliges vollständig ausgefülltes sudoku generieren (30-60 wirklich zufällige felder)
-von diesem garantiert lösbaren ausgeüllten sudoku bis zu 50 felder löschen (je nach schwierigkeit)
-wenn man sich von beiden "seiten" an eine lösung annähert erhält man eine gute balance zwischen zufälligkeit, lösbarkeit und geschwindigkeit
(nach jeder generierten zahl zu testen, ob das sudoku noch lösbar ist, wäre nicht performant, da der lösungs-algorithmus zu oft ausgeführt werden müsste)
-deshalb nähert sich der algorithmus "konstanten" zahlen an, die eine hohe warscheinlichekeit haben erfolgreich zu sein
-so muss der lösbarkeits-test nur möglichst selten durchgeführt werden 
*/

int sudokuGenerieren(int schwierigkeit) //schwierigkeit 1-5
{
	zufälligGefülltesSudokuGenerieren(); //sudoku komplett mit zufälligen möglichen werten füllen (aber lösbar/gelöst)

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

	//heap speicher freigeben
	free(tempBuffer1);
	free(tempBuffer2);
}

void zufälligGefülltesSudokuGenerieren()
{
	int maxVersuche = 45; //höhere Zahl erhöht Zufall, aber macht programm langsamer (30-60)
	int erfolgreich = 0; //schauen ob aktuelle generierung möglich/lösbar/voll ist

	while (!erfolgreich) //solange wiederhohlen bis mögliches/lösbares/volles sudoku erreicht
	{
		generatorSudokuLeeren(); //komplettes sudoku leeren/zurücksetzen

		for (int i = 0; i < maxVersuche; i++) //zufällige felder setzen
		{
			char element = charVon1Bis9(); //zufälliges element generieren
			int x = zahlVon1Bis9() - 1; //xIndex generieren
			int y = zahlVon1Bis9() - 1; //yIndex generieren

			if (platzierenMöglich(x, y, element)) //wenn platzieren möglich (also spalte, zeile und quadrat frei von elemet ist)
			{
				setGeneratorElement(x, y, element); //element setzen
			}
		}

		erfolgreich = sudokuLösen(); //sudoku lösen -> alle freien felder auffüllen
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
			printf("%c ", getGeneratorElement(x, y)); //element an x und y printen
		}
		printf("|\n"); //am ende eine letzte vertikale linie
	}
	printf("+ - - - + - - - + - - - +\n"); //am ende eine letzte horizonatle linie 
}

void generatorBeenden() //dynamischen speicher freigeben
{
	löserBeenden();
}

int zahlVon1Bis9() //zufälligen int zwischen 1-9 generieren
{
	int random = (rand() % 9) + 1; //von 1-9

	return random;
}

char charVon1Bis9() //zufälligen char zsichen 1-9 generieren
{
	int random = (rand() % 9) + 1; //von 1-9
	char zahlZuChar = (char)(random + 48); //in char konvertieren

	return zahlZuChar;
}


