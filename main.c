/* Author: Tammy VanDeGrift
   CS 305 Spring 2018
   Homework 2: mazes
   This is the main function: it opens the file specified at the command line,
   creates a maze object, and determines if the maze is solvable.
   DO NOT EDIT
*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

#define NUM_PARAMS 2

/* prototype */
void usage(char * executable);

/* main
   executable_name input_filename.txt
   opens input_filename.txt for reading
   creates maze object
   runs the maze solver
   frees maze
*/  
int main(int argc, char * argv[]) {
  if(argc != NUM_PARAMS) {
    usage(argv[0]);
    return EXIT_FAILURE;
  }    
  
  // open file for reading
  FILE *fp = NULL;
  fp = fopen(argv[1], "r");
  if(fp == NULL) {
    fprintf(stderr, "Error opening input file %s. Exiting.\n", argv[1]);
    return EXIT_FAILURE;
  }
  
  // create new maze object
  maze *the_maze = create_maze(fp);
  
  // check maze to see if it was created successfully
  if(the_maze == NULL) {
    return EXIT_FAILURE;
  }

  // done with file at this point
  fclose(fp);
  fp = NULL;
  
  // run the solve function from the maze entry position
  int can_solve = solve(the_maze->entry.row, the_maze->entry.col, the_maze);
  if(can_solve == 0) {
    printf("Maze cannot be solved.\n");
  } else {
    printf("Maze can be solved.\n");
  }

  // free memory and exit
  free(the_maze);
  return EXIT_SUCCESS;
}

/* usage
   prints error message to user
*/
void usage(char * executable) {
  printf("Usage: \n%s maze_file.txt\n", executable);
}
