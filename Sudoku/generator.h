#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//generator ist abh�ngig von l�ser (l�ser aber nat�rlich unabh�ngig von generator)
//einzige abh�ngigkeit zwischen bibliotheken im gesamten projekt, um code-dopplung zu vermeiden
//man h�tte eine kompakte version des l�sers in generator schreiben k�nnen, um die bibliotheken...
//...komplett unanbh�ngig zu machen, aber dann w�rden sich ca. 150 zeilen wiederhohlen...
//...und man w�rde mit den funktions namen durcheinander kommen
#include "l�ser.h" 

//true & false definiert
#define TRUE (1)
#define FALSE (0)

//farben 
#define FARBE_ROT "\x1b[31m" 
#define FARBE_GR�N "\x1b[32m"
#define FARBE_ZUR�CKSETZEN "\x1b[m"

void setGeneratorElement(int x, int y, char element); //element setter 
char getGeneratorElement(int x, int y); //element getter 

void generatorSudokuLeeren();
char* getGeneriertesSudoku();

int generatorDateiManager(char* originalPfad, char* dateiPfad, char* zahlen);

int sudokuGenerieren(int schwierigkeit);

void zuf�lligGef�lltesSudokuGenerieren();

void printGeneriertesSudoku();

int generatorInitialisieren();
void generatorBeenden();

int zahlVon1Bis9();
char charVon1Bis9();

