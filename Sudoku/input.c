#include "input.h"

//liste an datein
const datei dateinListe[] = {
	{.nummer = 1, .originalPfad = "./Sudoku1.txt", .schwierigkeit = "Einfach", .speicherPfad="./Sudoku1_Save.txt"},
	{.nummer = 2, .originalPfad = "./Sudoku2.txt", .schwierigkeit = "Mittel", .speicherPfad = "./Sudoku2_Save.txt"},
	{.nummer = 3, .originalPfad = "./Sudoku3.txt", .schwierigkeit = "Schwer", .speicherPfad = "./Sudoku3_Save.txt"},
	{.nummer = 4, .originalPfad = "./Sudoku4.txt", .schwierigkeit = "Unmöglich", .speicherPfad = "./Sudoku4_Save.txt"},
};

//datei per nummer anhand auswahl im menü finden
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

int dateiAuswahl()
{
	int auswahl = 0;

	printf("Wähle eine Sudoku Datei aus:\n");

	//alle auswahlmöglichkeiten printen
	for (int i = 0; i < dateinAnzahl; i++)
	{
		datei d = dateinListe[i];
		printf("%d - %s\n", d.nummer, d.schwierigkeit);
	}

	int test1 = 0; //scanf return test
	while (1)
	{
		test1 = scanf("%d", &auswahl); //auswahl scannen

		if ((test1 != 1) || (dateiFinden(auswahl) == -1)) //teste ob auswahl korrekt
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

	return auswahl;
}

int aktionAuswahl()
{
	int auswahl = 0;

	//aktion auswählen
	printf(
		"Was ist deine nächste Aktion:\n"
		"1 - Zahl eingeben\n"
		"2 - Sudoku speichern und neu auswählen\n"
		"3 - Sudoku speichern und Programm beenden\n"
	);


	int test = 0; //scanf return test
	while (1)
	{
		test = scanf("%d", &auswahl); //auswahl scannen

		if ((test != 1) || !((auswahl == 1) || (auswahl == 2) || (auswahl == 3))) //teste ob auswahl korrekt
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

	return auswahl;
}

void aktionEingabe(feldSetzenEvent setzen)
{
	int zeile = 0;
	int spalte = 0;
	char auswahl = 'x';

	int test1 = 0; //scanf return test
	int test2= 0; //scanf return test
	int test3 = 0; //scanf return test

	//zeile, spalte und zahl auswählen
	while (1)
	{
		zeile = 0;
		test1 = 0;
		printf("In welcher Zeile möchtest du eine Zahl platzieren: ");
		test1 = scanf("%d", &zeile); //auswahl scannen

		if (!(((zeile > 0) && (zeile <= 9)) && (test1 == 1))) //teste ob auswahl korrekt
		{
			printf("Falsche Eingabe. Versuche es nochmal!\n");

			while (fgetc(stdin) != '\n'); //stdin buffer leeren

			continue; //wenn nicht korrekt, dann nochmal
		}

		spalte = 0;
		test2 = 0;
		printf("In welcher Spalte möchtest du eine Zahl platzieren: ");
		test2 = scanf("%d", &spalte); //auswahl scannen

		if (!(((spalte > 0) && (spalte <= 9)) && (test2 == 1))) //teste ob auswahl korrekt
		{
			printf("Falsche Eingabe. Versuche es nochmal!\n");

			while (fgetc(stdin) != '\n'); //stdin buffer leeren

			continue; //wenn nicht korrekt, dann nochmal
		}

		while (fgetc(stdin) != '\n');

		auswahl = '0';
		test3 = 0;
		printf("Welche Zahl möchtest du platzieren: ");
		test3 = scanf("%c", &auswahl); //auswahl scannen
		printf("\n");

		if (setzen(zeile, spalte, auswahl) == 0)
		{
			system("cls");
			printSudoku(); //sudoku printen
			//printf("\n");
			//printEditierbar(); //printen, ob man feld ändern darf oder nicht
			printf("\n");
			return;
		}

		system("cls");

		printf("Falsche Eingabe. Versuche es nochmal!\n");

		printSudoku();

		while (fgetc(stdin) != '\n'); //stdin buffer leeren
	}
}
