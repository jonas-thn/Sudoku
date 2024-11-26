#include "dateiarbeit.h"

int zahlenLaden(char* zahlen, const char* dateiname, char* editierbar) //zahlen & editierbar mit datei werten beladen
{
	FILE* datei; //file pointer
	char temp; //temp char speichern
	int n = 0; //char nummer (in arrays)

	datei = fopen(dateiname, "r"); //datei in read mode öffen


	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei öffnen null error");
		return -1;
	}

	while ((temp = fgetc(datei)) != EOF) //solange char lesen und in temp speichern, bin end of file erreicht
	{
		if (temp != '\n') //'\n' nicht speichern
		{
			zahlen[n] = temp; //zahlen array beladen
			editierbar[n] = temp == '.' ? '1' : '0'; //editierbar array laden, je nachdem ob zahl oder . gelesen
			n++; //nächster char(in arrays)
		}
	}

	fclose(datei); //datei schließen

	return 0; //alles gut
}

int zahlenSpeichern(char* zahlen, const char* dateiname, int länge) //zahlen datei schreiben
{
	FILE* datei; //file pointer

	datei = fopen(dateiname, "w"); //datei öffnen

	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei öffnen null error");
		return -1;
	}

	for (int i = 0; i < länge; i++) //für array länge (81 zeichen) loop
	{
		if (i % 9 == 0) //nach jedem neunten zeichen ein zeilenumbruch für lesbarkeit
		{
			fputc('\n', datei); //zeilenumbruch
		}

		fputc(zahlen[i], datei); //char von zahlen array in datei schreiben
	}

	fclose(datei); //datei schließen

	return 0; //alles gut
}

