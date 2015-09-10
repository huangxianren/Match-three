#include "fads.h"

void Printmap(Block ** M)
{//Printing don't require editing the map
    int i = 0;
    int j = 0;
    printf("\n");
	printf("\t");
	for(i=0;i<N;i++)
	{
		printf("%2d", i+1);
	}//End for: print a line of column number
	printf("\n\n\n\n");
    for(i=0;i<N;i++)
    {
		printf("%d\t", i+1);//Print row number frist
        for(j=0;j<N;j++)
        {
            if(M[i][j].blank == 1)
            {
                printf("%2c", M[i][j].color);
            }//End if
            else
            {
                printf("  ");
            }//End else: only print not-eliminated blocks, leave blank for eliminated
        }//End inner for
        printf("\n");
    }//End outer for
    printf("\n");
}//Basic function: print the current game map

void Buildmap(Block ** &M)
{
    int i = 0;
    int j = 0;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            M[i][j].color = Genecolor(C);
            M[i][j].blank = 1;
			//Map[i][j].typ = 0;
        }//End inner for
    }//End outer for
    //Printmap(M);//test
}//Basic function: fill the map with random colors

Status Game()
{//Contains the most important game logic
    //Pre-activate the random seed, one time only.
    srand((int)time(0));
	//Since this is so important, put it here and it can be used in the future.

    int i = 0;
    int j = 0;
    //Build a map first.
    Block **Map;
    if(!(Map = (Block **)malloc(sizeof(Block *)*N)))
    {
        printf("Not enough memory space!\n");
        exit(FALSE);
    }//End if: check memory
    for(i=0;i<N;i++)
    {
        if(!(Map[i] = (Block *)malloc(sizeof(Block)*N)))
        {
            printf("Not enough memory space!\n");
            exit(FALSE);
        }//End if: check memory
        for(j=0;j<N;j++)
        {
            Map[i][j].color = '/';
            Map[i][j].blank = 0;
			//Map[i][j].typ = 0;
        }//End inner for
    }//End outer for: this terminates the initiation.
    //Printmap(Map);//test
    //Generate the map
    do
    {//Build the map until found a good map
        Buildmap(Map);
        //Printmap(Map);//test
        EraseandFalling(Map);//Generating the map succeeded, no more erasing
    }while(Checkava(Map)==FALSE);
    do
    {
        Printmap(Map);
        Movement(Map);
        EraseandFalling(Map);
    }while(Checkava(Map)!=FALSE);//end do while: the main step in the game
    Printmap(Map);//Final printing
    //Should have get a map where there is no erasing available
    //printf("Wanna play again?[Y/N]\n");

    printf("Thanks for playing!\nReturn to main menu.\n");
    //getchar();
    return(TRUE);
}//Core function: the game itself

char Genecolor(int R)
{
    srand(rand());
    switch(random(R))
    {
        case 0: return('R');
        case 1: return('G');
        case 2: return('W');
        case 3: return('Y');
        case 4: return('B');
        case 5: return('P');
        case 6: return('O');
        default :
			printf("ERROR CODE 3: Should be impossible in random\n");
			exit(FALSE);
    }//End switch: randomly assigned a color
}//Basic function: generate a random color for any block

Status GeneralErase(Block ** &M)
{
	int flag = 0;
    flag += RCErase(M);
    //flag += SQErase(M);
    //flag += BasicThreeErase(M);
	//printf("General erase flag = %d\n", flag);
	return(flag);//flag == 0 means FALSE, flags records the number of erasing
}//Basic function: all kinds of erasing

Status RCErase(Block ** &M)
{//Erase according to row & col, just do in one row or col
    int i = 0;
    int j = 0;
    int k = 0;
    int flag = 0;
    int count = 0;
    //printf("Entering RCE part\n");//test
    for (i=0;i<N;i++)
    {//For every row
        count = 0;//Reset count to 0
        //printf("row # i=%d\n", i);
        for(k=0;k<N;k++)
        {//Add count if found same color
            //printf("position k=%d, count=%d\n", k, count);
            if(k+1 >= N or M[i][k].color != M[i][k+1].color)
            {//Reached a different color at k+1 or reached the end
                if(count >= 2)
                {//Three or more same blocks
                    //printf("Elimination at k=%d\n", k);
                    flag += 1;
                    for(;count>=0;count--)
                    {//Eliminate same color blocks
                        //printf("count=%d\n", count);
                        M[i][k-count].blank = 0;
                    }//End for: count should be -1 now
                    //printf("count=%d, should be -1\n", count);
                }//End if
                count = 0;//reset count, no matter erasing or not
            }//End if: not the same color, reset count
            else
            {//Found same color
                count += 1;
            }//End else: found same color, add 1 to count
        }//End inner for: scanned a whole row
    }//End outer for: scanned every row
    for (j=0;j<N;j++)
    {//For every column
        count = 0;//Reset count to 0
        //printf("column # j=%d\n", j);
        for(k=0;k<N;k++)
        {//Add count if found same color
            //printf("position k=%d, count=%d\n", k, count);
            if(k+1 >= N or M[k][j].color != M[k+1][j].color)
            {//Reached a different color at k+1 or reached the end
                if(count >= 2)
                {//Three or more same blocks
                    //printf("Elimination at k=%d\n", k);
                    flag += 1;
                    for(;count>=0;count--)
                    {//Eliminate same color blocks
                        //printf("count=%d\n", count);
                        M[i][k-count].blank = 0;
                    }//End for: count should be -1 now
                    //printf("count=%d, should be -1\n", count);
                }//End if
                count = 0;//reset count, no matter erasing or not
            }//End if: not the same color, reset count
            else
            {//Found same color
                count += 1;
            }//End else: found same color, add 1 to count
        }//End inner for: scanned a whole column
    }//End outer for: scanned every column
    return(flag);
}//Basic function: erasing according to row & col

Status SQErase(Block ** &M)
{//Square erasing, 4 blocks at a time (definitely)
    printf("Entering SQE section\n");//test
    int i = 0;
    int j = 0;
    int flag = 0;
    for(i=0;i<N-1;i++)
    {//The range here because SQE are very well organized
        for(j=0;j<N-1;j++)
        {//Don't need to worry about the last row and column
            //printf("Now checking i = %d, j = %d\n", i, j);
            if(M[i][j].color == M[i+1][j].color and M[i][j].color == M[i][j+1].color and M[i][j].color == M[i+1][j+1].color)
            {
                M[i][j].blank = 0;
                M[i+1][j].blank = 0;
                M[i][j+1].blank = 0;
                M[i+1][j+1].blank = 0;
                flag += 1;
            }//End if: erased a square
        }//End inner for
    }//End outer for
    return(flag);
}//Basic function: Erasing a square
    
/*Status BasicThreeErase(Block ** &M)
{
    int i = 0;
    int j = 0;
    int flag = 0;
    //printf("Entering BTE part\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            //printf("Now checking i = %d, j = %d\n", i, j);
            if(i != 0 and i != N-1)
            {
                if(M[i-1][j].color==M[i][j].color and M[i+1][j].color==M[i][j].color)
                {
                    M[i-1][j].color='-';
                    M[i][j].color='-';
                    M[i+1][j].color='-';
                    M[i-1][j].blank=0;
                    M[i][j].blank=0;
                    M[i+1][j].blank=0;
                    flag += 1;
                }//End inner if: erasing the matching-three
            }//Don't need to check first and last row for row +1 -1
            if(j != 0 and j != N-1)
            {
                if(M[i][j-1].color==M[i][j].color and M[i][j].color==M[i][j+1].color)
                {
                    M[i][j-1].color='-';
                    M[i][j].color='-';
                    M[i][j+1].color='-';
                    M[i][j-1].blank=0;
                    M[i][j].blank=0;
                    M[i][j+1].blank=0;
                    flag += 1;
                }//End inner if: erasing the matching-three
            }//Don't need to check first and last column for column +1 -1
        }//End inner for
    }//End outer for: scan for the whole map to find all basic three erasing
    //printf("BTE flag = %d\n", flag);
    return(flag);//flag == 0 means FALSE, flags records the number of erasing
}//Basic function: basic three erasing, the easiest erasing function*/

Status Falling(Block ** &M)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int flag = 0;
    Printmap(M);//test before falling
    for(i=N-1;i>=0;i--)
    {//Scan starting from the bottom row
        for(j=0;j<N;j++)
        {
            if(M[i][j].blank==0)
            {//if found the erased block M[i][j], use blank as criteria
                //printf("i= %d, j= %d\n", i, j);
                k = i - 1;
                while(k >= 0 and M[k][j].blank==0)
                {
                    k -= 1;
                }//End while: found the first nonzero block above M[i][j]
				//or reached top
                //printf("k=%d\n", k);
                if(k < 0)
                {//if at the top
                    //printf("Entering k < 0 section\n");
                    M[i][j].color = Genecolor(C);
                    M[i][j].blank = 1;
                    //printf("New Block generated\n");
                    flag += 1;
                }//End if: generate a new block at M[i][j]
                else
                {//not at the top
                    M[i][j].color = M[k][j].color;
                    M[k][j].color = '-';
                    M[i][j].blank = M[k][j].blank;
                    M[k][j].blank = 0;
                }//End else: one block falls down
            }//End if: process on erased block M[i][j] finished
        }//End inner for
    }//End outer for: finished scanning for the whole map
    Printmap(M);//test after falling
	return(flag);//flag == 0 means FALSE, flags records the number of blocks erased
}//Basic function: falling down, returning the # of newly generated blocks

void EraseandFalling(Block ** &M)
{
    //printf("Entering E&F section\n");
    while(GeneralErase(M)!=FALSE)
    {//Use while loop to make sure no matching exist naturally
        //After one step of erasing
        //Printmap(Map);//Used for debugging
        Falling(M);//Don't check error here any more
        //Printmap(Map);//Printing after erasing and falling
    }//End while
}//Basic function: Erase and Falling, to save some code...

Status Checkava(Block ** &M)
{
	int i = 0;
	int j = 0;
	int flag = 0;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(j < N-1)
			{//for all the column other than the last
				Moveright(M, i, j);
				flag += Checkera(M);
				Moveright(M, i, j);
			}//End if: all moved right once
			if(i < N-1)
			{
				Movedown(M, i, j);
				flag += Checkera(M);
				Movedown(M, i, j);
			}//End if: all moved down once
		}//End inner for
	}//End outer for: checked every possible movement
    if(flag==0)
    {
        return(FALSE);
    }
    else
    {
        return(TRUE);
    }//end if else: FALSE means no available movement
}//Basic function: Check availability of continuing game

Status Movement(Block ** &M)
{//Provide two different style of movement, input two coordinates or one coordinate + direction
    char ii = '0';
    char jj = '0';
    char kk = '0';
    char ll = '0';
    char buffer[80] = "";
    //int h = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    Block * temp;
    if(!(temp=(Block *)malloc(sizeof(Block))))
    {
        printf("Not enough memory space!\n");
        exit(FALSE);
    }//End if: check memory
    do
    {
        printf("Please input your movement:(row, column and direction, no spaces)\n");
        //scanf("%c%c%c", &ii, &jj, &kk);//rewrite later
        scanf("%s", buffer);
        //printf("%s", buffer);
        /*while(buffer[h] < '0' or buffer[h] > 'z')
        {
            h += 1;
        }//End while: move i to the first normal char
        ii = buffer[h];
        while(buffer[h] < '0' or buffer[h] > 'z')
        {
            h += 1;
        }//End while: move i to the first normal char
        jj = buffer[h];
        while(buffer[h] < '0' or buffer[h] > 'z')
        {
            h += 1;
        }//End while: move i to the first normal char
        kk = buffer[h];*/
        ii = buffer[0];
        jj = buffer[1];
        kk = buffer[2];
        //printf("ii = %c, jj = %c, kk = %c\n", ii, jj, kk);
        i = ii - '1';
        j = jj - '1';
        if(kk == 'U' or kk == 'u')
        {//Up section
            if(1 <= i and i <= N-1 and 0 <= j and j <= N-1)
            {
                if(M[i][j].blank == 1 and M[i-1][j].blank == 1)
                {//Check existence
                    //printf("The first block %d %d\n", i+1, j+1);
                    //printf("Direction: up\n");
                    Movedown(M, i-1, j);
                }//End if: exist, move
                else
                {//Don't exist
                    printf("ERROR CODE 11: block not exist!\n");
                    exit(FALSE);
                }//End else
            }//End if: Check range of desired movement
            else
            {
                printf("ERROR CODE 4: Illegal input format\n");
                return(FALSE);
            }
        }//End of up section
        else if(kk == 'D' or kk == 'd')
        {//down section
            if(0 <= i and i <= N-2 and 0 <= j and j <= N-1)
            {
                if(M[i][j].blank == 1 and M[i+1][j].blank == 1)
                {//Check existence
                    //printf("The first block %d %d\n", i+1, j+1);
                    //printf("Direction: down\n");
                    Movedown(M, i, j);
                }//End if: exist, move
                else
                {//Don't exist
                    printf("ERROR CODE 11: block not exist!\n");
                    exit(FALSE);
                }//End else
            }//End if: Check range of desired movement
            else
            {
                printf("ERROR CODE 4: Illegal input format\n");
                return(FALSE);
            }
        }//End of down section
        else if(kk == 'L' or kk == 'l')
        {//Left section
            if(0 <= i and i <= N-1 and 1 <= j and j <= N-1)
            {
                if(M[i][j].blank == 1 and M[i][j-1].blank == 1)
                {//Check existence
                    //printf("The first block %d %d\n", i+1, j+1);
                    //printf("Direction: left\n");
                    Moveright(M, i, j-1);
                }//End if: exist, move
                else
                {//Don't exist
                    printf("ERROR CODE 11: block not exist!\n");
                    exit(FALSE);
                }//End else
            }//End if: Check range of desired movement
            else
            {
                printf("ERROR CODE 4: Illegal input format\n");
                return(FALSE);
            }
        }//End of left section
        else if(kk == 'R' or kk == 'r')
        {//Right section
            if(0 <= i and i <= N-1 and 0 <= j and j <= N-2)
            {
                if(M[i][j].blank == 1 and M[i][j-1].blank == 1)
                {//Check existence
                    //printf("The first block %d %d\n", i+1, j+1);
                    //printf("Direction: right\n");
                    Moveright(M, i, j);
                }//End if: exist, move
                else
                {//Don't exist
                    printf("ERROR CODE 11: block not exist!\n");
                    exit(FALSE);
                }//End else
            }//End if: Check range of desired movement
            else
            {
                printf("ERROR CODE 4: Illegal input format\n");
                return(FALSE);
            }
        }//End of right section
        else if(kk >= '0' and kk <= '9')
        {
            ll = buffer[3];
            k = kk - '1';
            l = ll - '1';
            printf("Movement type B\n");
            printf("Block 1: %d, %d; Block 2: %d, %d\n", i+1, j+1, k+1, l+1);
            if((abs(i-k) == 1 and j == l) or (abs(j-l) == 1 and i == k))
            {
                if(M[i][j].blank == 1 and M[k][l].blank == 1)
                {
                    temp->color = M[i][j].color;
                    M[i][j].color = M[k][l].color;
                    M[k][l].color = temp->color;
                    //temp->blank = M[i][j].blank;
                    //M[i][j].blank = M[k][l].blank;
                    //M[k][l].blank = temp->blank;//Leave it here for further function
                }//End inner if
                else
                {
                    printf("ERROR CODE 10: trying to move blank block\n");
                    exit(FALSE);
                }//End else
            }//End outer if
            else
            {
                printf("Wrong input! Redo the movement!\n");
            }//End if else
        }
        else
        {
            printf("ERROR CODE 8: unexpected third input char\n");
            exit(FALSE);
        }
        free(temp);
    }while(Checkera(M)==FALSE);
    return(TRUE);
}

Status Moveright(Block ** &M, int i, int j)
{
    if(i < 0 or i >= N or j < 0 or j >= N-1)
    {
        printf("ERROR CODE 6: Moving right at the last column!\n");
        exit(FALSE);
    }//End if: checking last column
    if(M[i][j].blank == 0 or M[i][j+1].blank == 0)
    {
        printf("ERROR CODE 9: trying to move blank block\n");
        exit(FALSE);
    }//End if
	Block * temp;
	temp = (Block *)malloc(sizeof(Block));
	temp->color = M[i][j].color;
	M[i][j].color = M[i][j+1].color;
	M[i][j+1].color = temp->color;
	temp->blank = M[i][j].blank;
	M[i][j].blank = M[i][j+1].blank;
	M[i][j+1].blank = temp->blank;
	free(temp);
	return(TRUE);
}//function: Move right

Status Movedown(Block ** &M, int i, int j)
{
    if(i < 0 or i >= N-1 or j < 0 or j >= N)
    {
        printf("ERROR CODE 7: Moving down at the last row!\n");
        exit(FALSE);
    }//End if: checking last row
    if(M[i][j].blank == 0 or M[i+1][j].blank == 0)
    {
        printf("ERROR CODE 9: trying to move blank block\n");
        exit(FALSE);
    }//End if
	Block * temp;
	temp = (Block *)malloc(sizeof(Block));
	temp->color = M[i][j].color;
	M[i][j].color = M[i+1][j].color;
	M[i+1][j].color = temp->color;
	temp->blank = M[i][j].blank;
	M[i][j].blank = M[i+1][j].blank;
	M[i+1][j].blank = temp->blank;
	free(temp);
	return(TRUE);
}//function: Move down

Status Checkera(Block ** &M)
{
    int cflag = 0;
    //cflag += CheckBTE(M);
    cflag += CheckRCE(M);
    return(cflag);
}//Basic function: check availability of all kinds of erasing

Status CheckRCE(Block ** &M)
{//Erase according to row & col, just do in one row or col
    int i = 0;
    int j = 0;
    int k = 0;
    int flag = 0;
    int count = 0;
    //printf("Entering RCE part\n");
    for (i=0;i<N;i++)
    {//For every row
        count = 0;//Reset count to 0
        //printf("row # i=%d\n", i);
        for(k=0;k<N-1;k++)
        {//Add count if found same color
            //printf("position k=%d, count=%d\n", k, count);
            if(k+1 >= N or M[i][k].color != M[i][k+1].color)
            {//Reached a different color at k+1 or reached the end
                if(count >= 2)
                {//Three or more same blocks
                    //printf("Elimination at k=%d\n", k);
                    flag += 1;
                    for(;count>=0;count--)
                    {//Eliminate same color blocks
                        //printf("count=%d\n", count);
                        //M[i][k-count].blank = 0;
                    }//End for: count should be -1 now
                    //printf("count=%d, should be -1\n", count);
                }//End if
                count = 0;//reset count, no matter erasing or not
            }//End if: not the same color, reset count
            else
            {//Found same color
                count += 1;
            }//End else: found same color, add 1 to count
        }//End inner for: scanned a whole row
    }//End outer for: scanned every row
    for (j=0;j<N;j++)
    {//For every column
        count = 0;//Reset count to 0
        //printf("column # j=%d\n", j);

        for(k=0;k<N-1;k++)
        {//Add count if found same color
            //printf("position k=%d, count=%d\n", k, count);
            if(k+1 >= N or M[k][j].color != M[k+1][j].color)
            {//Reached a different color at k+1 or reached the end
                if(count >= 2)
                {//Three or more same blocks
                    //printf("Elimination at k=%d\n", k);
                    flag += 1;
                    for(;count>=0;count--)
                    {//Eliminate same color blocks
                        //printf("count=%d\n", count);
                        //M[i][k-count].blank = 0;
                    }//End for: count should be -1 now
                    //printf("count=%d, should be -1\n", count);
                }//End if
                count = 0;//reset count, no matter erasing or not
            }//End if: not the same color, reset count
            else
            {//Found same color
                count += 1;
            }//End else: found same color, add 1 to count
        }//End inner for: scanned a whole column
    }//End outer for: scanned every column
    return(flag);
}//Basic function: check availability of RCE

Status CheckBTE(Block ** &M)
{
    int i = 0;
    int j = 0;
    int flag = 0;
	//printf("Entering BTE part\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
			//printf("Now checking i = %d, j = %d\n", i, j);
            if(i != 0 and i != N-1)
            {
                if(M[i-1][j].color==M[i][j].color and M[i+1][j].color==M[i][j].color)
                {
                    //M[i-1][j].color='-';
                    //M[i][j].color='-';
                    //M[i+1][j].color='-';
                    flag += 1;//No erasing, just flagging up
                }//End inner if: erasing the matching-three
            }//Don't need to check first and last row for row +1 -1
            if(j != 0 and j != N-1)
            {
                if(M[i][j-1].color==M[i][j].color and M[i][j].color==M[i][j+1].color)
                {
                    //M[i][j-1].color='-';
                    //M[i][j].color='-';
                    //M[i][j+1].color='-';
                    flag += 1;//No erasing, just flagging up
                }//End inner if: erasing the matching-three
            }//Don't need to check first and last column for column +1 -1
        }//End inner for
    }//End outer for: scan for the whole map to find all basic three erasing
    //if(flag==0)
    //{
        //return(FALSE);
    //}
    //else
    //{
        //return(flag);
    //}//end if else: FALSE means no erasing, TRUE means one or more erasing
	return(flag);//flag == 0 means FALSE, flags records the number of erasing
}//Basic function: check availability of BTE

Status Undconstr()
{
    printf("ERROR CODE 1: This Function Under Construction! Come back later!\n");
    printf("Thanks for cooperation!\n");
    return(FALSE);
}//function "Under Construction": print a prompt
