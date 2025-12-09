#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(x) gettext(x)
#define LOCALEDIR "po"

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALEDIR);
    textdomain("guess");

    puts(_("Think of a number between 1 and 100."));

    int left = 1, right = 100;
    char buf[32];
    while (left < right) {
        int mid = (left + right) / 2;
        printf(_("Is it greater than %d? (Yes/No)\n"), mid);

        for (;;) {
            if (!fgets(buf, sizeof buf, stdin)) {
                puts(_("Input closed or error. Try again."));
                continue;
            }
            size_t n = strlen(buf);
            if (n && buf[n-1] == '\n')
                buf[n-1] = 0;

            if (!strcmp(buf, _("Yes"))) { left = mid+1; break; }
            if (!strcmp(buf, _("No")))  { right = mid;  break; }
            puts(_("Please answer with 'Yes' or 'No'."));
        }
    }
    printf(_("I guess your number: %d\n"), left);
    return 0;
}
