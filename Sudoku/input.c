#include "input.h"

//static variablem muessen in der c datei definiert werden
#define dateinAnzahl (6) //anzahlt von sudoku datein 

//liste an sudoku datein
static const datei dateinListe[dateinAnzahl] = {
	{.nummer = SCHWIERIGKEIT_EINFACH, .originalPfad = "Sudokus/Sudoku1.txt", .schwierigkeit = "Einfach", .speicherPfad="Sudokus/Sudoku1_Save.txt"},
	{.nummer = SCHWIERIGKEIT_MITTEL, .originalPfad = "Sudokus/Sudoku2.txt", .schwierigkeit = "Mittel", .speicherPfad = "Sudokus/Sudoku2_Save.txt"},
	{.nummer = SCHWIERIGKEIT_SCHWER, .originalPfad = "Sudokus/Sudoku3.txt", .schwierigkeit = "Schwer", .speicherPfad = "Sudokus/Sudoku3_Save.txt"},
	{.nummer = SCHWIERIGKEIT_UNMOEGLICH, .originalPfad = "Sudokus/Sudoku4.txt", .schwierigkeit = "Unmoeglich", .speicherPfad = "Sudokus/Sudoku4_Save.txt"},
	{.nummer = SCHWIERIGKEIT_GENERIERT, .originalPfad = "Sudokus/Sudoku5.txt", .schwierigkeit = "Generiert laden", .speicherPfad = "Sudokus/Sudoku5_Save.txt"},
	{.nummer = NEU_GENERIEREN, .originalPfad = "Sudokus/Sudoku5.txt", .schwierigkeit = "Neu generieren", .speicherPfad = "Sudokus/Sudoku5_Save.txt"}
};

//datei per nummer anhand auswahl im menue finden
int dateiFinden(int auswahl)
{
	for (int i = 0; i < dateinAnzahl; i++)
	{
		if (auswahl == dateinListe[i].nummer)
		{
			return i; //gefunden index
		}
	}

	return -1; //nicht gefunden 
}

//datei auswahl menue
int dateiAuswahl()
{
	int auswahl = 0;

	printf("Waehle eine Sudoku Datei aus:\n");

	//alle auswahlmoeglichkeiten printen
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
			printf("\nFalsche Eingabe. Versuche es nochmal!\n\n");

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

//aktion auswahl menue
int aktionAuswahl()
{
	int auswahl = 0;

	//aktion auswaehlen
	printf(
		"Was ist deine naechste Aktion:\n"
		"1 - Zahl eingeben\n"
		"2 - Sudoku speichern und neu auswaehlen\n"
		"3 - Sudoku speichern und Programm beenden\n"
		"4 - Aktion rueckgaengig machen\n"
		"5 - Loesung anzeigen\n"
		"6 - Leeren (unwiederruflich)\n"
	);


	int test = 0; //scanf return test
	while (1)
	{
		test = scanf("%d", &auswahl); //auswahl scannen

		if ((test != 1) || !((auswahl == 1) || (auswahl == 2) || (auswahl == 3) || (auswahl == 4) || (auswahl == 5) || (auswahl == 6))) //teste ob auswahl korrekt
		{
			printf("\nFalsche Eingabe. Versuche es nochmal!\n\n");

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

//eingabe von aktion / zahl in feld setzen
void aktionEingabe(feldSetzenEvent setzen)
{
	int zeile = 0;
	int spalte = 0;
	char auswahl = 'x';

	int test1 = 0; //scanf return test
	int test2= 0; //scanf return test
	int test3 = 0; //scanf return test

	//zeile, spalte und zahl auswaehlen
	while (1)
	{
		zeile = 0;
		printf("In welcher Zeile moechtest du eine Zahl platzieren: ");
		test1 = scanf("%d", &zeile); //auswahl scannen

		if (!(((zeile > 0) && (zeile <= 9)) && (test1 == 1))) //teste ob auswahl korrekt
		{
			printf("\nFalsche Eingabe. Versuche es nochmal!\n\n");

			while (fgetc(stdin) != '\n'); //stdin buffer leeren

			continue; //wenn nicht korrekt, dann nochmal
		}

		spalte = 0;
		printf("In welcher Spalte moechtest du eine Zahl platzieren: ");
		test2 = scanf("%d", &spalte); //auswahl scannen

		if (!(((spalte > 0) && (spalte <= 9)) && (test2 == 1))) //teste ob auswahl korrekt
		{
			printf("\nFalsche Eingabe. Versuche es nochmal!\n\n");

			while (fgetc(stdin) != '\n'); //stdin buffer leeren

			continue; //wenn nicht korrekt, dann nochmal
		}

		while (fgetc(stdin) != '\n');

		auswahl = '0';
		printf("Welche Zahl moechtest du platzieren: ");
		test3 = scanf("%c", &auswahl); //auswahl scannen

		if (!(test3 == 1)) //teste ob auswahl korrekt
		{
			printf("\nFalsche Eingabe. Versuche es nochmal!\n\n");

			while (fgetc(stdin) != '\n'); //stdin buffer leeren

			continue; //wenn nicht korrekt, dann nochmal
		}

		while (fgetc(stdin) != '\n');

		//WICHTIG: spalte = x, zeile = y !!!!
		if (setzen(spalte, zeile, auswahl, 1) == 0) //feld setzen wenn moeglich 
		{
			return;
		}

		printf("\nFalsche Eingabe. Versuche es nochmal!\n\n");
	}
}

datei getDateinListeElement(int index)
{
	return dateinListe[index];
}
