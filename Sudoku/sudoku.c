#include "sudoku.h"

int initialisieren()
{
	zahlen = (char*)malloc(sizeof(char) * BREITE * HÖHE);

	if (zahlen == NULL)
	{
		fprintf(stderr, "zahlen malloc null error");
		return -1;
	}

	for (int i = 0; i < BREITE * HÖHE; i++)
	{
		zahlen[i] = '.';
	}

	return 0;
}

void beenden()
{
	free(zahlen);
}

char* getZahlen()
{
	return zahlen;
}

int gibLänge()
{
	return (BREITE * HÖHE);
}

void printSudoku()
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
			printf("%c ", zahlen[BREITE * x + y]); //x und y getauscht, sonst transformiert 
		}
		printf("|\n");
	}
	printf("+ - - - + - - - + - - - +\n");
}
