#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BREITE (9) //horizontale anzahl an sudoku feldern
#define HÖHE (9) //vertikale anzahl an sudoku feldern
#define QUADRAT (3) //3x3 elemente pro quadrat

typedef struct undoFeld
{
	int x;
	int y;
	char zahl;
} undoFeld;

static char* zahlen = NULL; //entählt zahlen 
static char* editierbar = NULL; //1 ist editierbar und 0 nicht

#define UNDO_SPEICHER 100
undoFeld undoFelderStack[UNDO_SPEICHER]; //undo stack, um bis zu 100 züge zu speichern 
static int undoIndex = -1; //oberstes element vom stack 

int aktionUndoSpeichern(int x, int y);
int undo();
void resetUndo();

int initialisieren(); //sudoku buffer initialisieren (malloc, default werte, usw...)

void printSudoku(); //sudoku mit zahlen printen

int feldSetzen(int x, int y, char zahl, int undoMöglich); //ein feld setzen (wenn editierbar)
int zahlCheck(char zahl); //testen ob zahl (char) passt

void setZahlenElement(int x, int y, char element);
char getZahlenElement(int x, int y);

void setEditierbarElement(int x, int y, char element);
char getEditierbarElement(int x, int y);

char* getZahlen(); //zahlen array getter
int getLänge(); //länge getter
char* getEditierbar(); //editierbar array getter

void beenden(); //program aufräumen (free, usw...)




