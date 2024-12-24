#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidString(char *str) {
    int length = strlen(str);

    if (length < 2 || str[length-1] != 'b' || str[length-2] != 'b') {
        return 0;
    }

    for (int i = 0; i < length - 2; i++) {
        if (str[i] != 'a') {
            return 0;
        }
    }

    return 1;
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    if (isValidString(str)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }

    return 0;
}
