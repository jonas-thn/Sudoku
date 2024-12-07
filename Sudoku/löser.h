#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//true & false definiert
#define TRUE (1)
#define FALSE (0)

//farben 
#define FARBE_ROT "\x1b[31m" 
#define FARBE_GRÜN "\x1b[32m"
#define FARBE_ZURÜCKSETZEN "\x1b[m"

//(ursprünglich) leeres feld zum speichern im algorithmus
typedef struct leeresFeld
{
	int x; //x koordinate
	int y; //y koordinate
	char zahl; //zahl gespeichert
	int startZahl;	//start zahl (für 1-9 loop) gespeichert, um zu verhindern, dass der algorithmus beim 
					//zurückgehen den gleichen fehler mehrmals begeht (unendliche loop vermeiden + optimierung ermöglichen)
} leeresFeld;

//Löser in extra "initialisieren" und "beenden" methode aufgeteilt, um in main / dem aufrufendem das trennen von lösen, printen, usw zu ermöglichen

int löserInitialisieren(const char* original); //löser initialisieren (malloc, datei laden, usw...)

void setLöserElement(int x, int y, char element); //element setter 
char getLöserElement(int x, int y); //element getter 
char* getLöserSudokuBuffer();

int zahlInZeile(int zeile, char zahl); //testen ob zahl bereits in zeile
int zahlInSpalte(int spalte, char zahl); //testen ob zahl bereits in spalte
int zahlInQuadrat(int x, int y, char zahl); //testen ob zahl bereits in quadrat

int platzierenMöglich(int x, int y, char zahl); //fasst "zahlenInZeile", "zahlenInSpalte" und "zahlenInQuadrat" zusammen -> kann man element in feld platzieren

int leereFelderFinden(); //findet alle leeren felder vor dem lösen, die im algorithmus betrachtet werden (leereFelder array)

int sudokuLösen(); //sudoku lösungsalgorithmus

void printGelöstesSudoku(); //gelöstes sudoku ausgeben (in grün)

void löserBeenden(); //löser beenden (free)


