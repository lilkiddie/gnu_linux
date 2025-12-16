#include <stdio.h>
#include <stdlib.h>

#define N 6
#define MAP_SIZE (2 * N + 1)

typedef struct {
    int x, y;
} Point;

char map[MAP_SIZE][MAP_SIZE];

void init_map() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (i % 2 == 0 || j % 2 == 0) {
                map[i][j] = '#';
            } else {
                map[i][j] = '.';
            }
        }
    }
}

int is_valid(int x, int y) {
    return x > 0 && x < MAP_SIZE - 1 && y > 0 && y < MAP_SIZE - 1;
}

void carve_passage(Point from, Point to) {
    int dx = (to.x - from.x) / 2;
    int dy = (to.y - from.y) / 2;
    map[from.x + dx][from.y + dy] = '.';
    map[to.x][to.y] = '.';
}

void generate_maze() {
    int visited[N][N] = {0};
    Point stack[N * N];
    int stack_size = 0;

    Point current = {1, 1};
    visited[0][0] = 1;
    stack[stack_size++] = current;

    while (stack_size > 0) {
        Point neighbors[4];
        int neighbors_count = 0;

        Point directions[] = {
            {current.x + 2, current.y}, {current.x - 2, current.y},
            {current.x, current.y + 2}, {current.x, current.y - 2}
        };

        for (int i = 0; i < 4; i++) {
            int nx = directions[i].x;
            int ny = directions[i].y;

            if (is_valid(nx, ny) && !visited[(nx - 1) / 2][(ny - 1) / 2]) {
                neighbors[neighbors_count++] = (Point){nx, ny};
            }
        }

        if (neighbors_count > 0) {
            Point next = neighbors[rand() % neighbors_count];
            carve_passage(current, next);
            current = next;
            visited[(current.x - 1) / 2][(current.y - 1) / 2] = 1;
            stack[stack_size++] = current;
        } else {
            current = stack[--stack_size];
        }
    }
}

void print_map() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    init_map();
    generate_maze();
    print_map();
    return 0;
}
