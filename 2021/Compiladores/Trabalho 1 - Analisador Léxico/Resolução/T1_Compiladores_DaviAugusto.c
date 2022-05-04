/*
Nome: Davi Augusto Neves Leite
RA: 191027383

Realizado em: Windows 10 (x64) e compilado pelo TDM-GCC x64 (https://jmeubank.github.io/tdm-gcc/)
Deixar o programa e arquivo texto (Trab1_Compiladores.txt) no MESMO DIRETÓRIO.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN 1000               //Define o tamanho máximo de escrita de um átomo
#define MAX_KEYWORD 20              //Define o tamanho máximo das palavras reservadas
#define MAX_SYMBOL 12               //Define o conjunto máximo de símbolos especiais da linguagem

typedef long long int lld;

//Variáveis GLOBAIS
int varSymbol; //Marca o código de identificação do último átomo analisado

//Par de identificador e token
typedef struct pair pairSymbol;
struct pair{
    int identifier;           //Salva o identificador (número) do átomo associado
    char token[MAX_TOKEN];    //Salva o átomo associado
};

//Tabela de Símbolos por LISTA ENCADEADA (não se sabe o limite de átomos...)
typedef struct symbol *table;
struct symbol{
    pairSymbol pair;    //Par com o identificador e o átomo (palavra) associada
    struct symbol *prox;
};
table symbolTable;

///////////////////////////////////////////////////////////
//* FUNÇÕES DO ANALISADOR LÉXICO *//
///////////////////////////////////////////////////////////
//Função PROXIMO: responsável por pular linhas vazias e espaços em branco
char PROXIMO(FILE *arq){
    return toupper(fgetc(arq));
}
///////////////////////////////////////////////////////////
//Função CÓDIGO: responsável por verificar na tabela (matriz) de símbolos os identificadores e seus respectivos átomos associados!
//Insere caso não esteja contido na tabela...
int CODIGO(char *token, lld *countTableSymbol){
    //Percorre a tabela de símbolos em busca do átomo associado
    table p = symbolTable;
    while(p){
        if(strcmp(p->pair.token, token) == 0){
            return p->pair.identifier;
        }
        p = p->prox;
    }

    //Caso não tenha encontrado nada, insere o átomo na tabela e retorna o valor do identificador associado
    pairSymbol pair;
    pair.identifier = (*countTableSymbol)++;
    strcpy(pair.token, token);

    endInsertList(pair); //Inserção no fim da Tabela de Símbolos

    return pair.identifier; //Retorna o identificador do elemento inserido atualmente
}

///////////////////////////////////////////////////////////
//Função ERRO: retorna um erro ao usuário e a linha em que foi encontrado o erro
void ERRO(lld line){
    printf("\nERRO DE COMPILACAO!\n\n");
    printf("Ocorreu um erro lexico na linha %lld do codigo-fonte!", line);
    printf("\n\n");
    system("PAUSE");
    exit(0);
}

///////////////////////////////////////////////////////////
//Verificador de LETRAS
int isLetter(char character){
    return ((character >= 'A') && (character <= 'Z'));
}

//Verificador de NÚMEROS
int isNumber(char character){
    return ((character >= '0') && (character <= '9'));
}

//Verificador de LETRAS e DÍGITOS
int isLetterOrNumber(char character){
    return (isLetter(character) || isNumber(character));
}

//Verificador de SÍMBOLOS ESPECIAIS
int isSpecialSymbol(char character){
    //Símbolos Especiais do PASCAL
    char symbols[MAX_SYMBOL] = {".;,():=<>+-*"};

    int i;
    for(i = 0; i < MAX_SYMBOL; i++){
        if(character == symbols[i]){
            //Caso o caractere seja um símbolo especial
            return 1;
        }
    }
    return 0;
}

//Verificador de PALAVRAS-CHAVE
void isKeyword(char *word){
    ///////////////////////////////////////////////////////////
    //Palavras e Símbolos Reservados do PASCAL
    ///////////////////////////////////////////////////////////
    char keywords[][MAX_KEYWORD] = {"TK_PROGRAM", "TK_LABEL", "TK_VAR", "TK_PROCEDURE",
                                    "TK_FUNCTION", "TK_BEGIN", "TK_END", "TK_IF", "TK_THEN",
                                    "TK_ELSE", "TK_WHILE", "TK_DO", "TK_OR", "TK_AND", "TK_DIV",
                                    "TK_NOT", "DOT", "SEMICOLOR", "COMMA", "OPEN_PAIR",
                                    "CLOSE_PAIR", "OPEN_BRACKET", "CLOSE_BRACKET",
                                    "COLON", "EQUALS", "DIFFERENT", "MORE_THAN", "LESS_THAN",
                                    "MORE_EQUALS_THAN", "LESS_EQUALS_THAN", "PLUS",
                                    "MINUS", "MULTIPLY", "TK_ASSIGNMENT", "TWO_COLON", "TK_OPEN_COMMENT",
                                    "TK_CLOSE_COMMENT", "TK_READ", "TK_WRITE", "TK_INTEGER", "TK_BOOLEAN"};

    int size = *(&keywords + 1) - keywords; //Tamanho da tabela de palavras-chave
    if (varSymbol > 0 && varSymbol <= size){
        strcpy(word, keywords[varSymbol - 1]);
    }
}

///////////////////////////////////////////////////////////
//* FUNÇÕES DA LISTA ENCADEADA *//
///////////////////////////////////////////////////////////
//Inserir ao fim da lista
void endInsertList(pairSymbol pair){
    //Alocando espaço para inserção
    table p = (table) malloc(sizeof(struct symbol));
    //Recebendo a informação
    p->pair = pair;
    p->prox = NULL;
    
    //Caso a lista esteja nula
    if(symbolTable == NULL){
        symbolTable = p;
    }
    else{
        table q = symbolTable;
        while(q->prox){
            q = q->prox;
        }
        q->prox = p;
    }
}

//Percorre a lista e retorna o par (identificador, token) associado
void retPairSymbol(int identifier, pairSymbol *auxPair){
    table p = symbolTable;

    (*auxPair).identifier = -1;

    while(p){
        if(p->pair.identifier == identifier){
            (*auxPair) = p->pair;
            break;
        }
        p = p->prox;
    }
}

///////////////////////////////////////////////////////////
//* FUNÇÕES DE ARQUIVO *//
///////////////////////////////////////////////////////////
//Abrir arquivo TEXTO
int readTextFile(FILE *(*arq), char *filename, char *mode){
    //Tenta abrir o arquivo texto por algum modo (escrita/leitura)
    return ((*arq) = fopen(filename, mode));
}
//Mostrar conteúdo do Arquivo TEXTO por CARACTERE
void printTextFile(FILE *arq){
    char character;
    while (!feof(arq)){
        character = getc(arq);
        if (!feof(arq)) //Não printar o fim de arquivo
            printf("%c", character);
    }
}
///////////////////////////////////////////////////////////
//* OUTRAS FUNÇÕES *//
///////////////////////////////////////////////////////////
//Inserir os Símbolos Especiais, Símbolos Especiais Compostos e Palavras-Chave na Tabela de Símbolos
void insertSpecialSymbolsOnSymbolTable(lld *countTableSymbol){
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

///////////////////////////////////////////////////////////

int main(){

    //Abertura de Arquivo Texto
    FILE *arq;
    char *filename = "Trab1_Compiladores.txt"; //Diretório/Nome do arquivo (neste caso, local...)
    char *mode = "rt"; //Leitura de Arquivo Texto com opção de Escrita

    if(readTextFile(&arq, filename, mode)){
        //Sucesso na abertura do arquivo texto!
        
        ///////////////////////////////////////////////////////////////
        //Estruturas do Analisador Léxico
        ///////////////////////////////////////////////////////////////
        //Átomo/Token (palavra encontrada)
        char token[MAX_TOKEN] = "\0";
        varSymbol = -1;         //Inicia a identificação GLOBAL com nulo (-1)
        lld countTableSymbol;   //Contador para os identificadores na inserção da Tabela de Símbolos

        //Caractere do Código (variável "proximo") e a do anterior ("s")
        char characterCode = '\0', prevCharacterCode;

        //Auxiliares para os simbolos especiais compostos
        char specialSymbol[5] = "\0"; //String auxiliar para salvar simbolos especiais compostos (ex: <=)

        //Linha em análise do código
        lld line = 1;

        //Inserção das palavras e símbolos pré-definidos na Tabela de Símbolos
        symbolTable = NULL;
        insertSpecialSymbolsOnSymbolTable(&countTableSymbol);

        ///////////////////////////////////////////////////////////////
        //Início de verificação do Analisador Léxico
        ///////////////////////////////////////////////////////////////
        
        printf("%d.\t", line);
        
        //Percorrer o arquivo texto
        characterCode = PROXIMO(arq); //Realiza a leitura do primeiro caractere
        while (!feof(arq))
        {

            //Reseta a string que contém os tokens para próximo token
            strcpy(token, "\0");

            //Reseta a string associada ao símbolo especial composto
            strcpy(specialSymbol, "\0");

            //Não é caractere especial = SPACE pra anterior na tabela ASCII
            if(characterCode > 32)
            {
                ///////////////////////////////////////////////////////////////
                //Análise de Símbolos Especiais e Símbolos Especiais Compostos
                ///////////////////////////////////////////////////////////////
                if (isSpecialSymbol(characterCode))
                {
                    //String associada ao símbolo especial composto
                    strncat(specialSymbol, &characterCode, 1);

                    //Recuperando o próximo caractere
                    prevCharacterCode = characterCode;
                    characterCode = PROXIMO(arq);

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
                    varSymbol = CODIGO(specialSymbol, &countTableSymbol);
                    
                    printf(" %s", specialSymbol);
                }

                ///////////////////////////////////////////////////////////////
                //Análise de Letras e Palavras-Chave
                ///////////////////////////////////////////////////////////////
                else if (isLetter(characterCode))
                {
                    do
                    {
                        strncat(token, &characterCode, 1);
                        characterCode = PROXIMO(arq);
                    } while (isLetterOrNumber(characterCode));

                    //Retornando o código identificador de uma PALAVRA-CHAVE ou de um novo Átomo
                    varSymbol = CODIGO(token, &countTableSymbol);
                    
                    printf(" %s", token);
                }

                ///////////////////////////////////////////////////////////////
                //Análise de Números
                ///////////////////////////////////////////////////////////////
                else if (isNumber(characterCode))
                {
                    do
                    {
                        strncat(token, &characterCode, 1);
                        characterCode = PROXIMO(arq);
                    } while (isNumber(characterCode));

                    //Caso haja letras após uma sequencia de números...
                    if (isLetter(characterCode))
                    {
                        ERRO(line);
                    }

                    varSymbol = CODIGO(token, &countTableSymbol);

                    strcpy(token, "NUMBER");
                    printf(" %s", token);
                }

                ///////////////////////////////////////////////////////////////
                //Retorna erro em não ocorrência aos casos anteriores
                ///////////////////////////////////////////////////////////////
                else
                {
                    ERRO(line);
                }

                //Realizando manipulações no ponteiro de arquivo após espaços vazios
                if (characterCode >= 32)
                {
                    fseek(arq, -1, SEEK_CUR);
                }

                //Caso tenha tido um símbolo especial, avança o último caractere
                if (strlen(specialSymbol) > 1)
                {
                    characterCode = PROXIMO(arq);
                }
            }

            //Pulando as quebras de linha e armazenando na variável
            if (characterCode == '\n')
            {
                line++;

                printf("\n%d.\t", line);
            }

            //Realiza a leitura eliminando os espaços
            characterCode = PROXIMO(arq);
        }

        //Caso tenha passado em TODOS os testes...
        printf("\n\nSUCESSO NA ANALISE LEXICA DO CODIGO-FONTE!\n\n");

        //Fechar arquivo após o uso
        fclose(arq);
    }
    else{
        //Erro na abertura de arquivo
        printf("Erro na abertura de arquivo!\n\n");
    }

    system("PAUSE");
    return 0;
}
