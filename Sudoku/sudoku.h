#pragma once
#include <stdio.h>
#include <stdlib.h>

#define BREITE (9)
#define H�HE (9)
#define QUADRAT (3) 

static char* zahlen = NULL; //ent�hlt zahlen 
static char* editierbar = NULL; //1 ist editierbar und 0 nicht

int initialisieren(); 

void printSudoku(); //sudoku mit zahlen printen
void printEditierbar(); //printen, wo man editieren darf

char* getZahlen(); //zahlen array getter
int getL�nge(); //l�nge getter
char* getEditierbar(); //editierbar array getter

void beenden(); //program aufr�umen (free, usw...)





