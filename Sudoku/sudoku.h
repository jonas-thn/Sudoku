#pragma once
#include <stdio.h>
#include <stdlib.h>

#define BREITE (9)
#define H�HE (9)
#define QUADRAT (3)

static char* zahlen = NULL;
static char* editierbar = NULL; //1 ist editierbar und 0 nicht

int initialisieren();

void printSudoku();
void printEditierbar();

char* getZahlen();
int getL�nge();
char* getEditierbar();

void beenden();





