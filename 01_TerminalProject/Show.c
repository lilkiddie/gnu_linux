#include <curses.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int len;
    char *p;
} Line;

unsigned int count_lines(FILE* file) {
    unsigned int count = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            count += 1;
        }
    }
    rewind(file);
    return count;
}

void read_file(FILE *file, Line *lines, unsigned int n_lines) {
    char c;
    for (unsigned int i = 0; i < n_lines; i++) {
        size_t size = 0;
        fpos_t pos;
        fgetpos(file, &pos);
        Line line;
        while ((c = fgetc(file)) != '\n') {
            size++;
        }
        line.len = 0;
        line.p = malloc((size + 1) * sizeof(char));
        fsetpos(file, &pos);
        while ((c = fgetc(file)) != '\n') {
            line.p[line.len] = c;
            line.len += 1;
        }
        lines[i] = line;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Required filepath. Terminating.\n");
        return 1;
    }   
    
    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File %s can not be opened. Terminating.\n", filename);
        return 1;
    }

    unsigned int n_lines = count_lines(file);
    Line content[n_lines];

    read_file(file, content, n_lines);
    fclose(file);


    char c;
    WINDOW *win;

    initscr();
    noecho();
    cbreak();

    win = newwin(LINES / 2, COLS / 2, LINES / 3, LINES / 3);
    keypad(win, TRUE);
    wmove(win, 1, 0);

    int height = 0;
    int width = 0;
    getmaxyx(win, height, width);

    char buff[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            buff[i][j] = '\0';
        }
    }

    int offset_l = 0;
    int offset_c = 0;

    while (TRUE) {
        for (int line = offset_l; line < offset_l + height; line++) {
            for (int col = offset_c; col < offset_c + width; col++) {
                if (line >= n_lines || col >= content[line].len) {
                     buff[line - offset_l][col - offset_c] = '\0';
                } else {
                    buff[line - offset_l][col - offset_c] = content[line].p[col];
                }
            }
        }

        for (int line = 0; line < height; line++) {
            mvwprintw(win, line + 1, 1, "%d: %s\n", line + offset_l + 1, buff[line]);
        }

        box(win, 0, 0);
        wrefresh(win);

        c = wgetch(win);
        if (c == 3) { // KEY_UP
            if (offset_l != 0) {
                offset_l--;
            }
        }
        else if (c == 2) { // KEY_DOWN
            offset_l++;
        }
        else if (c == 4) { // KEY_LEFT
            if (offset_c != 0) {
                offset_c--;
            }
        }
        else if (c == 5) { // KEY_RIGHT
            offset_c++;
        }
        else if (c == 27) { // ESC
            break;
        }
    }
    endwin();

    for (int i = 0; i < n_lines; i++) {
        free(content[i].p);
    }
    return 0;
}
