#include "sudoku.h"
#include "dateiarbeit.h"
#include "input.h"

int mainMen�()
{
	while (1) //neu auswahl schlefe
	{
		int auswahl1 = dateiAuswahl(); //datei auswhlen men�

		datei dateiAuswahl = dateinListe[dateiFinden(auswahl1)]; //datei auswahl pfad speichern

		//zahlen von datei in sudoku laden
		if (zahlenLaden(getZahlen(), dateiAuswahl.originalPfad, getEditierbar(), dateiAuswahl.speicherPfad) == -1)
		{
			return -1; //schlechtes ende
		}

		//main men� schleife
		while (1)
		{
			system("cls"); //clear console (nur auf windows)

			printSudoku(); //sudoku printen
			printf("\n");

			int auswahl2 = aktionAuswahl(); //w�hle men� aktion aus

			if (auswahl2 == 1) //eingabe 
			{
				aktionEingabe(feldSetzen); //feld setzen eingabe
				system("cls");
				printSudoku(); //sudoku printen
			}
			else if (auswahl2 == 2) //speichern und neu ausw�hlen
			{
				system("cls"); //nur windows
				
				//zahlen speichern in datei
				if (zahlenSpeichern(getZahlen(), dateiAuswahl.speicherPfad, getL�nge()) == -1)
				{
					return -1; //schlechtes ende
				}
				
				break; // geht in �u�ere schleife
			}
			else if (auswahl2 == 3) //speichern und programm beenden
			{
				//zahlen speichern in datei

				if (zahlenSpeichern(getZahlen(), dateiAuswahl.speicherPfad, getL�nge()) == -1)
				{
					return -1; //schlchtes ende
				}

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

	//sudoku initialisieren (malloc, usw...)
	if (initialisieren() == -1)
	{
		fprintf(stderr, "INIT fehlgeschlagen!");
		exit(1);
	}

	//main men� auswahl usw...
	if (mainMen�() == -1)
	{
		fprintf(stderr, "MEN� fehlgeschlagen!");
		exit(1);
	}

	beenden(); //program aufr�umen (free, usw...)

	return 0;
}