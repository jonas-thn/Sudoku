//CBI BRANCH

#include <stdio.h>

/*
keine abh�ngigkeiten der bibliotheken untereinader
alle bibliotheken funktionieren f�r sich selbst und kommen lediglich in main zusammen

!!! ausanahme:	-generator ist von l�ser abh�ngig, um ~150 zeilen an code wiederhohlung zu vermeiden
				-l�sungsalgorithmus wird ben�tigt um sudoku zu generieren
*/
#include "sudoku.h"
#include "dateiarbeit.h"
#include "input.h"
#include "l�ser.h"
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


int mainMen�()
{
	while (1) //neu auswahl schlefe
	{
		int auswahl1 = dateiAuswahl(); //datei auswhlen men�

		 //datei auswahl pfad speichern
		datei dateiAuswahl = getDateinListeElement(dateiFinden(auswahl1));

		//normalerweise wird sudoku datei anhand von auswahl geladen
		//au�er wenn "neu generieren" ausgew�hlt wurde
		if(dateiAuswahl.nummer == NEU_GENERIEREN) 
		{
			int schwierigkeit = 0; //schwierigkeitsgrad des generierten sudokus
			int test = 0; //scanf r�ckgabe test

			while ((test != 1) || (schwierigkeit > 5) || (schwierigkeit < 1)) //testen ob eingabe fehlerhaft
			{
				printf("W�hle die Schwierigkeit aus (1-5): ");
				test = scanf("%d", &schwierigkeit); //Schwierigkeit eingabe

				//wenn flache eingabe, fehler text anzeigen
				//if statement eigendlich nicht n�tig -> text nur angezeigt wenn while loop wiederhohlt wird und erneut bei scanf stoppt
				//wenn richtige eingabe wird die console sowieso direkt geleert
				if ((test != 1) || (schwierigkeit > 5) || (schwierigkeit < 1)) 
				{
					printf("\n");
					printf("Falsche Eingabe, versuche es erneut!\n");
				}
				while (fgetc(stdin) != '\n'); //input buffer leeren
			}

			generatorInitialisieren(); //generator initialisieren (und l�ser indirekt auch)

			sudokuGenerieren(schwierigkeit); //zuf�lliges sudoku entsprechend schwierigkeit generieren

			zahlenBufferBeladen(getGeneriertesSudoku()); //generiertes sudoku in zahlen buffer laden

			generatorDateiManager(dateiAuswahl.originalPfad, dateiAuswahl.speicherPfad, getZahlen()); //datein Sudoku5 und Sudoku5_save f�llen / �berschreiben

			generatorBeenden(); //generator beenden (und l�ser indirekt auch)

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

		//main men� schleife
		while (1)
		{
			clearConsole(); //clear console

			printSudoku(); //sudoku printen
			printf("\n");

			int auswahl2 = aktionAuswahl(); //w�hle men� aktion aus

			if (auswahl2 == 1) //eingabe 
			{
				aktionEingabe(feldSetzen); //feld setzen eingabe
				clearConsole();
				printSudoku(); //sudoku printen
			}
			else if (auswahl2 == 2) //speichern und neu ausw�hlen
			{
				clearConsole();
				
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

				clearConsole();

				printf("Deine L�sung:\n");
				printSudoku(); //sudoku printen
				printf("\n");

				printf("Richtige L�sung:\n");
				printGel�stesSudoku(); //gel�stes sudoku printen

				l�serBeenden(); //l�ser beenden (free)

				printf("\n");
				printf("Dr�cke \"Enter\" um ur�ck zum Men� zu kommen!");

				while (fgetc(stdin) != '\n'); //stdin buffer l�schen + auf enter warten

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

	//main men� auswahl usw...
	if (mainMen�() == -1)
	{
		fprintf(stderr, "MEN� fehlgeschlagen!");
		exit(1);
	}

	beenden(); //program aufr�umen (free, usw...)

	return 0;
}