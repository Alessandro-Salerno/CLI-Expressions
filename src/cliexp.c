/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>


typedef enum {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    LightGray,
    Gray,
    LightRed,
    LightGreen,
    LightYellow,
    LightBlue,
    LightMagenta,
    LightCyan,
    White
} color_t;


void textcolor(color_t color) {
    printf(
        "\033[38;5;%dm",
        color
    );
}


int find(char *array, char val) {
    int i = 0;
    for (char *cp = array, chr; (chr = *cp); cp++, i++) {
        if (chr == val) {
            return i;
        }
    }

    return -1;
}

bool contains(char *array, char val) {
    return find(array, val) != -1;
}

int evaluate(int val1, int val2, char operand) {
    switch (operand) {
        case '+': return val1 + val2;
        case '-': return val1 - val2;
        case '*': return val1 * val2;
        case '/': return val1 / val2;
    }

    return 0;
}

char *genexp() {
    char operands[] = { '+', '-', '*', '/' };
    int opindex = rand() % sizeof operands;
    char operand = operands[opindex];

    int len1 = rand() % 3 + 1;
    int len2 = rand() % 3 + 1;

    int max1 = pow(10, len1);
    int max2 = pow(10, len2);

    int val1;
    int val2;

    do {
        do {
            val1 = rand() % (max1 - 1) + 1;
            val2 = rand() % (max2 - 1) + 1;
        } while (operand == '/' && val1 % val2 != 0);
    } while (val1 < val2 || val1 * val2 > 1000);

    char *expression = calloc(16, 1);
    sprintf(expression, "%d%c%d=%d", val1, operand, val2, evaluate(val1, val2, operand));

    return expression;
}

bool attempt(char *expression) {
    int val1, val2, r;
    char operand;
    sscanf(expression, "%d%c%d=%d", &val1, &operand, &val2, &r);    // I know this is bad but I don't care
    
    int u1, u2, ur;
    char uop, uexp[16];
    bool wrong = false;
    
    do {
        printf("ATTEMPT ");
        if (wrong) printf("[WRONG RESULT] ");
        printf("-> ");

        scanf("%s", uexp);
        sscanf(uexp, "%d%c%d=%d", &u1, &uop, &u2, &ur);
    } while ((wrong = (evaluate(u1, u2, uop) != ur)));

    if (strcmp(expression, uexp) == 0) {
        printf("\n\nCONGRATULATIONS! YOU WON!\n");
        return true;
    }

    for (char *cp = expression, *up = uexp, cc, uc; (cc = *cp) && (uc = *up); cp++, up++) {
        color_t color = Red;

        if (contains(expression, uc)) color = Yellow;
        if (uc == cc)                 color = Green;

        textcolor(color);
        printf("%c", uc);
        textcolor(White);
    }

    printf("\n\n");
    return false;
}

void printexp(char *expression) {
    printf("EXPRESSION FORMAT: ");
    
    for (char *cp = expression; *cp; cp++) {
        printf("_ ");
    }

    printf("\n\n");
}

int main() {
    srand(time(NULL));
    
    #ifdef WIN32
        system("");
    #endif

    char *expression = genexp();
    printexp(expression);

    for (int i = 0; i < 6 && !attempt(expression); i++);
    
    getchar();
    getchar();
}
