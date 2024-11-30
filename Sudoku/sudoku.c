#include "sudoku.h"

int aktionUndoSpeichern(int x, int y) //verheriges element + zug speichern
{
	if (undoIndex >= (UNDO_SPEICHER - 1)) //wenn stack voll, dann nicht speichern
	{
		return -1; 
	}

	undoIndex++; //undoIndex erh�hen
	undoFeld undoTemp = { //undo struktur anlegen, um auf stack zu speichern
		.x = x,
		.y = y,
		.zahl = getZahlenElement(x, y) //element hohlen, was aktuell in sudoku steht (vor dem editieren)
	};
	undoFelderStack[undoIndex] = undoTemp; //auf stack legen

	return 0;
}

int undo() //letzten zug r�ckg�ngig machen
{
	if (undoIndex < 0) //testen ob �berhaupt ein zug zum r�ckg�ngig machen existiert
	{
		return -1;
	}

	undoFeld undoTemp = undoFelderStack[undoIndex]; //undo feld daten von stack holen & entpacken
	int x = undoTemp.x;
	int y = undoTemp.y;
	char zahl = undoTemp.zahl;

	//x und y um 1 erh�hen (da feld setzen eine benutzer eingabe (1-9) und keinen index (0-8) erwartet) 
	if (feldSetzen(++x, ++y, zahl, 0) == -1) //feld setzen (sollte immer m�glich sein) 
	{
		return -1;
	}

	undoIndex--; //stack index dekrementieren

	return 0;
}

void resetUndo() //undo funktionalit�t zur�cksetzen
{
	undoIndex = -1; //stack index wieder auf -1 (leer)
	memset(undoFelderStack, 0, sizeof(undoFelderStack)); //stack mit 0 f�llen
}

int initialisieren()
{
	zahlen = (char*)malloc(sizeof(char) * BREITE * H�HE); //speicher f�r zahlen buffer

	if (zahlen == NULL) //test ob malloc funktioniert hat
	{
		fprintf(stderr, "zahlen malloc null error");
		return -1;
	}

	editierbar = (char*)malloc(sizeof(char) * BREITE * H�HE); //speicher f�r editierbar array

	if (editierbar == NULL) //test ob malloc funktioniert hat
	{
		fprintf(stderr, "editierbar malloc null error");
		return -1;
	}

	for (int i = 0; i < BREITE * H�HE; i++) //array inhalt f�llen mit deafault werten
	{
		zahlen[i] = '.'; //zahlen array mit punkten f�llen (initial)
		editierbar[i] = '0'; //editierbar array mit 0 f�llen (initial)
	}

	return 0; //alles ok
}

void beenden() //free dynamischen speicher
{
	free(zahlen);
	free(editierbar);
}

int feldSetzen(int x, int y, char zahl, int undoM�glich)
{
	x--; y--; //eingabe von nutzer (1-9) zu index (0-8) konvertieren

	int zCheck = zahlCheck(zahl); //checken ob zahl valide
	int xCheck = ((x >= 0) && (x < BREITE)); //checken ob x eingabe in breite
	int yCheck = ((y >= 0) && (y < H�HE)); //checken ob y eingabe in breite

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
		if (undoM�glich) //nur speichern, wenn undo m�glich sein soll (um undo loop zu verhindern)  
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
	char valideZahlen[] = { '1', '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9', '.'}; //mange an m�glichen zahlen
	int n = 10; //l�nge von valide Zahlen

	for (int i = 0; i < n; i++)
	{
		if (zahl == valideZahlen[i]) //testen ob eingegebene zahl in valide zahlen enthalten ist
		{
			return TRUE; 
		}
	}

	return FALSE; //nicht g�ltige eingabe
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

int getL�nge() //l�nge sollte 9x9 = 81 sein
{
	return (BREITE * H�HE);
}

char* getEditierbar() //editierbar array getter
{
	return editierbar;
}

void printSudoku() //sudoku mit zahlen in console rpinten 
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

			if (getEditierbarElement(x, y) == '0')
			{
				printf("%s%c%s ",FARBE_ROT, getZahlenElement(x, y), FARBE_ZUR�CKSETZEN); //x und y getauscht, sonst transformiert 
			}
			else if (getEditierbarElement(x, y) == '1')
			{
				printf("%c ", getZahlenElement(x, y)); //x und y getauscht, sonst transformiert 
			}
		}
		printf("|\n"); //am ende eine letzte vertikale linie
	}
	printf("+ - - - + - - - + - - - +\n"); //am ende eine letzte horizonatle linie 
}

