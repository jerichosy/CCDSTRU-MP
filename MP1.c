#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	CCDSTRU MP - Group 34
		SY, MATTHEW JERICHO GO
		ANIVERSARIO, SAMANTHA GRACE SALVADOR
		ARBOLEDA, JOHN PAOLO LUIS ACLAO
*/

typedef char String8[9];

/*
	DISPLAYS THE 4x4 BOARD
*/
void display_Board(char B[4][4]) //for creating the board
{
    int i, j;
    int num = 1;

    printf("\n     |C#1|C#2|C#3|C#4|\n"); //identifies column number
    printf("______________________");

    printf("\n");

    for (i = 0; i < 4; i++)
    {
        printf("Row#%d| ", num);

        for (j = 0; j < 4; j++)
        {
            if (j < 3)
                printf("%c | ", B[i][j]);
            else
                printf("%c |", B[i][j]);
        }

        if (i < 3)
        {
            printf("\n");
            printf("+--------------------+\n");
        }
        num++;
    }
}

/*
	FILLS THE CONTENTS OF THE BOARD WITH BLANK SPACES AND H SPACES
*/
void init_Board(char B[4][4]) {
	int i, j;	
	
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			B[i][j] = ' ';	// Initialize with blank space
			
	// H:{(1,1),(1,2),(1,3),(2,1),(3,1)}

	B[0][0] = 'H';
	B[0][1] = 'H';
	B[0][2] = 'H';
	B[1][0] = 'H';
	B[2][0] = 'H';
}

/*
	COUNTS THE NUMBER OF PIECES ORD HAS ON THE BOARD
	Returns the count.
*/
int count_Ord(char B[4][4]) {
	int i, j;
	int nCount = 0;
	
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if (B[i][j] == 'O')
				nCount++;
				
	return nCount;
}

/*
	CHECKS THE INPUT AND STORES IT IF THERE ARE NO CONFLICTS
	Returns 1 if there are conflicts.
*/
int validate_Input(int posRow, int posCol, char B[4][4], int turn) {
	// CHECK IF SPACE IS H
	if (B[posRow - 1][posCol - 1] == 'H') {
		printf("\nINVALID INPUT! You can't choose an H space.\n");
		return 1;
	}
	// CHECK IF SPACE IS OWNED BY CHA
	else if (B[posRow - 1][posCol - 1] == 'C') {
		if (count_Ord(B) >= 3 && turn == 1)
			printf("\nINVALID INPUT! Cha owns that space! You must choose a space you own.\n");
		else
			printf("\nINVALID INPUT! You must choose a free space.\n");
		return 1;	
	}
	// IF IT'S ORD'S TURN and ORD HAS 3 PIECES ON THE BOARD, ORD MUST CHOOSE AN O SPACE
	else if (count_Ord(B) >= 3 && turn == 1) {
		// CHECKS IF SPACE IS BLANK 
		if (B[posRow - 1][posCol - 1] == ' ') {
			printf("\nINVALID INPUT! You must choose a space you own.\n");
			return 1;
		// IF SPACE IS O, REMOVE THE PIECE
		}
		if (B[posRow - 1][posCol - 1] == 'O')
			B[posRow - 1][posCol - 1] = ' ';
	}
	// CHECK IF SPACE IS OWNED BY ORD
	else if (B[posRow - 1][posCol - 1] == 'O') {
		printf("\nINVALID INPUT! You must choose a free space.\n");
		return 1;
	}
	// ELSE, STORE THE INPUT
	else {
		if (turn == 0)
			B[posRow - 1][posCol - 1] = 'C';
		else
			B[posRow - 1][posCol - 1] = 'O';
	}
		
	return 0;
}

/*
	CHECK IF THERE'S A WINNER and if so, WHO WON
	Returns 1 if there is a winner. Stores who won to the string "result."
*/
int check_Win(char B[4][4], String8 result) {
	/*
	W:{{(1,4),(2,4),(3,4)},
       {(2,2),(3,3),(4,4)},
       {(2,3),(3,2),(4,1)},
	   {(4,2),(4,3),(4,4)}}
	*/

	// CHECK IF CHA WON
	if ( ((B[0][3] == 'C') && (B[1][3] == 'C') && (B[2][3] == 'C')) ||
	     ((B[1][1] == 'C') && (B[2][2] == 'C') && (B[3][3] == 'C')) ||  
		 ((B[1][2] == 'C') && (B[2][1] == 'C') && (B[3][0] == 'C')) ||
		 ((B[3][1] == 'C') && (B[3][2] == 'C') && (B[3][3] == 'C')) ) 
	{
		strcpy(result, "Cha wins");
		return 1; 	
	}
	
	// CHECK IF ORD WON
	int i, j;
	int nCount = 0;
	
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if (B[i][j] == ' ')
				nCount++;
				
	if (nCount == 0) {
		strcpy(result, "Ord wins");
		return 1;
	}
	
	return 0;
}


int main()
{
    char B[4][4] = {}; //to initialize the program for the board
    init_Board(B);
    
    int posRow, posCol;
    int turn = 1;
    int over = 0;
    String8 result;
    
    printf("Game Instructions: \n");
    printf("- There are two players: Cha and Ord. Cha goes first.\n");
    printf("- Cha wins when it completes at least one of the ff. positions:\n\n");
    printf("     |C#1|C#2|C#3|C#4|	     |C#1|C#2|C#3|C#4|	     |C#1|C#2|C#3|C#4|	     |C#1|C#2|C#3|C#4|\n");
    printf("______________________	______________________	______________________	______________________\n");
    printf("Row#1|   |   |   | C |	Row#1|   |   |   |   |	Row#1|   |   |   |   |	Row#1|   |   |   |   |\n");
    printf("+--------------------+	+--------------------+	+--------------------+	+--------------------+\n");
    printf("Row#2|   |   |   | C |	Row#2|   | C |   |   |	Row#2|   |   | C |   |	Row#2|   |   |   |   |\n");
    printf("+--------------------+	+--------------------+	+--------------------+	+--------------------+\n");
    printf("Row#3|   |   |   | C |	Row#3|   |   | C |   |	Row#3|   | C |   |   |	Row#3|   |   |   |   |\n");
    printf("+--------------------+	+--------------------+	+--------------------+	+--------------------+\n");
    printf("Row#4|   |   |   |   |	Row#4|   |   |   | C |	Row#4| C |   |   |   |	Row#4|   | C | C | C |\n\n");
    printf("- If the board has all of its spaces filled and Cha did not complete any winning position, Ord wins.\n");
    printf("- Ord may only have a max of 3 pieces on the board at any time. If Ord already has 3 pieces on\n");
    printf("  the board, Ord must remove a piece and place it on an empty space.\n");
    printf("- No piece may be placed on any H spaces.\n\n");
    // END of instructions
    
    display_Board(B);
    
    do
    {
		turn = !turn;
		// 0 - Cha's turn, 1 - Ord's turn
		// printf("\n\nTurn no: %d", turn);
		printf("\n\nIt's %s turn.\n", turn ? "Ord" : "Cha");
    	
    	// IF ORD ALREADY HAS 3 PIECES ON THE BOARD
		if (count_Ord(B) >= 3 && turn == 1) {
			printf("\nYou already have 3 pieces on the board. Choose a piece to remove.");
			
			do
			{	
    			//GET INPUTS
				do
				{
    				printf("\nEnter row number [1-4]: ");
					scanf("%d", &posRow);
					if (posRow <= 0 || posRow >= 5)
						printf("\nINVALID INPUT! Enter a number from 1-4.\n");
				}while(posRow <= 0 || posRow >= 5);
		
				do
				{
    				printf("\nEnter column number [1-4]: ");
					scanf("%d", &posCol);
					if (posCol <= 0 || posCol >= 5)
						printf("\nINVALID INPUT! Enter a number from 1-4.\n");
				}while(posCol <= 0 || posCol >= 5);
		
			}while(validate_Input(posRow, posCol, B, turn) == 1); // CHECK IF COORDINATE IS VALID - CHANGE THIS!
			
			system("cls");
			display_Board(B);
			printf("\n");
		}
    	
    	// GET INPUTS
    	do
		{	
			do
			{
    			printf("\nEnter row number [1-4]: ");
				scanf("%d", &posRow);
				if (posRow <= 0 || posRow >= 5)
					printf("\nINVALID INPUT! Enter a number from 1-4.\n");
			}while(posRow <= 0 || posRow >= 5);
		
			do
			{
    			printf("\nEnter column number [1-4]: ");
				scanf("%d", &posCol);
				if (posCol <= 0 || posCol >= 5)
					printf("\nINVALID INPUT! Enter a number from 1-4.\n");
			}while(posCol <= 0 || posCol >= 5);
		
		}while(validate_Input(posRow, posCol, B, turn) == 1); // CHECKS IF COORDINATE IS VALID
		
		system("cls");
		display_Board(B);
		
		over = check_Win(B, result); // CHECKS IF THERE'S A WINNER
		
	}while(!over); // LOOP TERMINATES IF GAME IS OVER (OVER = 1)
    
    printf("\n\n%s", result);
    
    
    return 0;
}
