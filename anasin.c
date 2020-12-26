#include "LEXICO.h"
#include "anasin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prog()
{
    token = Lexico();
    if (tipo())
    {
        TipoSimbolo tipoFuncao;
        switch(token.codigoPR)
        {
            case CARACTER:
                tipoFuncao = CHAR;
                break;
            case INTEIRO:
                tipoFuncao = INT;
                break;
            case REAL:
                tipoFuncao = FLOAT;
                break;
            case BOOLEANO:
                tipoFuncao = BOOL;
                break;
        }
        prog_tipo(tipoFuncao);
    }
    else if (VerificarPR(PROTOTIPO))
    {
       prog_prototipo();
    }
    else if (VerificarPR(SEMRETORNO))
    {
       prog_sem_retorno();
    }
    else
    {
       printf("Erro na construcao do prog \n");
       return 0;
    }

}

void prog_sem_retorno()
{
    token=Lexico();
    if(!(token.tipo == ID))
    {
        printf("Erro#2 na contrução do prog_sem_retorno");
        exit(0);
    }
    adiciona_funcao_tabela(VOID, token.lexema);

    token=Lexico();

    if (VerificarSinal(ABRE_PARENTESE))
    {
        if(cabecalho()==0)
        {
            printf("Erro#2 na contrução prog_sem_retorno");
            exit(0);
            /*erro*/
        }
        token=Lexico();


        if(VerificarSinal(ABRE_CHAVE)==0)
        {
            printf("Erro#3 na contrução do prog_sem_retorno");
            exit(0);/*erro*/
        }

        /*corpo da funcao*/

        token = Lexico();

        if(tipo())
        {
            TipoSimbolo tipoFuncao;
            switch(token.codigoPR)
            {
                case CARACTER:
                tipoFuncao = CHAR;
                break;
                case INTEIRO:
                tipoFuncao = INT;
                break;
                case REAL:
                tipoFuncao = FLOAT;
                break;
                case BOOLEANO:
                tipoFuncao = BOOL;
                break;
            }
            while(tipo())
            {
                token=Lexico();
                if(!(token.tipo==ID))
                {
                    printf("Erro#4 na contrução do prog_sem_retorno");
                    exit(0);
                }
                adiciona_funcao_tabela(tipoFuncao,token.lexema);
                token=Lexico();
                if(VerificarSinal(VIRGULA))
                {
                    while(VerificarSinal(VIRGULA))
                    {
                        token=Lexico();
                        if(token.tipo!=ID)
                        {
                            printf("Erro#5 na contrução do prog_sem_retorno");
                            exit(0);
                        }
                        adiciona_funcao_tabela(tipoFuncao,token.lexema);
                        token=Lexico();
                    }
                }

                if(VerificarSinal(PONTO_E_VIRGULA)==0)
                {
                    printf("Erro#6 na contrução do prog_sem_retorno");
                    exit(0);
                }
                token = Lexico();
            }
        }

        /*cmd*/

        while((cmd()))
        {
        }

        /*token=Lexico(); ESSE TOKEN SOBRESCREVE O DE CIMA ( TA CERTO LINCE?*/

        if(VerificarSinal(FECHA_CHAVE)==0)
        {
            exit(0);/*erro*/
        }
    }

}

void prog_prototipo()
{
    token=Lexico();
    if(tipo())
    {
        TipoSimbolo tipoFuncao;
        switch(token.codigoPR)
        {
            case CARACTER:
                tipoFuncao = CHAR;
                break;
            case INTEIRO:
                tipoFuncao = INT;
                break;
            case REAL:
                tipoFuncao = FLOAT;
                break;
            case BOOLEANO:
                tipoFuncao = BOOL;
                break;
        }

        token=Lexico();
        if(!(token.tipo == ID))
        {
            printf("Erro#2 na contrução do prog_prototipo");
            exit(0);
        }
        adiciona_funcao_tabela_ehprototipo(tipoFuncao, token.lexema);

        token=Lexico();
        if(VerificarSinal(ABRE_PARENTESE)==0)
        {
            printf("Erro#3 na contrução do prog_prototipo");
            exit(0);
        }
        token = Lexico();
        if((tipo_p_opc())==0)
        {
            printf("Erro#4 na contrução do prog_prototipo");
            exit(0);
        }
        /*token=Lexico(); função ja consome um token */

        if(VerificarSinal(FECHA_PARENTESE)==0)
        {
            printf("Erro#5 na contrução do prog_prototipo");
            exit(0);
        }
        token=Lexico();

        if(VerificarSinal(VIRGULA))
        {
            while(VerificarSinal(VIRGULA))
            {
                token=Lexico();
                if(token.tipo!=ID)
                {
                    printf("Erro#6 na contrução do prog_tipo");
                    exit(0);
                }
                adiciona_funcao_tabela_ehprototipo(tipoFuncao,token.lexema);
                token=Lexico();

                if(VerificarSinal(ABRE_PARENTESE)==0)
                {
                    printf("Erro#7 na contrução do prog_prototipo");
                    exit(0);
                }
                token=Lexico();
                if((tipo_p_opc())==0)
                {
                    printf("Erro#8 na contrução do prog_prototipo");
                    exit(0);
                }

                /*token=Lexico();  funcçâo consome o proximo token*/

                if(VerificarSinal(FECHA_PARENTESE)==0)
                {
                    printf("Erro#9 na contrução do prog_prototipo");
                    exit(0);
                }

                token=Lexico();
            }
        }

        if(VerificarSinal(PONTO_E_VIRGULA)==0)
        {
            printf("Erro#10 na contrução do prog_prototipo");
            exit(0);
        }
    }

    /*****************SEGUNDA OPÇÃO **********************************/

    else if(VerificarPR(SEMRETORNO))
    {
        token=Lexico();
        if(!(token.tipo == ID))
        {
            printf("Erro#2 na contrução do prog_protosemretorno");
            exit(0);
        }
        adiciona_funcao_tabela_ehprototipo(VOID, token.lexema);
        token=Lexico();
        if(VerificarSinal(ABRE_PARENTESE)==0)
        {
            printf("Erro#3 na contrução do prog_protosemretorno");
            exit(0);
        }
        token=Lexico();
        if((tipo_p_opc())==0)
        {
            printf("Erro#4 na contrução do prog_semretorno");
            exit(0);
        }
        /*token=Lexico(); função tipo_p_op consome o proximo token */

        if(VerificarSinal(FECHA_PARENTESE)==0)
        {
            printf("Erro#5 na contrução do prog_protosemretorno");
            exit(0);
        }
        token=Lexico();

        if(VerificarSinal(VIRGULA))
        {
            while(VerificarSinal(VIRGULA))
            {
                token=Lexico();
                if(token.tipo!=ID)
                {
                    printf("Erro#8 na contrução do prog_protosemretorno");
                    exit(0);
                }
                adiciona_funcao_tabela_ehprototipo(VOID, token.lexema);
                token=Lexico();

                if(VerificarSinal(ABRE_PARENTESE)==0)
                {
                    printf("Erro#3 na contrução do prog_protosemretorno");
                    exit(0);
                }

                token=Lexico();
                if((tipo_p_opc())==0)
                {
                    printf("Erro#4 na contrução do prog_protosemretorno");
                    exit(0);
                }

                /*token=Lexico(); função ja consome o proximo token*/

                if(VerificarSinal(FECHA_PARENTESE)==0)
                {
                    printf("Erro#5 na contrução do prog_protosemretorno");
                    exit(0);
                }

                token=Lexico();
            }
        }


        if(VerificarSinal(PONTO_E_VIRGULA)==0)
        {
            printf("Erro#40 na contrução do prog_prototipo");
            exit(0);
        }
    }

   /*************************ERRO*********************************/

    else
    {
        printf("Erro#1 na construçâo do prog_prototipo \n");
        exit(0);
    }


}

int tipo_p_opc()
{
    if(VerificarPR(SEMPARAM))
    {
        token=Lexico();
        return 1;
    }
    if(tipo())
    {
        TipoSimbolo tipoFuncao;
        switch(token.codigoPR)
        {
            case CARACTER:
                tipoFuncao = CHAR;
                break;
            case INTEIRO:
                tipoFuncao = INT;
                break;
            case REAL:
                tipoFuncao = FLOAT;
                break;
            case BOOLEANO:
                tipoFuncao = BOOL;
                break;
        }
        token=Lexico();
        if(token.tipo == ID)
        {
            adiciona_param_tabela(tipoFuncao,token.lexema);
            token=Lexico();
            if(VerificarSinal(VIRGULA))
            {
                while(VerificarSinal(VIRGULA))
                {
                    token=Lexico();
                    if(tipo())
                    {
                        TipoSimbolo tipoFuncao;
                        switch(token.codigoPR)
                        {
                        case CARACTER:
                        tipoFuncao = CHAR;
                        break;
                        case INTEIRO:
                        tipoFuncao = INT;
                        break;
                        case REAL:
                        tipoFuncao = FLOAT;
                        break;
                        case BOOLEANO:
                        tipoFuncao = BOOL;
                        break;
                        }
                    }
                    else
                    {
                        printf("Erro#2 na construçâo do tipo_p_opc \n");
                        return 0;
                    }

                    token=Lexico();
                    if(token.tipo != ID)
                    {
                        strcpy(token.lexema, "sem nome");
                        adiciona_funcao_tabela(tipoFuncao,token.lexema);
                        return 1;
                    }
                    else
                    {
                        adiciona_param_tabela(tipoFuncao,token.lexema);
                        token=Lexico();
                    }
                }
            }
            else
            {
                return 1;
            }
        }
/**********/

        if(VerificarSinal(VIRGULA))
        {
           while(VerificarSinal(VIRGULA))
                {
                    token=Lexico();
                    if(tipo())
                    {
                        TipoSimbolo tipoFuncao;
                        switch(token.codigoPR)
                        {
                        case CARACTER:
                        tipoFuncao = CHAR;
                        break;
                        case INTEIRO:
                        tipoFuncao = INT;
                        break;
                        case REAL:
                        tipoFuncao = FLOAT;
                        break;
                        case BOOLEANO:
                        tipoFuncao = BOOL;
                        break;
                        }
                    }
                    else
                    {
                        printf("Erro#2 na construçâo do tipo_p_opc \n");
                        return 0;
                    }
                    token=Lexico();
                    if(token.tipo != ID)
                    {
                        strcpy(token.lexema, "sem_nome");
                        adiciona_param_tabela(tipoFuncao,token.lexema);
                        return 1;
                    }
                    else
                    {
                        adiciona_funcao_tabela(tipoFuncao,token.lexema);
                        token=Lexico();
                    }
                }
        }

        else
        {
            return 1;
        }

    }
    else
    {
        printf("Erro#1 na construçâo do tipo_p_opc \n");
        return 0;
    }


}
void prog_tipo (TipoSimbolo tipoFuncao)
{
    token = Lexico();
    if(!(token.tipo == ID))
    {
        printf("Erro#1 na contrução do prog_tipo");
        exit(0);
    }
    token=Lexico();

    if (VerificarSinal(ABRE_PARENTESE))
    {
        adiciona_funcao_tabela(tipoFuncao,token.lexema);
        if(cabecalho()==0)
        {
            printf("Erro#2 na contrução fo prog_tipo");
            exit(0);
            /*erro*/
        }
        token=Lexico();


        if(VerificarSinal(ABRE_CHAVE)==0)
        {
            printf("Erro#3 na contrução do prog_tipo");
            exit(0);/*erro*/
        }

        /*corpo da funcao*/

        token=Lexico();

        if(tipo())
        {
            while(tipo())
            {
                token=Lexico();
                if(!(token.tipo==ID))
                {
                    printf("Erro#4 na contrução do prog_tipo");
                    exit(0);
                }
                token=Lexico();
                if(VerificarSinal(VIRGULA))
                {
                    while(VerificarSinal(VIRGULA))
                    {
                        token=Lexico();
                        if(token.tipo!=ID)
                        {
                            printf("Erro#5 na contrução do prog_tipo");
                            exit(0);
                        }
                        token=Lexico();
                    }
                }


                if(VerificarSinal(PONTO_E_VIRGULA)==0)
                {
                    printf("Erro#6 na contrução do prog_tipo");
                    exit(0);
                }
                token=Lexico();
            }
        }

        /*cmd*/
        while(cmd());

        /*token=Lexico(); ESSE TOKEN SOBRESCREVE O DE CIMA ( TA CERTO LINCE?*/

        if(VerificarSinal(FECHA_CHAVE)==0)
        {
           exit(0);/*erro*/
        }


        return 1;
    }
/***segunda opção */
    else if(VerificarSinal(VIRGULA))
    {
        adiciona_var_tabela(tipoFuncao,token.lexema);
        while(VerificarSinal(VIRGULA))
        {
            token=Lexico();
                if(token.tipo!=ID)
                {
                    printf("Erro#8 na contrução do prog_tipo");
                    exit(0);
                }
                adiciona_var_tabela(tipoFuncao,token.lexema);
            token=Lexico();
        }
    }

     /*token=Lexico(); ESSE TOKEN SOBRESCREVE O DE CIMA ( TA CERTO LINCE?*/
    if(VerificarSinal(PONTO_E_VIRGULA)==0)
    {
        printf("Erro#9 na contrução do prog_tipo");
        exit(0);
    }

}

int cabecalho() /* '(' tipos_param ')' BLZ */
{
    if (VerificarSinal(ABRE_PARENTESE) == 0)
    {
        printf("Abre parenteses esperado na linha %d\n", contador_linha);
        return 0;
    }
    if (tipos_param() == 0)
    {
        printf("Erro #2 ao construir cabecalho %d\n", contador_linha);
        return 0;
    }
    if (VerificarSinal(FECHA_PARENTESE) == 0)
    {
        printf("Fecha parenteses esperado na linha %d\n", contador_linha);
        return 0;
    }
    return 1;
}
int tipos_param() /* blz */
{
    token = Lexico();
    if (VerificarPR(SEMPARAM))
    {
        token = Lexico();
        return 1;
    }
    else if (tipo())
    {
        TipoSimbolo tipoFuncao;
        switch(token.codigoPR)
        {
            case CARACTER:
                tipoFuncao = CHAR;
                break;
            case INTEIRO:
                tipoFuncao = INT;
                break;
            case REAL:
                tipoFuncao = FLOAT;
                break;
            case BOOLEANO:
                tipoFuncao = BOOL;
                break;
        }
        token = Lexico();
        if (token.tipo != ID)
        {
            printf("Erro #1 ao construir parametros %d\n", contador_linha);
            return 0;
        }
        adiciona_param_tabela(tipoFuncao,token.lexema);
        token = Lexico();
        if (VerificarSinal(VIRGULA))
        {
            while (VerificarSinal(VIRGULA))
            {
                token = Lexico();
                if (tipo())
                {
                    TipoSimbolo tipoFuncao;
                    switch(token.codigoPR)
                    {
                        case CARACTER:
                        tipoFuncao = CHAR;
                        break;
                        case INTEIRO:
                        tipoFuncao = INT;
                        break;
                        case REAL:
                        tipoFuncao = FLOAT;
                        break;
                        case BOOLEANO:
                        tipoFuncao = BOOL;
                        break;
                    }

                }
                else{
                  printf("Erro #2 ao construir parametros %d\n", contador_linha);
                  return 0;
                }
                token = Lexico();
                if (token.tipo != ID)
                {
                    printf("Erro #3 ao construir parametros %d\n", contador_linha);
                    return 0;
                }
                adiciona_funcao_tabela(tipoFuncao,token.lexema);
                token = Lexico();
            }
        }
        return 1;
    }
    else
    {
        printf("Erro #1 ao construir parametros %d\n", contador_linha);
        return 0;
    }
}

int decl()
{
    Token token = Lexico();
    int ehTipo = tipo();
    if (ehTipo == 1)
    {
        token = Lexico();
        if (token.tipo == ID)
        {

        }
        else
        {
            printf("Erro");
            return 0;
        }
    }
    else
    {
    }
}
int decl_var()
{
    if (token.tipo == ID)
    {


        return 1;
    }
    else
    {
        return 0;
    }
}
int tipo()
{
    if (token.tipo == PR)
    {
        switch(token.codigoPR)
        {
            case CARACTER:
            case INTEIRO:
            case REAL:
            case BOOLEANO:
                return 1;
            default:
                return 0;
        }
    }
    else
    {
        return 0;
    }
}


int cmd()
{
    printf("\n\tCMD\n");
 /**************************SE************************/
    if(VerificarPR(SE))
    {
        token=Lexico();
        if(VerificarSinal(ABRE_PARENTESE)==0)
        {
            printf("abre parenteses esperado dentro do SE\n");
            return 0;
        }
        token=Lexico();
        if(expr()==0)
        {
            printf("expr esperada dentro de SE\n");
            return 0;
        }
        if(VerificarSinal(FECHA_PARENTESE)==0)
        {
            printf("fecha parenteses esperado dentro do SE\n");
            return 0;
        }
        token=Lexico();
        if(cmd()==0)
        {
            printf("Erro#1 ao contruir cmd dentro do SE\n");
            return 0;
        }
        if(VerificarPR(SENAO))
        {
            token=Lexico();
            if(cmd()==0)
            {
                printf("Erro#5 ao contruir cmd dentro do SE\n");
                return 0;
            }
        }
        return 1;
    }
/**************************ENQUANTO************************/
    else if(VerificarPR(ENQUANTO))
    {
        token=Lexico();
        if(VerificarSinal(ABRE_PARENTESE)==0)
        {
            printf("abre parenteses esperado dentro do ENQUANTO\n");
            exit(0);
        }
        token=Lexico();
        if(expr()==0)
        {
            printf("erro ao construir expressao dentro do ENQUANTO\n");
            exit(0);
        }
        token=Lexico();
        if(VerificarSinal(FECHA_PARENTESE)==0)
        {
            printf("fecha parenteses esperado dentro do ENQUANTO\n");
            exit(0);
        }

        token=Lexico();
        if (cmd()==0)
        {
            printf("Erro#1 ao contruir cmd dentro do ENQUANTO\n");
            return 0;
        }
    }
 /*************************PARA************************/
    else if(VerificarPR(PARA))
    {
        token = Lexico();
        if(VerificarSinal(ABRE_PARENTESE)==0)
        {
            printf("Erro#1 ao contruir cmd dentro do PARA\n");
            return 0;
        }
        token = Lexico();
        atrib();

        if(VerificarSinal(PONTO_E_VIRGULA)==0)
        {
             printf("ponto e virgula esperado\n");
             return 0;
        }
        token = Lexico();
        expr();

        if(VerificarSinal(PONTO_E_VIRGULA)==0)
        {
             printf("ponto e virgula esperado\n");
             return 0;
        }
        token = Lexico();
        atrib();

        if(VerificarSinal(FECHA_PARENTESE)==0)
        {
            printf("Fecha parenteses esperado\n");
            return 0;
        }

        token = Lexico();
        if(cmd()==0)
        {
            printf("Erro#6 ao contruir cmd dentro do PARA\n");
            return 0;
        }
    }
     /**************************RETORNE************************/
    else if(VerificarPR(RETORNE))
    {
        token = Lexico();
        expr();
        if(VerificarSinal(PONTO_E_VIRGULA)==0)
        {
            printf("ponto e virgula esperado\n");
            exit(0);
        }
        token = Lexico();
        return 1;
    }
    /**************************ID************************/
    else if(token.tipo == ID)
    {
        token = Lexico();

        if (VerificarSinal(ATRIBUICAO))
        {
            token = Lexico();
            if (expr() == 0)
            {
                printf("erro ao construir atribuição\n");
                return 0;
            }
            if (VerificarSinal(PONTO_E_VIRGULA) == 0)
            {
                printf("ponto e virgula esperado\n");
                exit(0);
            }
            token = Lexico();
            return 1;
        }
        else if(VerificarSinal(ABRE_PARENTESE))
        {
            printf("\tCHAMADA DE FUCNAO\n");
            token = Lexico();
            if(expr())
            {
                if(VerificarSinal(VIRGULA))
                {
                    while(VerificarSinal(VIRGULA))
                    {
                        token=Lexico();
                        if(expr()==0)
                        {
                            printf("Erro#2 ao contruir cmd dentro de ID\n");
                            return 0;
                        }

                    }
                }
            }

            if(VerificarSinal(FECHA_PARENTESE) == 0)
            {
                printf("Fecha parenteses esperado\n");
                return 0;
            }
            token = Lexico();
            if(VerificarSinal(PONTO_E_VIRGULA)==0)
            {
                printf("Ponto e virgula esperado\n");
                return 0;
            }
            token = Lexico();
            return 1;
        }
        else
        {
            printf("Erro ao construir cmd (abre parenteses ou atribuicao esperada)\n");
            exit(1);
        }
    }
    /************ABRE CHAVE ********************/
    else if (VerificarSinal(ABRE_CHAVE))
    {
        token=Lexico();
        while(cmd());

        token=Lexico();

        if(VerificarSinal(FECHA_CHAVE)==0)
        {
            printf("Erro#1 ao contruir cmd dentro ABRECHAVE\n");
            return 0;
        }
        token = Lexico();
        return 1;
    }

 /**************************PONTO E VIRGULA************************/
    else if (VerificarSinal(PONTO_E_VIRGULA))
    {
        token = Lexico();
        return 1;
    }
    return 0;
}
int atrib()
{
    if(token.tipo == ID)
    {
        token = Lexico();

        if (VerificarSinal(ATRIBUICAO))
        {
            token = Lexico();
            if (expr() == 0)
            {
                printf("erro na expr da atribuição\n");
                exit(0);
            }
            return 1;
        }
        else
        {
            printf("atribuição invalida\n");
            exit(0);
        }
    }
    else
    {
        return 0;
    }
}

int op_rel()
{
    if (token.tipo == SN)
    {
        switch(token.codigoSinal)
        {
            case IGUAL:
            case DIFERENTE:
            case MENOR_IGUAL:
            case MENOR:
            case MAIOR_IGUAL:
            case MAIOR:
                return 1;
            default:
                return 0;
        }
    }
    else
    {
        return 0;
    }

}

int expr ()
{
    if(expr_simp()==0)
    {
        printf("Erro#1 ao construir expr\n");
        return 0;
    }
    if(op_rel()==0)
    {
        return 1;
    }
    else
    {
        token = Lexico();
        if(expr_simp()==0)
        {
            printf("Erro#2 ao construir expr\n");
            return 0;
        }
        return 1;
    }
}

int expr_simp()
{
    if (VerificarSinal(MAIS) || VerificarSinal(MENOS))
    {
        token = Lexico();
    }
    if (termo() == 0)
    {
        printf("erro expr_simp\n");
        return 0;
    }

    if (VerificarSinal(MAIS) || VerificarSinal(MENOS) || VerificarSinal(OU))
    {
        token = Lexico();
        if (termo() == 0)
        {
            printf("erro expr_simp\n");
            return 0;
        }
    }
    return 1;
}

int termo()
{
    if (fator() == 0)
    {
       printf("erro fator\n");
       return 0;
    }
    if (VerificarSinal(ASTERISCO) ||
       VerificarSinal(BARRA) ||
       VerificarSinal(E))
    {
       while ((VerificarSinal(ASTERISCO) ||
                VerificarSinal(BARRA) ||
                VerificarSinal(E)))
       {
           token = Lexico();
           if (fator() == 0)
           {
               printf("erro fator\n");
               return 0;
           }
       }
    }
    return 1;
}

int fator()
{
    if(token.tipo == CT_I ||
       token.tipo == CT_R ||
       token.tipo == CT_C ||
       token.tipo == CT_L)
    {
        token = Lexico();
        return 1;
    }
    else if(token.tipo == ID)
    {
        token = Lexico();
        if (VerificarSinal(ABRE_PARENTESE))
        {
            token = Lexico();
            if (expr())
            {
                if (VerificarSinal(VIRGULA))
                {
                    while (VerificarSinal(VIRGULA))
                    {
                        token = Lexico();
                        if (expr() == 0)
                        {
                            printf("erro#1 fator\n");
                            return 0;
                        }
                    }
                }
            }
            if (VerificarSinal(FECHA_PARENTESE) == 0)
            {
                printf("erro#2 fator\n");
                return 0;
            }
            token = Lexico();
        }

        return 1;
    }
    else if (VerificarSinal(ABRE_PARENTESE))
    {
        token = Lexico();
        if (expr() == 0)
        {
            printf("erro#3 fator\n");
            return 0;
        }
        if (VerificarSinal(FECHA_PARENTESE) == 0)
        {
            printf("erro#4 fator\n");
            return 0;
        }
        token = Lexico();
        return 1;
    }
    else if (VerificarSinal(EXCLAMACAO))
    {
        token = Lexico();
        if (fator() == 0)
        {
            printf("erro#5 fator\n");
            return 0;
        }
        token = Lexico();
        return 1;
    }
    else
    {
        printf("Erro#1 ao construir fator\n");
        return 0;
    }
}

int VerificarSinal(enum Sinal sinal)
{
    if (token.tipo == SN && token.codigoSinal == sinal)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int VerificarPR(enum PalavraReservada pr)
{
    if (token.tipo == PR && token.codigoPR == pr)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
