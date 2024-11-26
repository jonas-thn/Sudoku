#include "sudoku.h"

int initialisieren()
{
	zahlen = (char*)malloc(sizeof(char) * BREITE * HÖHE);
	editierbar = (char*)malloc(sizeof(char) * BREITE * HÖHE);

	if (zahlen == NULL)
	{
		fprintf(stderr, "zahlen malloc null error");
		return -1;
	}

	for (int i = 0; i < BREITE * HÖHE; i++)
	{
		zahlen[i] = '.';
		editierbar[i] = '0';
	}

	return 0;
}

void beenden()
{
	free(zahlen);
	free(editierbar);
}

char* getZahlen()
{
	return zahlen;
}

int getLänge()
{
	return (BREITE * HÖHE);
}

char* getEditierbar()
{
	return editierbar;
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

void printEditierbar()
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
