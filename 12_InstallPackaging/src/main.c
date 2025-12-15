/**
 * @file main.c
 * @brief Calculator CLI application
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include "libcalc.h"

#define _(String) gettext(String)
#define PACKAGE "calc"

#ifndef LOCALEDIR
#define LOCALEDIR "/usr/local/share/locale"
#endif

void print_usage(const char *prog_name) {
    printf(_("Usage: %s <operation> <num1> <num2>\n"), prog_name);
    printf(_("Operations:\n"));
    printf("  add       - %s\n", _("addition"));
    printf("  sub       - %s\n", _("subtraction"));
    printf("  mul       - %s\n", _("multiplication"));
    printf("  div       - %s\n", _("division"));
    printf("  pow       - %s\n", _("power"));
    printf("\n");
    printf(_("Example: %s add 5 3\n"), prog_name);
}

int main(int argc, char *argv[]) {
    double a, b, result;
    
    /* Setup gettext */
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);
    
    if (argc != 4) {
        print_usage(argv[0]);
        return 1;
    }
    
    a = atof(argv[2]);
    b = atof(argv[3]);
    
    if (strcmp(argv[1], "add") == 0) {
        result = calc_add(a, b);
        printf(_("Result: %.2f + %.2f = %.2f\n"), a, b, result);
    } else if (strcmp(argv[1], "sub") == 0) {
        result = calc_subtract(a, b);
        printf(_("Result: %.2f - %.2f = %.2f\n"), a, b, result);
    } else if (strcmp(argv[1], "mul") == 0) {
        result = calc_multiply(a, b);
        printf(_("Result: %.2f * %.2f = %.2f\n"), a, b, result);
    } else if (strcmp(argv[1], "div") == 0) {
        if (b == 0.0) {
            fprintf(stderr, _("Error: Division by zero!\n"));
            return 1;
        }
        result = calc_divide(a, b);
        printf(_("Result: %.2f / %.2f = %.2f\n"), a, b, result);
    } else if (strcmp(argv[1], "pow") == 0) {
        result = calc_power(a, b);
        printf(_("Result: %.2f ^ %.2f = %.2f\n"), a, b, result);
    } else {
        fprintf(stderr, _("Error: Unknown operation '%s'\n"), argv[1]);
        print_usage(argv[0]);
        return 1;
    }
    
    return 0;
}
