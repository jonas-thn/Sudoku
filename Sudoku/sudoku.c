#include "sudoku.h"

#define TRUE 1
#define FALSE 0

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[m"

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
		zahlen[i] = '.';
		editierbar[i] = '0';
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

	int zCheck = zahlCheck(zahl);
	int xCheck = ((x >= 0) && (x < BREITE));
	int yCheck = ((y >= 0) && (y < HÖHE));

	int editierbarCheck = -1;
	if (editierbar[BREITE * y + x] == '0')
	{
		editierbarCheck = 0;
	}
	else if (editierbar[BREITE * y + x] == '1')
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

int zahlCheck(char zahl)
{
	char valideZahlen[] = { '1', '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' };
	int n = 9;

	for (int i = 0; i < n; i++)
	{
		if (zahl == valideZahlen[i])
		{
			return TRUE; //true
		}
	}

	return FALSE; //false
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
		if (x % QUADRAT == 0) 
		{
			printf("+ - - - + - - - + - - - +\n");
		}

		for (int y = 0; y < HÖHE; y++)
		{
			if (y % QUADRAT == 0)
			{
				printf("| ");
			}

			if (editierbar[BREITE * x + y] == '0')
			{
				printf("%s%c%s ",COLOR_RED, zahlen[BREITE * x + y], COLOR_RESET); //x und y getauscht, sonst transformiert 
				//printf("%c ",zahlen[BREITE * x + y]); //x und y getauscht, sonst transformiert 
			}
			else if (editierbar[BREITE * x + y] == '1')
			{
				//printf("%s%c%s ", COLOR_GREEN, zahlen[BREITE * x + y], COLOR_RESET); //x und y getauscht, sonst transformiert 
				printf("%c ", zahlen[BREITE * x + y]); //x und y getauscht, sonst transformiert 
			}
		}
		printf("|\n");
	}
	printf("+ - - - + - - - + - - - +\n");
}

void printEditierbar() //sudoku mit editierbar - werten in console printen
{
	for (int x = 0; x < BREITE; x++)
	{
		if (x % QUADRAT == 0)
		{
			printf("+ - - - + - - - + - - - +\n");
		}

		for (int y = 0; y < HÖHE; y++)
		{
			if (y % QUADRAT == 0)
			{
				printf("| ");
			}
			printf("%c ", editierbar[BREITE * x + y]); //x und y getauscht, sonst transformiert 
		}
		printf("|\n");
	}
	printf("+ - - - + - - - + - - - +\n");
}
