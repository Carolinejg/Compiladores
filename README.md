# Sobre o projeto

Trabalho apresentado como parte das avaliações parciais da disciplina Fundamentos de Compiladores do curso de Sistemas de Informação do Campus I da UNEB na qual tinhamos como objtivo construir um compilador para a linguagem cmm. 

## Análise Léxica
Essa etapa é responsável por reconhecer os tokens da linguagem cmm, para implementar essa etapa foi desenvolvido o AFD (Autômato Finito Determinístico) como mostra a figura a seguir. O analisador léxico ler caracter por caracter quando encontrado um token o AFD estará em um estado de aceitação, demostrando que a cadeia encontrada pertence a linguagem, caso contrário ele emite uma mensagem de erro.

![Mobile 1](https://github.com/Carolinejg/Compiladores/blob/main/Figuras/AFD.png)


## Análise Sintática
O sintático é responsável por verificar a coerência sintática do arquivo fonte, a sintaxe das construções utilizadas foram determinadas mediante a gramática da linguagem cmm
fornecidas na especificação da mesma. As funções criadas no anasin seguem as regras de produção também disponibilizadas nas especificações. Vale ressaltar que o sintático e o
léxico trabalham em conjunto.

## Gerenciador de Tabela de Símbolos e Gerenciador de Erros
 Quando uma função é encontrada no analisador sintático a mesma é adicionada na tabela com os seguintes parâmetros (escopo global, nome, indicação de função), antes no entanto e verificado se já existe uma função com mesmo lexema, caso exista e emitido uma mensagem de erro.

![Mobile 1](https://github.com/Carolinejg/Compiladores/blob/main/Figuras/tabela.png)

# Tecnologias utilizadas
- C
- Ferramenta para criar o AFD: http://www.jflap.org/
- IDE utilizada: Code::Blocks

# Autor

Caroline Souza

https://www.linkedin.com/in/caroline-souza-946b0118a/


