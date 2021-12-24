#include <stdio.h>
#include <unistd.h>


#define ALIVE 1
#define DEAD 0
#define CLEAR "\033[H\033[2J"


/* RULES
 * Any live cell with two or three live neighbours survives.
 * Any dead cell with three live neighbours becomes a live cell.
 * All other live cells die in the next generation. Similarly, all other dead cells stay dead.
 * */

struct game {
    int **cells;
    int rows;
    int columns;
};

void game_init(struct game *game);
void game_read(struct game *game, const char *file_name);
void game_free(struct game *game);
// TODO: expand struct game
// TODO: read map from file



void print_cells(int rows, int cols, int (*cells)[cols]);
void next_generation(int rows, int cols, int (*cells)[cols]);


int main() {
    int cells[][10] = {
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 1, 1, 0, 0, 0, 1, 0, 0, 0 },
            { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
            { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
            { 0, 0, 0, 0, 1, 0, 0, 1, 1, 0 },
            { 0, 0, 0, 1, 1, 0, 0, 0, 1, 1 },
            { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }
    };
    size_t rows = sizeof(cells) / sizeof(cells[0]);
    size_t cols = sizeof(cells[0]) / sizeof(int);

    print_cells((int) rows, (int) cols, cells);
    int generation = 0;
    while (1) {
        printf(CLEAR); // Clear the screen
        printf("Conway's Game of Life!\n");
        printf("Generation %d\n", generation);
        print_cells(rows, cols, cells);
        next_generation(rows, cols, cells);
        generation++;
        usleep(1000000 * 0.3); // update every 0.5 seconds
    }
    return 0;
}

void game_init(struct game *game) {

}

void game_read(struct game *game, const char *file_name) {

}

void game_free(struct game *game) {

}







void print_cells(int rows, int cols, int (*cells)[cols]) {
    printf(" ");
    for (int i = 0; i < cols; i++) {
        printf(" -");
    }
    printf("\n");
    for (int y = 0; y < rows; y++) {
        printf("| ");
        for (int x = 0; x < cols; x++) {
            int cell = cells[y][x];
            printf("%c ", cell == ALIVE ? '0' : ' ');
        }
        printf("|\n");
    }
    printf(" ");
    for (int i = 0; i < cols; i++) {
        printf(" -");
    }
    printf("\n");
}

void next_generation(int rows, int cols, int (*cells)[cols]) {
    int next[rows][cols];
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            next[y][x] = DEAD;
        }
    }

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            const int n_amount = 8;
            int neighbours[][2] = {
                    { x - 1, y },
                    { x + 1, y },
                    { x, y - 1 },
                    { x, y + 1 },
                    { x - 1, y - 1 },
                    { x - 1, y + 1 },
                    { x + 1, y - 1 },
                    { x + 1, y + 1 }
            };

            int alive = 0;
            for (int i = 0; i < n_amount; i++) {
                if (0 <= neighbours[i][0] && neighbours[i][0] < cols && 0 <= neighbours[i][1] && neighbours[i][1] < rows) {
                    // CHECK IF NEIGHBOUR IS ALIVE
                    int x = neighbours[i][0], y = neighbours[i][1];
                    if (cells[y][x] == ALIVE) {
                        alive++;
                    }
                }
            }

            int cell = cells[y][x];
            if (cell == ALIVE && alive < 2) {
                next[y][x] = DEAD;
            } else if (cell == ALIVE && alive > 3) {
                next[y][x] = DEAD;
            } else if (cell == DEAD && alive == 3) {
                next[y][x] = ALIVE;
            } else {
                next[y][x] = cells[y][x];
            }
        }
    }

    // COPY NEXT GENERATION TO ORIGINAL `CELLS`
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            cells[y][x] = next[y][x];
        }
    }
}
