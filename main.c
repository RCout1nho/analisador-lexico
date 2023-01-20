/**
 * @file main.c
 * @author Ricardo Coutinho (ricardo.coutinho@icomp.ufam.edu.br)
 * @author Gabriel Maciel (gabriel.maciel@icomp.ufam.edu.br)
 * @date 2023-01-10
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
// #include "tokens/tokens_enum.h"
// #include "tokens/operadores.h"

typedef struct Token
{
    char *type;
    char *lexema;
} Token;

const Token tokens_palavras_reservadas[] = {
    {"BOOL", "bool"},
    {"BREAK", "break"},
    {"CHAR", "char"},
    {"CONTINUE", "continue"},
    {"DO", "do"},
    {"ELSE", "else"},
    {"FALSE", "false"},
    {"FLOAT", "float"},
    {"FOR", "for"},
    {"GOTO", "goto"},
    {"IF", "if"},
    {"INT", "int"},
    {"RETURN", "return"},
    {"TRUE", "true"},
    {"VOID", "void"},
    {"WHILE", "while"},
};

const Token tokens_operadores[] = {
    {"OP_EXCL", "!"},
    {"OP_DIF", "!="},
    {"OP_MOD", "%"},
    {"OP_ATRIB_MOD", "%="},
    {"OP_E", "&"},
    {"OP_AND", "&&"},
    {"OP_MULT", "*"},
    {"OP_ATRIB_MULT", "*="},
    {"OP_AD", "+"},
    {"OP_INC", "++"},
    {"OP_ATRIB_AD", "+="},
    {"OP_SUB", "-"},
    {"OP_DEC", "--"},
    {"OP_ATRIB_SUB", "-="},
    {"OP_FECHA_D", "->"},
    {"OP_PT", "."},
    {"OP_DIV", "/"},
    {"OP_ATRIB_DIV", "/="},
    {"OP_2PT", ":"},
    {"OP_MENOR", "<"},
    {"OP_FLECHA_E", "<-"},
    {"OP_MENOR_IGUAL", "<="},
    {"OP_ATRIB", "="},
    {"OP_COMP", "=="},
    {"OP_MAIOR", ">"},
    {"OP_MAIOR_IGUAL", ">="},
    {"OP_QUEST", "?"},
    {"OP_PIPE", "|"},
    {"OP_OR", "||"},
};

const Token tokens_operadores_simples[] = {
    {"OP_EXCL", "!"},
    {"OP_MOD", "%"},
    {"OP_E", "&"},
    {"OP_MULT", "*"},
    {"OP_AD", "+"},
    {"OP_SUB", "-"},
    {"OP_PT", "."},
    {"OP_DIV", "/"},
    {"OP_2PT", ":"},
    {"OP_MENOR", "<"},
    {"OP_ATRIB", "="},
    {"OP_MAIOR", ">"},
    {"OP_QUEST", "?"},
    {"OP_PIPE", "|"},
};

const Token tokens_sinais_pontuacao[] = {
    {"SP_PRT_A", "("},
    {"SP_PRT_F", ")"},
    {"SP_VIRG", ","},
    {"SP_PT_VIRG", ";"},
    {"SP_CHT_A", "["},
    {"SP_CHT_F", "]"},
    {"SP_CHV_A", "{"},
    {"SP_CHV_F", "}"},
};

#define NUM_INT "NUM_INT"     // numero
#define NUM_FLOAT "NUM_FLOAT" // numero.numero
#define CARACTER "CARACTER"   // 'c'
#define STRING "STRING"       // "string"
#define ID "ID"               // identificador

int binary_search(const Token array[], int size, const char *target)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;
        int comparison = strcmp(array[middle].lexema, target);

        if (comparison == 0)
        {
            return middle;
        }
        else if (comparison < 0)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return -1;
}

int is_palavra_reservada(char *lexema)
{
    return binary_search(tokens_palavras_reservadas, sizeof(tokens_palavras_reservadas) / sizeof(tokens_palavras_reservadas[0]), lexema);
}

int is_operador(char *lexema)
{
    return binary_search(tokens_operadores, sizeof(tokens_operadores) / sizeof(tokens_operadores[0]), lexema);
}

int is_operador_simples(char *lexema)
{
    return binary_search(tokens_operadores_simples, sizeof(tokens_operadores_simples) / sizeof(tokens_operadores_simples[0]), lexema);
}

int is_sinal_pontuacao(char *lexema)
{
    return binary_search(tokens_sinais_pontuacao, sizeof(tokens_sinais_pontuacao) / sizeof(tokens_sinais_pontuacao[0]), lexema);
}

char *parse_char_to_string(char x) {
    char buffer[2];
    sprintf(buffer, "%c", x);
    char *result = malloc(sizeof(char)*2);
    strncpy(result, buffer, 2);
    return result;
}

char prox_char(FILE *file)
{
    return fgetc(file);
}

void grava_token(const char *token, char *lexema)
{
    printf("%s %s\n", token, lexema);
}

Token analex(char ch, FILE *file)
{
    // if (ch == ' ' || ch == '\t' || ch == '\n')
    // {
    //     Token token = {"ESPACO", " "};
    //     return token;
    // }
    if (isalpha(ch) || ch == '_' || ch == '$')
    {
        // reconehce se começar com letra ou _ ou $
        char *lexema = malloc(sizeof(char));
        int i = 0;
        do
        {
            lexema[i++] = ch;
        } while ((ch = prox_char(file)) != EOF && (isalpha(ch) || isdigit(ch) || ch == '_'));
        // ungetc(ch, file);
        lexema[i] = '\0';

        int index = is_palavra_reservada(lexema);

        if (index == -1)
        {
            Token token = {ID, lexema};
            return token;
        }

        Token token = {tokens_palavras_reservadas[index].type, lexema};
        return token;
    }
    else if (isdigit(ch))
    {
        // reconhece: inteiro
        // falta reconhecer: float
        char *lexema = malloc(sizeof(char));
        int i = 0;
        do
        {
            lexema[i++] = ch;
        } while ((ch = prox_char(file)) != EOF && isdigit(ch));
        // ungetc(ch, file);
        lexema[i] = '\0';
        Token token = {NUM_INT, lexema};
        return token;
    }
    else if (is_operador_simples(&ch) != -1)
    {
        // reconhece os operadores
        char *lexema = malloc(sizeof(char));
        int i = 0;
        do
        {
            lexema[i++] = ch;
        } while ((ch = prox_char(file)) != EOF && (is_operador_simples(&ch) != -1));
        ungetc(ch, file);
        lexema[i] = '\0';

        int index = is_operador(lexema);

        if (index != -1)
        {
            Token token = {tokens_operadores[index].type, lexema};
            return token;
        }

        Token token = {"ERROR", lexema};
        return token;
    }
    else if (ch == '\'')
    {
        // reconhece caracter
        char *lexema = malloc(sizeof(char));
        int i = 0;
        bool tem_par = false;
        do
        {
            lexema[i++] = ch;
            if(i > 1 && ch == '\'' ) {
                tem_par = true;
                break;
            }
        } while ((ch = prox_char(file)) != EOF);
        // ungetc(ch, file);
        lexema[i] = '\0';
        if(i <= 3){
            Token token = {CARACTER, lexema};
            return token;
        }
        if(!tem_par){
            Token token = {"ERRO: char incompleto", lexema};
            return token;
        }
        Token token = {"ERRO: char maior que o permitido", lexema};
        return token;
    }else if(ch == '"'){
        // reconhece string
        char *lexema = malloc(sizeof(char));
        int i = 0;
        bool tem_par = false;
        do
        {
            lexema[i++] = ch;
            if(i > 1 && ch == '"' ) {
                tem_par = true;
                break;
            }
        } while ((ch = prox_char(file)) != EOF);
        // ungetc(ch, file);
        lexema[i] = '\0';
        if(!tem_par){
            Token token = {"ERRO: string incompleta", lexema};
            return token;
        }

        Token token = {STRING, lexema};
        return token;
    }else if(is_sinal_pontuacao(parse_char_to_string(ch)) != -1){
        char *lexema = malloc(sizeof(char));
        lexema[0] = ch;
        // ungetc(ch, file);
        Token token = {tokens_sinais_pontuacao[is_sinal_pontuacao(lexema)].type, lexema};
        return token;
    }

    // printf("--> '%c' is_sinal: %d\n", ch, is_sinal_pontuacao(&ch));

    Token token = {"SKIP", " "};
    return token;
}

int main(int argc, char **argv)
{
    FILE *file = fopen(argv[1], "r");

    char ch;

    do
    {
        ch = prox_char(file);
        Token token = analex(ch, file);
        if (strcmp(token.type, "ESPACO") != 0 && strcmp(token.type, "SKIP") != 0)
        {
            grava_token(token.type, token.lexema);
        }
    } while (ch != EOF);
    fclose(file);
    // char ch = ')';
    // printf("%d\n", is_sinal_pontuacao(&ch));
}