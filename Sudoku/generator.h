#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//generator ist abhaengig von loeser (loeser aber natuerlich unabhaengig von generator)
//einzige abhaengigkeit zwischen bibliotheken im gesamten projekt, um code-dopplung zu vermeiden
//man haette eine kompakte version des loesers in generator schreiben koennen, um die bibliotheken...
//...komplett unanbhaengig zu machen, aber dann wuerden sich ca. 150 zeilen wiederhohlen...
//...und man wuerde mit den funktions namen durcheinander kommen
#include "loeser.h" 

int generatorInitialisieren(); //sudoku generator wird initialisiert (und loeser)
void generatorBeenden(); //sudoku generator wird beendet (und loeser)

void setGeneratorElement(int x, int y, char element); //element setter 
char getGeneratorElement(int x, int y); //element getter 

void generatorSudokuLeeren(); //gesamtes generator sudoku leeren
char* getGeneriertesSudoku(); //generator sudoku getter

int generatorDateiManager(char* originalPfad, char* dateiPfad, char* zahlen); //setzt noetige datein fuer generator

int sudokuGenerieren(int schwierigkeit); //zufaelliges sudoku generieren algorithmus

void zufaelligGefuelltesSudokuGenerieren(); //zufaelliges gefuelltes sudoku wird generiert (zwischenschritt im algorithmus)

void printGeneriertesSudoku(); //generiertes sudoku printen (debug)

int zahlVon1Bis9(); //zufaellige zahl zwischen 1-9 als int
char charVon1Bis9(); //zufaellige zahl zwischen 1-9 als char

