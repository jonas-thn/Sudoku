#include "sudoku.h"
#include "dateiarbeit.h"
#include "input.h"

int mainMenü()
{
	while (1) //neu auswahl schlefe
	{
		//goto label
		int auswahl1 = dateiAuswahl();

		datei dateiAuswahl = dateinListe[dateiFinden(auswahl1)]; //datei auswahl pfad speichern

		zahlenLaden(getZahlen(), dateiAuswahl.originalPfad, getEditierbar(), dateiAuswahl.speicherPfad); //zahlen von datei in sudoku laden

		//main menü schleife
		while (1)
		{
			system("cls"); //clear console (nur auf windows)

			printSudoku(); //sudoku printen
			printf("\n");

			int auswahl2 = aktionAuswahl();

			if (auswahl2 == 1) //eingabe 
			{
				aktionEingabe(feldSetzen);
				system("cls");
				printSudoku();
			}
			else if (auswahl2 == 2) //speichern und neu auswählen
			{
				system("cls"); //nur windows
				zahlenSpeichern(getZahlen(), dateiAuswahl.speicherPfad, getLänge());
				break; // geht in äußere schleife
			}
			else if (auswahl2 == 3) //speichern und programm beenden
			{
				zahlenSpeichern(getZahlen(), dateiAuswahl.speicherPfad, getLänge());
				return 0; //gutes ende
			}
			else //sollte nie passieren 
			{
				fprintf(stderr, "sollte nie passieren error");
				return -1; //schlechtes ende
			}
		}
	}
}

int main(void)
{
	system("chcp 1252 > NUL");

	initialisieren(); //sudoku initialisieren (malloc, usw...)

	mainMenü(); //main menü auswahl usw...

	beenden(); //program aufräumen (free, usw...)

	return 0;
}