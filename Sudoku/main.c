//CBI BRANCH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./lib/cgi-lib.h"

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

void auswahlMenue()
{
	printf("<FORM ACTION=\"\" METHOD=\"POST\">\n");
	printf("<LABEL FOR=\"auswahl\">Was moechtest du machen:</LABEL>\n");
	printf("<SELECT NAME=\"auswahl\" ID=\"auswahl\">\n");
		printf("<OPTION VALUE=\"speichern\">Speichern</OPTION>\n");
		printf("<OPTION VALUE=\"undo\">Undo</OPTION>\n");
		printf("<OPTION VALUE=\"loesen\">Loesen</OPTION>\n");
		printf("<OPTION VALUE=\"zuruecksetzen\">Zuruecksetzen</OPTION>\n");
	printf("</SELECT>\n");
	printf("<BR>\n");
	printf("<BUTTON TYPE=\"SUBMIT\">Auswhaehlen</BUUTON>\n");
	printf("</FORM>\n");
}

void einfachQuery(char* content)
{	
	char* originalPfad = "./Sudokus/Sudoku1.txt";
	char* speicherPfad = "./Sudokus/Sudoku1_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
	printSudoku();
	auswahlMenue();
	printf(content);
}

void mittelQuery(char* content)
{
	char* originalPfad = "./Sudokus/Sudoku2.txt";
	char* speicherPfad = "./Sudokus/Sudoku2_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
	printSudoku();
	auswahlMenue();
	printf(content);
}

void schwerQuery(char* content)
{
	char* originalPfad = "./Sudokus/Sudoku3.txt";
	char* speicherPfad = "./Sudokus/Sudoku3_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
	printSudoku();
	auswahlMenue();
	printf(content);
}

void unmoeglichQuery(char* content)
{
	char* originalPfad = "./Sudokus/Sudoku4.txt";
	char* speicherPfad = "./Sudokus/Sudoku4_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
	printSudoku();
	auswahlMenue();
	printf(content);
}

void generiertQuery(char* content)
{
	char* originalPfad = "./Sudokus/Sudoku5.txt";
	char* speicherPfad = "./Sudokus/Sudoku5_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
	printSudoku();
	
	printf("<FORM ACTION=\"\" METHOD=\"POST\">\n");
	printf("<LABEL FOR=\"auswahl\">Was moechtest du machen:</LABEL>\n");
	printf("<SELECT NAME=\"auswahl\" ID=\"auswahl\">\n");
		printf("<OPTION VALUE=\"speichern\">Speichern</OPTION>\n");
		printf("<OPTION VALUE=\"undo\">Undo</OPTION>\n");
		printf("<OPTION VALUE=\"loesen\">Loesen</OPTION>\n");
		printf("<OPTION VALUE=\"zuruecksetzen\">Zuruecksetzen</OPTION>\n");
		printf("<OPTION VALUE=\"neu\">Neu generieren</OPTION>\n");
	printf("</SELECT>\n");
	printf("<BR>\n");
	printf("<BUTTON TYPE=\"SUBMIT\">Auswhaehlen</BUUTON>\n");
	printf("</FORM>\n");
	
	printf(content);
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


//void queryAuswahlLib(LIST* data)
//{
//	char* content = find_val(data, "auswahl");
//	
//	char* env;
//	
//	if(env = getenv("QUERY_STRING"))
//	{
//		if(strcmp("einfach", env) == 0)
//		{
//			einfachQuery(content);
//		}
//		else if(strcmp("mittel", env) == 0)
//		{
//			mittelQuery(content);
//		}
//		else if(strcmp("schwer", env) == 0)
//		{
//			schwerQuery(content);
//		}
//		else if(strcmp("unmoeglich", env) == 0)
//		{
//			unmoeglichQuery(content);
//		}
//		else if(strcmp("generiert", env) == 0)
//		{
//			generiertQuery(content);
//		}
//		else
//		{
//			startQuery();
//		}
//	}
//}


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

//	LIST* data;
//	data = cgi_input_parse();
//	queryAuswahlLib(data);

	
	char* contentLengthString = getenv("CONTENT_LENGTH");
	if(contentLengthString != NULL)
	{
		int contentLength = atoi(contentLengthString);
		char data[contentLength + 1];
		fread(data, 1, contentLength, stdin);
		data[contentLength] = '\0';			
		queryAuswahl(data);		
	}
	else
	{
		queryAuswahl(NULL);
	}
	
	
	//list_clear(data);

	printf("</BODY></HTML>\n");

	beenden(); //program aufrauumen (free, usw...)

	return 0;
}
