#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BREITE (9) //horizontale anzahl an sudoku feldern
#define H�HE (9) //vertikale anzahl an sudoku feldern
#define QUADRAT (3) //3x3 elemente pro quadrat

#define TRUE (1)
#define FALSE (0)

#define FARBE_ROT "\x1b[31m" 
#define FARBE_GR�N "\x1b[32m"
#define FARBE_ZUR�CKSETZEN "\x1b[m"

typedef struct leeresFeld
{
	int x;
	int y;
	char zahl;
	int startZahl;
} leeresFeld;

#define MAX_LEERE_FLDER 81
leeresFeld leereFelder[81];
static int testFeldIndex = -1;

static char* sudoku = NULL;

int l�serInitialisieren(const char* original);

void setSudokuElement(int x, int y, char element); //zahlen-element setter 
char getSudokuElement(int x, int y); //zahlen-element getter 

int zahlInZeile(int zeile, char zahl);
int zahlInSpalte(int spalte, char zahl);
int zahlInQuadrat(int x, int y, char zahl);

int platzierenM�glich(int x, int y, char zahl);

int leereFelderFinden();

int sudokuL�sen();

void printGel�stesSudoku();

int l�serBeenden();


