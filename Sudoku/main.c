//CBI BRANCH

#include <stdio.h>

/*
keine abhaengigkeiten der bibliotheken untereinader
alle bibliotheken funktionieren fuer sich selbst und kommen lediglich in main zusammen

!!! ausanahme:	-generator ist von loeser abhaengig, um ~150 zeilen an code wiederhohlung zu vermeiden
				-loesungsalgorithmus wird benoetigt um sudoku zu generieren
*/
#include "sudoku.h"
#include "dateiarbeit.h"
#include "input.h"
#include "loeser.h"
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


int mainMenue()
{
	while (1) //neu auswahl schlefe
	{
		int auswahl1 = dateiAuswahl(); //datei auswhlen menue

		 //datei auswahl pfad speichern
		datei dateiAuswahl = getDateinListeElement(dateiFinden(auswahl1));

		//normalerweise wird sudoku datei anhand von auswahl geladen
		//ausser wenn "neu generieren" ausgewaehlt wurde
		if(dateiAuswahl.nummer == NEU_GENERIEREN) 
		{
			int schwierigkeit = 0; //schwierigkeitsgrad des generierten sudokus
			int test = 0; //scanf rueckgabe test

			while ((test != 1) || (schwierigkeit > 5) || (schwierigkeit < 1)) //testen ob eingabe fehlerhaft
			{
				printf("Waehle die Schwierigkeit aus (1-5): ");
				test = scanf("%d", &schwierigkeit); //Schwierigkeit eingabe

				//wenn flache eingabe, fehler text anzeigen
				//if statement eigendlich nicht noetig -> text nur angezeigt wenn while loop wiederhohlt wird und erneut bei scanf stoppt
				//wenn richtige eingabe wird die console sowieso direkt geleert
				if ((test != 1) || (schwierigkeit > 5) || (schwierigkeit < 1)) 
				{
					printf("\n");
					printf("Falsche Eingabe, versuche es erneut!\n");
				}
				while (fgetc(stdin) != '\n'); //input buffer leeren
			}

			generatorInitialisieren(); //generator initialisieren (und loeser indirekt auch)

			sudokuGenerieren(schwierigkeit); //zufaelliges sudoku entsprechend schwierigkeit generieren

			zahlenBufferBeladen(getGeneriertesSudoku()); //generiertes sudoku in zahlen buffer laden

			generatorDateiManager(dateiAuswahl.originalPfad, dateiAuswahl.speicherPfad, getZahlen()); //datein Sudoku5 und Sudoku5_save fuellen / ueberschreiben

			generatorBeenden(); //generator beenden (und loeser indirekt auch)

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

		//main menue schleife
		while (1)
		{
			clearConsole(); //clear console

			printSudoku(); //sudoku printen
			printf("\n");

			int auswahl2 = aktionAuswahl(); //waehle menue aktion aus

			if (auswahl2 == 1) //eingabe 
			{
				aktionEingabe(feldSetzen); //feld setzen eingabe
				clearConsole();
				printSudoku(); //sudoku printen
			}
			else if (auswahl2 == 2) //speichern und neu auswaehlen
			{
				clearConsole();
				
				//zahlen speichern in datei
				if (zahlenSpeichern(getZahlen(), dateiAuswahl.speicherPfad, getLaenge()) == -1)
				{
					return -1; //schlechtes ende
				}
				
				break; // geht in aeussere schleife
			}
			else if (auswahl2 == 3) //speichern und programm beenden
			{
				//zahlen speichern in datei

				if (zahlenSpeichern(getZahlen(), dateiAuswahl.speicherPfad, getLaenge()) == -1)
				{
					return -1; //schlchtes ende
				}

				return 0; //gutes ende
			}
			else if (auswahl2 == 4) //UNDO
			{
				undo(); //letzten zug rueckgaengig machen
			}
			else if (auswahl2 == 5) //LOESEN
			{
				loeserInitialisieren(dateiAuswahl.originalPfad); //loeser fuer ausgewaehltes sudoku initialisieren (malloc, usw...)

				sudokuLoesen(); //sudoku loesungs algorithmus

				clearConsole();

				printf("Deine Loesung:\n");
				printSudoku(); //sudoku printen
				printf("\n");

				printf("Richtige Loesung:\n");
				printGeloestesSudoku(); //geloestes sudoku printen

				loeserBeenden(); //loeser beenden (free)

				printf("\n");
				printf("Druecke \"Enter\" um zurueck zum Menue zu kommen!");

				while (fgetc(stdin) != '\n'); //stdin buffer loeschen + auf enter warten

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
	
#if defined(_WIN32) || defined(_WIN64)
	system("chcp 1252 > NUL"); 
#endif

	printf("Content-Type: text/html\n\n");
	printf("<HTML><HEAD><TITLE>Sudoku</TITLE></HEAD>\n");
	printf("</BODY>\n");

//	sudoku initialisieren (malloc, usw...)
//	if (initialisieren() == -1)
//	{
//		fprintf(stderr, "INIT fehlgeschlagen!");
//		exit(1);
//	}

	//main menue auswahl usw...
//	if (mainMenue() == -1)
//	{
//		fprintf(stderr, "MENUE fehlgeschlagen!");
//		exit(1);
//	}
//
//	beenden(); //program aufrauumen (free, usw...)
	printf("<FORM ACTION=\"http://www.informatik.htw-dresden.de/~s88217/cgi-bin/Sudoku/Sudoku/sudoku.cgi\" METHOD=\"POST\">\n");
	printf("<TABLE BORDER=\"1\">\n");
	
	for(int i = 0; i < 9; i++)
	{
		printf("<TR>\n");
		for(int j = 0; j < 9; j++)
		{
			printf("<TD><INPUT TYPE=\"TEXT\" NAME=\"feld_%d_%d\" MAXLENGTH=\"1\" SIZE=\"1\" VALUE=\"%d\"></TD>\n", i, j, 1);
		}
		printf("</TR>\n");
	}
	printf("</TABLE>\n");
	printf("<BR>");
	printf("<INPUT TYPE=\"SUBMIT\" VALUE=\"Test\">\n");
	printf("</FORM>");
	printf("</BODY></HTML>\n");

	return 0;
}
