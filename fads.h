#ifndef FADS_H_INCLUDED
#define FADS_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define N 9//The size of the map, not flexible, can have small number for test
#define C 5//Number of colors used, can have small number for test
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define random(x) (rand()%x)//Simplest way to get random integer from 0 to x

//define the type of most functions as Status
typedef int Status;

typedef struct
{
	char color;//Color is represented by a letter, printed with the letter itself
    int blank;//Is-blank-or-not is represented by an integer, 0 means eliminated, 1 means not
	//int typ;
}Block;

//Declaration of functions
Status Undconstr();
Status Game();
//Status Game(int A);//This integer shows the mode of game, for the possibility of extending function
void Printmap(Block ** M);
void Buildmap(Block ** &M);
char Genecolor(int R);
//The R here is used as a possibility to add more function in the future
Status GeneralErase(Block ** &M);
//Status BasicThreeErase(Block ** &M);
//Only a part of the overall erasing function, built first for basic functions
Status RCErase(Block ** &M);
Status SQErase(Block ** &M);
Status Falling(Block ** &M);
void EraseandFalling(Block ** &M);
//If I am clever enough already, this falling function works for
//any sophisticated cases in the future
Status Checkava(Block ** &M);
Status Movement(Block ** &M);
Status Moveright(Block ** &M, int i, int j);
Status Movedown(Block ** &M, int i, int j);
//Moveright and Movedown are used in Movement function
Status Checkera(Block ** &M);
//Status CheckBTE(Block ** &M);
Status CheckRCE(Block ** &M);

#endif // FADS_H_INCLUDED
