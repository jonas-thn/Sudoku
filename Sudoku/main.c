#include <stdio.h>

/*
keine abhängigkeiten der bibliotheken untereinader
alle bibliotheken funktionieren für sich selbst und kommen lediglich in main zusammen
*/
#include "sudoku.h"
#include "dateiarbeit.h"
#include "input.h"
#include "löser.h"

#pragma warning (disable: 4996) 

/*						
!!!MERKEN:				
spalte = x			
zeile = y							
*/

int mainMenü()
{
	while (1) //neu auswahl schlefe
	{
		int auswahl1 = dateiAuswahl(); //datei auswhlen menü

		datei dateiAuswahl = dateinListe[dateiFinden(auswahl1)]; //datei auswahl pfad speichern

		//zahlen von datei in sudoku laden
		if (zahlenLaden(getZahlen(), dateiAuswahl.originalPfad, getEditierbar(), dateiAuswahl.speicherPfad) == -1)
		{
			return -1; //schlechtes ende
		}

		resetUndo();

		//main menü schleife
		while (1)
		{
			system("cls"); //clear console (nur auf windows)

			printSudoku(); //sudoku printen
			printf("\n");

			int auswahl2 = aktionAuswahl(); //wähle menü aktion aus

			if (auswahl2 == 1) //eingabe 
			{
				aktionEingabe(feldSetzen); //feld setzen eingabe
				system("cls");
				printSudoku(); //sudoku printen
			}
			else if (auswahl2 == 2) //speichern und neu auswählen
			{
				system("cls"); //nur windows
				
				//zahlen speichern in datei
				if (zahlenSpeichern(getZahlen(), dateiAuswahl.speicherPfad, getLänge()) == -1)
				{
					return -1; //schlechtes ende
				}
				
				break; // geht in äußere schleife
			}
			else if (auswahl2 == 3) //speichern und programm beenden
			{
				//zahlen speichern in datei

				if (zahlenSpeichern(getZahlen(), dateiAuswahl.speicherPfad, getLänge()) == -1)
				{
					return -1; //schlchtes ende
				}

				return 0; //gutes ende
			}
			else if (auswahl2 == 4) //UNDO
			{
				undo(); //letzten zug rückgängig machen
			}
			else if (auswahl2 == 5) //LÖSEN
			{
				löserInitialisieren(dateiAuswahl.originalPfad); //löser für ausgewähltes sudoku initialisieren (malloc, usw...)

				sudokuLösen(); //sudoku lösungs algorithmus

				system("cls");

				printf("Deine Lösung:\n");
				printSudoku(); //sudoku printen
				printf("\n");

				printf("Richtige Lösung:\n");
				printGelöstesSudoku(); //gelöstes sudoku printen

				löserBeenden(); //löser beenden (free)

				printf("\n");
				printf("Drücke \"Enter\" um urück zum Menü zu kommen!");

				while (fgetc(stdin) != '\n'); //stdin buffer löschen + auf enter warten

				system("cls");

				break;
			}
			else if (auswahl2 == 6)
			{
				sudokuLeeren();
				resetUndo();
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

	//main menü auswahl usw...
	if (mainMenü() == -1)
	{
		fprintf(stderr, "MENÜ fehlgeschlagen!");
		exit(1);
	}

	beenden(); //program aufräumen (free, usw...)

	return 0;
}