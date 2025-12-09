#include "roman.h"
#include <string.h>
#include <stdlib.h>

static const struct { int value; const char *roman; } roman_table[] = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
    {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
};

static char roman_buffer[32];

const char* arabic_to_roman(int n) {
    if(n < 1 || n > 3999) return NULL;
    roman_buffer[0] = 0;
    int i = 0, p = 0;
    while(n > 0) {
        while(n >= roman_table[i].value) {
            strcpy(roman_buffer + p, roman_table[i].roman);
            p += strlen(roman_table[i].roman);
            n -= roman_table[i].value;
        }
        i++;
    }
    roman_buffer[p] = 0;
    return roman_buffer;
}

int roman_to_arabic(const char* s) {
    if(!s || !*s) return 0;
    int n = 0;
    unsigned len = strlen(s);
    for(unsigned i = 0; i < len; ) {
        int matched = 0;
        for(int j = 0; j < (int)(sizeof(roman_table)/sizeof(roman_table[0])); ++j) {
            size_t l = strlen(roman_table[j].roman);
            if(strncmp(s + i, roman_table[j].roman, l) == 0) {
                n += roman_table[j].value;
                i += l;
                matched = 1;
                break;
            }
        }
        if (!matched) return 0;
    }
    if(strcmp(arabic_to_roman(n), s) != 0) return 0;
    return n;
}
