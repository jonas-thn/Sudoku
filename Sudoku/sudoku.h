#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//true und false definitionen
#define TRUE (1)
#define FALSE (0)

//farbcodes für print
#define FARBE_ROT "\x1b[31m" 
#define FARBE_GRÜN "\x1b[32m"
#define FARBE_ZURÜCKSETZEN "\x1b[m"

#define BREITE (9) //horizontale anzahl an sudoku feldern
#define HÖHE (9) //vertikale anzahl an sudoku feldern
#define QUADRAT (3) //3x3 elemente pro quadrat

typedef struct undoFeld //zug mit vorherigem element speichern
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

int aktionUndoSpeichern(int x, int y); //letzten zug & vorheeriges element speichern in stack 
int undo(); //letzten zug rückgängig machen
void resetUndo(); //undo stack wird bei neuem laden von datei zurückgesetzt

int initialisieren(); //sudoku buffer initialisieren (malloc, default werte, usw...)

void printSudoku(); //sudoku mit zahlen printen

int feldSetzen(int x, int y, char zahl, int undoMöglich); //ein feld setzen (wenn editierbar)
int zahlCheck(char zahl); //testen ob zahl (char) passt

void setZahlenElement(int x, int y, char element); //zahlen-element setter 
char getZahlenElement(int x, int y); //zahlen-element getter 

void setEditierbarElement(int x, int y, char element); //editierbar-element setter 
char getEditierbarElement(int x, int y); //editierbar-element getter

char* getZahlen(); //zahlen array getter
int getLänge(); //länge getter
char* getEditierbar(); //editierbar array getter

void sudokuLeeren();

void beenden(); //program aufräumen (free, usw...)




