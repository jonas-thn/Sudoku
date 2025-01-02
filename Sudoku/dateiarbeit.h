#pragma once

#include <stdio.h>

int zahlenLaden(char* zahlen, const char* original, char* editierbar, char* speicher); //zahlen von datei in zahlen buffer laden
int zahlenSpeichern(char* zahlen, const char* dateiname, int laenge); //zahlen von zahlen buffer in datei laden / ueberschreiben

