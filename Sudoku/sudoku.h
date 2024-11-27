#pragma once
#include <stdio.h>
#include <stdlib.h>

#define BREITE (9) //horizontale anzahl an sudoku feldern
#define HÖHE (9) //vertikale anzahl an sudoku feldern
#define QUADRAT (3) //3x3 elemente pro quadrat

static char* zahlen = NULL; //entählt zahlen 
static char* editierbar = NULL; //1 ist editierbar und 0 nicht

int initialisieren(); //sudoku buffer initialisieren (malloc, default werte, usw...)

void printSudoku(); //sudoku mit zahlen printen
void printEditierbar(); //printen, wo man editieren darf

int feldSetzen(int x, int y, char zahl); //ein feld setzen (wenn editierbar)
int zahlCheck(char zahl); //testen ob zahl (char) passt

char* getZahlen(); //zahlen array getter
int getLänge(); //länge getter
char* getEditierbar(); //editierbar array getter

void beenden(); //program aufräumen (free, usw...)




