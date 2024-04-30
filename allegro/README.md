### Passo a passo para rodar o programa usando biblioteca gráfica: 

- cd allegro
- gcc -I ./allegro/include -c main.c
- gcc -o labirinto.exe main.o ./allegro/lib/liballegro-5.0.10-monolith-mt.a
- ./labirinto.exe
