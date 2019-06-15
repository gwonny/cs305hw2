/* Author: Tammy VanDeGrift
   CS 305 Homework 2
   Mazes
   Header file maze.h
   defines coord and maze structs and function prototypes on mazes
   DO NOT MODIFY
*/
#ifndef MAZE_H
#define MAZE_H

/* struct definition for coord */
typedef struct coord {
  int row;
  int col;
} coord;

/* struct definition for maze */
typedef struct maze {
  coord entry;
  coord exit;
  int width;
  int height;
  char ** data;
} maze;

/* prototypes */
maze * create_maze(FILE *in);
int solve(int row, int col, maze * the_maze);
void free_maze(maze * the_maze);
#endif
