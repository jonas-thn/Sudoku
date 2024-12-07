#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//true & false definiert
#define TRUE (1)
#define FALSE (0)

//farben 
#define FARBE_ROT "\x1b[31m" 
#define FARBE_GR�N "\x1b[32m"
#define FARBE_ZUR�CKSETZEN "\x1b[m"

//(urspr�nglich) leeres feld zum speichern im algorithmus
typedef struct leeresFeld
{
	int x; //x koordinate
	int y; //y koordinate
	char zahl; //zahl gespeichert
	int startZahl;	//start zahl (f�r 1-9 loop) gespeichert, um zu verhindern, dass der algorithmus beim 
					//zur�ckgehen den gleichen fehler mehrmals begeht (unendliche loop vermeiden + optimierung erm�glichen)
} leeresFeld;

//L�ser in extra "initialisieren" und "beenden" methode aufgeteilt, um in main / dem aufrufendem das trennen von l�sen, printen, usw zu erm�glichen

int l�serInitialisieren(const char* original); //l�ser initialisieren (malloc, datei laden, usw...)

void setL�serElement(int x, int y, char element); //element setter 
char getL�serElement(int x, int y); //element getter 
char* getL�serSudokuBuffer();

int zahlInZeile(int zeile, char zahl); //testen ob zahl bereits in zeile
int zahlInSpalte(int spalte, char zahl); //testen ob zahl bereits in spalte
int zahlInQuadrat(int x, int y, char zahl); //testen ob zahl bereits in quadrat

int platzierenM�glich(int x, int y, char zahl); //fasst "zahlenInZeile", "zahlenInSpalte" und "zahlenInQuadrat" zusammen -> kann man element in feld platzieren

int leereFelderFinden(); //findet alle leeren felder vor dem l�sen, die im algorithmus betrachtet werden (leereFelder array)

int sudokuL�sen(); //sudoku l�sungsalgorithmus

void printGel�stesSudoku(); //gel�stes sudoku ausgeben (in gr�n)

void l�serBeenden(); //l�ser beenden (free)


