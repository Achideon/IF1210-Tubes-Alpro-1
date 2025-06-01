#ifndef CIRNOSPIN_H
#define CIRNOSPIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MoveCursorHome();

char **LoadFramesFromFile(const char *filename, int *frameCount);

void PlayCirno();

#endif
