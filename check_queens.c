////////////////////////////////////////////////////////////////////////////////
// Main File:        Check_queens.c
// This File:        check_queens.c
// Other Files:      Check2.txt, check3.txt, check4.txt
// Semester:         CS 354 Fall 2018
//
// Author:           Erik Umhoefer
// Email:            ejumhoefer@wisc.edu
// CS Login:         umhoefer
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
//					https://en.cppreference.com/w/c/memory/malloc
//					https://www.tutorialspoint.com/cprogramming/c_error_handling.htm
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>   

char *COMMA = ",";

/* COMPLETED:
 * Retrieves from the first line of the input file,
 * the number of rows and columns for the board.
 * 
 * fp: file pointer for input file
 * rows: pointer to number of rows
 * cols: pointer to number of columns
 */
void get_dimensions(FILE *fp, int *rows, int *cols) {     
	char *line = NULL; 
	size_t len = 0;
	if (getline(&line, &len, fp) == -1) { 
		printf("Error in reading the file\n");
		exit(1); 
	}

	char *token = NULL; 
	token = strtok(line, COMMA);
	*rows = atoi(token); 

	token = strtok(NULL, COMMA); 
	*cols = atoi(token);
}      


/* TODO:
 * Returns 1 if and only if there exists at least one pair
 * of queens that can attack each other.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * rows: number of rows
 * cols: number of columns
 */
int check_queens(int **board, int rows, int cols) {           
	int canAttack = 0;

	//Navigates through each element of the 2D array
	for(int row = 0; row < rows; row++)
	{
		for(int col = 0; col < cols; col++)
		{	

			//Found a queen, compare to other elements
			if( *(*(board+row) + col) == 1)
			{

				//Checks for a match horizontal to the current element
				 for(int i = row, j = 0; j < cols; j++)
				 {
				 	//If element is a new queen horizontal to the previous queen, return 1
				 	if(j != col && *(*(board+i)+j) == 1)
				 	{
				 		return 1;
				 	}
				 }

				 //Check for a match vertical to the current element
				 for(int i = 0, j = col; i < rows; i++)
				 {
				 	//If element is a new queen vertical to the previous queen, return 1
				 	if(i != row && *(*(board+i)+j) == 1)
				 	{
				 		return 1;
				 	}
				 		
				 }

				 //Check for a match diagonal to the current element
				 for(int i = row, j = col; i < rows && j < cols; i++,j++)
				 {
				 	//If element is a new queen diagonal to the previous queen, return 1
				 	if(i != row && j != col && *(*(board+i)+j) == 1)
				 		return 1;
				 }
				 for(int i = row, j = col; i < rows && j < cols; i++,j--)
				 {
				 	//If element is a new queen diagonal to the previous queen, return 1
				 	if(i != row && j != col && *(*(board+i)+j) == 1)
				 		return 1;
				 }
			}
			
		}
	}

	return canAttack; //1 if a pair of queens were found to attack each other, otherwise 0
}     


/* PARTIALLY COMPLETED:
 * This program prints true if the input file has any pair
 * of queens that can attack each other, and false otherwise
 * 
 * argc: CLA count
 * argv: CLA value 
 */
int main(int argc, char *argv[]) {                

 	//Check if number of command-line arguments is correct.
 	//If not, print an error message and exit. 
	if(argc != 2)
	{
		printf("Usage: ./check_queens <input_filename>\n");
		exit(1);
	}

	//Open the file and check if it opened successfully.
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("Cannot open file for reading\n");
		exit(1);
	}


        //Declare local variables.
		//Rows is the number of rows in the board, cols is the number of columns in the board
        int rows, cols;


        //Call get_dimensions to retrieve the board dimensions.
        get_dimensions(fp, &rows, &cols);


        //Dynamically allocate a 2D array of dimensions retrieved above.
		int **board;
		board = malloc(sizeof(int *) * rows);
		if(board == NULL)	//Malloc did not allocate memory correctly
		{
			printf("Board Memory Allocation Error; Exiting\n");
			exit(1);
		}
		for(int x = 0; x < rows; x++)
		{
			board[x] = malloc(sizeof(int) * cols); //Allocating 2D array of arrays
			if(board[x] == NULL)	//Malloc did not allocate memory correctly
			{
				printf("Board Memory Allocation Error; Exiting\n");
				exit(1);
			}
		}



	//Read the file line by line.
	//Tokenize each line wrt comma to store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < rows; i++) {

		if (getline(&line, &len, fp) == -1) {
			printf("Error while reading the file\n");
			exit(1);	
		}

		token = strtok(line, COMMA);

		for (int j = 0; j < cols; j++) {
            
            //initialize 2D Array with address arithmetic
			*(*(board+i) + j) = atoi(token);	
			token = strtok(NULL, COMMA);

		}

	}



	//Call the function check_queens and print the appropriate
        //output depending on the function's return value.
       if(check_queens(board, rows, cols) == 1)
       {
       		printf("True\n"); //Exists a pair of queens that can attack, print true
       }
       else
       	printf("False\n");	//No pair of queens that can attack, print false
	
        
	//Free all dynamically allocated memory.
    for(int i = 0; i < rows; i++)
    	free(*(board+i));
    free(board);
    board = NULL;

	//Close the file.
	if (fclose(fp) != 0) {
		printf("Error while closing the file\n");
		exit(1);	
	}

	return 0;
}    
