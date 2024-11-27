#pragma once

#include <stdio.h>

//im menü auwählbare datei
typedef struct datei
{
	int nummer;
	const char* originalPfad;
	const char* schwierigkeit;
	const char* speicherPfad;
} datei;

#define dateinAnzahl (4)
const datei dateinListe[dateinAnzahl];

typedef int (*feldSetzenEvent)(int, int, char); //function pointer um keine abhängkeiten untereinander zu erzeugen (alle inclues in main)

int dateiFinden(int auswahl);

int dateiAuswahl();
int aktionAuswahl();
void aktionEingabe(feldSetzenEvent setzen);



