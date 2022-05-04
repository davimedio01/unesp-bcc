/*
Nome: Davi Augusto Neves Leite
RA: 191027383

Realizado em: Windows 10 (x64) e compilado pelo TDM-GCC x64 (https://jmeubank.github.io/tdm-gcc/)
Deixar o programa e arquivo texto (Exemplo1_Trab2_Compiladores.txt) no MESMO DIRETÓRIO.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

/////////////////////////////////////////////////////////////
//* DEFINIÇÕES DOS IDENTIFICADORES PARA ANÁLISE SINTÁTICA *//
//* ----------------------------------------------------- *//
//* RETIRADOS DO LIVRO DO KOWALTOVSKI E  *//
//* DO ARQUIVO DE GRAMÁTICA SIMPLIFICADA *//
/////////////////////////////////////////////////////////////
#define PROGRAM 1
#define LABEL 2
#define VAR 3
#define PROCEDURE 4
#define FUNCTION 5
#define BEGIN 6
#define END 7
#define IF 8
#define THEN 9
#define ELSE 10
#define WHILE 11
#define DO 12
#define OR 13
#define AND 14
#define DIV 15
#define NOT 16
#define PONTO_FINAL 17
#define PONTO_VIRGULA 18
#define VIRGULA 19
#define ABRE_PARENTESIS 20
#define FECHA_PARENTESIS 21
#define ABRE_COLCHETES 22
#define FECHA_COLCHETES 23
#define DOIS_PONTOS 24
#define IGUAL 25
#define DIFERENTE 26
#define MAIOR_QUE 27
#define MENOR_QUE 28
#define MAIOR_IGUAL_QUE 29
#define MENOR_IGUAL_QUE 30
#define SOMA 31             //Símbolo: +
#define SUBTRAI 32          //Símbolo: -
#define MULTIPLICA 33       //Símbolo: *
#define DOISPONTOS_IGUAL 34 //Símbolo: :=
#define PONTO_PONTO 35      //Símbolo: ..
#define ABRE_COMENTARIO 36  //Símbolo: (*
#define FECHA_COMENTARIO 37 //Símbolo: *)
#define READ 38             //Símbolo: read(var)
#define WRITE 39            //Símbolo: write(var)
#define INTEIRO 40          //Palavra: integer
#define BOOLEANO 41         //Palavra: boolean
#define TOKEN 42            //Todo token que não é palavra/simbolo reservado
#define NUMERO 43           //Todo número associado no código-fonte (valores)

#define MAX_LETTERS 1000 //Máximo de Caracteres para um Token
#define MAX_KEYWORD 10   //Máximo de Caracteres por Token/Símbolo Reservado
#define MAX_SYMBOL 15    //Máximo de Caracteres para um Símbolo

typedef long long int lld;

///////////////////////////////////////////////////////////////////////////////
//* ESCOPOS DAS FUNÇÕES PARA CADA REGRA DA GRAMÁTICA SIMPLIFICADA DO PASCAL *//
///////////////////////////////////////////////////////////////////////////////
void PROGRAMA();
void BLOCO();
void PARTE_DECLARACAO_VARIAVEL();
void DECLARACAO_VARIAVEL();
void LISTA_IDENTIFICADOR();
void TIPO_VARIAVEL();
void AUXILIAR_DECLARACAO_VARIAVEL();
void PARTE_DECLARACAO_SUBTORINA();
void DECLARACAO_PROCEDIMENTO();
void DECLARACAO_FUNCAO();
void PARAMETROS_FORMAIS();
void SECAO_PARAMETROS_FORMAIS();
void PARTE_SECAO_PARAMETROS_FORMAIS();
void LISTA_IDENTIFICADOR_PARAMETROS_FORMAIS();
void FIM_SECAO_PARAMETROS_FORMAIS();
void COMANDO_COMPOSTO();
void COMANDO();
void FIM_COMANDO();
void COMANDO_SEM_ROTULO();
void ATRIBUICAO_OU_PROCEDIMENTO();
void ATRIBUICAO();
void CHAMADA_PROCEDIMENTO();
void COMANDO_CONDICIONAL();
void FIM_COMANDO_CONDICIONAL();
void COMANDO_REPETITIVO();
void COMANDO_LEITURA_DADOS();
void FIM_COMANDO_LEITURA_DADOS();
void EXPRESSAO();
void EXPRESSAO_SIMPLES();
void EXPRESSAO_SIMPLES_OPCIONAL();
void EXPRESSAO_COM_RELACAO();
void LISTA_DE_EXPRESSAO();
void TERMO();
void FATOR();
void FATOR_COM_OPERACAO();

///////////////////////////////////////////////////////////
//* FILA DINÂMICA (CIRCULAR S.E.): ESTRUTURA PARA TOKEN *//
///////////////////////////////////////////////////////////

//Tupla contendo: identificador, token e linha do token
struct struct_tuple_token
{
    int identifier;          //Identificador: valor inteiro do token na tabela de símbolos da análise léxica
    char token[MAX_LETTERS]; //Token: cadeia de caracteres
    lld line;                //Linha do Token: linha em que o token está
};
typedef struct struct_tuple_token tuple_token;

//Variável tupla para obter o elemento atual para Análise Sintática
tuple_token tokenSyntactical;

//Estrutura da Fila
typedef struct struct_queue *queue;
struct struct_queue
{
    tuple_token element;
    queue next;
};

//Fila contendo cada token, sua linha respectiva e seu identificador
queue token;

//Alocação de Elemento
queue allocQueue(int *identifier, char *token_word, lld *line)
{
    queue q = (queue)malloc(sizeof(struct struct_queue));
    tuple_token element;

    element.identifier = (*identifier);
    strcpy(element.token, token_word);
    element.line = (*line);

    q->element = element;
    q->next = NULL;

    return q;
}

//Verifica se Fila está vazia
int isEmptyQueue(queue q)
{
    return (q == NULL);
}

//Inserção na Fila
void pushQueue(int *identifier, char *token_word, lld *line)
{
    //Alocando elemento
    queue element = allocQueue(identifier, token_word, line);

    //Se estiver vazia, aloca elemento único
    if (isEmptyQueue(token))
    {
        token = element;
    }
    else
    {
        //Se não estiver vazia, aloca mais de um elemento
        element->next = token->next;
    }

    token->next = element;
    token = element;
}

//Remover da Fila
void popQueue()
{
    //Não remove se estiver vazia
    if (isEmptyQueue(token))
    {
        return;
    }

    //Salvando elemento anterior na auxiliar para erro
    //prevTokenSyntactical.identifier = tokenSyntactical.identifier;
    //strcpy(prevTokenSyntactical.token, tokenSyntactical.token);
    //prevTokenSyntactical.line = tokenSyntactical.line;

    //Recuperando elemento da cabeça da lista
    tokenSyntactical.identifier = token->next->element.identifier;
    strcpy(tokenSyntactical.token, token->next->element.token);
    tokenSyntactical.line = token->next->element.line;

    //Recuperando elemento pra eliminar
    queue element = token->next;

    //Se tiver só um elemento
    if (element == token)
    {
        token = NULL;
    }
    //Se tiver mais de um elemento
    else
    {
        token->next = element->next;
    }

    //Eliminando elemento
    free(element);

    //return 1;
}

///////////////////////////////////////////////////////////
//* VARIÁVEIS GLOBAIS *//
///////////////////////////////////////////////////////////

//Marca o código de identificação do último átomo analisado pela Análise Léxica
int varSymbol;

//Variável para salvar o identificador do erro na Análise Sintática
//int idErrorSyntactic;

///////////////////////////////////////////////////////////
//* ANÁLISE LÉXICA: GERAÇÃO DOS TOKENS
///////////////////////////////////////////////////////////

//Par contendo o identificador e token associado
typedef struct struct_pair_symbol pairSymbol;
struct struct_pair_symbol
{
    int identifier;          //Salva o identificador (número) do átomo associado
    char token[MAX_LETTERS]; //Salva o átomo associado
};

//Tabela de Símbolos PRÉ-DEFINIDOS por LISTA ENCADEADA
typedef struct struct_symbol_table *table;
struct struct_symbol_table
{
    pairSymbol pair;
    struct symbol *prox;
};
table symbolTable;

//Inserir ao fim da Tabela de Símbolos
void endInsertList(pairSymbol pair)
{
    //Alocando espaço para inserção
    table p = (table)malloc(sizeof(struct struct_symbol_table));
    //Recebendo a informação
    p->pair = pair;
    p->prox = NULL;

    //Caso a lista esteja nula
    if (symbolTable == NULL)
    {
        symbolTable = p;
    }
    else
    {
        table q = symbolTable;
        while (q->prox)
        {
            q = q->prox;
        }
        q->prox = p;
    }
}

//Verificador de SÍMBOLOS ESPECIAIS
int isSpecialSymbol(char character)
{
    //Símbolos Especiais do PASCAL
    char symbols[MAX_SYMBOL] = {".;,()[]:=><+-*"};

    int i;
    for (i = 0; i < MAX_SYMBOL; i++)
    {
        if (character == symbols[i])
        {
            //Caso o caractere seja um símbolo especial
            return 1;
        }
    }
    return 0;
}

//Verificador de LETRAS
int isLetter(char character)
{
    return ((character >= 'A') && (character <= 'Z'));
}

//Verificador de NÚMEROS
int isNumber(char character)
{
    return ((character >= '0') && (character <= '9'));
}

//Verificador de LETRAS e DÍGITOS
int isLetterOrNumber(char character)
{
    return (isLetter(character) || isNumber(character));
}

//Verificador de NÚMEROS (0 até 9)
int isOnlyNumber(char *word)
{
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        if (isNumber(word[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

//Inserir os Símbolos Especiais, Símbolos Especiais Compostos e Palavras-Chave na Tabela de Símbolos
void insertSpecialSymbolsOnSymbolTable(int *countTableSymbol)
{
    (*countTableSymbol) = 1; //Inicia os identificadores em 1
    int i = 0, size;
    pairSymbol pair;

    ///////////////////////////////////////////////////////////
    //Palavras e Símbolos Reservados do PASCAL
    ///////////////////////////////////////////////////////////
    char keywords[][MAX_KEYWORD] = {"PROGRAM", "LABEL", "VAR", "PROCEDURE",
                                    "FUNCTION", "BEGIN", "END", "IF", "THEN",
                                    "ELSE", "WHILE", "DO", "OR", "AND", "DIV",
                                    "NOT", ".", ";", ",", "(", ")", "[", "]",
                                    ":", "=", "<>", ">", "<", ">=", "<=", "+",
                                    "-", "*", ":=", "..", "(*", "*)",
                                    "READ", "WRITE", "INTEGER", "BOOLEAN"};

    size = *(&keywords + 1) - keywords; //Tamanho da tabela de palavras-chave
    for (i = 0; i < size; i++)
    {
        pair.identifier = (*countTableSymbol)++;
        strcpy(pair.token, keywords[i]);

        //Inserção na Tabela de Símbolos
        endInsertList(pair);
    }
}

//Função PROXIMO: responsável por ler o arquivo que contenha o código-fonte
char *PROXIMO_LEXICO(FILE *file)
{
    return toupper(fgetc(file));
}

//Função CÓDIGO: responsável por retornar o par(id, token) caso contido na Tabela de Símbolos
int CODIGO_LEXICO(char *token, int *countTableSymbol)
{
    //Percorre a tabela de símbolos em busca do átomo associado
    table p = symbolTable;
    while (p)
    {
        if (strcmp(p->pair.token, token) == 0)
        {
            return p->pair.identifier;
        }
        p = p->prox;
    }

    //Caso não tenha encontrado nada, verifica se é número ou palavra
    if (isOnlyNumber(token))
    {
        //Se for número
        (*countTableSymbol) = NUMERO;
    }
    else
    {
        //Se for palavra
        (*countTableSymbol) = TOKEN;
    }

    return (*countTableSymbol); //Retorna o identificador do elemento atual
}

//Função ERRO: retorna um erro ao usuário e a linha em que foi encontrado o erro
void ERRO_LEXICO(lld line)
{
    printf("\nERRO DE COMPILACAO!\n\n");
    printf("ERRO LEXICO!\n");
    printf("Ocorreu um erro lexico na linha %lld do codigo-fonte!", line);
    printf("\n\n");
    printf("Pressione ENTER para sair...");
    getchar();
    exit(0);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//* ANÁLISE SINTÁTICA *//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

//Utilizada para mostrar o respectivo erro da Análise Sintática
char *convertIDtoToken()
{
    switch (tokenSyntactical.identifier)
    {
    case PROGRAM:
        return "PROGRAM";
    case LABEL:
        return "LABEL";
    case VAR:
        return "VAR";
    case PROCEDURE:
        return "PROCEDURE";
    case FUNCTION:
        return "FUNCTION";
    case BEGIN:
        return "BEGIN";
    case END:
        return "END";
    case IF:
        return "IF";
    case THEN:
        return "THEN";
    case ELSE:
        return "ELSE";
    case WHILE:
        return "WHILE";
    case DO:
        return "DO";
    case OR:
        return "OR";
    case AND:
        return "AND";
    case DIV:
        return "DIV";
    case NOT:
        return "NOT";
    case PONTO_FINAL:
        return ".";
    case PONTO_VIRGULA:
        return ";";
    case VIRGULA:
        return ",";
    case ABRE_PARENTESIS:
        return "(";
    case FECHA_PARENTESIS:
        return ")";
    case ABRE_COLCHETES:
        return "[";
    case FECHA_COLCHETES:
        return "]";
    case DOIS_PONTOS:
        return ":";
    case IGUAL:
        return "=";
    case DIFERENTE:
        return "<>";
    case MAIOR_QUE:
        return ">";
    case MENOR_QUE:
        return "<";
    case MAIOR_IGUAL_QUE:
        return ">=";
    case MENOR_IGUAL_QUE:
        return "<=";
    case SOMA:
        return "+";
    case SUBTRAI:
        return "-";
    case MULTIPLICA:
        return "*";
    case DOISPONTOS_IGUAL:
        return ":=";
    case PONTO_PONTO:
        return "..";
    case ABRE_COMENTARIO:
        return "(*";
    case FECHA_COMENTARIO:
        return "*)";
    case READ:
        return "READ(variavel)";
    case WRITE:
        return "WRITE(variavel)";
    case INTEIRO:
        return "INTEGER";
    case BOOLEANO:
        return "BOOLEAN";
    default:
        return tokenSyntactical.token;
    }
}

//Função para retornar a ocorrência de um erro sintático
void syntacticError()
{
    printf("\nERRO DE COMPILACAO!\n\n");
    printf("ERRO SINTATICO!\n\n");
    printf("Linha %lld\nErro: %s", tokenSyntactical.line, convertIDtoToken());
    printf("\n\n");
    printf("Pressione ENTER para sair...");
    getchar();
    exit(0);
}

//Função para percorrer a Fila de Tokens e ver os elementos corretamente
void parser(int identifier)
{
    //Verifica se o identificador do elemento corresponde, corretamente, ao analisado
    if (tokenSyntactical.identifier == identifier)
    {
        //Recuperando próximo elemento da fila para análise
        popQueue();
    }
    //Ocorre um erro caso contrário
    else
    {
        syntacticError();
    }
}

//Início da Análise Sintática pela análise do PROGRAM
void startSyntacticAnalyzer()
{
    //Recuperando o primeiro elemento para análise
    popQueue();

    //Verificando se a primeira palavra é PROGRAM
    switch (tokenSyntactical.identifier)
    {
    case PROGRAM:
        PROGRAMA();
        break;

    //Caso não seja PROGRAM, ocorre erro
    default:
        syntacticError();
    }
}

///////////////////////////////////////////////////////////////////
//* FUNÇÕES PARA CADA REGRA DA GRAMÁTICA SIMPLIFICADA DO PASCAL *//
//////////////////////////////////////////////////////////////////
void PROGRAMA()
{
    //* PROGRAM <TOKEN>; <BLOCO>.
    switch (tokenSyntactical.identifier)
    {
    case PROGRAM:
        parser(PROGRAM);
        parser(TOKEN);
        parser(PONTO_VIRGULA);
        BLOCO();
        parser(PONTO_FINAL);
        break;
    default:
        syntacticError();
    }
}

void BLOCO()
{
    //* [<PARTE_DECLARACAO_VARIAVEL>]  -> VAR (opcional)
    //* [<PARTE_DECLARACAO_SUBROTINA>] -> PROCEDURE/FUNCTION (opcional)
    //* <COMANDO_COMPOSTO>             -> BEGIN
    switch (tokenSyntactical.identifier)
    {
    case VAR:
        PARTE_DECLARACAO_VARIAVEL();
        break;
    case PROCEDURE:
        PARTE_DECLARACAO_SUBTORINA();
        break;
    case FUNCTION:
        PARTE_DECLARACAO_SUBTORINA();
        break;
    case BEGIN:
        COMANDO_COMPOSTO();
        break;
    default:
        syntacticError();
    }
}

void PARTE_DECLARACAO_VARIAVEL()
{
    //* <PARTE_DECLARACAO_VARIAVEL> -> VAR <DECLARACAO_VARIAVEL>
    switch (tokenSyntactical.identifier)
    {
    case VAR:
        parser(VAR);
        DECLARACAO_VARIAVEL();
        break;
    default:
        syntacticError();
    }
}

void DECLARACAO_VARIAVEL()
{
    //* <DECLARACAO_VARIAVEL> -> IDENTIFICADOR [<LISTA_IDENTIFICADOR>]
    switch (tokenSyntactical.identifier)
    {
    case TOKEN:
        parser(TOKEN);         //Variável
        LISTA_IDENTIFICADOR(); //Verifica se tem mais variável ou já o tipo
        break;
    default:
        syntacticError();
    }
}

void LISTA_IDENTIFICADOR()
{
    //* <LISTA_IDENTIFICADOR> -> <, IDENTIFICADOR> ou ": <TIPO_VARIAVEL>"
    switch (tokenSyntactical.identifier)
    {
    case VIRGULA:
        parser(VIRGULA);
        DECLARACAO_VARIAVEL(); //Declarar mais variável
        break;
    case DOIS_PONTOS:
        parser(DOIS_PONTOS);
        TIPO_VARIAVEL();
        parser(PONTO_VIRGULA); //Fim declaração de variável

        //Verificar o que vem depois de declarar variável...
        AUXILIAR_DECLARACAO_VARIAVEL();
        break;
    default:
        syntacticError();
    }
}

void TIPO_VARIAVEL()
{
    //* <TIPO_VARIAVEL> -> INTEGER ou BOOLEAN
    switch (tokenSyntactical.identifier)
    {
    case INTEIRO:
        parser(INTEIRO);
        break;
    case BOOLEANO:
        parser(BOOLEANO);
        break;
    default:
        syntacticError();
    }
}

void AUXILIAR_DECLARACAO_VARIAVEL()
{
    //* <AUXILIAR_DECLARACAO_VARIAVEL> -> verificar qual procedimento vem agora: VAR, PROCEDURA, FUNCTION ou BEGIN
    switch (tokenSyntactical.identifier)
    {
    //Mais variável: mesmo tipo ou outro tipo
    case TOKEN:
        DECLARACAO_VARIAVEL();
        break;
    case PROCEDURE:
        BLOCO();
        break;
    case FUNCTION:
        BLOCO();
        break;
    case BEGIN:
        BLOCO();
        break;
    default:
        syntacticError();
    }
}

void PARTE_DECLARACAO_SUBTORINA()
{
    //* <PARTE_DECLARACAO_SUBTORINA> -> PROCEDIMENTO; ou FUNÇÃO;
    switch (tokenSyntactical.identifier)
    {
    case PROCEDURE:
        parser(PROCEDURE);
        DECLARACAO_PROCEDIMENTO();
        break;
    case FUNCTION:
        parser(FUNCTION);
        DECLARACAO_FUNCAO();
        break;
    default:
        syntacticError();
    }
}

void DECLARACAO_PROCEDIMENTO()
{
    //* <DECLARACAO_PROCEDIMENTO> -> IDENTIFICADOR [<PARAMETROS_FORMAIS>]; <BLOCO>
    switch (tokenSyntactical.identifier)
    {
    case TOKEN:
        parser(TOKEN);
        PARAMETROS_FORMAIS();
        parser(PONTO_VIRGULA);
        BLOCO();
        break;
    default:
        syntacticError();
    }
}

void DECLARACAO_FUNCAO()
{
    //* <DECLARACAO_FUNCAO> -> IDENTIFICADOR [<PARAMETROS_FORMAIS>]: IDENTIFICADOR; <BLOCO>
    switch (tokenSyntactical.identifier)
    {
    case TOKEN:
        parser(TOKEN);
        PARAMETROS_FORMAIS();
        parser(DOIS_PONTOS);
        parser(TOKEN);
        parser(PONTO_VIRGULA);
        BLOCO();
        break;
    default:
        syntacticError();
    }
}

void PARAMETROS_FORMAIS()
{
    //* <PARAMETROS_FORMAIS> -> ( <SECAO_PARAMETROS_FORMAIS> )
    switch (tokenSyntactical.identifier)
    {
    case ABRE_PARENTESIS:
        parser(ABRE_PARENTESIS);
        SECAO_PARAMETROS_FORMAIS();
        parser(FECHA_PARENTESIS);
        break;
    //Caso não tenham parâmetros formais, voltar pra função
    case DOIS_PONTOS:
        break;
    case PONTO_VIRGULA:
        break;
    default:
        syntacticError();
    }
}

void SECAO_PARAMETROS_FORMAIS()
{
    //* <SECAO_PARAMETROS_FORMAIS> -> [VAR] <PARTE_SECAO_PARAMETROS_FORMAIS>
    switch (tokenSyntactical.identifier)
    {
    case VAR:
        parser(VAR);
        PARTE_SECAO_PARAMETROS_FORMAIS();
        break;
    case TOKEN:
        PARTE_SECAO_PARAMETROS_FORMAIS();
        break;
    default:
        syntacticError();
    }
}

void PARTE_SECAO_PARAMETROS_FORMAIS()
{
    //* <PARTE_SECAO_PARAMETROS_FORMAIS> -> IDENTIFICADOR <LISTA_IDENTIFICADOR>
    switch (tokenSyntactical.identifier)
    {
    case TOKEN:
        parser(TOKEN);
        LISTA_IDENTIFICADOR_PARAMETROS_FORMAIS();
        break;
    default:
        syntacticError();
    }
}

void LISTA_IDENTIFICADOR_PARAMETROS_FORMAIS()
{
    //* <LISTA_IDENTIFICADOR_PARAMETROS_FORMAIS> -> <, IDENTIFICADOR> : <IDENTIFICADOR>
    switch (tokenSyntactical.identifier)
    {
    case VIRGULA:
        parser(VIRGULA);
        PARTE_SECAO_PARAMETROS_FORMAIS(); //Declarar mais variável
        break;
    case DOIS_PONTOS:
        parser(DOIS_PONTOS);
        parser(TOKEN);
        FIM_SECAO_PARAMETROS_FORMAIS(); //Caso haja mais um parâmetros formais
        break;
    default:
        syntacticError();
    }
}

void FIM_SECAO_PARAMETROS_FORMAIS()
{
    //* <FIM_SECAO_PARAMETROS_FORMAIS> -> verificar se tem mais seção de parâmetros formais
    switch (tokenSyntactical.identifier)
    {
    //Declarar mais parametro formal
    case PONTO_VIRGULA:
        parser(PONTO_VIRGULA);
        SECAO_PARAMETROS_FORMAIS();
        break;
    }
}

void COMANDO_COMPOSTO()
{
    //* <COMANDO_COMPOSTO> -> BEGIN <COMANDOS> END
    switch (tokenSyntactical.identifier)
    {
    case BEGIN:
        parser(BEGIN);
        COMANDO();
        break;
    default:
        syntacticError();
    }
}

void COMANDO()
{
    //* <COMANDO> -> [<NUMERO>;] <COMANDO_SEM_ROTULO>
    switch (tokenSyntactical.identifier)
    {
    case NUMERO:
        parser(NUMERO);
        parser(DOIS_PONTOS);
        COMANDO_SEM_ROTULO();
        FIM_COMANDO();
        break;
    default:
        COMANDO_SEM_ROTULO();
        FIM_COMANDO();
        break;
    }
}

void FIM_COMANDO()
{
    //* <FIM_COMANDO> -> verificar se tem mais comandos
    switch (tokenSyntactical.identifier)
    {
    //Declarar mais comandos pós fim de comando em comando composto
    case PONTO_VIRGULA:
        parser(PONTO_VIRGULA);
        COMANDO();
        break;
    case END:
        parser(END);
        break;
    }
}

void COMANDO_SEM_ROTULO()
{
    //* <COMANDO_SEM_ROTULO> -> <ATRIBUICAO> | <CHAMADA_PROCEDIMENTO_OU_FUNCAO> | <DESVIO> | <COMANDO COMPOSTO> | <COMANDO CONDICIONAL> | <COMANDO REPETITIVO>
    switch (tokenSyntactical.identifier)
    {
    //Atribuição ou Chamada Procedimento
    case TOKEN:
        parser(TOKEN);
        ATRIBUICAO_OU_PROCEDIMENTO();
        FIM_COMANDO();
        break;
    //Comando Composto
    case BEGIN:
        COMANDO_COMPOSTO();
        FIM_COMANDO();
        break;
    case END:
        break;
    //Comando Condicional
    case IF:
        COMANDO_CONDICIONAL();
        FIM_COMANDO();
        break;
    //Comando Repetitivo
    case WHILE:
        COMANDO_REPETITIVO();
        FIM_COMANDO();
        break;
    //Entrada de Dados (READ)
    case READ:
        parser(READ);
        parser(ABRE_PARENTESIS);
        COMANDO_LEITURA_DADOS();  //Variáveis de Leitura de Dados
        parser(FECHA_PARENTESIS);
        FIM_COMANDO();
        break;
    //Saída de Dados (WRITE) 
    case WRITE:
        parser(WRITE);
        parser(ABRE_PARENTESIS);
        EXPRESSAO();            //Expressão para saída..
        parser(FECHA_PARENTESIS);
        FIM_COMANDO();
        break;   
    default:
        syntacticError();
    }
}

void ATRIBUICAO_OU_PROCEDIMENTO()
{
    //* <ATRIBUICAO_OU_PROCEDIMENTO> -> Atribuição          => IDENTIFICADOR := EXPRESSAO
    //*                              -> Procedimento/Função => IDENTIFICADOR [ ( LISTA_DE_EXPRESSOES ) ]
    switch (tokenSyntactical.identifier)
    {
    //Atribuição
    case DOISPONTOS_IGUAL:
        ATRIBUICAO();
        break;
    //Procedimento/Função
    default:
        CHAMADA_PROCEDIMENTO();
        break;
    }
}

void ATRIBUICAO()
{
    //* <ATRIBUICAO> -> IDENTIFICADOR := EXPRESSAO
    switch (tokenSyntactical.identifier)
    {
    //Atribuição
    case DOISPONTOS_IGUAL:
        parser(DOISPONTOS_IGUAL);
        EXPRESSAO();
        break;
    default:
        syntacticError();
    }
}

void CHAMADA_PROCEDIMENTO()
{
    //* <CHAMADA_PROCEDIMENTO> -> IDENTIFICADOR [ ( LISTA_EXPRESSOES ) ]
    switch (tokenSyntactical.identifier)
    {
    case ABRE_PARENTESIS:
        parser(ABRE_PARENTESIS);
        EXPRESSAO();
        parser(FECHA_PARENTESIS);
        break;
    }
}

void COMANDO_CONDICIONAL()
{
    //* <COMANDO_CONDICIONAL> -> IF <EXPRESSAO> THEN <COMANDO_SEM_ROTULO>
    switch (tokenSyntactical.identifier)
    {
    case IF:
        parser(IF);
        EXPRESSAO();
        parser(THEN);
        COMANDO_SEM_ROTULO();
        FIM_COMANDO_CONDICIONAL(); //Verificando se tem ELSE
        break;
    default:
        syntacticError();
    }
}

void FIM_COMANDO_CONDICIONAL()
{
    //* <FIM_COMANDO_CONDICIONAL> -> verificar se tem ELSE
    switch (tokenSyntactical.identifier)
    {
    case ELSE:
        parser(ELSE);
        COMANDO_SEM_ROTULO();
        break;
    }
}

void COMANDO_REPETITIVO()
{
    //* <COMANDO_REPETITIVO> -> WHILE <EXPRESSAO> DO <COMANDO_SEM_ROTULO>
    switch (tokenSyntactical.identifier)
    {
    case WHILE:
        parser(WHILE);
        EXPRESSAO();
        parser(DO);
        COMANDO_SEM_ROTULO();
        break;
    default:
        syntacticError();
    }
}

void COMANDO_LEITURA_DADOS(){
    //* <COMANDO_LEITURA_DADOS> -> IDENTIFICADOR { <FIM_COMANDO_LEITURA_DADOS> }
    switch (tokenSyntactical.identifier)
    {
    case TOKEN:
        parser(TOKEN);
        FIM_COMANDO_LEITURA_DADOS();    //Ver se tem mais variável
        break;
    default:
        syntacticError();
    }
}

void FIM_COMANDO_LEITURA_DADOS(){
    //* <COMANDO_LEITURA_DADOS> -> { , <COMANDO_LEITURA_DADOS> } (vários)
    switch (tokenSyntactical.identifier)
    {
    case VIRGULA:
        parser(VIRGULA);
        COMANDO_LEITURA_DADOS();    //Uso de mais variáveis
        break;
    }
}

void EXPRESSAO()
{
    //* <EXPRESSAO> -> <EXPRESSAO_SIMPLES> [ <EXPRESSAO_COM_RELACAO> ]
    EXPRESSAO_SIMPLES();
    EXPRESSAO_COM_RELACAO(); //Caso haja uma <RELACAO> <EXPRESSAO_SIMPLES>
    LISTA_DE_EXPRESSAO();    //Caso haja mais de uma expressão
}

void EXPRESSAO_SIMPLES()
{
    //* <EXPRESSAO_SIMPLES> ->  [+|-] <TERMO> { <EXPRESSAO_SIMPLES_OPCIONAL> }
    switch (tokenSyntactical.identifier)
    {
    case SOMA:
        parser(SOMA);
        TERMO();
        EXPRESSAO_SIMPLES_OPCIONAL();
        break;
    case SUBTRAI:
        parser(SUBTRAI);
        TERMO();
        EXPRESSAO_SIMPLES_OPCIONAL();
        break;
    default:
        TERMO();
        EXPRESSAO_SIMPLES_OPCIONAL();
        break;
    }
}

void EXPRESSAO_SIMPLES_OPCIONAL()
{
    //* <EXPRESSAO_SIMPLES_OPCIONAL> ->   + | - | OR <TERMO>
    switch (tokenSyntactical.identifier)
    {
    case SOMA:
        parser(SOMA);
        TERMO();
        break;
    case SUBTRAI:
        parser(SUBTRAI);
        TERMO();
        break;
    case OR:
        parser(OR);
        TERMO();
        break;
    }
}

void EXPRESSAO_COM_RELACAO()
{
    //* <EXPRESSAO_COM_RELACAO> -> <RELACAO><EXPRESSAO_SIMPLES>
    switch (tokenSyntactical.identifier)
    {
    case IGUAL:
        parser(IGUAL);
        EXPRESSAO_SIMPLES();
        break;
    case DIFERENTE:
        parser(DIFERENTE);
        EXPRESSAO_SIMPLES();
        break;
    case MENOR_QUE:
        parser(MENOR_QUE);
        EXPRESSAO_SIMPLES();
        break;
    case MENOR_IGUAL_QUE:
        parser(MENOR_IGUAL_QUE);
        EXPRESSAO_SIMPLES();
        break;
    case MAIOR_QUE:
        parser(MAIOR_QUE);
        EXPRESSAO_SIMPLES();
        break;
    case MAIOR_IGUAL_QUE:
        parser(MAIOR_IGUAL_QUE);
        EXPRESSAO_SIMPLES();
        break;
    }
}

void LISTA_DE_EXPRESSAO()
{
    //* <LISTA_DE_EXPRESSAO> -> {, <EXPRESSAO>}
    switch (tokenSyntactical.identifier)
    {
    case VIRGULA:
        parser(VIRGULA);
        EXPRESSAO();
        break;
    }
}

void TERMO()
{
    //* <TERMO> -> <FATOR> { FATOR_COM_OPERACAO }
    FATOR();
    FATOR_COM_OPERACAO(); //Opcional...
}

void FATOR()
{
    //* <FATOR> -> <VARIAVEL> | <NUMERO> | <CHAMADA_FUNCAO> | ( <EXPRESSAO> ) | NOT <FATOR>
    switch (tokenSyntactical.identifier)
    {
    //Variável ou Chamada Função
    case TOKEN:
        parser(TOKEN);
        CHAMADA_PROCEDIMENTO(); //Verifica se é chamada de função com lista de expressões
        break;
    //Número
    case NUMERO:
        parser(NUMERO);
        break;
    //Expressão
    case ABRE_PARENTESIS:
        parser(ABRE_PARENTESIS);
        EXPRESSAO();
        parser(FECHA_PARENTESIS);
        break;
    //NOT
    case NOT:
        parser(NOT);
        FATOR();
        break;
    default:
        syntacticError();
    }
}

void FATOR_COM_OPERACAO()
{
    //* <FATOR_COM_OPERACAO> -> * | DIV | AND <FATOR>
    switch (tokenSyntactical.identifier)
    {
    case MULTIPLICA:
        parser(MULTIPLICA);
        FATOR();
        break;
    case DIV:
        parser(DIV);
        FATOR();
        break;
    case AND:
        parser(AND);
        FATOR();
        break;
    }
}


///////////////////////////////////////////////////////////
//* FUNÇÕES DE ARQUIVO *//
///////////////////////////////////////////////////////////
//Abrir arquivo TEXTO
int readTextFile(FILE *(*file), char *filename, char *mode)
{
    //Tenta abrir o arquivo texto por algum modo (escrita/leitura)
    return ((*file) = fopen(filename, mode));
}

//Mostrar conteúdo do Arquivo TEXTO por CARACTERE
void printTextFile(FILE *file)
{
    char character;
    while (!feof(file))
    {
        character = getc(file);
        if (!feof(file)) //Não printar o fim de arquivo
            printf("%c", character);
    }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void verTabelaSimbolos()
{
    if (isEmptyQueue(token))
    {
        printf("Tabelixo esta vazia.\n");
        return;
    }

    queue p;

    p = token->next;

    do
    {
        printf("ID: %d - Token: %s - Linha: %d\n", p->element.identifier, p->element.token, p->element.line);

        p = p->next;
    } while (p != token->next);

    printf("\n");
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

int main()
{

    //Inicializando variáveis globais
    token = NULL;

    //Abertura de Arquivo Texto
    FILE *file;
    char *filename = "Exemplo1_Trab2_Compiladores.txt"; //Diretório/Nome do arquivo (neste caso, local...)
    char *mode = "rt";                                  //Leitura de Arquivo Texto com opção de Escrita

    if (readTextFile(&file, filename, mode))
    {
        //Sucesso na abertura do arquivo texto!

        ///////////////////////////////////////////////////////////
        //* 1°: REALIZAR ANÁLISE LÉXICA E OBTER OS TOKENS E OS IDENTIFICADORES
        ///////////////////////////////////////////////////////////
        //Estruturas do Analisador Léxico
        char lex_token[MAX_LETTERS] = "\0"; //String auxiliar para verificação léxica
        varSymbol = -1;                     //Inicia a identificação GLOBAL com nulo (-1)
        int countTableSymbol;               //Contador para os identificadores na inserção da Tabela de Símbolos

        //Caractere do Código (variável "proximo") e a do anterior ("s")
        char characterCode = '\0', prevCharacterCode;

        //Auxiliares para os simbolos especiais compostos
        char specialSymbol[5] = "\0"; //String auxiliar para salvar simbolos especiais compostos (ex: <=)

        //Linha em análise do código
        lld line = 1;

        //Inicializando a Tabela de Símbolos
        symbolTable = NULL;
        insertSpecialSymbolsOnSymbolTable(&countTableSymbol);

        //Início de verificação do Analisador Léxico
        characterCode = PROXIMO_LEXICO(file); //Realiza a leitura do primeiro caractere
        while (!feof(file))
        {
            //Reseta a string que contém os tokens para próximo token
            strcpy(lex_token, "\0");

            //Reseta a string associada ao símbolo especial composto
            strcpy(specialSymbol, "\0");

            //SPACE na Tabela ASCII = 32
            if (characterCode > 32)
            {
                //Análise de Símbolos Especiais e Símbolos Especiais Compostos
                if (isSpecialSymbol(characterCode))
                {
                    //String associada ao símbolo especial composto
                    strncat(specialSymbol, &characterCode, 1);

                    //Recuperando o próximo caractere
                    prevCharacterCode = characterCode;
                    characterCode = PROXIMO_LEXICO(file);
                    
                    //Símbolo-> >=
                    if (prevCharacterCode == '>')
                    {
                        if (characterCode == '=')
                        {
                            strncat(specialSymbol, &characterCode, 1);
                        }
                    }
                    //Símbolo-> <=
                    else if (prevCharacterCode == '<')
                    {
                        if (characterCode == '=')
                        {
                            strncat(specialSymbol, &characterCode, 1);
                        }
                    }
                    //Símbolo-> :=
                    else if (prevCharacterCode == ':')
                    {
                        if (characterCode == '=')
                        {
                            strncat(specialSymbol, &characterCode, 1);
                        }
                    }
                    //Símbolo-> ..
                    else if (prevCharacterCode == '.')
                    {
                        if (characterCode == '.')
                        {
                            strncat(specialSymbol, &characterCode, 1);
                        }
                    }
                    //Símbolo-> (*
                    else if (prevCharacterCode == '(')
                    {
                        if (characterCode == '*')
                        {
                            strncat(specialSymbol, &characterCode, 1);
                        }
                    }
                    //Símbolo-> *)
                    else if (prevCharacterCode == '*')
                    {
                        if (characterCode == ')')
                        {
                            strncat(specialSymbol, &characterCode, 1);
                        }
                    }

                    //Retorna o valor do Símbolo Especial associado
                    varSymbol = CODIGO_LEXICO(specialSymbol, &countTableSymbol);

                    //Salvando os tokens na fila para a análise sintática
                    pushQueue(&varSymbol, specialSymbol, &line);
                }

                //Análise de Letras e Palavras-Chave
                else if (isLetter(characterCode))
                {
                    do
                    {
                        strncat(lex_token, &characterCode, 1);
                        characterCode = PROXIMO_LEXICO(file);
                    } while (isLetterOrNumber(characterCode));

                    //Retornando o código identificador de uma PALAVRA-CHAVE ou de um novo Átomo
                    varSymbol = CODIGO_LEXICO(lex_token, &countTableSymbol);

                    //Salvando os tokens na fila para a análise sintática
                    pushQueue(&varSymbol, lex_token, &line);
                }

                //Análise de Números
                else if (isNumber(characterCode))
                {
                    do
                    {
                        strncat(lex_token, &characterCode, 1);
                        characterCode = PROXIMO_LEXICO(file);
                    } while (isNumber(characterCode));

                    //Caso haja letras após uma sequencia de números...
                    if (isLetter(characterCode))
                    {
                        ERRO_LEXICO(line);
                    }

                    //Retornando o código identificador de um NÚMERO
                    varSymbol = CODIGO_LEXICO(lex_token, &countTableSymbol);

                    //Salvando os tokens na fila para a análise sintática
                    pushQueue(&varSymbol, lex_token, &line);
                }

                //Retorna erro em não ocorrência aos casos anteriores
                else
                {
                    ERRO_LEXICO(line);
                }

                //Realizando manipulações no ponteiro de arquivo após espaços vazios
                if (characterCode >= 32)
                {
                    fseek(file, -1, SEEK_CUR);
                }

                //Caso tenha tido um símbolo especial, avança o último caractere
                if (strlen(specialSymbol) > 1)
                {
                    characterCode = PROXIMO_LEXICO(file);
                }
            }

            //Pulando as quebras de linha e armazenando na variável
            if (characterCode == '\n')
            {
                line++;
            }

            //Realiza a leitura eliminando os espaços
            characterCode = PROXIMO_LEXICO(file);
        }
        //Sucesso na análise léxica! Tokens foram armazenados =)

        //Fechar arquivo após o uso
        fclose(file);
    }
    else
    {
        //Erro na abertura de arquivo
        printf("Erro na abertura de arquivo!\n\n");
        printf("Pressione ENTER para sair...");
        getchar();
        exit(0);
    }

    //verTabelaSimbolos();  //Resultado da Análise Léxica (ID, Token e Linha)

    ///////////////////////////////////////////////////////////
    //* 2°: REALIZAR ANÁLISE SINTÁTICA
    //* --------------------------------------------------- *//
    //* OBS: SOMENTE REALIZADO APÓS ANÁLISE LÉXICA!
    ///////////////////////////////////////////////////////////
    
    //Início da Análise Sintática pela função startSyntacticAnalyzer
    startSyntacticAnalyzer();

    //Caso tenha analisado tudo, significa que não houve erros: sucesso na análise sintática
    printf("\nSUCESSO NA ANALISE SINTATICA DO CODIGO-FONTE!\n\n");

    printf("Pressione ENTER para sair...");
    getchar();

    return 0;
}