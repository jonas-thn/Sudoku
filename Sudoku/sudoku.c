#include "sudoku.h"

//static variablem muessen in der c datei definiert werden
static const int BREITE = 9;
static const int HOEHE = 9;
static const int QUADRAT = 3;

static char* zahlen = NULL; //entaehlt zahlen 
static char* editierbar = NULL; //1 ist editierbar und 0 nicht

#define UNDO_SPEICHER 100
static undoFeld undoFelderStack[UNDO_SPEICHER]; //undo stack, um bis zu 100 zuege zu speichern 
static int undoIndex = -1; //oberstes element vom stack

int aktionUndoSpeichern(int x, int y) //verheriges element + zug speichern
{
	if (undoIndex >= (UNDO_SPEICHER - 1)) //wenn stack voll, dann nicht speichern
	{
		return -1; 
	}

	undoIndex++; //undoIndex erhoehen
	undoFeld undoTemp = { //undo struktur anlegen, um auf stack zu speichern
		.x = x,
		.y = y,
		.zahl = getZahlenElement(x, y) //element hohlen, was aktuell in sudoku steht (vor dem editieren)
	};
	undoFelderStack[undoIndex] = undoTemp; //auf stack legen

	return 0;
}

int undo() //letzten zug rueckgaengig machen
{
	if (undoIndex < 0) //testen ob ueberhaupt ein zug zum rueckgaengig machen existiert
	{
		return -1;
	}

	undoFeld undoTemp = undoFelderStack[undoIndex]; //undo feld daten von stack holen & entpacken
	int x = undoTemp.x;
	int y = undoTemp.y;
	char zahl = undoTemp.zahl;

	//x und y um 1 erhoehen (da feld setzen eine benutzer eingabe (1-9) und keinen index (0-8) erwartet) 
	if (feldSetzen(++x, ++y, zahl, 0) == -1) //feld setzen (sollte immer moeglich sein) 
	{
		return -1;
	}

	undoIndex--; //stack index dekrementieren

	return 0;
}

void resetUndo() //undo funktionalitaet zuruecksetzen
{
	undoIndex = -1; //stack index wieder auf -1 (leer)
	memset(undoFelderStack, 0, sizeof(undoFelderStack)); //stack mit 0 faellen
}

int initialisieren()
{
	zahlen = (char*)malloc(sizeof(char) * BREITE * HOEHE); //speicher fuer zahlen buffer

	if (zahlen == NULL) //test ob malloc funktioniert hat
	{
		fprintf(stderr, "zahlen malloc null error");
		return -1;
	}

	editierbar = (char*)malloc(sizeof(char) * BREITE * HOEHE); //speicher fuer editierbar array

	if (editierbar == NULL) //test ob malloc funktioniert hat
	{
		fprintf(stderr, "editierbar malloc null error");
		return -1;
	}

	for (int i = 0; i < BREITE * HOEHE; i++) //array inhalt fuellen mit deafault werten
	{
		zahlen[i] = '.'; //zahlen array mit punkten fuellen (initial)
		editierbar[i] = '0'; //editierbar array mit 0 fuellen (initial)
	}

	return 0; //alles ok
}

void beenden() //free dynamischen heap speicher
{
	free(zahlen);
	free(editierbar);
}

int feldSetzen(int x, int y, char zahl, int undoMoeglich)
{
	x--; y--; //eingabe von nutzer (1-9) zu index (0-8) konvertieren

	int zCheck = zahlCheck(zahl); //checken ob zahl valide
	int xCheck = ((x >= 0) && (x < BREITE)); //checken ob x eingabe in breite
	int yCheck = ((y >= 0) && (y < HOEHE)); //checken ob y eingabe in breite

	int editierbarCheck = -1;
	if (getEditierbarElement(x, y) == '0') //testen ob feld nicht editierbar
	{
		editierbarCheck = 0;
	}
	else if (getEditierbarElement(x, y) == '1') //testen ob feld editierbar
	{
		editierbarCheck = 1;
	}
	else
	{
		printf("sollte nicht passieren error");
		return -1;
	}

	if (zCheck && xCheck && yCheck && editierbarCheck) //nur setzen, wenn alle vorherigen tests bestanden
	{
		if (undoMoeglich) //nur speichern, wenn undo moeglich sein soll (um undo loop zu verhindern)  
		{
			aktionUndoSpeichern(x, y); //wenn es sich bei dieser aktion nicht gerade um ein "undo" handelt, dann wird aktion auf undo stack gespeichert
		}
		setZahlenElement(x, y, zahl); //element setzen
		return 0; //alles ok
	}

	return -1; //nicht funktioniert
}

int zahlCheck(char zahl) //testen ob eingegebene zahl (char) passt
{
	char valideZahlen[] = { '1', '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9', '.'}; //mange an moeglichen zahlen
	int n = 10; //laenge von valide Zahlen

	for (int i = 0; i < n; i++)
	{
		if (zahl == valideZahlen[i]) //testen ob eingegebene zahl in valide zahlen enthalten ist
		{
			return TRUE; 
		}
	}

	return FALSE; //nicht gueltige eingabe
}

void setZahlenElement(int x, int y, char element) //zahlen element setter
{
	zahlen[BREITE * y + x] = element;
}

char getZahlenElement(int x, int y) //zahlen element getter 
{
	return zahlen[BREITE * y + x];
}

void setEditierbarElement(int x, int y, char element) //editierbar elemnent setter
{
	editierbar[BREITE * y + x] = element;
}

char getEditierbarElement(int x, int y) //editierbar element getter
{
	return editierbar[BREITE * y + x];
}

char* getZahlen() //zahlen array getter
{
	return zahlen;
}

void zahlenBufferBeladen(char* buffer) //zahlen buffer element fuer element beladen
{
	for (int i = 0; i < BREITE*HOEHE; i++)
	{
		zahlen[i] = buffer[i];
	}
}

int getLaenge() //laenge sollte 9x9 = 81 sein
{
	return (BREITE * HOEHE);
}

char* getEditierbar() //editierbar array getter
{
	return editierbar;
}

void sudokuLeeren() //sudoku an allen stellen zu "." zuruecksetzen, die vom benutzer eingegeben wurden und nicht vorgeschrieben waren
{
	for (int y = 0; y < HOEHE; y++)
	{
		for (int x = 0; x < BREITE; x++)
		{
			if (getEditierbarElement(x, y) == '1') //wenn editierbar
			{
				setZahlenElement(x, y, '.'); //auf leeres feld zuruecksetzen
			}
		}
	}
}

void printSudoku() //sudoku mit zahlen in console rpinten 
{	
	printf("<TABLE BORDER=\"1\">\n");
	for (int y = 0; y < HOEHE; y++) //!!!!!! erst zeilen(spalte fuer spalte) fuellen, dann spalten fuellen -> sonst transponiert
	{	
		printf("<TR>\n");
		for (int x = 0; x < BREITE; x++)
		{
			if (getEditierbarElement(x, y) == '0')
			{
				printf("<TD><INPUT TYPE=\"TEXT\" NAME=\"feld%d%d\" MAXLENGTH=\"1\" SIZE=\"1\" VALUE=\"%c\" readonly></TD>\n", x, y, getZahlenElement(x, y));	
			}
			else if (getEditierbarElement(x, y) == '1')
			{
				printf("<TD><INPUT TYPE=\"TEXT\" NAME=\"feld%d%d\" MAXLENGTH=\"1\" SIZE=\"1\" VALUE=\"%c\"></TD>\n", x, y, getZahlenElement(x, y));	
			}
		}
		printf("<TR>\n");
	}
	printf("</TABLE>");
}

