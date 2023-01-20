#include <stdbool.h>
#include <string.h>
#include "token.h"

const tupla_token_t tokens_palavras_reservadas[] = {
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

const tupla_token_t tokens_operadores[] = {
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

const tupla_token_t tokens_operadores_simples[] = {
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

const tupla_token_t tokens_sinais_pontuacao[] = {
    {"SP_PRT_A", "("},
    {"SP_PRT_F", ")"},
    {"SP_VIRG", ","},
    {"SP_PT_VIRG", ";"},
    {"SP_CHT_A", "["},
    {"SP_CHT_F", "]"},
    {"SP_CHV_A", "{"},
    {"SP_CHV_F", "}"},
};

tupla_token_t build_token(char *tipo, char *lexema)
{
    tupla_token_t token;
    token.tipo = tipo;
    token.lexema = lexema;
    token.error = false;
    return token;
}

tupla_token_t build_token_with_error(char *tipo, char *lexema)
{
    tupla_token_t token;
    token.tipo = tipo;
    token.lexema = lexema;
    token.error = true;
    return token;
}

int busca_binaria(const tupla_token_t array[], int tam, const char *alvo)
{
    int esq = 0;
    int dir = tam - 1;

    while (esq <= dir)
    {
        int meio = (esq + dir) / 2;
        int comp = strcmp(array[meio].lexema, alvo);

        if (comp == 0)
        {
            return meio;
        }
        else if (comp < 0)
        {
            esq = meio + 1;
        }
        else
        {
            dir = meio - 1;
        }
    }

    return -1;
}

int is_palavra_reservada(char *palavra){
    return busca_binaria(tokens_palavras_reservadas, sizeof(tokens_palavras_reservadas) / sizeof(tokens_palavras_reservadas[0]), palavra);
}

tupla_token_t get_palavra_reservada(int index){
    return tokens_palavras_reservadas[index];
}

int is_operador(char *palavra)
{
    return busca_binaria(tokens_operadores, sizeof(tokens_operadores) / sizeof(tokens_operadores[0]), palavra);
}

tupla_token_t get_operador(int index){
    return tokens_operadores[index];
}

int is_operador_simples(char *palavra)
{
    return busca_binaria(tokens_operadores_simples, sizeof(tokens_operadores_simples) / sizeof(tokens_operadores_simples[0]), palavra);
}

tupla_token_t get_operador_simples(int index){
    return tokens_operadores_simples[index];
}

int is_sinal_pontuacao(char *palavra)
{
    return busca_binaria(tokens_sinais_pontuacao, sizeof(tokens_sinais_pontuacao) / sizeof(tokens_sinais_pontuacao[0]), palavra);
}

tupla_token_t get_sinal_pontuacao(int index){
    return tokens_sinais_pontuacao[index];
}