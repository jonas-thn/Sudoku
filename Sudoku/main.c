//CBI BRANCH

#include <stdio.h>

/*
keine abhängigkeiten der bibliotheken untereinader
alle bibliotheken funktionieren für sich selbst und kommen lediglich in main zusammen

!!! ausanahme:	-generator ist von löser abhängig, um ~150 zeilen an code wiederhohlung zu vermeiden
				-lösungsalgorithmus wird benötigt um sudoku zu generieren
*/
#include "sudoku.h"
#include "dateiarbeit.h"
#include "input.h"
#include "löser.h"
#include "generator.h"

#pragma warning (disable: 4996) 

/*						
!!!MERKEN:				
spalte = x			
zeile = y							
*/

void clearConsole() //cross platform clear console
{
#if defined(__unix__) || defined(__linux__)
	system("clear");
#elif defined(_WIN32) || defined(_WIN64)
	system("cls");
#else
	printf("\033[H\033[J");
#endif
}


int mainMenü()
{
	while (1) //neu auswahl schlefe
	{
		int auswahl1 = dateiAuswahl(); //datei auswhlen menü

		 //datei auswahl pfad speichern
		datei dateiAuswahl = getDateinListeElement(dateiFinden(auswahl1));

		//normalerweise wird sudoku datei anhand von auswahl geladen
		//außer wenn "neu generieren" ausgewählt wurde
		if(dateiAuswahl.nummer == NEU_GENERIEREN) 
		{
			int schwierigkeit = 0; //schwierigkeitsgrad des generierten sudokus
			int test = 0; //scanf rückgabe test

			while ((test != 1) || (schwierigkeit > 5) || (schwierigkeit < 1)) //testen ob eingabe fehlerhaft
			{
				printf("Wähle die Schwierigkeit aus (1-5): ");
				test = scanf("%d", &schwierigkeit); //Schwierigkeit eingabe

				//wenn flache eingabe, fehler text anzeigen
				//if statement eigendlich nicht nötig -> text nur angezeigt wenn while loop wiederhohlt wird und erneut bei scanf stoppt
				//wenn richtige eingabe wird die console sowieso direkt geleert
				if ((test != 1) || (schwierigkeit > 5) || (schwierigkeit < 1)) 
				{
					printf("\n");
					printf("Falsche Eingabe, versuche es erneut!\n");
				}
				while (fgetc(stdin) != '\n'); //input buffer leeren
			}

			generatorInitialisieren(); //generator initialisieren (und löser indirekt auch)

			sudokuGenerieren(schwierigkeit); //zufälliges sudoku entsprechend schwierigkeit generieren

			zahlenBufferBeladen(getGeneriertesSudoku()); //generiertes sudoku in zahlen buffer laden

			generatorDateiManager(dateiAuswahl.originalPfad, dateiAuswahl.speicherPfad, getZahlen()); //datein Sudoku5 und Sudoku5_save füllen / überschreiben

			generatorBeenden(); //generator beenden (und löser indirekt auch)

			//zahlen von datei in sudoku laden
			if (zahlenLaden(getZahlen(), dateiAuswahl.originalPfad, getEditierbar(), dateiAuswahl.speicherPfad) == -1)
			{
				return -1; //schlechtes ende
			}
		}
		else
		{
			//zahlen von datei in sudoku laden
			if (zahlenLaden(getZahlen(), dateiAuswahl.originalPfad, getEditierbar(), dateiAuswahl.speicherPfad) == -1)
			{
				return -1; //schlechtes ende
			}
		}

		resetUndo();

		//main menü schleife
		while (1)
		{
			clearConsole(); //clear console

			printSudoku(); //sudoku printen
			printf("\n");

			int auswahl2 = aktionAuswahl(); //wähle menü aktion aus

			if (auswahl2 == 1) //eingabe 
			{
				aktionEingabe(feldSetzen); //feld setzen eingabe
				clearConsole();
				printSudoku(); //sudoku printen
			}
			else if (auswahl2 == 2) //speichern und neu auswählen
			{
				clearConsole();
				
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

				clearConsole();

				printf("Deine Lösung:\n");
				printSudoku(); //sudoku printen
				printf("\n");

				printf("Richtige Lösung:\n");
				printGelöstesSudoku(); //gelöstes sudoku printen

				löserBeenden(); //löser beenden (free)

				printf("\n");
				printf("Drücke \"Enter\" um urück zum Menü zu kommen!");

				while (fgetc(stdin) != '\n'); //stdin buffer löschen + auf enter warten

				clearConsole();
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
	
#ifdef _WIN32 || _WIN64
	system("chcp 1252 > NUL"); 
#endif

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