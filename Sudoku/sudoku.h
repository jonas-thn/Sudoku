#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//true und false definitionen
#define TRUE (1)
#define FALSE (0)

//farbcodes f�r print
#define FARBE_ROT "\x1b[31m" 
#define FARBE_GR�N "\x1b[32m"
#define FARBE_ZUR�CKSETZEN "\x1b[m"

#define BREITE (9) //horizontale anzahl an sudoku feldern
#define H�HE (9) //vertikale anzahl an sudoku feldern
#define QUADRAT (3) //3x3 elemente pro quadrat

typedef struct undoFeld //zug mit vorherigem element speichern
{
	int x;
	int y;
	char zahl;
} undoFeld;

static char* zahlen = NULL; //ent�hlt zahlen 
static char* editierbar = NULL; //1 ist editierbar und 0 nicht

#define UNDO_SPEICHER 100
undoFeld undoFelderStack[UNDO_SPEICHER]; //undo stack, um bis zu 100 z�ge zu speichern 
static int undoIndex = -1; //oberstes element vom stack 

int aktionUndoSpeichern(int x, int y); //letzten zug & vorheeriges element speichern in stack 
int undo(); //letzten zug r�ckg�ngig machen
void resetUndo(); //undo stack wird bei neuem laden von datei zur�ckgesetzt

int initialisieren(); //sudoku buffer initialisieren (malloc, default werte, usw...)

void printSudoku(); //sudoku mit zahlen printen

int feldSetzen(int x, int y, char zahl, int undoM�glich); //ein feld setzen (wenn editierbar)
int zahlCheck(char zahl); //testen ob zahl (char) passt

void setZahlenElement(int x, int y, char element); //zahlen-element setter 
char getZahlenElement(int x, int y); //zahlen-element getter 

void setEditierbarElement(int x, int y, char element); //editierbar-element setter 
char getEditierbarElement(int x, int y); //editierbar-element getter

char* getZahlen(); //zahlen array getter
int getL�nge(); //l�nge getter
char* getEditierbar(); //editierbar array getter

void sudokuLeeren();

void beenden(); //program aufr�umen (free, usw...)




