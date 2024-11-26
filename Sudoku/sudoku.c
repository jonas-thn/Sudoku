#include "sudoku.h"

int initialisieren()
{
	zahlen = (char*)malloc(sizeof(char) * BREITE * H�HE); //speicher f�r zahlen array

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
	for (int x = 0; x < BREITE; x++)
	{
		if (x % QUADRAT == 0) 
		{
			printf("+ - - - + - - - + - - - +\n");
		}

		for (int y = 0; y < H�HE; y++)
		{
			if (y % QUADRAT == 0)
			{
				printf("| ");
			}
			printf("%c ", zahlen[BREITE * x + y]); //x und y getauscht, sonst transformiert 
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

		for (int y = 0; y < H�HE; y++)
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
