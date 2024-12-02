#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h" //enth�lt farben und true/false

typedef struct undoFeld //zug mit vorherigem element speichern
{
	int x;
	int y;
	char zahl;
} undoFeld;

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




