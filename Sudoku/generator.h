#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//generator ist abhängig von löser (löser aber natürlich unabhängig von generator)
//einzige abhängigkeit zwischen bibliotheken im gesamten projekt, um code-dopplung zu vermeiden
//man hätte eine kompakte version des lösers in generator schreiben können, um die bibliotheken...
//...komplett unanbhängig zu machen, aber dann würden sich ca. 150 zeilen wiederhohlen...
//...und man würde mit den funktions namen durcheinander kommen
#include "löser.h" 

//true & false definiert
#define TRUE (1)
#define FALSE (0)

//farben 
#define FARBE_ROT "\x1b[31m" 
#define FARBE_GRÜN "\x1b[32m"
#define FARBE_ZURÜCKSETZEN "\x1b[m"

void setGeneratorElement(int x, int y, char element); //element setter 
char getGeneratorElement(int x, int y); //element getter 

void generatorSudokuLeeren();
char* getGeneriertesSudoku();

int generatorDateiManager(char* originalPfad, char* dateiPfad, char* zahlen);

int sudokuGenerieren(int schwierigkeit);

void zufälligGefülltesSudokuGenerieren();

void printGeneriertesSudoku();

int generatorInitialisieren();
void generatorBeenden();

int zahlVon1Bis9();
char charVon1Bis9();

