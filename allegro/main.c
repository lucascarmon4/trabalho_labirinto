#include <stdio.h>
#include <stdlib.h>
#include "allegro/include/allegro5/allegro.h"
#include "allegro/include/allegro5/allegro_image.h"
#include "functions.c"
#include <windows.h>

int main() {
    Maze maze;
    Position start;
    int result;

    if (!al_init()) {
        fprintf(stderr, "Falha ao inicializar o Allegro.\n");
        return -1;
    }
    if (!al_init_image_addon()) {
        fprintf(stderr, "Falha ao inicializar Allegro Image Addon.\n");
        return -1;
    }

    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    if (!display) {
        fprintf(stderr, "Falha ao criar tela.\n");
        return -1;
    }

    ALLEGRO_BITMAP *brick_img = al_load_bitmap("brick.png");
    ALLEGRO_BITMAP *rat_img = al_load_bitmap("rat.png");
    ALLEGRO_BITMAP *cheese_img = al_load_bitmap("cheese.png");
    ALLEGRO_BITMAP *path_img = al_load_bitmap("path.png");

    if (!brick_img || !rat_img || !cheese_img || !path_img) {
        fprintf(stderr, "Falha ao carregar uma ou mais imagens.\n");
        al_destroy_display(display);
        return -1;
    }

    loadMaze(&maze, "labirinto.txt");
    if (!validateMaze(&maze)) {
        printf("Labirinto invalido!\n");
        return 1;
    }

    displayMaze(&maze, display, brick_img, rat_img, cheese_img, path_img);
    printf("\nDigite a posicao inicial (x y): ");
    scanf("%d %d", &start.x, &start.y);

    while (!isValidMove(&maze, start.x, start.y)) {
        printf("Posicao inicial invalida!\n");
        printf("Digite a posicao inicial (x y): ");
        scanf("%d %d", &start.x, &start.y);
    }

    result = findExit(&maze, start, display, brick_img, rat_img, cheese_img, path_img);

    if (result) {
        printf("Queijo encontrado!\n");
    } else {
        printf("Nenhum caminho encontrado para o queijo.\n");
    }

    Sleep(10000);

    al_destroy_bitmap(brick_img);
    al_destroy_bitmap(rat_img);
    al_destroy_bitmap(cheese_img);
    al_destroy_bitmap(path_img);
    al_destroy_display(display);
    al_shutdown_image_addon();

    return 0;
}
