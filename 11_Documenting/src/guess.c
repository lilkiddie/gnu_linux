/**
 * @file guess.c
 * @brief Угадайка чисел с поддержкой римских чисел и двухъязычного --help (gettext)
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <libintl.h>
#include "roman.h"

#define _(x) gettext(x)
#define LOCALEDIR "po"
#define DOMAIN "guess"

int use_roman = 0;

void print_help() {
    puts(_("Usage: number-game [OPTIONS]\n"
           "\n"
           "Options:\n"
           "  -r          Use Roman numerals for the game\n"
           "  -h, --help  Show this help and exit\n"
           "  --help-md   Output help in Markdown format\n"
           "\n"
           "In Roman mode, enter answers using uppercase Roman numerals.\n"));
}

void print_help_md() {
    puts(_("# number-game\n"
           "\n"
           "A simple number-guessing game supporting Roman numerals.\n"
           "\n"
           "## Usage\n"
           "\n"
           "`number-game [OPTIONS]`\n"
           "\n"
           "### Options\n"
           "\n"
           "- `-r` Use Roman numerals for the game\n"
           "- `-h, --help` Show help and exit\n"
           "- `--help-md` Output help in Markdown format\n"
           "\n"
           "In Roman mode, enter answers as uppercase Roman numerals (e.g. LX).\n"));
}

int input_line(char *buf, size_t size) {
    if (!fgets(buf, size, stdin))
        return 0;
    size_t n = strlen(buf);
    if (n && buf[n - 1] == '\n')
        buf[n - 1] = 0;
    return 1;
}

void play_game(int left, int right, int use_roman) {
    char buf[64];
    while (left < right) {
        int mid = (left + right) / 2;
        if (use_roman)
            printf(_("Is it greater than %s? (Yes/No)\n"), arabic_to_roman(mid));
        else
            printf(_("Is it greater than %d? (Yes/No)\n"), mid);

        for (;;) {
            if (!input_line(buf, sizeof(buf))) {
                puts(_("Input closed or error. Try again."));
                continue;
            }
            if (strcmp(buf, _("Yes")) == 0) {
                left = mid + 1;
                break;
            }
            if (strcmp(buf, _("No")) == 0) {
                right = mid;
                break;
            }
            puts(_("Please answer with 'Yes' or 'No'."));
        }
    }
    if (use_roman)
        printf(_("I guess your number: %s\n"), arabic_to_roman(left));
    else
        printf(_("I guess your number: %d\n"), left);
}

int main(int argc, char **argv) {    
    setlocale(LC_ALL, "");
    bindtextdomain(DOMAIN, LOCALEDIR);
    textdomain(DOMAIN);

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-r")) use_roman = 1;
        else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            print_help();
            return 0;
        }
        else if (!strcmp(argv[i], "--help-md")) {
            print_help_md();
            return 0;
        }
        else {
            fprintf(stderr, _("Unknown option: %s\n"), argv[i]);
            print_help();
            return 1;
        }
    }
    if (use_roman)
        puts(_("Think of a number between I and C (that is, from 1 to 100, in Roman numerals)."));
    else
        puts(_("Think of a number between 1 and 100."));

    play_game(1, 100, use_roman);

    return 0;
}
