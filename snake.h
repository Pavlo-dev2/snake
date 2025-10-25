#ifndef SNAKE_H
#define SNAKE_H

listelement *movesnake(char d, listelement *st, int x, int y, int higth, int length, char apple);//moves snake in direction d(u- up; r- rigth; d- down; l- left) appele 1 if hit apple, 0 if not
int checksnake(listelement *snake);//check if snake does fit itselve, 1 if it do;
int createapple(char *feld, int length, int heigth, int snakelen, int r);//creates apple on the random free possion, returns apple possion in arrey feld;
int checkapple(listelement *snake, int apple, int length);//check if snake hit apple

#endif
