#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include "LEXICO.h"
#include "anasin.h"


int retorno;
int contador_linha = 1;

char palavrasReservadas[quantPalavraReservada][11];

void inicializarTabelaDePR()
{

    strcpy(palavrasReservadas[CARACTER], "caracter");
    strcpy(palavrasReservadas[INTEIRO], "inteiro");
    strcpy(palavrasReservadas[REAL], "real");
    strcpy(palavrasReservadas[BOOLEANO], "booleano");
    strcpy(palavrasReservadas[SEMPARAM], "semparam");
    strcpy(palavrasReservadas[SEMRETORNO], "semretorno");
    strcpy(palavrasReservadas[SE], "se");
    strcpy(palavrasReservadas[ENQUANTO], "enquanto");
    strcpy(palavrasReservadas[PARA], "para");
    strcpy(palavrasReservadas[RETORNE], "retorne");
    strcpy(palavrasReservadas[PROTOTIPO], "prototipo");
    strcpy(palavrasReservadas[SENAO], "senao");
}

enum PalavraReservada verificarPR(char* lexema)
{
    int i;
    for(i=0;i<quantPalavraReservada;i++)
    {
        /*printf("%d - %s - %s\n", i, palavrasReservadas[i], lexema);*/

        if(strcmp(lexema,palavrasReservadas[i]) == 0)
        {
            return i;
        }
    }
    return NENHUM;
}

FILE * abrirArquivo(char nomeArquivo[])
{
    FILE *arq;

	if ( (arq = fopen(nomeArquivo,"r")) != NULL )
	{
        printf("Arquivo aberto com sucesso!\n");
        return arq;
    }
    else
    {
        printf("Erro ao abrir o arquivo\n");
        system("PAUSE");
        return NULL;
    }
}

FILE *arquivo;

int letraDigitoUnderline(int c)
{
    switch (c)
    {
        case 'a'...'z':
        case 'A'...'Z':
        case '0'...'9':
        case '_':
            return 1;
        default:
            return 0;
    }
}

int digito(int c)
{
    switch(c)
    {
        case '0'...'9':
        return 1;
        default: return 0;
    }
}


int ponto_e_virgula(int c)
{
    switch(c)
    {
        case ';':
        return 1;
        default: return 0;

    }
}
Token estado1(char primeiroChar)
{
    char lexema[lexe_ma];
    lexema[0] = primeiroChar;
    int i = 1;

     retorno= fgetc(arquivo);

    while (letraDigitoUnderline(retorno))
    {
        lexema[i] = retorno;
        i++;
        retorno= fgetc(arquivo);
    }
    lexema[i]= '\0';

    enum PalavraReservada codigoPR = verificarPR(lexema);

    if (codigoPR == NENHUM)
    {
        Token token;
        token.tipo = ID;
        strcpy(token.lexema, lexema);
        return token;
    }
    else
    {
        Token token;
        token.tipo = PR;
        token.codigoPR = codigoPR;
        return token;
    }
}
Token estado2(char primeiroChar)
{
    char numero[lexe_ma];
    memset(numero, 0, lexe_ma);
    numero [0] = primeiroChar;
    int i = 1;
    int param=0;

    retorno = fgetc(arquivo);

    while (digito(retorno))
    {
        numero [i] = retorno;
        i++;
        retorno = fgetc(arquivo);
    }
    if(retorno=='.')
    {
        numero[i]='.';
        i++;
        param=1;
        retorno = fgetc(arquivo);
        if(digito(retorno))
        {
            while (digito(retorno))
            {
                numero [i] = retorno;
                i++;
                retorno = fgetc(arquivo);
            }
        }
        else
        {
            printf("Erro!\n");
            exit(1);
        }

    }

    numero[i]= '\0';
    if(param==0)
    {
        Token token;
        token.tipo = CT_I;
        token.valorInteiro = atoi(numero);
        return token;
    }
    else
    {
        Token token;
        token.tipo=CT_R;
        token.valorReal = atof(numero);
        /*printf("%s\n",numero);*/
        return token;
    }
}
Token estado3()
{
    Token token;
    token.tipo=SN;
    token.codigoSinal=PONTO_E_VIRGULA;
    retorno=fgetc(arquivo);
    return token;
}
Token estado4()
{
    Token token;
    retorno=fgetc(arquivo);
    if(retorno=='*')
    {
        int flag=0;
        while(1)
        {
            retorno=fgetc(arquivo);
            if(retorno=='*')
            {
                flag=1;

            }
            else if(retorno=='/')
            {
                if(flag==1)
                {
                    break;
                }
            }
            else
            {
                flag=0;
                if(retorno=='\n')
                {
                    contador_linha=contador_linha+1;
                }
            }
        }
        return estado0();
    }
    else
    {
       token.tipo=SN;
       token.codigoSinal=BARRA;
       return token;

    }
}

Token estado5()
{
    retorno=fgetc(arquivo);

    if(retorno=='\\')/* se for (\)*/
    {
        retorno=fgetc(arquivo);

        if(retorno=='0')
        {
            retorno=fgetc(arquivo);
            if(retorno=='\'')
            {
                Token token;
                token.tipo=CT_C;
                token.valorCaracter='\0';
                return token;
            }
             else
            {
             printf("Erro esperado  apostrofo \n");
             exit(1);
            }
         }
         if(retorno=='n')
         {
            retorno=fgetc(arquivo);
            if(retorno=='\'')
            {
               Token token;
               token.tipo=CT_C;
               token.valorCaracter='\n';
               return token;
            }
         }

         else
         {
             printf("Erro esperado  apostrofo \n");
             exit(1);
         }
    }

    if(isprint(retorno))/*pra saber se é imprimivel 5.1*/
    {
        char result=retorno;
        /*printf("%c\n",result);*/
        retorno=fgetc(arquivo);
        if(retorno=='\'')
        {
            retorno=fgetc(arquivo);
            Token token;
            token.tipo=CT_C;
            token.valorCaracter=result;
            return token;
        }
        else
        {
            printf("Erro: Esperado um apostrofo\n");
            exit(1);
        }

    }
    else
    {
        printf("Erro leu so um apostrofo\n");
        exit(1);
    }

}
Token estado6()
{
    retorno=fgetc(arquivo);
    if(retorno=='|')
    {
        Token token;
        token.tipo=SN;
        token.codigoSinal=OU;
        retorno=fgetc(arquivo);
        return token;
    }
    else
    {
        printf("Erro na formação do ou\n");
        exit(1);
    }
}
Token estado7()
{
    Token token;
    token.tipo=SN;
    token.codigoSinal=VIRGULA;
    retorno=fgetc(arquivo);
    return token;
}
Token estado8()
{
    Token token;
    token.tipo=SN;
    token.codigoSinal=ABRE_CHAVE;
    retorno=fgetc(arquivo);
    return token;
}
Token estado9()
{
    Token token;
    token.tipo=SN;
    token.codigoSinal=FECHA_CHAVE;
    retorno=fgetc(arquivo);
    return token;
}
Token estado10()
{
    Token token;
    token.tipo=SN;
    token.codigoSinal=ABRE_PARENTESE;
    retorno=fgetc(arquivo);
    return token;
}
Token estado11()
{
    Token token;
    token.tipo=SN;
    token.codigoSinal=FECHA_PARENTESE;
    retorno=fgetc(arquivo);
    return token;
}
Token estado12()
{
    Token token;
    token.tipo=SN;
    token.codigoSinal=MAIS;
    retorno=fgetc(arquivo);
    return token;
}
Token estado13()
{
    Token token;
    token.tipo=SN;
    token.codigoSinal=MENOS;
    retorno=fgetc(arquivo);
    return token;
}
Token estado14()
{
    retorno=fgetc(arquivo);
    if(retorno=='=')
    {
        Token token;
        token.tipo=SN;
        token.codigoSinal=DIFERENTE;
        retorno=fgetc(arquivo);
        return token;
    }
    else
    {
        Token token;
        token.tipo=SN;
        token.codigoSinal=EXCLAMACAO;
        retorno=fgetc(arquivo);
        return token;
    }

}
Token estado15()
{
    retorno=fgetc(arquivo);
    if(retorno=='&')
    {
        Token token;
        token.tipo=SN;
        token.codigoSinal=E;
        retorno=fgetc(arquivo);
        return token;
    }
    else
    {
        printf("Erro na formação do E\n");
        exit(1);
    }
}
Token estado16()
{
    retorno=fgetc(arquivo);
    if(retorno=='=')
    {
        Token token;
        token.tipo=SN;
        token.codigoSinal=IGUAL;
        retorno=fgetc(arquivo);
        return token;
    }
    else
    {
        Token token;
        token.tipo=SN;
        token.codigoSinal=ATRIBUICAO;
        return token;
    }

}
Token estado17()
{
    retorno=fgetc(arquivo);
    if(retorno=='=')
    {
        Token token;
        token.tipo=SN;
        token.codigoSinal=MAIOR_IGUAL;
        retorno=fgetc(arquivo);
        return token;
    }
    else
    {
        Token token;
        token.tipo=SN;
        token.codigoSinal=MAIOR;
        retorno=fgetc(arquivo);
        return token;
    }
}
Token estado18()
{
    retorno=fgetc(arquivo);
    if(retorno=='=')
    {
        Token token;
        token.tipo=SN;
        token.codigoSinal=MENOR_IGUAL;
        retorno=fgetc(arquivo);
        return token;
    }
    else
    {
        Token token;
        token.tipo=SN;
        token.codigoSinal=MENOR;
        retorno=fgetc(arquivo);
        return token;
    }
}
Token estado19()
{
    Token token;
    token.tipo=SN;
    token.codigoSinal=ASTERISCO;
    retorno=fgetc(arquivo);
    return token;
}

Token estado20(char primeiroChar)
{
    Token token;
    char qualquerCoisa [500];
    qualquerCoisa[0]=primeiroChar;
    int i=1;
    retorno = fgetc(arquivo);
    while(1)
    {
        if(retorno == '"') break;
        qualquerCoisa[i]=retorno;
        i++;
        retorno=fgetc(arquivo);
    }
    qualquerCoisa[i] = '\0';
    if(retorno =='"')
    {
        token.tipo=CT_L;
    }
    retorno = fgetc(arquivo);
    printf("%s\n", qualquerCoisa);
    return token;
}
Token estado0()
{
     Token token;
     retorno = fgetc(arquivo);
     /*printf("%d - %c", c, c);*/
     switch(retorno)
     {
        case 'a'...'z':
        case 'A'...'Z':
        token = estado1(retorno);
        break;

        case '0'...'9':
        token = estado2(retorno);
        break;

        case ';':
        token = estado3();
        break;

        case'/':
        token = estado4();
        break;

        case '\'':
        token = estado5();
        break;

        case '|':
        token = estado6();
        break;

        case ',':
        token = estado7();
        break;

        case '{':
        token = estado8();
        break;

        case '}':
        token = estado9();
        break;

        case '(':
        token = estado10();
        break;

        case ')':
        token = estado11();
        break;

        case '+':
        token = estado12();
        break;

        case '-':
        token = estado13();
        break;

        case '!':
        token = estado14();
        break;

        case '&':
        token = estado15();
        break;

        case '=':
        token = estado16();
        break;

        case '>':
        token = estado17();
        break;

        case '<':
        token = estado18();
        break;

        case '*':
        token = estado19();
        break;

        case '"':
        token=estado20(retorno);
        break;

        case '\n':
        contador_linha=contador_linha+1;
        printf("linhas = %d\n",contador_linha);
        return estado0();
        break;

        case '\t':
        case ' ':
        return estado0();
        break;

        case -1:
        token.tipo = TOKEN_EOF;
        break;

        default:
        printf("Caracter nao valido na linha:%d",contador_linha);
        exit(1);
   }
    return token;

}
const char* nome_sinal(enum Sinal sinal)
{
    switch(sinal)
    {
        case PONTO_E_VIRGULA:
            return ";";
        case VIRGULA:
            return ",";
        case ABRE_CHAVE:
            return "{";
        case FECHA_CHAVE:
            return "}";
        case ABRE_PARENTESE:
            return "(";
        case FECHA_PARENTESE:
            return ")";
        case MAIS:
            return "+";
        case MENOS:
            return "-";
        case OU:
            return "||";
        case E:
            return "&&";
        case IGUAL:
            return "==";
        case EXCLAMACAO:
            return "!";
        case ATRIBUICAO:
            return "=";
        case DIFERENTE:
            return "!=";
        case MENOR_IGUAL:
            return "<=";
        case MENOR:
            return "<";
        case MAIOR_IGUAL:
            return ">=";
        case MAIOR:
            return ">";
        case ASTERISCO:
            return "*";
        case BARRA:
            return "/";
    }
    return "nada";
}
void print_token(Token token)
{
    switch (token.tipo)
    {
        case ID:
            printf("ID: %s\n", token.lexema);
            break;
        case PR:
            printf("PR: %d ----> %s\n", token.codigoPR, palavrasReservadas[token.codigoPR]);
            break;
        case CT_I:
             printf("CT_I: %d \n", token.valorInteiro);
             break;
        case CT_R:
            printf("CT_R: %g \n", token.valorReal);
            break;
        case SN:
            printf("SN: %d %s\n",token.codigoSinal, nome_sinal(token.codigoSinal));
            break;
        case CT_C:
            printf("CT_C: %c\n",token.valorCaracter);
            break;
        case CT_L:
            printf("CT_L\n");
            break;
    }
}
Token Lexico()
{
    Token token = estado0();
    ungetc(retorno, arquivo);
    print_token(token);
    return token;
}


