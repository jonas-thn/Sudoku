#pragma once

#include <stdio.h>
#include <stdlib.h>

//enum um nummern der sudoku datein sinn zu geben (falls man sie nochmal außerhalb des liste / struktur braucht)
enum
{
	EINFACH_NUM = 1,
	MITTEL_NUM = 2,
	SCHWER_NUM = 3,
	UNMÖGLICH_NUM = 4,

	GENERIERT_NUM = 5, //zuletzt generiertes sudoku laden
	NEU_GENERIEREN_NUM = 6 //neues sudoku generieren und zuletzt generiertes sudoku überschreiben
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



