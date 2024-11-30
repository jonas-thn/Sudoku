#include <stdio.h>

/*
keine abh�ngigkeiten der bibliotheken untereinader
alle bibliotheken funktionieren f�r sich selbst und kommen lediglich in main zusammen
*/
#include "sudoku.h"
#include "dateiarbeit.h"
#include "input.h"
#include "l�ser.h"

#pragma warning (disable: 4996) 

/*						
!!!MERKEN:				
spalte = x			
zeile = y							
*/

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

		resetUndo();

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
			else if (auswahl2 == 4) //UNDO
			{
				undo(); //letzten zug r�ckg�ngig machen
			}
			else if (auswahl2 == 5) //L�SEN
			{
				l�serInitialisieren(dateiAuswahl.originalPfad); //l�ser f�r ausgew�hltes sudoku initialisieren (malloc, usw...)

				sudokuL�sen(); //sudoku l�sungs algorithmus

				system("cls");

				printf("Deine L�sung:\n");
				printSudoku(); //sudoku printen
				printf("\n");

				printf("Richtige L�sung:\n");
				printGel�stesSudoku(); //gel�stes sudoku printen

				l�serBeenden(); //l�ser beenden (free)

				printf("\n");
				printf("Dr�cke \"Enter\" um ur�ck zum Men� zu kommen!");

				while (fgetc(stdin) != '\n'); //stdin buffer l�schen + auf enter warten

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

	//main men� auswahl usw...
	if (mainMen�() == -1)
	{
		fprintf(stderr, "MEN� fehlgeschlagen!");
		exit(1);
	}

	beenden(); //program aufr�umen (free, usw...)

	return 0;
}