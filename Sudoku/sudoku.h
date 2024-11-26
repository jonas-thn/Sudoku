#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "dateiarbeit.h"

#define BREITE (9)
#define HÖHE (9)
#define QUADRAT (3)

static char* zahlen = NULL;

int initialisieren();

void printSudoku();

char* getZahlen();

void beenden();





