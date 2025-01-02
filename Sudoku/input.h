#pragma once

#include <stdio.h>
#include <stdlib.h>

//enum um nummern der sudoku datein sinn zu geben (falls man sie nochmal außerhalb des liste / struktur braucht)
enum SchwierigkeitOptionen
{
	SCHWIERIGKEIT_EINFACH = 1,
	SCHWIERIGKEIT_MITTEL = 2,
	SCHWIERIGKEIT_SCHWER = 3,
	SCHWIERIGKEIT_UNMÖGLICH = 4,

	SCHWIERIGKEIT_GENERIERT = 5, //zuletzt generiertes sudoku laden
	NEU_GENERIEREN = 6 //neues sudoku generieren und zuletzt generiertes sudoku überschreiben
};

//im menü auwählbare datei
typedef struct datei
{
	int nummer; //nummer (eingabe)
	const char* originalPfad; //pfad für originale / unveränderte sudoku datei
	const char* schwierigkeit; //schwierigkeit text
	const char* speicherPfad; //pfad für speicherung von editierter sudoku datei 
} datei;

typedef int (*feldSetzenEvent)(int, int, char, int); //function pointer um keine abhängkeiten untereinander zu erzeugen (alle inclues in main)

int dateiFinden(int auswahl); //datei finden via eingabe nummer

int dateiAuswahl(); //datei auswahl menü
int aktionAuswahl(); //aktion auswahl menü
void aktionEingabe(feldSetzenEvent setzen); //eingabe von aktion / zahl in feld setzen
datei getDateinListeElement(int index); //element aus datei liste getter



