#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
int findExit(Maze *maze, Position start);
int exploreMaze(Maze *maze, Position start, int visited[MAX_SIZE][MAX_SIZE]);
void displayMaze(Maze *maze);
int isValidMove(Maze *maze, int x, int y);

#endif
