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

	return -1;
}

int main(void)
{
	system("chcp 1252 > NUL");

	initialisieren();



	//--WHILE--


	printf("Wähle eine Sudoku Datei aus:\n");

	for (int i = 0; i < dateinAnzahl; i++)
	{
		datei d = dateinListe[i];
		printf("%d - %s\n", d.nummer, d.schwierigkeit);
	}

	int test1 = 0;
	int auswahl1 = 0;
	while (1)
	{
		test1 = scanf("%d", &auswahl1);

		if ((test1 != 1) || (dateiFinden(auswahl1) == -1))
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
	
	const char* dateiAuswahl = dateinListe[dateiFinden(auswahl1)].pfad;

	zahlenLaden(getZahlen(), dateiAuswahl, getEditierbar());

	system("cls"); //nur auf windows

	printSudoku();
	printf("\n");
	printEditierbar();
	printf("\n");

	printf(
		"Was ist deine nächste Aktion:\n"
		"1 - Zahl eingaben\n"
		"2 - Sudoku speichern und neu auswählen\n"
		"3 - Sudoku speichern und Programm beenden\n"
	);


	int test2 = 0;
	int auswahl2 = 0;
	while (1)
	{
		test2 = scanf("%d", &auswahl2);

		if ((test1 != 1) || !((auswahl2 == 1) || (auswahl2 == 2) || (auswahl2 == 3)))
		{
			printf("Falsche Eingabe. Versuche es nochmal!\n");

			while (fgetc(stdin) != '\n');

			continue;
		}
		else
		{
			while (fgetc(stdin) != '\n');
			break;
		}
	}

	printf("Auswahl: %d", auswahl2);

	//zahlenSpeichern(getZahlen(), "./Sudoku5.txt", getLänge());

	beenden();

	return 0;
}