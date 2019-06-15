#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
 * Johnny Huang
 * CS 305 HW 2
 * maze.c
*/

maze * create_maze(FILE *in)//takes in maze info as file pointer
{
	maze* new_maze = malloc(sizeof(maze));//allocates maze-sized worth of memory
	
	char* line = malloc(50*sizeof(char));//guarantees 50-char worth of memory to read off of file
	size_t num_read;//holds size of input line
	getline(&line, &num_read, in);//function from stdio.h import, gets contents of first line of file
	
	//v two functions: 1. stores 6 scanned integers in variables, 2. if scanned integers does not amount to 6...
	if(sscanf(line, "%d %d %d %d %d %d", &(*new_maze).height, &(*new_maze).width, &(*new_maze).entry.row, &(*new_maze).entry.col, &(*new_maze).exit.row, &(*new_maze).exit.col)!=6)
	{
		fprintf(stderr, "Maze file format incorrect. Top line must include 6 numbers.\n");//...returns file format error from first line
		return NULL;
	}
	if((*new_maze).height<1||(*new_maze).width<1)//if height or width of maze is scanned to be 0 or less, show error
	{
		fprintf(stderr, "Maze dimension not valid. Either height or width of maze is zero or a negative.\n");
		return NULL;
	}
	if((*new_maze).entry.row<0||(*new_maze).entry.row>(*new_maze).height)//if entry-row is less than 0 or exceeds the height specified, show error
	{
		fprintf(stderr, "Maze parameter not valid. Maze entry row is negative or exceeds maze height.\n");
		return NULL;
	}
	else if((*new_maze).entry.col<0||(*new_maze).entry.col>=(*new_maze).width)//if entry-column is less than 0 or exceeds the specified width, show error. also, entry column must not be equal to width either
	{
		fprintf(stderr, "Maze parameter not valid. Maze entry column is negative or exceeds or is maze width.\n");
		return NULL;
	}
	else if((*new_maze).exit.row<0||(*new_maze).exit.row>(*new_maze).height)//same thing as two if-statements above, but with exit row and column
	{
		fprintf(stderr, "Maze parameter not valid. Maze exit row is negative or exceeds maze height.\n");
		return NULL;
	}
	else if((*new_maze).exit.col<0||(*new_maze).exit.col>(*new_maze).width)
	{
		fprintf(stderr, "Maze parameter not valid. Maze exit column is negative or exceeds maze width.\n");
		return NULL;
	}

	(*new_maze).data = malloc((*new_maze).height*sizeof(char*));//allocates memory for char array in accordance to height
	int i;
	for(i = 0; i<(*new_maze).height; i++)//process done for all rows (height)
	{
		(*new_maze).data[i] = malloc((*new_maze).width*sizeof(char));//allocates memory for char array in accordance to width for every row (height), creates 2d char array to store data
	}
	
	int y;
	for(y = 0; y<(*new_maze).height; y++)//for all rows of data...
	{
	int num_vals_read = getline(&line, &num_read, in);
	
	if(num_vals_read<0)
	{
		fprintf(stderr, "Reached EOF when expecting additional rows.\n");//gives error when short on lines
		return NULL;
	}
		
	if(!(num_vals_read  == (*new_maze).width+1))//if number of characters read does not match with given width, show error
	{
		fprintf(stderr, "Maze file format invalid. Found %d characters when declared width is %d\n", num_vals_read-1, (*new_maze).width);
	}
		
	int x;
	for(x = 0; x<(*new_maze).width; x++)//runs through entire width, sure to scan every char in line
	{
		if(!(line[x] == ' '||line[x] == '*'))//if there exists a symbol not a whitespace or *, show error
		{
			fprintf(stderr, "Maze symbol error. Detected character that is neither whitespace nor asterisk.\n");
			return NULL;
		}
		
		(*new_maze).data[y][x]=line[x];//otherwise, put that char into data
	}

	}//at this point, data of maze is filled with info of file
	
	if(getline(&line, &num_read, in)!=EOF)//if there exists more lines of the maze past its intended height (EOF not detected)
	{
		fprintf(stderr, "Maze row error. Additional maze rows exceeding given maze amount detected.\n");//give error
		return NULL;
	}
	free(line);//line used freed
	return new_maze;//returns the maze along with all the data
}

int solve(int row, int col, maze * the_maze)
{
	if(row<0||row>=(*the_maze).height||col<0||col>=(*the_maze).width)//base cases start here; if solve recursion passes a coordinate out of maze...
	{
		return 0;//...return nothing
	}
	else if((*the_maze).data[row][col]=='*')//if the coordinate point is a wall...
	{
		return 0;//...return nothing
	}
	else if(row==(*the_maze).exit.row&&col==(*the_maze).exit.col)//if the coordinate point matches with the exit, row for row, column to column...
	{
		return 1;//...return a success
	}
	else//if no base case triggered, continue to search further in maze via recursion
	{
	
	(*the_maze).data[row][col]='*';//first, places current coordinate point with * so recursive backtracking never happens and infinite loop never occurs
	return solve(row,col-1,the_maze)||solve(row-1,col,the_maze)||solve(row,col+1,the_maze)||solve(row+1,col,the_maze);//recursively calls four solve functions, passing either a changed row or changed column
	//if any recursive function returns a 1, entire statement will be a 1
	}
}

void free_maze(maze * the_maze)
{
	int free_y;//frees everything mallocd in reverse order
	for(free_y = 0; free_y<(*the_maze).height; free_y++)
	{
		free((*the_maze).data[free_y]);
	}
	free((*the_maze).data);
	free(the_maze);
}

