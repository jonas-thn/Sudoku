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

void zurueckZuRoot()
{
	printf("Content-Type: text/html\n\n");
	printf("Status: 302 Found\n");
	printf("Location: https://www.informatik.htw-dresden.de/~88217/cgi-bin/Sudoku/Sudoku/sudoku.cgi\n\n");
}

int parsenUndAusfuehren(char* content, char* schwierigkeit, char* originalPfad, char* speicherPfad)
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
		if(output == '1') //speichern
		{
			return 1; 
		}
		else if(output == '2') //loesen
		{
			loeserInitialisieren(originalPfad);
			sudokuLoesen();
			zahlenBufferBeladen(getLoeserSudokuBuffer());
			loeserBeenden();
		}	
		else if(output == '3') //zuruecksetzen
		{
			sudokuLeeren();
		}
		else if(output == '4') //neu
		{
			generatorInitialisieren();
			sudokuGenerieren(3); //schwierigkeit 1-5
			zahlenBufferBeladen(getGeneriertesSudoku());
			generatorDateiManager(originalPfad, speicherPfad, getZahlen());
			generatorBeenden();
		}

		else //nix 
		{

		}
	}
	else
	{
		printf("PROBLEM");
	}

	return 0;
}

void auswahlMenue()
{
printf("<H1>Sudoku!</H1>\n");

	printf("<FORM ACTION=\"\" METHOD=\"POST\">\n");
	printSudoku();
	printf("<LABEL FOR=\"auswahl\">Was moechtest du machen:</LABEL>\n");
	printf("<SELECT NAME=\"auswahl\" ID=\"auswahl\">\n");
		printf("<OPTION VALUE=\"speichern\">Speichern</OPTION>\n");
		printf("<OPTION VALUE=\"loesen\">Loesen</OPTION>\n");
		printf("<OPTION VALUE=\"zuruecksetzen\">Zuruecksetzen</OPTION>\n");
	printf("</SELECT>\n");
	printf("<BR>\n");
	printf("<BUTTON TYPE=\"SUBMIT\">Auswhaehlen</BUTTON>\n");
	printf("</FORM>\n");
}

void sudokuMenue(int zurueck)
{
	if(zurueck == 1)
	{
		printf("Es wurde erfolgreich gespeichert. <BR>\n");
		printf("<A href=\"sudoku.cgi\">Zurueck zum Menue.</A>");
	}
	else
	{
		auswahlMenue();
	}
}

void einfachQuery(char* content)
{	
	char* originalPfad = "./Sudokus/Sudoku1.txt";
	char* speicherPfad = "./Sudokus/Sudoku1_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
	
	int zurueck = parsenUndAusfuehren(content, "&schwierigkeit=einfach", originalPfad, speicherPfad);

	sudokuMenue(zurueck);
}	

void mittelQuery(char* content)
{
	char* originalPfad = "./Sudokus/Sudoku2.txt";
	char* speicherPfad = "./Sudokus/Sudoku2_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);

	int zurueck = parsenUndAusfuehren(content, "&schwierigkeit=mittel", originalPfad, speicherPfad);

	sudokuMenue(zurueck);
}

void schwerQuery(char* content)
{
	char* originalPfad = "./Sudokus/Sudoku3.txt";
	char* speicherPfad = "./Sudokus/Sudoku3_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);

	int zurueck = parsenUndAusfuehren(content, "&schwierigkeit=schwer", originalPfad, speicherPfad);

	sudokuMenue(zurueck);
}

void unmoeglichQuery(char* content)
{
	char* originalPfad = "./Sudokus/Sudoku4.txt";
	char* speicherPfad = "./Sudokus/Sudoku4_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);

	int zurueck = parsenUndAusfuehren(content, "&schwierigkeit=unmoeglich", originalPfad, speicherPfad);

	sudokuMenue(zurueck);
}

void generiertQuery(char* content)
{
	char* originalPfad = "./Sudokus/Sudoku5.txt";
	char* speicherPfad = "./Sudokus/Sudoku5_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);

	int zurueck = parsenUndAusfuehren(content, "&schwierigkeit=generiert", originalPfad, speicherPfad);
	
	if(zurueck == 1)
	{
		printf("Es wurde erfolgreich gespeichert. <BR>\n");
		printf("<A href=\"sudoku.cgi\">Zurueck zum Menue.</A>");
	}
	else
	{
		printf("<H1>Sudoku!</H1>\n");
	
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
		printf("<BUTTON TYPE=\"SUBMIT\">Auswhaehlen</BUTTON>\n");
		printf("</FORM>\n");
	}	
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
	printf("<HTML><HEAD>\n");
	printf("<TITLE>Sudoku</TITLE>\n");

	printf("<STYLE>\n");
	printf("@keyframes farbwechsel {\n");
	printf("0% { color:35b154; }\n");
	printf("50% { color:35b187; }\n");
	printf("100% { color:35abb1; }\n");
	printf("}\n");
	printf("H1 {\n");
	//printf("	color: #4CAF50;\n");
	printf("	animation: farbwechsel 5s ease-in-out infinite alternate;\n");
	printf("	font-size: 84px;\n");
	printf(" 	text-shadow: 3px 3px 0px rgba(0, 70, 30, 1.0);\n");
	printf("	font-family: \"Impact\", sans-serif;\n");
	printf(" 	font-weight: normal;\n");
	printf("	margin-bottom: 0;\n");
	printf("}\n");
	printf("</STYLE>\n");

	printf("</HEAD>\n");	
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
