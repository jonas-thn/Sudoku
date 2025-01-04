//CBI BRANCH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./lib/cgi-lib.h"
#include "./lib/cgi-priv.h"

/*
keine abhaengigkeiten der bibliotheken untereinader
alle bibliotheken funktionieren fuer sich selbst und kommen lediglich in main zusammen

!!! ausanahme:	-generator ist von loeser abhaengig, um ~150 zeilen an code wiederhohlung zu vermeiden
				-loesungsalgorithmus wird benoetigt um sudoku zu generieren
*/
#include "sudoku.h"
#include "dateiarbeit.h"
#include "loeser.h"
#include "generator.h"

#pragma warning (disable: 4996) 

/*						
!!!MERKEN:				
spalte = x			
zeile = y							
*/

void parsenUndSpeichern(char* content, char* schwierigkeit)
{
	char* leer = "0";
			

	FILE* datei = fopen("./parser_temp.txt", "w");
	if(datei == NULL)
	{
		printf("ERROR");
	}
	if(content != NULL)
	{
		strcat(content, schwierigkeit);
		fputs(content, datei);	
	}
	else
	{
		fputs(leer, datei);
	}
	fclose(datei);

	const char* befehl = "python3 parser_saver";
	
	FILE* p = popen(befehl, "r");
	if(p == NULL)
	{
		perror("popopen error");
	}
		
	char output = '0';
	if((output = fgetc(p)) != EOF)
	{
		printf("%c\n", output);
		if(output == '1') //speichern
		{
			printf("speichern");
		}
		else if(output == '2') //loesen
		{
			printf("loesen");
		}	
		else if(output == '3') //zuruecksetzen
		{
			printf("zuruecksetzen");
		}
		else if(output == '4') //neu
		{
			printf("neu");
		}

		else //nix 
		{
			printf("0");
		}
	}
	else
	{
		printf("PROBLEM");
	}
}

void auswahlMenue()
{
	printf("<FORM ACTION=\"\" METHOD=\"POST\">\n");
	printSudoku();
	printf("<LABEL FOR=\"auswahl\">Was moechtest du machen:</LABEL>\n");
	printf("<SELECT NAME=\"auswahl\" ID=\"auswahl\">\n");
		printf("<OPTION VALUE=\"speichern\">Speichern</OPTION>\n");
		printf("<OPTION VALUE=\"loesen\">Loesen</OPTION>\n");
		printf("<OPTION VALUE=\"zuruecksetzen\">Zuruecksetzen</OPTION>\n");
	printf("</SELECT>\n");
	printf("<BR>\n");
	printf("<BUTTON TYPE=\"SUBMIT\">Auswhaehlen</BUUTON>\n");
	printf("</FORM>\n");
}

void einfachQuery(char* content)
{	
	parsenUndSpeichern(content, "&schwierigkeit=einfach");

	char* originalPfad = "./Sudokus/Sudoku1.txt";
	char* speicherPfad = "./Sudokus/Sudoku1_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
	auswahlMenue();
}

void mittelQuery(char* content)
{
	parsenUndSpeichern(content, "&schwierigkeit=mittel");

	char* originalPfad = "./Sudokus/Sudoku2.txt";
	char* speicherPfad = "./Sudokus/Sudoku2_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
	auswahlMenue();
}

void schwerQuery(char* content)
{
	parsenUndSpeichern(content, "&schwierigkeit=schwer");

	char* originalPfad = "./Sudokus/Sudoku3.txt";
	char* speicherPfad = "./Sudokus/Sudoku3_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
	auswahlMenue();
}

void unmoeglichQuery(char* content)
{
	parsenUndSpeichern(content, "&schwierigkeit=unmoeglich");

	char* originalPfad = "./Sudokus/Sudoku4.txt";
	char* speicherPfad = "./Sudokus/Sudoku4_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
	auswahlMenue();
}

void generiertQuery(char* content)
{
	parsenUndSpeichern(content, "&schwierigkeit=generiert");

	char* originalPfad = "./Sudokus/Sudoku5.txt";
	char* speicherPfad = "./Sudokus/Sudoku5_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
		
	printf("<FORM ACTION=\"\" METHOD=\"POST\">\n");
	printSudoku();
	printf("<LABEL FOR=\"auswahl\">Was moechtest du machen:</LABEL>\n");
	printf("<SELECT NAME=\"auswahl\" ID=\"auswahl\">\n");
		printf("<OPTION VALUE=\"speichern\">Speichern</OPTION>\n");
		printf("<OPTION VALUE=\"loesen\">Loesen</OPTION>\n");
		printf("<OPTION VALUE=\"zuruecksetzen\">Zuruecksetzen</OPTION>\n");
		printf("<OPTION VALUE=\"neu\">Neu generieren</OPTION>\n");
	printf("</SELECT>\n");
	printf("<BR>\n");
	printf("<BUTTON TYPE=\"SUBMIT\">Auswhaehlen</BUUTON>\n");
	printf("</FORM>\n");
}

void startQuery()
{
	char* start = "Waehle eine Option aus:<BR><A href=\"sudoku.cgi?einfach\">Einfach</A><BR><A href=\"sudoku.cgi?mittel\">Mittel</A><BR><A href=\"sudoku.cgi?schwer\">Schwer</A><BR><A href=\"sudoku.cgi?unmoeglich\">Unmoeglich</A><BR><A href=\"sudoku.cgi?generiert\">Generiert</A>";
	
	printf(start);
}

void queryAuswahl(char* content)
{
	char* env;

	if(env = getenv("QUERY_STRING"))
	{
		if(strcmp("einfach", env) == 0)
		{
			einfachQuery(content);
		}			
		else if(strcmp("mittel", env) == 0)
		{				
			mittelQuery(content);
		}
		else if(strcmp("schwer", env) == 0)
		{
			schwerQuery(content);
		}
		else if(strcmp("unmoeglich", env) == 0)
		{
			unmoeglichQuery(content);
		}
		else if(strcmp("generiert", env) == 0)
		{
			generiertQuery(content);
		}
		else
		{
			startQuery();
		}
	}

}

int main(void)
{	
	printf("Content-Type: text/html\n\n");
	printf("<HTML><HEAD><TITLE>Sudoku</TITLE></HEAD>\n");
	printf("</BODY>\n");

	//sudoku initialisieren (malloc, usw...)
	if (initialisieren() == -1)
	{
		printf("ERROR!");
		fprintf(stderr, "INIT fehlgeschlagen!");
		exit(1);
	}

	char* contentLengthString = getenv("CONTENT_LENGTH");
	if(contentLengthString != NULL)
	{
		int contentLength = atoi(contentLengthString);
		char daten[contentLength + 1];
		fread(daten, 1, contentLength, stdin);
		daten[contentLength] = '\0';
		queryAuswahl(daten);
	}
	else
	{
		queryAuswahl(NULL);
	}
	

//BIBLIOTHEK HAT MEMORY LEAKS------------------------------
//	LIST* daten

//	daten = cgi_input_parse();

//	queryAuswahl(daten);
	
//	list_clear(daten);
	
//----------------------------------------------------------


	printf("</BODY></HTML>\n");

	beenden(); //program aufrauumen (free, usw...)

	return 0;
}
