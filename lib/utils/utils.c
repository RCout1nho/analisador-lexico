#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *parse_char_to_string(char x)
{
    char buffer[2];
    sprintf(buffer, "%c", x);
    char *result = malloc(sizeof(char) * 2);
    strncpy(result, buffer, 2);
    return result;
}