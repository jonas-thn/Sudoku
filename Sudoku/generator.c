#include "generator.h"

//static variablem m�ssen in der c datei definiert werden
static const int BREITE = 9;
static const int H�HE = 9;
static const int QUADRAT = 3;

static char* sudoku = NULL; //sudoku buffer f�r algorithmus

int generatorInitialisieren() //sudoku generator initialisieren
{
	srand(time(NULL)); //zufallsgenerator initialisieren (Seed = time)

	//l�ser mit leerer datei initialisieren
	//aufgrund der struktur des l�sers wird leere datei ben�tigt
	int test = l�serInitialisieren("Sudokus/Generiert.txt"); 

	if (test == -1) //wenn l�ser fehlschl�gt, dann auch generator
	{
		return -1;
	}

	//WICHTIG:
	//sudoku buffer im generator zeigt auf gleichen buffer wie l�ser (pointer referenz)
	//man arbeitet als eigendlich die ganze zeit mit dem l�ser buffer
	//hin- und herkopieren von verschiedenen arrays gespaart
	sudoku = getL�serSudokuBuffer(); 

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
	for (int i = 0; i < BREITE * H�HE; i++)
	{
		sudoku[i] = '.';
	}
}

char* getGeneriertesSudoku() //gibt generator sudoku buffer zur�ck (pointer referenz)
{
	return sudoku;
}

//setzt / �berschreibt datein falls neues sudoku generiert wird 
int generatorDateiManager(char* originalPfad, char* dateiPfad, char* zahlen)
{
	FILE* datei; //file pointer

	datei = fopen(originalPfad, "w"); //ORIGINAL datei �ffnen

	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei �ffnen null error");
		return -1;
	}

	for (int i = 0; i < BREITE*H�HE; i++) //f�r array l�nge (81 zeichen) loop
	{
		if (i % 9 == 0) //nach jedem 9. zeichen ein zeilenumbruch f�r lesbarkeit
		{
			fputc('\n', datei); //zeilenumbruch einf�gen
		}

		fputc(zahlen[i], datei); //char von zahlen array in datei schreiben
	}

	fclose(datei); //datei schlie�en

	//------------------------------------------------------------------------------

	datei = fopen(dateiPfad, "w"); //SPEICHER datei �ffnen

	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei �ffnen null error");
		return -1;
	}

	for (int i = 0; i < BREITE * H�HE; i++) //f�r array l�nge (81 zeichen) loop
	{
		if (i % 9 == 0) //nach jedem neunten zeichen ein zeilenumbruch f�r lesbarkeit
		{
			fputc('\n', datei); //zeilenumbruch
		}

		fputc(zahlen[i], datei); //char von zahlen array in datei schreiben
	}

	fclose(datei); //datei schlie�en

	return 0; //alles gut
}

/* ALGORITHMUS ZUSAMMENFASSUNG :
-zuerst ein pseudo zuf�lliges vollst�ndig ausgef�lltes sudoku generieren (30-60 wirklich zuf�llige felder)
-von diesem garantiert l�sbaren ausge�llten sudoku bis zu 50 felder l�schen (je nach schwierigkeit)
-wenn man sich von beiden "seiten" an eine l�sung ann�hert erh�lt man eine gute balance zwischen zuf�lligkeit, l�sbarkeit und geschwindigkeit
(nach jeder generierten zahl zu testen, ob das sudoku noch l�sbar ist, w�re nicht performant, da der l�sungs-algorithmus zu oft ausgef�hrt werden m�sste)
-deshalb n�hert sich der algorithmus "konstanten" zahlen an, die eine hohe warscheinlichekeit haben erfolgreich zu sein
-so muss der l�sbarkeits-test nur m�glichst selten durchgef�hrt werden 
*/

int sudokuGenerieren(int schwierigkeit) //schwierigkeit 1-5
{
	zuf�lligGef�lltesSudokuGenerieren(); //sudoku komplett mit zuf�lligen m�glichen werten f�llen (aber l�sbar/gel�st)

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

	//heap speicher freigeben
	free(tempBuffer1);
	free(tempBuffer2);
}

void zuf�lligGef�lltesSudokuGenerieren()
{
	int maxVersuche = 45; //h�here Zahl erh�ht Zufall, aber macht programm langsamer (30-60)
	int erfolgreich = 0; //schauen ob aktuelle generierung m�glich/l�sbar/voll ist

	while (!erfolgreich) //solange wiederhohlen bis m�gliches/l�sbares/volles sudoku erreicht
	{
		generatorSudokuLeeren(); //komplettes sudoku leeren/zur�cksetzen

		for (int i = 0; i < maxVersuche; i++) //zuf�llige felder setzen
		{
			char element = charVon1Bis9(); //zuf�lliges element generieren
			int x = zahlVon1Bis9() - 1; //xIndex generieren
			int y = zahlVon1Bis9() - 1; //yIndex generieren

			if (platzierenM�glich(x, y, element)) //wenn platzieren m�glich (also spalte, zeile und quadrat frei von elemet ist)
			{
				setGeneratorElement(x, y, element); //element setzen
			}
		}

		erfolgreich = sudokuL�sen(); //sudoku l�sen -> alle freien felder auff�llen
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
			printf("%c ", getGeneratorElement(x, y)); //element an x und y printen
		}
		printf("|\n"); //am ende eine letzte vertikale linie
	}
	printf("+ - - - + - - - + - - - +\n"); //am ende eine letzte horizonatle linie 
}

void generatorBeenden() //dynamischen speicher freigeben
{
	l�serBeenden();
}

int zahlVon1Bis9() //zuf�lligen int zwischen 1-9 generieren
{
	int random = (rand() % 9) + 1; //von 1-9

	return random;
}

char charVon1Bis9() //zuf�lligen char zsichen 1-9 generieren
{
	int random = (rand() % 9) + 1; //von 1-9
	char zahlZuChar = (char)(random + 48); //in char konvertieren

	return zahlZuChar;
}


