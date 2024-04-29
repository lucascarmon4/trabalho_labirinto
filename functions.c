#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>


/*
* Função que inicializa a pilha.
*/
void initStack(Stack *s) {
    s->top = -1;
}

/*
* Função que verifica se a pilha está vazia.
* Retorna 1 se a pilha estiver vazia, 0 caso contrário.
*/
int isStackEmpty(Stack *s) {
    return s->top == -1;
}

/*
* Função que insere um elemento no topo da pilha.
* Se a pilha estiver cheia, não faz nada.
*/
void push(Stack *s, Position pos) {
    if (s->top < MAX_SIZE * MAX_SIZE - 1) {
        s->positions[++s->top] = pos;
    }
} 

/*
* Função que remove e retorna o elemento do topo da pilha.
* Se a pilha estiver vazia, retorna uma posição inválida (-1, -1).
*/
Position pop(Stack *s) {
    if (!isStackEmpty(s)) {
        return s->positions[s->top--];
    }
    return (Position){-1, -1};
}

/*
* Função que carrega o labirinto a partir de um arquivo labirinto.txt.
* O arquivo deve ter o seguinte formato:
*   <número de linhas> <número de colunas>
*   <labirinto> (0 para caminho livre, X para parede, S para queijo)
*/
void loadMaze(Maze *maze, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    fscanf(file, "%d %d", &maze->rows, &maze->cols);
    fgetc(file);

    for (int i = 0; i < maze->rows; i++) {
        fgets(maze->maze[i], maze->cols + 2, file); // +2 => inclui o '\n' e o '\0'
        maze->maze[i][maze->cols] = '\0';
    }
    fclose(file);
}

/*
* Função que explora o labirinto a partir de uma posição inicial.
* Retorna 1 se encontrar o queijo, 0 caso contrário.    
*/
int exploreMaze(Maze *maze, Position start, int visited[MAX_SIZE][MAX_SIZE]) {
    Stack path;
    initStack(&path);
    push(&path, start);

    Position lastPosition = {-1, -1}; 

    while (!isStackEmpty(&path)) {
        Position current = pop(&path);

        if (lastPosition.x != -1 && (lastPosition.x != current.x || lastPosition.y != current.y)) {
            if (maze->maze[lastPosition.x][lastPosition.y] == 'R') {
                maze->maze[lastPosition.x][lastPosition.y] = '#';
            }
        }

        if (maze->maze[current.x][current.y] == 'S') {
            maze->maze[current.x][current.y] = 'R';  
            displayMaze(maze);
            return 1;
        }

        maze->maze[current.x][current.y] = 'R';
        displayMaze(maze);
        Sleep(200);

        lastPosition = current; 

        Position adjPositions[4] = {
            {current.x, current.y + 1},
            {current.x + 1, current.y},
            {current.x, current.y - 1},
            {current.x - 1, current.y}
        };

        int validMoveFound = 0;
        for (int i = 0; i < 4; i++) {
            Position next = adjPositions[i];
            if (next.x >= 0 && next.x < maze->rows && next.y >= 0 && next.y < maze->cols &&
                !visited[next.x][next.y] && maze->maze[next.x][next.y] != 'X' && maze->maze[next.x][next.y] != 'R') {
                push(&path, next);
                visited[next.x][next.y] = 1;
                validMoveFound = 1;
            }
        }

        if (!validMoveFound && maze->maze[current.x][current.y] == 'R') {
            maze->maze[current.x][current.y] = 'R';  
        }
    }

    return 0; 
}

/*
* Função que verifica se um movimento é válido.
* Retorna 1 se o movimento é válido, 0 caso contrário.
*/
int isValidMove(Maze *maze, int x, int y) {
    if (x < 0 || x >= maze->rows || y < 0 || y >= maze->cols) return 0;
    char cell = maze->maze[x][y];
    return cell == '0' || cell == 'S';  // Movimento válido se for '0' ou 'S'
}


/*
* Função que valida o labirinto.
* Retorna 1 se o labirinto contém apenas '0', 'X' e 'S' e se há pelo menos uma saída, 0 caso contrário.
*/
int validateMaze(Maze *maze) {
    int foundExit = 0;
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            if (maze->maze[i][j] == 'S') {
                foundExit = 1;
            }
            if (maze->maze[i][j] != '0' && maze->maze[i][j] != 'X' && maze->maze[i][j] != 'S') {
                return 0;
            }
        }
    }
    return foundExit;
}


/*
* Função que encontra a saída do labirinto a partir de uma posição inicial.
* Retorna 1 se encontrar o queijo, 0 caso contrário.
*/
int findExit(Maze *maze, Position start) {
    if (maze->maze[start.x][start.y] == 'X') {
        printf("A posicao inicial esta em uma parede.\n");
        return 0;
    }
    if (maze->maze[start.x][start.y] == 'S') {
        printf("A posicao inicial eh a posicao do queijo!\n");
        maze->maze[start.x][start.y] = 'R';
        displayMaze(maze);
        return 1;
    }

    int visited[MAX_SIZE][MAX_SIZE] = {{0}};
    
    visited[start.x][start.y] = 1; 

    return exploreMaze(maze, start, visited);
}

/*
* Função que exibe o labirinto.
* Não retorna nada.
*/
void displayMaze(Maze *maze) {
    system("cls || clear");

    printf("  ");
    for (int j = 0; j < maze->cols; j++) {
        printf("%d ", j % 10);
    }
    printf("\n");
    for (int i = 0; i < maze->rows; i++) {
        printf("%d ", i % 10);
        for (int j = 0; j < maze->cols; j++) {
            char printChar = maze->maze[i][j];
            if (printChar == '0') {
                printChar = ' ';
            } else if (printChar == 'S') {
                printChar = 'Q';
            }
            printf("%c ", printChar);
        }
        printf("\n");
    }
    fflush(stdout);  // Garante que a saída seja exibida imediatamente
}
