#pragma once

#include <stdio.h>
#include <stdlib.h>

//im menü auwählbare datei
typedef struct datei
{
	int nummer; //nummer (eingabe)
	const char* originalPfad; //pfad für originale / unveränderte sudoku datei
	const char* schwierigkeit; //schwierigkeit text
	const char* speicherPfad; //pfad für speicherung von editierter sudoku datei 
} datei;

#define dateinAnzahl (4) //anzahlt von sudoku datein 
const datei dateinListe[dateinAnzahl]; //liste an sudoku datein

typedef int (*feldSetzenEvent)(int, int, char); //function pointer um keine abhängkeiten untereinander zu erzeugen (alle inclues in main)

int dateiFinden(int auswahl); //datei finden via eingabe nummer

int dateiAuswahl(); //datei auswahl menü
int aktionAuswahl(); //aktion auswahl menü
void aktionEingabe(feldSetzenEvent setzen); //eingabe von aktion / zahl in feld setzen



