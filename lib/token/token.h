#define NUM_INT "NUM_INT"     // numero
#define NUM_FLOAT "NUM_FLOAT" // numero.numero
#define CARACTER "CARACTER"   // 'c'
#define STRING "STRING"       // "string"
#define ID "ID"               // identificador
#define SKIP "SKIP"           // skip

/* Mensagens de erro */
#define ERROR_NUMERIC_TYPE_HAVE_LETTERS "ERRO: um tipo numérico não pode conter letras"
#define ERROR_NUMERIC_TYPE_CANNOT_HAVE_MORE_THAN_ONE_POINT "ERRO: um tipo numérico não pode conter mais de um ponto"
#define ERROR_COMMENT_WHITOUT_END "ERRO: comentário sem fim"
#define ERROR_INVALID_OPERAND "ERRO: operando inválido"
#define ERROR_INCOMPLETE_CHAR "ERRO: char incompleto, está faltando o fechamendo com '"
#define ERROR_TOO_LONG_CHAR "ERRO: char maior que o permitido"
#define ERROR_INCOMPLETE_STRING "ERRO: string incompleta, está faltando o fechamendo com \""
#define UNKNOWN_CARACTER "ERRO: Caracter não reconhecido"

typedef struct tupla_token_t
{
    char *tipo;
    char *lexema;
    bool error;
} tupla_token_t;

tupla_token_t build_token(char *tipo, char *lexema);
tupla_token_t build_token_with_error(char *tipo, char *lexema);

int is_palavra_reservada(char *palavra);
tupla_token_t get_palavra_reservada(int index);

int is_operador(char *palavra);
tupla_token_t get_operador(int index);

int is_operador_simples(char *palavra);
tupla_token_t get_operador_simples(int index);

int is_sinal_pontuacao(char *palavra);
tupla_token_t get_sinal_pontuacao(int index);