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

int generatorInitialisieren(); //sudoku generator wird initialisiert (und l�ser)
void generatorBeenden(); //sudoku generator wird beendet (und l�ser)

void setGeneratorElement(int x, int y, char element); //element setter 
char getGeneratorElement(int x, int y); //element getter 

void generatorSudokuLeeren(); //gesamtes generator sudoku leeren
char* getGeneriertesSudoku(); //generator sudoku getter

int generatorDateiManager(char* originalPfad, char* dateiPfad, char* zahlen); //setzt n�tige datein f�r generator

int sudokuGenerieren(int schwierigkeit); //zuf�lliges sudoku generieren algorithmus

void zuf�lligGef�lltesSudokuGenerieren(); //zuf�lliges gef�lltes sudoku wird generiert (zwischenschritt im algorithmus)

void printGeneriertesSudoku(); //generiertes sudoku printen (debug)

int zahlVon1Bis9(); //zuf�llige zahl zwischen 1-9 als int
char charVon1Bis9(); //zuf�llige zahl zwischen 1-9 als char

