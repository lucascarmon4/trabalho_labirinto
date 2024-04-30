#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <allegro5/allegro.h>
#define MAX_SIZE 20

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position positions[MAX_SIZE * MAX_SIZE];
    int top;
} Stack;

typedef struct {
    int rows, cols;
    char maze[MAX_SIZE][MAX_SIZE];
} Maze;

void initStack(Stack *s);
int isStackEmpty(Stack *s);
void push(Stack *s, Position pos);
Position pop(Stack *s);
void loadMaze(Maze *maze, const char *filename);
int validateMaze(Maze *maze);
int findExit(Maze *maze, Position start, ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *brick_img, ALLEGRO_BITMAP *rat_img, ALLEGRO_BITMAP *cheese_img, ALLEGRO_BITMAP *path_img);
int exploreMaze(Maze *maze, Position start, int visited[MAX_SIZE][MAX_SIZE], ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *brick_img, ALLEGRO_BITMAP *rat_img, ALLEGRO_BITMAP *cheese_img, ALLEGRO_BITMAP *path_img);
void displayMaze(Maze *maze, ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *brick_img, ALLEGRO_BITMAP *rat_img, ALLEGRO_BITMAP *cheese_img, ALLEGRO_BITMAP *path_img);
int isValidMove(Maze *maze, int x, int y);

#endif
