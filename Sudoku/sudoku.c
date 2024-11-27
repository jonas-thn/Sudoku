#include "sudoku.h"

//true und false definitionen
#define TRUE 1 
#define FALSE 0

//farbcodes für print
#define FARBE_ROT "\x1b[31m" 
#define FARBE_GRÜN "\x1b[32m"
#define FARBE_ZURÜCKSETZEN "\x1b[m"

int initialisieren()
{
	zahlen = (char*)malloc(sizeof(char) * BREITE * HÖHE); //speicher für zahlen array

	if (zahlen == NULL) //test ob malloc funktioniert hat
	{
		fprintf(stderr, "zahlen malloc null error");
		return -1;
	}

	editierbar = (char*)malloc(sizeof(char) * BREITE * HÖHE); //speicher für editierbar array

	if (editierbar == NULL) //test ob malloc funktioniert hat
	{
		fprintf(stderr, "editierbar malloc null error");
		return -1;
	}

	for (int i = 0; i < BREITE * HÖHE; i++) //array inhalt füllen mit deafault werten
	{
		zahlen[i] = '.'; //zahlen array mit punkten füllen (initial)
		editierbar[i] = '0'; //editierbar array mit 0 füllen (initial)
	}

	return 0; //alles ok
}

void beenden() //free dynamischen speicher
{
	free(zahlen);
	free(editierbar);
}

int feldSetzen(int x, int y, char zahl)
{
	x--; y--; //eingabe von nutzer (1-9) zu index (0-8) konvertieren

	int temp = x; //x und y tauschen (transformieren)
	x = y;
	y = temp;

	int zCheck = zahlCheck(zahl); //checken ob zahl valide
	int xCheck = ((x >= 0) && (x < BREITE)); //checken ob x eingabe in breite
	int yCheck = ((y >= 0) && (y < HÖHE)); //checken ob y eingabe in breite

	int editierbarCheck = -1;
	if (editierbar[BREITE * y + x] == '0') //testen ob feld nicht editierbar :(
	{
		editierbarCheck = 0;
	}
	else if (editierbar[BREITE * y + x] == '1') //testen ob feld editierbar :)
	{
		editierbarCheck = 1;
	}
	else
	{
		printf("sollte nicht passieren error");
		return -1;
	}

	if (zCheck && xCheck && yCheck && editierbarCheck)
	{
		zahlen[BREITE * y + x] = zahl; 
		return 0; //alles ok
	}

	return -1; //nicht funktioniert
}

int zahlCheck(char zahl) //testen ob eingegebene zahl (char) passt
{
	char valideZahlen[] = { '1', '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' }; //mange an möglichen zahlen
	int n = 9; //länge von  valideZahlen

	for (int i = 0; i < n; i++)
	{
		if (zahl == valideZahlen[i]) //testen ob eingegebene zahl in valide zahlen enthalten ist
		{
			return TRUE; 
		}
	}

	return FALSE; //nicht gültige eingabe
}

char* getZahlen() //zahlen array getter
{
	return zahlen;
}

int getLänge() //länge sollte 9x9 = 81 sein
{
	return (BREITE * HÖHE);
}

char* getEditierbar() //editierbar array getter
{
	return editierbar;
}

void printSudoku() //sudoku mit zahlen in console rpinten 
{
	for (int x = 0; x < BREITE; x++)
	{
		if (x % QUADRAT == 0) //nach jedem Quadrat horizontale linie
		{
			printf("+ - - - + - - - + - - - +\n");
		}

		for (int y = 0; y < HÖHE; y++)
		{
			if (y % QUADRAT == 0)
			{
				printf("| "); //nach jedem Quadrat vertikale Linie
			}

			if (editierbar[BREITE * x + y] == '0')
			{
				printf("%s%c%s ",FARBE_ROT, zahlen[BREITE * x + y], FARBE_ZURÜCKSETZEN); //x und y getauscht, sonst transformiert 
			}
			else if (editierbar[BREITE * x + y] == '1')
			{
				printf("%c ", zahlen[BREITE * x + y]); //x und y getauscht, sonst transformiert 
			}
		}
		printf("|\n"); //am ende eine letzte vertikale linie
	}
	printf("+ - - - + - - - + - - - +\n"); //am ende eine letzte horizonatle linie 
}

void printEditierbar() //sudoku mit editierbar - werten in console printen
{
	for (int x = 0; x < BREITE; x++)
	{
		if (x % QUADRAT == 0)
		{
			printf("+ - - - + - - - + - - - +\n"); //nach jedem Quadrat horizontale linie
		}

		for (int y = 0; y < HÖHE; y++)
		{
			if (y % QUADRAT == 0)
			{
				printf("| "); //nach jedem Quadrat vertikale Linie
			}
			printf("%c ", editierbar[BREITE * x + y]); //x und y getauscht, sonst transformiert 
		}
		printf("|\n"); //am ende eine letzte vertikale linie
	}
	printf("+ - - - + - - - + - - - +\n"); //am ende eine letzte horizonatle linie 
}
