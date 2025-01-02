#include "dateiarbeit.h"

int zahlenLaden(char* zahlen, const char* original, char* editierbar, char* speicher) //zahlen & editierbar mit datei werten beladen
{
	FILE* datei; //file pointer
	char temp; //temp char speichern
	int n = 0; //char nummer (in arrays)

	datei = fopen(speicher, "r"); //datei in read mode oeffnen


	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei oeffnen null error");
		return -1;
	}

	while ((temp = fgetc(datei)) != EOF) //solange char lesen und in temp speichern, bin end of file erreicht
	{
		if (temp != '\n') //'\n' nicht speichern
		{
			zahlen[n] = temp; //zahlen array beladen
			n++; //naechster char(in arrays)
		}
	}

	fclose(datei); //datei schliessen

	//---------- gesamten prozess wiederholen fuer originale datei, um editierbare stellen zu finden ----------

	n = 0; //char nummer (in arrays)
	datei = fopen(original, "r"); //datei in read mode oeffen

	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei oeffnen null error");
		return -1;
	}

	while ((temp = fgetc(datei)) != EOF) //solange char lesen und in temp speichern, bin end of file erreicht
	{
		if (temp != '\n') //'\n' nicht speichern
		{
			editierbar[n] = temp == '.' ? '1' : '0'; //editierbar array laden, je nachdem ob zahl oder . gelesen
			n++; //naechster char(in arrays)
		}
	}

	fclose(datei); //datei schliessen

	return 0; //alles gut
}

int zahlenSpeichern(char* zahlen, const char* dateiname, int laenge) //zahlen datei schreiben
{
	FILE* datei; //file pointer

	datei = fopen(dateiname, "w"); //datei oeffnen

	if (datei == NULL) //checken ob es funktioniert hat
	{
		fprintf(stderr, "datei oeffnen null error");
		return -1;
	}

	for (int i = 0; i < laenge; i++) //fuer array laenge (81 zeichen) loop
	{
		if (i % 9 == 0) //nach jedem 9. zeichen ein zeilenumbruch fuer lesbarkeit
		{
			fputc('\n', datei); //zeilenumbruch
		}

		fputc(zahlen[i], datei); //char von zahlen array in datei schreiben
	}

	fclose(datei); //datei schliessen

	return 0; //alles gut
}

