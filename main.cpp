#include "fads.h"

//using namespace std;
//Trying to comment namespace out

int main()
{//Entering the main function
	char buffer[80] = "";
    char option = '0';
	int i = 0;
    while(1)
    {
		//printf("%d", 1234567890);
		//printf("%d", 1234567890);
		//printf("%d", 1234567890);
		//printf("%d", 1234567890);
		//printf("%d", 1234567890);
		//printf("%d", 1234567890);
		//printf("%d", 1234567890);
		//printf("%d", 1234567890);
		//printf("%d", 1234567890);
		//printf("%d", 1234567890);
		printf("\n");
        printf("Main Menu\n");
		printf("\n");
        printf("(N)ew Game\n");
        printf("(L)oad Game\n");
        printf("(E)xit\n");
		//printf("\n");
		//printf("\n");
		//printf("\n");
		//printf("\n");
		//printf("\n");
		//printf("\n");
		//printf("\n");
		//printf("\n");
		scanf("%s", buffer);
        //scanf("%c", &option);
		while(buffer[i] < '0' or buffer[i] > 'z')
		{
			i += 1;
		}//End while: move i to the first normal char
		option = buffer[i];
		if(option < '0' or option > 'z')
		{
			printf("ERROR CODE 5: Illegal input!\n");
			exit(ERROR);
		}//End if: check again to avoid invalid input
        //getchar();//This getchar() is important.
        //I think this will get the "Enter" after the option you typed here
        //so it makes no mistake in your next cycle or option
		//But I used another way to solve it here.
		//Use buffer to get the string, and get the first char
        switch(option)//we need to make a choice
        {
            case 'N':
                if(Game()==ERROR)
                {
                    printf("ERROR CODE 0: Main game function error.\n");
                    exit(ERROR);
                }//end if: main game function called
                break;
            case 'L': Undconstr(); break;
            case 'E': exit(OK);
            default :
                printf("Unknown option. Try again!\n");
                //getchar();
                break;
        }//end switch
    }//end while: end of main menu
    return 0;
}
