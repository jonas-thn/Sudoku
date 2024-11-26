#include "sudoku.h"
#include "dateiarbeit.h"

//im men� auw�hlbare datei
typedef struct datei 
{
	int nummer;
	const char* pfad;
	const char* schwierigkeit;
} datei;

//liste an datein
const datei dateinListe[] = { 
	{.nummer = 1, .pfad = "./Sudoku1.txt", .schwierigkeit = "Einfach"},
	{.nummer = 2, .pfad = "./Sudoku2.txt", .schwierigkeit = "Mittel"},
	{.nummer = 3, .pfad = "./Sudoku3.txt", .schwierigkeit = "Schwer"},
	{.nummer = 4, .pfad = "./Sudoku4.txt", .schwierigkeit = "Unm�glich"},
	};

//l�nge von datei liste
const dateinAnzahl = sizeof(dateinListe) / sizeof(dateinListe[0]);

//datei per nummer anhand auswahl im men� finden
int dateiFinden(int auswahl)
{
	for (int i = 0; i < dateinAnzahl; i++)
	{
		if (auswahl == dateinListe[i].nummer)
		{
			return i;
		}
	}

	return -1;
}

int main(void)
{
	system("chcp 1252 > NUL");

	initialisieren(); //sudoku initialisieren (malloc, usw...)

	//main while schleife
	while (1)
	{
		printf("W�hle eine Sudoku Datei aus:\n");

		//alle auswahlm�glichkeiten printen
		for (int i = 0; i < dateinAnzahl; i++)
		{
			datei d = dateinListe[i];
			printf("%d - %s\n", d.nummer, d.schwierigkeit);
		}

		int test1 = 0; //scanf return test
		int auswahl1 = 0; //auswahl nummer
		while (1)
		{
			test1 = scanf("%d", &auswahl1); //auswahl scannen

			if ((test1 != 1) || (dateiFinden(auswahl1) == -1)) //teste ob auswahl korrekt
			{
				printf("Falsche Eingabe. Versuche es nochmal!\n");

				while (fgetc(stdin) != '\n'); //stdin buffer leeren

				continue; //wenn nicht korrekt, dann nochmal
			}
			else
			{
				while (fgetc(stdin) != '\n'); //stdin buffer leeren
				break; //aus while ausbrechen
			}
		}

		const char* dateiAuswahl = dateinListe[dateiFinden(auswahl1)].pfad; //datei auswahl pfad speichern

		zahlenLaden(getZahlen(), dateiAuswahl, getEditierbar()); //zahlen von datei in sudoku laden

		system("cls"); //clear console (nur auf windows)

		printSudoku(); //sudoku printen
		printf("\n");
		printEditierbar(); //printen, ob man feld �ndern darf oder nicht
		printf("\n");

		//aktion ausw�hlen
		printf(
			"Was ist deine n�chste Aktion:\n"
			"1 - Zahl eingeben\n"
			"2 - Sudoku speichern und neu ausw�hlen\n"
			"3 - Sudoku speichern und Programm beenden\n"
		);


		int test2 = 0; //scanf return test
		int auswahl2 = 0; //auswahl nummer 
		while (1)
		{
			test2 = scanf("%d", &auswahl2); //auswahl scannen

			if ((test1 != 1) || !((auswahl2 == 1) || (auswahl2 == 2) || (auswahl2 == 3))) //teste ob auswahl korrekt
			{
				printf("Falsche Eingabe. Versuche es nochmal!\n");

				while (fgetc(stdin) != '\n'); //stdin buffer leeren

				continue; //wenn nicht korrekt, dann nochmal
			}
			else
			{
				while (fgetc(stdin) != '\n'); //stdin buffer leeren
				break; //aus while ausbrechen
			}
		}

		if (auswahl2 == 1) //eingabe 
		{
			printf("EINGABE");
			break;
		}
		else if(auswahl2 == 2) //speichern und neu ausw�hlen
		{
			system("cls"); //nur windows
			zahlenSpeichern(getZahlen(), dateiAuswahl, getL�nge());
			continue;
		}
		else if(auswahl2 == 3) //speichern und programm beenden
		{
			zahlenSpeichern(getZahlen(), dateiAuswahl, getL�nge());
			return 0;
		}
		else //sollte nie passieren - TEST
		{
			fprintf(stderr, "sollte nie passieren error");
			return -1;
		}
	}

	beenden(); //program aufr�umen (free, usw...)

	return 0;
}