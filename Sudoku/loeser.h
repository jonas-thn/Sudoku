#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//true & false definiert
#define TRUE (1)
#define FALSE (0)

//farben 
#define FARBE_ROT "\x1b[31m" 
#define FARBE_GRUEN "\x1b[32m"
#define FARBE_ZURUECKSETZEN "\x1b[m"

//(urspruenglich) leeres feld zum speichern im algorithmus
typedef struct leeresFeld
{
	int x; //x koordinate
	int y; //y koordinate
	char zahl; //zahl gespeichert
	int startZahl;	//start zahl (fuer 1-9 loop) gespeichert, um zu verhindern, dass der algorithmus beim 
					//zurueckgehen den gleichen fehler mehrmals begeht (unendliche loop vermeiden + optimierung ermoeglichen)
} leeresFeld;

//Loeser in extra "initialisieren" und "beenden" methode aufgeteilt, um in main / dem aufrufendem das trennen von loesen, printen, usw zu ermoeglichen

int loeserInitialisieren(const char* original); //loeser initialisieren (malloc, datei laden, usw...)

void setLoeserElement(int x, int y, char element); //element setter 
char getLoeserElement(int x, int y); //element getter 
char* getLoeserSudokuBuffer(); //loeser sudoku buffer getter

int zahlInZeile(int zeile, char zahl); //testen ob zahl bereits in zeile
int zahlInSpalte(int spalte, char zahl); //testen ob zahl bereits in spalte
int zahlInQuadrat(int x, int y, char zahl); //testen ob zahl bereits in quadrat

int platzierenMoeglich(int x, int y, char zahl); //fasst "zahlenInZeile", "zahlenInSpalte" und "zahlenInQuadrat" zusammen -> kann man element in feld platzieren

int leereFelderFinden(); //findet alle leeren felder vor dem loesen, die im algorithmus betrachtet werden (leereFelder array)

int sudokuLoesen(); //sudoku loesungsalgorithmus

void printGeloestesSudoku(); //geloestes sudoku ausgeben (in gruen)

void loeserBeenden(); //loeser beenden (free)


