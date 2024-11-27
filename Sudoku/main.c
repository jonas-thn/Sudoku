#include "sudoku.h"
#include "dateiarbeit.h"
#include "input.h"

int mainMen�()
{
	Neu: //goto label
	int auswahl1 = dateiAuswahl();

	datei dateiAuswahl = dateinListe[dateiFinden(auswahl1)]; //datei auswahl pfad speichern

	zahlenLaden(getZahlen(), dateiAuswahl.originalPfad, getEditierbar(), dateiAuswahl.speicherPfad); //zahlen von datei in sudoku laden
	
	//main while schleife
	while (1)
	{
		system("cls"); //clear console (nur auf windows)

		printSudoku(); //sudoku printen
		printf("\n");

		int auswahl2 = aktionAuswahl();

		if (auswahl2 == 1) //eingabe 
		{
			aktionEingabe(feldSetzen);
		}
		else if (auswahl2 == 2) //speichern und neu ausw�hlen
		{
			system("cls"); //nur windows
			zahlenSpeichern(getZahlen(), dateiAuswahl.speicherPfad, getL�nge());
			goto Neu;
		}
		else if (auswahl2 == 3) //speichern und programm beenden
		{
			zahlenSpeichern(getZahlen(), dateiAuswahl.speicherPfad, getL�nge());
			return 0;
		}
		else //sollte nie passieren - TEST
		{
			fprintf(stderr, "sollte nie passieren error");
			return -1;
		}
	}
}

int main(void)
{
	system("chcp 1252 > NUL");

	initialisieren(); //sudoku initialisieren (malloc, usw...)

	mainMen�(); //main men� auswahl usw...

	beenden(); //program aufr�umen (free, usw...)

	return 0;
}