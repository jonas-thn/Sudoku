#include "sudoku.h"
#include "dateiarbeit.h"

int main(void)
{
	initialisieren();

	zahlenLaden(getZahlen(), "./Sudoku1.txt");

	printSudoku();

	zahlenSpeichern(getZahlen(), "./Sudoku4.txt", gibLänge());

	beenden();

	return 0;
}