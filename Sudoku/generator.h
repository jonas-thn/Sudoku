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

int generatorInitialisieren(); //sudoku generator wird initialisiert (und löser)
void generatorBeenden(); //sudoku generator wird beendet (und löser)

void setGeneratorElement(int x, int y, char element); //element setter 
char getGeneratorElement(int x, int y); //element getter 

void generatorSudokuLeeren(); //gesamtes generator sudoku leeren
char* getGeneriertesSudoku(); //generator sudoku getter

int generatorDateiManager(char* originalPfad, char* dateiPfad, char* zahlen); //setzt nötige datein für generator

int sudokuGenerieren(int schwierigkeit); //zufälliges sudoku generieren algorithmus

void zufälligGefülltesSudokuGenerieren(); //zufälliges gefülltes sudoku wird generiert (zwischenschritt im algorithmus)

void printGeneriertesSudoku(); //generiertes sudoku printen (debug)

int zahlVon1Bis9(); //zufällige zahl zwischen 1-9 als int
char charVon1Bis9(); //zufällige zahl zwischen 1-9 als char

