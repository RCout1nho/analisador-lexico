/**
 * @file main.c
 * @author Ricardo Coutinho (ricardo.coutinho@icomp.ufam.edu.br)
 * @author Gabriel Maciel (gabriel.maciel@icomp.ufam.edu.br)
 * @date 2023-01-10
 *
 */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lib/color/color.h"
#include "./lib/token/token.h"
#include "./lib/utils/utils.h"

char prox_char(FILE *file) { return fgetc(file); }

void grava_token_beautify(const char *tipo, char *lexema, bool error) {
    if (error) {
        set_color_red();
    } else {
        set_color_green();
    }
    printf("%s\t", tipo);

    set_color_blue();
    printf("<");

    set_color_white();
    set_bg_color_black();
    printf("%s", lexema);
    set_color_reset();

    set_color_blue();
    printf(">\n");

    set_color_reset();
}

void grava_token(const char *tipo, char *lexema, bool error) {
    printf("%s\t %s\n", tipo, lexema);
}

bool is_skip_char(char ch) { return ch == ' ' || ch == '\t' || ch == '\n' || ch == EOF; }

bool is_identifier(char ch) { return isalpha(ch) || ch == '_' || ch == '$'; }

tupla_token_t analex(char ch, FILE *file) {
    if (is_skip_char(ch)) {
        return build_token(SKIP, "");
    }
    if (is_identifier(ch)) {
        char *lexema = malloc(sizeof(char));
        int i = 0;
        do {
            lexema[i++] = ch;
        } while ((ch = prox_char(file)) != EOF && (isalpha(ch) || isdigit(ch) || ch == '_'));

        ungetc(ch, file);

        lexema[i] = '\0';

        int index = is_palavra_reservada(lexema);

        if (index == -1) {
            return build_token(ID, lexema);
        }

        return build_token(get_palavra_reservada(index).tipo, lexema);
    } else if (isdigit(ch)) {
        char *lexema = malloc(sizeof(char));
        int i = 0;
        bool is_float = false;
        bool is_valid = true;
        char *error = malloc(sizeof(char) * 100);

        do {
            lexema[i++] = ch;
            if (isalpha(ch)) {
                is_valid = false;
                error = ERROR_NUMERIC_TYPE_HAVE_LETTERS;
                break;
            }
            if (ch == '.') {
                if (!is_float)
                    is_float = true;
                else {
                    is_valid = false;
                    error = ERROR_NUMERIC_TYPE_CANNOT_HAVE_MORE_THAN_ONE_POINT;
                    break;
                }
            }

        } while ((ch = prox_char(file)) != EOF && (isdigit(ch) || isalpha(ch) || ch == '.'));

        lexema[i] = '\0';

        if (is_valid) {
            ungetc(ch, file);
            if (is_float) {
                return build_token(NUM_FLOAT, lexema);
            } else {
                return build_token(NUM_INT, lexema);
            }
        }
        return build_token(error, lexema);
    } else if (is_operador_simples(parse_char_to_string(ch)) != -1) {
        char *lexema = malloc(sizeof(char));
        int i = 0;
        bool is_simple_line_comment = false;
        bool is_block_comment = false;
        do {
            if (i >= 1) {
                if (lexema[i - 1] == '/' && ch == '/') {
                    is_simple_line_comment = true;
                    break;
                } else if (lexema[i - 1] == '/' && ch == '*') {
                    is_block_comment = true;
                    break;
                }
                if (ch == '/' || ch == '*') {
                    int index = is_operador(parse_char_to_string(lexema[i - 1]));

                    ungetc(ch, file);

                    if (index != -1) {
                        return build_token(get_operador(index).tipo, lexema);
                    }
                }
            }
            lexema[i++] = ch;
        } while ((ch = prox_char(file)) != EOF &&
                 (is_operador_simples(parse_char_to_string(ch)) != -1));

        ungetc(ch, file);

        lexema[i] = '\0';

        if (is_simple_line_comment) {
            // skiping line
            do {
                ch = prox_char(file);
            } while (ch != '\n' && ch != EOF);
            return build_token(SKIP, " ");
        }

        if (is_block_comment) {
            // skiping block
            do {
                ch = prox_char(file);
                if (ch == '*') {
                    ch = prox_char(file);
                    if (ch == '/') {
                        return build_token(SKIP, "");
                    } else
                        ungetc(ch, file);
                }
            } while (ch != EOF);
            return build_token_with_error(ERROR_COMMENT_WHITOUT_END, "");
        }

        int index = is_operador(lexema);

        if (index != -1) {
            return build_token(get_operador(index).tipo, lexema);
        }

        return build_token_with_error(ERROR_INVALID_OPERAND, lexema);
    } else if (ch == '\'') {
        char *lexema = malloc(sizeof(char));
        int i = 0;
        bool tem_par = false;
        do {
            lexema[i++] = ch;
            if (i > 1 && ch == '\'') {
                tem_par = true;
                break;
            }
        } while ((ch = prox_char(file)) != EOF);
        lexema[i] = '\0';

        if (!tem_par) {
            return build_token_with_error(ERROR_INCOMPLETE_CHAR, lexema);
        }

        if (i <= 3) {
            return build_token(CARACTER, lexema);
        }
        return build_token_with_error(ERROR_TOO_LONG_CHAR, lexema);
    } else if (ch == '"') {
        // reconhece string
        char *lexema = malloc(sizeof(char));
        int i = 0;
        bool tem_par = false;
        do {
            lexema[i++] = ch;
            if (i > 1 && ch == '"') {
                tem_par = true;
                break;
            }
        } while ((ch = prox_char(file)) != EOF);
        lexema[i] = '\0';
        if (!tem_par) {
            return build_token_with_error(ERROR_INCOMPLETE_STRING, lexema);
        }

        return build_token(STRING, lexema);
    } else if (is_sinal_pontuacao(parse_char_to_string(ch)) != -1) {
        char *lexema = malloc(sizeof(char));
        lexema[0] = ch;
        return build_token(get_sinal_pontuacao(is_sinal_pontuacao(lexema)).tipo, lexema);
    }

    return build_token(UNKNOWN_CARACTER, parse_char_to_string(ch));
}

int main(int argc, char **argv) {
    FILE *file = fopen(argv[1], "r");
    int beautify_output = atoi(argv[2]);

    char ch;

    do {
        ch = prox_char(file);
        tupla_token_t token = analex(ch, file);
        if (strcmp(token.tipo, SKIP) != 0) {
            if (beautify_output) {
                grava_token_beautify(token.tipo, token.lexema, token.error);
            } else {
                grava_token(token.tipo, token.lexema, token.error);
            }
        }
    } while (ch != EOF);
    fclose(file);
}