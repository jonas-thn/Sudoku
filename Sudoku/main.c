#include "sudoku.h"
#include "dateiarbeit.h"

typedef struct datei
{
	int nummer;
	const char* pfad;
	const char* schwierigkeit;
} datei;

const datei dateinListe[] = {
	{.nummer = 1, .pfad = "./Sudoku1.txt", .schwierigkeit = "Einfach"},
	{.nummer = 2, .pfad = "./Sudoku2.txt", .schwierigkeit = "Mittel"},
	{.nummer = 3, .pfad = "./Sudoku3.txt", .schwierigkeit = "Schwer"},
	{.nummer = 4, .pfad = "./Sudoku4.txt", .schwierigkeit = "Unmöglich"},
	};

const dateinAnzahl = sizeof(dateinListe) / sizeof(dateinListe[0]);

int dateiFinden(int auswahl)
{
	for (int i = 0; i < dateinAnzahl; i++)
	{
		if (auswahl == dateinListe[i].nummer)
		{
			return i;
		}
	}

	fprintf(stderr, "auswahl nicht in liste error");
	return -1;
}

int main(void)
{
	system("chcp 1252 > NUL");

	//test variables für scanf return
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0, test5 = 0;

	initialisieren();


	printf("Wähle eine Sudoku Datei aus:\n");

	for (int i = 0; i < dateinAnzahl; i++)
	{
		datei d = dateinListe[i];
		printf("%d - %s\n", d.nummer, d.schwierigkeit);
	}

	int auswahl = 0;
	while (1)
	{
		test1 = scanf("%d", &auswahl);

		if ((test1 != 1) || (dateiFinden(auswahl) == -1))
		{
			printf("Falsche Eingabe. Versuche es nochmal!\n");

			while(fgetc(stdin) != '\n');

			continue;
		}
		else
		{
			while (fgetc(stdin) != '\n');
			break;
		}
	}
	
	const char* dateiAuswahl = dateinListe[dateiFinden(auswahl)].pfad;

	zahlenLaden(getZahlen(), dateiAuswahl, getEditierbar());

	printSudoku();
	printf("\n");
	printEditierbar();

	zahlenSpeichern(getZahlen(), "./Sudoku5.txt", getLänge());

	beenden();

	return 0;
}