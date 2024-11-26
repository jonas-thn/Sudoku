#include "sudoku.h"
#include "dateiarbeit.h"

int main(void)
{
	initialisieren();

	zahlenLaden(getZahlen());

	printSudoku();

	beenden();

	return 0;
}