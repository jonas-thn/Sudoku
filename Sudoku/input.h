#pragma once

#include <stdio.h>
#include <stdlib.h>

//im men� auw�hlbare datei
typedef struct datei
{
	int nummer; //nummer (eingabe)
	const char* originalPfad; //pfad f�r originale / unver�nderte sudoku datei
	const char* schwierigkeit; //schwierigkeit text
	const char* speicherPfad; //pfad f�r speicherung von editierter sudoku datei 
} datei;

typedef int (*feldSetzenEvent)(int, int, char, int); //function pointer um keine abh�ngkeiten untereinander zu erzeugen (alle inclues in main)

int dateiFinden(int auswahl); //datei finden via eingabe nummer

int dateiAuswahl(); //datei auswahl men�
int aktionAuswahl(); //aktion auswahl men�
void aktionEingabe(feldSetzenEvent setzen); //eingabe von aktion / zahl in feld setzen
datei getDateinListeElement(int index);



