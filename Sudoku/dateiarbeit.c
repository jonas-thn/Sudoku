#include "dateiarbeit.h"

int zahlenLaden(char* zahlen, const char* dateiname, char* editierbar)
{
	FILE* datei;
	char temp;
	int n = 0;

	datei = fopen(dateiname, "r");


	if (datei == NULL)
	{
		fprintf(stderr, "datei öffnen null error");
		return -1;
	}

	while ((temp = fgetc(datei)) != EOF)
	{
		if (temp != '\n')
		{
			zahlen[n] = temp;
			editierbar[n] = temp == '.' ? '1' : '0';
			n++;
		}
	}

	fclose(datei);

	return 0;
}

int zahlenSpeichern(char* zahlen, const char* dateiname, int länge)
{
	FILE* datei;
	datei = fopen(dateiname, "w");

	if (datei == NULL)
	{
		fprintf(stderr, "datei öffnen null error");
		return -1;
	}

	for (int i = 0; i < länge; i++)
	{
		if (i % 9 == 0)
		{
			fputc('\n', datei);
		}

		fputc(zahlen[i], datei);
	}

	fclose(datei);

	return 0;
}

