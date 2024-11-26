#include "dateiarbeit.h"

int zahlenLaden(char* zahlen)
{
	FILE* datei;
	char temp;
	int n = 0;

	datei = fopen("./Sudoku1.txt", "r");


	if (datei == NULL)
	{
		fprintf(stderr, "datei laden null error");
		return -1;
	}

	while ((temp = fgetc(datei)) != EOF)
	{
		if (temp != '\n')
		{
			zahlen[n] = temp;
			n++;
		}
	}

	fclose(datei);

	return 0;
}
