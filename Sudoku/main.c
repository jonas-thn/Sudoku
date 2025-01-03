//CBI BRANCH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void einfachQuery()
{
	char* einfach = "<A href=\"sudoku.cgi?\">Zurueck</A>";

	char* originalPfad = "./Sudokus/Sudoku1.txt";
	char* speicherPfad = "./Sudokus/Sudoku1_Save.txt";

	zahlenLaden(getZahlen(), originalPfad, getEditierbar(), speicherPfad);
	printSudoku();

	printf(einfach);
}

void mittelQuery()
{
	char* mittel = "<A href=\"sudoku.cgi?\">Zurueck</A>";

	printf(mittel);
}

void schwerQuery()
{
	char* schwer = "<A href=\"sudoku.cgi?\">Zurueck</A>";

	printf(schwer);
}

void unmoeglichQuery()
{
	char* unmoeglich = "<A href=\"sudoku.cgi?\">Zurueck</A>";

	printf(unmoeglich);
}

void generiertQuery()
{
	char* generiert = "<A href=\"sudoku.cgi?\">Zurueck</A>";

	printf(generiert);
}

void neuQuery()
{
	char* neu = "<A href=\"sudoku.cgi?\">Zurueck</A>";

	printf(neu);
}

void startQuery()
{
	char* start = "Waehle eine Option aus:<BR><A href=\"sudoku.cgi?einfach\">Einfach</A><BR><A href=\"sudoku.cgi?mittel\">Mittel</A><BR><A href=\"sudoku.cgi?schwer\">Schwer</A><BR><A href=\"sudoku.cgi?unmoeglich\">Unmoeglich</A><BR><A href=\"sudoku.cgi?generiert\">Generiert</A><BR><A href=\"sudoku.cgi?neu\">Neu</A>";
	
	printf(start);
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
					
	char* env;

	if(env = getenv("QUERY_STRING"))
	{
		if(strcmp("einfach", env) == 0)
		{
			einfachQuery();
		}
		else if(strcmp("mittel", env) == 0)
		{
			mittelQuery();
		}
		else if(strcmp("schwer", env) == 0)
		{
			schwerQuery();
		}
		else if(strcmp("unmoeglich", env) == 0)
		{
			unmoeglichQuery();
		}
		else if(strcmp("generiert", env) == 0)
		{
			generiertQuery();
		}
		else if(strcmp("neu", env) == 0)
		{
			neuQuery();
		}
		else
		{
			startQuery();
		}
	}

	printf("</BODY></HTML>\n");

	beenden(); //program aufrauumen (free, usw...)

	return 0;
}
