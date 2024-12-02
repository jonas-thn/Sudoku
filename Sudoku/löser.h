#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h" //enthält farben und true false

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

void setSudokuElement(int x, int y, char element); //element setter 
char getSudokuElement(int x, int y); //element getter 

int zahlInZeile(int zeile, char zahl); //testen ob zahl bereits in zeile
int zahlInSpalte(int spalte, char zahl); //testen ob zahl bereits in spalte
int zahlInQuadrat(int x, int y, char zahl); //testen ob zahl bereits in quadrat

int platzierenMöglich(int x, int y, char zahl); //fasst "zahlenInZeile", "zahlenInSpalte" und "zahlenInQuadrat" zusammen -> kann man element in feld platzieren

int leereFelderFinden(); //findet alle leeren felder vor dem lösen, die im algorithmus betrachtet werden (leereFelder array)

void sudokuLösen(); //sudoku lösungsalgorithmus

void printGelöstesSudoku(); //gelöstes sudoku ausgeben (in grün)

int löserBeenden(); //löser beenden (free)


