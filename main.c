#include <stdio.h>
#include "functions.h"
// Se for rodar no CodeBlocks, comente a linha acima e descomente a linha abaixo
//  #include "functions.c"

int main() {
    Maze maze;
    Position start;
    int result;

    loadMaze(&maze, "labirinto.txt");

    if (!validateMaze(&maze)) {
        printf("Labirinto invalido!\n");
        return 1;
    }

    displayMaze(&maze);
    printf("\nDigite a posicao inicial (x y): ");
    scanf("%d %d", &start.x, &start.y);

    if (!isValidMove(&maze, start.x, start.y)) {
        printf("Posicao inicial invalida!\n");
        return 1;
    }

    result = findExit(&maze, start);

    if (result) {
        printf("Queijo encontrado!\n");
    } else {
        printf("Nenhum caminho encontrado para o queijo.\n");
    }

    return 0;
}
