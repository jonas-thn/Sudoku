#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h" //enth�lt farben und true false

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

void setSudokuElement(int x, int y, char element); //element setter 
char getSudokuElement(int x, int y); //element getter 

int zahlInZeile(int zeile, char zahl); //testen ob zahl bereits in zeile
int zahlInSpalte(int spalte, char zahl); //testen ob zahl bereits in spalte
int zahlInQuadrat(int x, int y, char zahl); //testen ob zahl bereits in quadrat

int platzierenM�glich(int x, int y, char zahl); //fasst "zahlenInZeile", "zahlenInSpalte" und "zahlenInQuadrat" zusammen -> kann man element in feld platzieren

int leereFelderFinden(); //findet alle leeren felder vor dem l�sen, die im algorithmus betrachtet werden (leereFelder array)

void sudokuL�sen(); //sudoku l�sungsalgorithmus

void printGel�stesSudoku(); //gel�stes sudoku ausgeben (in gr�n)

int l�serBeenden(); //l�ser beenden (free)


