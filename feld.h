#ifndef FELD_H
#define FELD_H

char *createfeld(int heigth, int length);
//create the game feld list
int printfeld(char *st, int height, int length);
//prints the game feld list
int updatesnake(listelement *snake, char *feld, int length, int heigth);
//update the snake on the feld

#endif



