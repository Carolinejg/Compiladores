#ifndef LEXICO_H
#define LEXICO_H

#define quantPalavraReservada 12
#define lexe_ma 40

enum PalavraReservada
{
    CARACTER,
    INTEIRO,
    REAL,
    BOOLEANO,
    SEMPARAM,
    SEMRETORNO,
    SE,
    ENQUANTO,
    PARA,
    RETORNE,
    PROTOTIPO,
    SENAO,
    NENHUM,

 };

enum Sinal
{
    PONTO_E_VIRGULA,
    VIRGULA,
    ABRE_CHAVE,
    FECHA_CHAVE,
    ABRE_PARENTESE,
    FECHA_PARENTESE,
    MAIS,
    MENOS,
    OU,
    E,
    IGUAL,
    EXCLAMACAO,
    ATRIBUICAO,
    DIFERENTE,
    MENOR_IGUAL,
    MENOR,
    MAIOR_IGUAL,
    MAIOR,
    ASTERISCO,
    BARRA
};
typedef struct Token
{
    enum Tipo
    {
        ID, /*identificador*/
        PR, /* Palavvra Reservada*/
        SN, /* Sinal*/
        CT_I, /* Contante Inteira*/
        CT_R, /* Contante Real*/
        CT_C, /* Caracter*/
        CT_L, /* constante literal string */
        TOKEN_EOF
    } tipo;

    char lexema[lexe_ma] ;
    enum Sinal codigoSinal;
    enum PalavraReservada codigoPR;
    float valorReal;
    int valorInteiro;
    char valorCaracter;
    int indiceLiteral;
} Token;

Token estado0();
Token Lexico();
extern int contador_linha;

#endif
