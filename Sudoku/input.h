#pragma once

#include <stdio.h>
#include <stdlib.h>

//enum um nummern der sudoku datein sinn zu geben (falls man sie nochmal ausserhalb des liste / struktur braucht)
enum SchwierigkeitOptionen
{
	SCHWIERIGKEIT_EINFACH = 1,
	SCHWIERIGKEIT_MITTEL = 2,
	SCHWIERIGKEIT_SCHWER = 3,
	SCHWIERIGKEIT_UNMOEGLICH = 4,

	SCHWIERIGKEIT_GENERIERT = 5, //zuletzt generiertes sudoku laden
	NEU_GENERIEREN = 6 //neues sudoku generieren und zuletzt generiertes sudoku ueberschreiben
};

//im menue auwaehlbare datei
typedef struct datei
{
	int nummer; //nummer (eingabe)
	const char* originalPfad; //pfad fuer originale / unveraenderte sudoku datei
	const char* schwierigkeit; //schwierigkeit text
	const char* speicherPfad; //pfad fuer speicherung von editierter sudoku datei 
} datei;

typedef int (*feldSetzenEvent)(int, int, char, int); //function pointer um keine abhaengkeiten untereinander zu erzeugen (alle inclues in main)

int dateiFinden(int auswahl); //datei finden via eingabe nummer

int dateiAuswahl(); //datei auswahl menue
int aktionAuswahl(); //aktion auswahl menue
void aktionEingabe(feldSetzenEvent setzen); //eingabe von aktion / zahl in feld setzen
datei getDateinListeElement(int index); //element aus datei liste getter



