#pragma once

#include <stdio.h>

int zahlenLaden(char* zahlen, const char* dateiname, char* editierbar); //zahlen von datei in zahlen buffer laden
int zahlenSpeichern(char* zahlen, const char* dateiname, int länge); //zahlen von zahlen buffer in datei laden / überschreiben

