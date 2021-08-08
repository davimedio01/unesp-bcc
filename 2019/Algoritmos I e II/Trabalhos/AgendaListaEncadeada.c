//Trabalho 6: Agenda de Alocação Dinâmica - Algoritmos II
//Alunos: Davi Augusto e Luiz Sementille
//Curso: BCC
//Data de Entrega: 02/12/2019

//Utilizar o Encoding "Windows 1252"
//Tamanho da Janela do Console: 120x30 (LxA) (para uma melhor experiência)

/*Funções da Agenda:
Inserir Compromisso (Data + Horário + TextoDescritivo);
Remover Compromisso(s) De Determinada Data (Todos);
Remover Determinado Compromisso (com base em uma palavra);
Consultar Compromisso(s);
Procurar Compromisso(s) Com Determinada Palavra Indicada;
Alterar Compromisso Com Determinada Palavra Indicada;
Alterar Compromisso Com Determinada Data e Horário;
Salvar Compromisso(s) em Arquivo Texto (agenda.txt);
Ler Compromisso(s) do Arquivo Texto (agenda.txt)
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

//Teclas em ASCII
#define CIMA 72
#define BAIXO 80
#define DIREITA 77
#define ESQUERDA 75
#define ESC 27
#define ENTER 13
#define BACKSPACE 8

#define max 82

//Struct da Data/Hora
typedef struct{
    int dia, mes, ano, hora, minutos;
}DataHora;

//Struct da Agenda
typedef struct Agenda *no;
struct Agenda
{
    char compromisso[max];
    DataHora data;
    struct Agenda *prox;
};

//Funções
//Funções dos Menus
void moveXY (int x, int y, char t[]);
void Menu_Principal();

int main()
{
	system("COLOR 4F");
    //system("COLOR 1F");
	setlocale(LC_ALL,"Portuguese");

    //Variáveis de Manipulação e Troca dos Menus
	char opcao_menuprincipal, opcao_submenu, opcao_funcao;
	short posX=11, posY=6;
	short posX_sub, posY_sub;
	int funcao[2], i;

    //Declaração da Lista e Auxiliares
    no Agenda = NULL;
    char compromisso[max];
    DataHora data;

    funcao[0]=0;  //Executando o Menu_Principal a primeira vez
    Menu_Principal();

    while(opcao_menuprincipal!=ESC)
    {
        //Executar Menu_Principal -> Opções de Manipulação
        if(funcao[0]==0)
        {
            moveXY(posX, posY, "->");
            opcao_menuprincipal = toupper(getch());

            switch(opcao_menuprincipal)
            {
                case DIREITA:
                    if(posX<67)
                    {
                        moveXY(posX,posY, "  ");
                        posX+=56;
                        posY=6;
                        moveXY(posX,posY, "->");
                        Beep(450,100);
                    }
                    break;
                case ESQUERDA:
                    if(posX>11)
                    {
                        moveXY(posX,posY, "  ");
                        posX-=56;
                        posY=6;
                        moveXY(posX,posY, "->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY<14 && posX==11)
                    {
                        if(posY==6)
                        {
                            moveXY(posX,posY, "  ");
                            posY+=2;
                            moveXY(posX,posY, "->");
                            Beep(450,100);
                        }
                        else if(posY==8)
                        {
                            moveXY(posX,posY, "  ");
                            posY+=6;
                            moveXY(posX,posY, "->");
                            Beep(450,100);
                        }
                    }
                    else if(posY<18 && posX==67)
                    {
                        moveXY(posX,posY, "  ");
                        posY+=6;
                        moveXY(posX,posY, "->");
                        Beep(450,100);
                    }
                    break;
                case CIMA:
                    if(posY>6 && posX==11)
                    {
                        if(posY==8)
                        {
                            moveXY(posX,posY, "  ");
                            posY-=2;
                            moveXY(posX,posY, "->");
                            Beep(450,100);
                        }
                        else if(posY==14)
                        {
                            moveXY(posX,posY, "  ");
                            posY-=6;
                            moveXY(posX,posY, "->");
                            Beep(450,100);
                        }
                    }
                    else if(posY>6 && posX==67)
                    {
                        moveXY(posX,posY, "  ");
                        posY-=6;
                        moveXY(posX,posY, "->");
                        Beep(450,100);
                    }
                    break;
                case ENTER:
                    if(posX==11 && posY==6)
                    {
                        moveXY(posX,posY, "  ");
                        funcao[0]=1; //Entrar na Função: Inserir
                        funcao[1]=0;
                    }
                    else if(posX==11 && posY==8)
                    {
                        moveXY(posX,posY, "  ");
                        funcao[0]=2; //Entrar no Sub-Menu: Remoções
                        funcao[1]=0;
                        posX_sub=14;
                        posY_sub=10;
                    }
                    else if(posX==11 && posY==14)
                    {
                        moveXY(posX,posY, "  ");
                        funcao[0]=3; //Entrar no Sub-Menu: Consultas
                        funcao[1]=0;
                        posX_sub=14;
                        posY_sub=16;
                    }
                    else if(posX==67 && posY==6)
                    {
                        moveXY(posX,posY, "  ");
                        funcao[0]=4; //Entrar no Sub-Menu: Alterações
                        funcao[1]=0;
                        posX_sub=70;
                        posY_sub=8;
                    }
                    else if(posX==67 && posY==12)
                    {
                        moveXY(posX,posY, "  ");
                        funcao[0]=5; //Entrar no Sub-Menu: Backup
                        funcao[1]=0;
                        posX_sub=70;
                        posY_sub=14;
                    }
                    else if(posX==67 && posY==18)
                    {
                        moveXY(posX,posY, "  ");
                        funcao[0]=6; //Entrar no Bônus: Exibir Agenda
                        funcao[1]=0;
                    }
                    break;
                case ESC:
                    system("cls");
                    break;
            }
        }
        else if(funcao[0]==1 && !funcao[1]) //Função: Inserir Compromisso(s)
        {
            system("cls");
            moveXY(43,2, ":::INSERIR COMPROMISSO(S):::");

            do
            {
                moveXY(3,5, "::Compromisso:: ");
                moveXY(3,7, "Nome do Compromisso: ");
                scanf(" %[^\n]s", &compromisso);
                moveXY(3,9, "::Data::");
                moveXY(3,11, "Dia (DD): ");
                scanf("%d", &data.dia);
                moveXY(3,12, "Mês (MM): ");
                scanf("%d", &data.mes);
                moveXY(3,13, "Ano (AAAA): ");
                scanf("%d", &data.ano);
                moveXY(3,15, "::Horário::");
                moveXY(3,17, "Hora (HH): ");
                scanf("%d", &data.hora);
                moveXY(3,18, "Minutos (MM): ");
                scanf("%d", &data.minutos);

                moveXY(3,21, "Inserindo compromisso. Por favor, aguarde...");
                Inserir_Compromisso(&Agenda, &compromisso, data);
                Sleep(3000);
                moveXY(3,24, "Compromisso inserido com sucesso!");
                moveXY(3,27, "");
                system("PAUSE");

                system("cls");
                moveXY(43,2, ":::INSERIR COMPROMISSO(S):::");
                do
                {
                    moveXY(3,5, "Deseja inserir outro compromisso na agenda?");
                    moveXY(3,6, "Tecle 'S' para Sim ou 'N' para Não: ");
                    opcao_funcao = toupper(getch());
                }while(opcao_funcao != 'N' && opcao_funcao != 'S');
                if(opcao_funcao == 'S')
                {
                    system("cls");
                    moveXY(43,2, ":::INSERIR COMPROMISSO(S):::");
                }
            }while(opcao_funcao != 'N');

            funcao[0]=0;
            system("cls");
            Menu_Principal();
        }
        else if(funcao[0]==2 && !funcao[1]) //Sub-Menu: Remoções
        {
            moveXY(posX_sub, posY_sub, "->");
            opcao_submenu = toupper(getch());

            switch(opcao_submenu)
            {
                case CIMA:
                    if(posY_sub>10)
                    {
                        moveXY(posX_sub,posY_sub, "  ");
                        posY_sub-=2;
                        moveXY(posX_sub,posY_sub, "->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY_sub<12)
                    {
                        moveXY(posX_sub,posY_sub, "  ");
                        posY_sub+=2;
                        moveXY(posX_sub,posY_sub, "->");
                        Beep(450,100);
                    }
                    break;
                case ENTER:
                    if(posY_sub==10)
                    {
                        funcao[1]=1;
                    }
                    else if(posY_sub==12)
                    {
                        funcao[1]=2;
                    }
                    break;
                case ESC:
                    moveXY(posX_sub, posY_sub, "  ");
                    funcao[0]=0;
                    break;
            }
        }
        else if(funcao[0]==2 && funcao[1]==1) //Função: Remover -> Determinada Data
        {
            system("cls");
            moveXY(40,2, ":::REMOVER COMPROMISSO(S) - DATA:::");

            moveXY(3,5, "::DATA (A SER CONSULTADA):: ");
            moveXY(3,8, "Dia (DD): ");
            scanf("%d", &data.dia);
            moveXY(3,9, "Mês (MM): ");
            scanf("%d", &data.mes);
            moveXY(3,10, "Ano (AAAA): ");
            scanf("%d", &data.ano);

            moveXY(3,13, "Consultando compromisso(s). Por favor, aguarde...");
            Sleep(3000);
            system("cls");
            moveXY(40,2, ":::REMOVER COMPROMISSO(S) - DATA:::");

            if(Remover_Data(&Agenda, data))
            {
                system("cls");
                moveXY(40,2, ":::REMOVER COMPROMISSO(S) - DATA:::");
                moveXY(3,5, "O(s) compromisso(s) dessa data foi(foram) removido(s) com sucesso!");
                moveXY(3,8, "");
                system("Pause");
            }
            else
            {
                system("cls");
                moveXY(40,2, ":::REMOVER COMPROMISSO(S) - DATA:::");
                moveXY(3,5, "O(s) compromisso(s) dessa data não foi(foram) removido(s). Tente novamente.");
                moveXY(3,8, "");
                system("Pause");
            }

            funcao[0]=0;
            system("cls");
            Menu_Principal();
        }
        else if(funcao[0]==2 && funcao[1]==2) //Função: Remover -> Busca Específica
        {
            system("cls");
            moveXY(42,2, ":::REMOVER COMPROMISSO - BUSCA:::");

            moveXY(3,5, "Digite a palavra a ser consultada: ");
            scanf(" %[^\n]s", &compromisso);
            moveXY(3,7, "Consultando compromisso(s). Por favor, aguarde...");
            Sleep(3000);
            system("cls");
            moveXY(42,2, ":::REMOVER COMPROMISSO - BUSCA:::");

            if(Remover_Desejado(&Agenda, &compromisso))
            {
                system("cls");
                moveXY(42,2, ":::REMOVER COMPROMISSO - BUSCA:::");
                moveXY(3,5, "O compromisso foi removido com sucesso!");
                moveXY(3,8, "");
                system("Pause");
            }
            else
            {
                system("cls");
                moveXY(42,2, ":::REMOVER COMPROMISSO - BUSCA:::");
                moveXY(3,5, "");
                system("Pause");
            }

            funcao[0]=0;
            system("cls");
            Menu_Principal();
        }
        else if(funcao[0]==3 && !funcao[1]) //Sub-Menu: Consultas
        {
            moveXY(posX_sub, posY_sub, "->");
            opcao_submenu = toupper(getch());

            switch(opcao_submenu)
            {
                case CIMA:
                    if(posY_sub>16)
                    {
                        moveXY(posX_sub,posY_sub, "  ");
                        posY_sub-=2;
                        moveXY(posX_sub,posY_sub, "->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY_sub<18)
                    {
                        moveXY(posX_sub,posY_sub, "  ");
                        posY_sub+=2;
                        moveXY(posX_sub,posY_sub, "->");
                        Beep(450,100);
                    }
                    break;
                case ENTER:
                    if(posY_sub==16)
                    {
                        funcao[1]=1;
                    }
                    else if(posY_sub==18)
                    {
                        funcao[1]=2;
                    }
                    break;
                case ESC:
                    moveXY(posX_sub, posY_sub, "  ");
                    funcao[0]=0;
                    break;
            }
        }
        else if(funcao[0]==3 && funcao[1]==1) //Função: Consultas -> Por Data
        {
            system("cls");
            moveXY(40,2, ":::CONSULTA COMPROMISSO(S) - DATA:::");

            moveXY(3,5, "::DATA (A SER CONSULTADA):: ");
            moveXY(3,8, "Dia (DD): ");
            scanf("%d", &data.dia);
            moveXY(3,9, "Mês (MM): ");
            scanf("%d", &data.mes);
            moveXY(3,10, "Ano (AAAA): ");
            scanf("%d", &data.ano);

            moveXY(3,13, "Consultando. Por favor, aguarde...");
            Sleep(3000);
            system("cls");
            moveXY(40,2, ":::CONSULTA COMPROMISSO(S) - DATA:::");

            Consulta_Total(Agenda, data);

            funcao[0]=0;
            system("cls");
            Menu_Principal();
        }
        else if(funcao[0]==3 && funcao[1]==2) //Função: Consultas -> Busca Específica
        {
            system("cls");
            moveXY(40,2, ":::CONSULTA COMPROMISSO(S) - BUSCA:::");

            moveXY(3,5, "Digite uma palavra a ser consultada: ");
            scanf(" %[^\n]s", &compromisso);
            moveXY(3,7, "Consultando. Por favor, aguarde...");
            Sleep(3000);
            system("cls");
            moveXY(40,2, ":::CONSULTA COMPROMISSO(S) - BUSCA:::");

            Consulta_Desejado(Agenda, &compromisso);

            funcao[0]=0;
            system("cls");
            Menu_Principal();
        }
        else if(funcao[0]==4 && !funcao[1]) //Sub-Menu: Alterações
        {
            moveXY(posX_sub, posY_sub, "->");
            opcao_submenu = toupper(getch());

            switch(opcao_submenu)
            {
                case CIMA:
                    if(posY_sub>8)
                    {
                        moveXY(posX_sub,posY_sub, "  ");
                        posY_sub-=2;
                        moveXY(posX_sub,posY_sub, "->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY_sub<10)
                    {
                        moveXY(posX_sub,posY_sub, "  ");
                        posY_sub+=2;
                        moveXY(posX_sub,posY_sub, "->");
                        Beep(450,100);
                    }
                    break;
                case ENTER:
                    if(posY_sub==8)
                    {
                        funcao[1]=1;
                    }
                    else if(posY_sub==10)
                    {
                        funcao[1]=2;
                    }
                    break;
                case ESC:
                    moveXY(posX_sub, posY_sub, "  ");
                    funcao[0]=0;
                    break;
            }
        }
        else if(funcao[0]==4 && funcao[1]==1) //Função: Alterações -> Por Data/Horário
        {
            system("cls");
            moveXY(38,2, ":::ALTERAR COMPROMISSO(S) - DATA/HORA:::");

            moveXY(3,5, "::DATA (A SER CONSULTADA):: ");
            moveXY(3,8, "Dia (DD): ");
            scanf("%d", &data.dia);
            moveXY(3,9, "Mês (MM): ");
            scanf("%d", &data.mes);
            moveXY(3,10, "Ano (AAAA): ");
            scanf("%d", &data.ano);
            moveXY(3,13, "::HORA (A SER CONSULTADA):");
            moveXY(3,16, "Hora (HH): ");
            scanf("%d", &data.hora);
            moveXY(3,17, "Minutos (MM): ");
            scanf("%d", &data.minutos);

            moveXY(3,20, "Consultando. Por favor, aguarde...");
            Sleep(3000);
            system("cls");
            moveXY(38,2, ":::ALTERAR COMPROMISSO(S) - DATA/HORA:::");
            if(Alterar_DataHora(&Agenda, data))
            {
                system("cls");
                moveXY(38,2, ":::ALTERAR COMPROMISSO(S) - DATA/HORA:::");
                moveXY(3,5, "O compromisso foi alterado com sucesso!");
                moveXY(3,8, "");
                system("Pause");
            }
            else
            {
                system("cls");
                moveXY(38,2, ":::ALTERAR COMPROMISSO(S) - DATA/HORA:::");
                moveXY(3,5, "");
                system("Pause");
            }

            funcao[0]=0;
            system("cls");
            Menu_Principal();
        }
        else if(funcao[0]==4 && funcao[1]==2) //Função: Alterações -> Busca Específica
        {
            system("cls");
            moveXY(42,2, ":::ALTERAR COMPROMISSO - BUSCA:::");

            moveXY(3,5, "Digite a palavra a ser consultada: ");
            scanf(" %[^\n]s", &compromisso);
            moveXY(3,7, "Consultando compromisso(s). Por favor, aguarde...");
            Sleep(3000);
            system("cls");
            moveXY(42,2, ":::ALTERAR COMPROMISSO - BUSCA:::");

            if(Alterar_Palavra(&Agenda, &compromisso))
            {
                system("cls");
                moveXY(42,2, ":::ALTERAR COMPROMISSO - BUSCA:::");
                moveXY(3,5, "O compromisso foi alterado com sucesso!");
                moveXY(3,8, "");
                system("Pause");
            }
            else
            {
                system("cls");
                moveXY(42,2, ":::ALTERAR COMPROMISSO - BUSCA:::");
                moveXY(3,5, "");
                system("Pause");
            }

            funcao[0]=0;
            system("cls");
            Menu_Principal();
        }
        else if(funcao[0]==5 && !funcao[1]) //Sub-Menu: Backup
        {
            moveXY(posX_sub, posY_sub, "->");
            opcao_submenu = toupper(getch());

            switch(opcao_submenu)
            {
                case CIMA:
                    if(posY_sub>14)
                    {
                        moveXY(posX_sub,posY_sub, "  ");
                        posY_sub-=2;
                        moveXY(posX_sub,posY_sub, "->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY_sub<16)
                    {
                        moveXY(posX_sub,posY_sub, "  ");
                        posY_sub+=2;
                        moveXY(posX_sub,posY_sub, "->");
                        Beep(450,100);
                    }
                    break;
                case ENTER:
                    if(posY_sub==14)
                    {
                        funcao[1]=1;
                    }
                    else if(posY_sub==16)
                    {
                        funcao[1]=2;
                    }
                    break;
                case ESC:
                    moveXY(posX_sub, posY_sub, "  ");
                    funcao[0]=0;
                    break;
            }
        }
        else if(funcao[0]==5 && funcao[1]==1) //Função: Backup -> Salvar em Arquivo Texto
        {
            system("cls");
            moveXY(38,2, ":::BACKUP - SALVAR EM ARQUIVO TEXTO:::");
            i = 7;
            Mostra_Agenda(Agenda, &i);
            do
            {
                moveXY(3,i+2, "Deseja realmente salvar esta agenda em um arquivo 'agenda.txt'?");
                moveXY(3,i+3, "Tecle 'S' para Sim ou 'N' para Não: ");
                opcao_funcao = toupper(getch());
            }while(opcao_funcao != 'N' && opcao_funcao != 'S');
            i=0;
            if(opcao_funcao == 'S')
            {
                system("cls");
                moveXY(38,2, ":::BACKUP - SALVAR EM ARQUIVO TEXTO:::");
                if(Backup_SalvarArqTxt(Agenda))
                {
                    moveXY(3,5, "Agenda salva com sucesso em 'agenda.txt'!");
                    moveXY(3,8, "");
                    system("pause");
                }
                else
                {
                    moveXY(3,8, "");
                    system("pause");
                }
            }

            funcao[0]=0;
            system("cls");
            Menu_Principal();
        }
        else if(funcao[0]==5 && funcao[1]==2) //Função: Backup -> Ler de Arquivo Texto
        {
            system("cls");
            moveXY(40,2, ":::BACKUP - LER DE ARQUIVO TEXTO:::");
            do
            {
                moveXY(3,5, "Deseja realmente ler e recuperar a agenda do arquivo 'agenda.txt'?");
                moveXY(3,6, "Tecle 'S' para Sim ou 'N' para Não: ");
                opcao_funcao = toupper(getch());
            }while(opcao_funcao != 'N' && opcao_funcao != 'S');
            if(opcao_funcao == 'S')
            {
                system("cls");
                moveXY(40,2, ":::BACKUP - LER DE ARQUIVO TEXTO:::");
                if(Backup_LerArqTxt(&Agenda))
                {
                    i=5;
                    Mostra_Agenda(Agenda, &i);
                    moveXY(3,i+2, "Agenda recuperada com sucesso de 'agenda.txt'!");
                    moveXY(3,i+5, "");
                    system("pause");
                }
                else
                {
                    moveXY(3,8, "");
                    system("pause");
                }
            }

            funcao[0]=0;
            system("cls");
            Menu_Principal();
        }
        else if(funcao[0]==6 && !funcao[1]) //Função: Bônus -> Exibir Agenda
        {
            system("cls");
            moveXY(42,2, ":::BÔNUS - EXIBIR AGENDA:::");
            i=7;
            Mostra_Agenda(Agenda, &i);
            moveXY(3,i+2, "");
            system("pause");

            funcao[0]=0;
            system("cls");
            Menu_Principal();
        }

    }

    Beep(300,650);
	return 0;
}

//Funções dos Menus
//Função MoveXY (do windows.h) para controle do Menu por meio de coordenadas
void moveXY (int x, int y, char t[])
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {x,y};
	SetConsoleCursorPosition(hStdout,position);
	printf("%s",t);
}

//Menu Principal
void Menu_Principal()
{
    int i;
    moveXY(47,2, "DAVI&LUIZ AGENDA");

    //Data e Hora Atuais do Sistema
    moveXY(3,3, "Data Atual: ");
    system("date /t");
    //printf("%s",__DATE__);
    moveXY(89,3, "Horário Atual: ");
    system("time /t");
    //printf("%s",__TIME__);
    for(i=3;i<=108;i++)
        moveXY(i,4, "-");

    moveXY(14,6, "INSERIR COMPROMISSO(S)");
    moveXY(14,8, "REMOVER COMPROMISSO(S)");
    moveXY(17,10, "* DE UMA DETERMINADA DATA");
    moveXY(17,12, "* POR UMA BUSCA ESPECÍFICA");
    moveXY(14,14, "CONSULTAR COMPROMISSO(S)");
    moveXY(17,16, "* POR UMA DETERMINADA DATA");
    moveXY(17,18, "* POR UMA BUSCA ESPECÍFICA");

    moveXY(70,6, "ALTERAR COMPROMISSO(S)");
    moveXY(73,8, "* POR DATA E HORÁRIO");
    moveXY(73,10, "* POR UMA BUSCA ESPECÍFICA");
    moveXY(70,12, "BACKUP");
    moveXY(73,14, "* SALVAR EM ARQUIVO TEXTO");
    moveXY(73,16, "* LER DE ARQUIVO TEXTO");
    moveXY(70,18, "BÔNUS: EXIBIR AGENDA");

    for(i=3;i<=108;i++)
        moveXY(i,20,"-");

	moveXY(83,21, "ENTER: SELECIONAR");
	moveXY(83,22, "ESC: SAIR DO PROGRAMA/MENU");
	moveXY(3,21, "CRÉDITOS: DAVI AUGUSTO E LUIZ SEMENTILLE");
	moveXY(3,22, "TRABALHO VI - ALGORITMOS II");
	moveXY(25,24, "OBS: USE AS SETAS DO TECLADO PARA ESCOLHER A FUNÇÃO DESEJADA");
}


//Funções da Agenda
//Inserir Compromisso(s)
void Inserir_Compromisso (no *Agenda, char *compromisso, DataHora data)
{

    //Armazenando a informação em uma auxiliar
    no p = (no)malloc(sizeof(struct Agenda));
    strcpy(p->compromisso, compromisso);
    (p->data).dia = data.dia;
    (p->data).mes = data.mes;
    (p->data).ano = data.ano;
    (p->data).hora = data.hora;
    (p->data).minutos = data.minutos;
    p->prox = NULL;

    if(!(*Agenda) || Verifica_DataHora((*Agenda)->data, data))
    {
        p->prox = (*Agenda);
        (*Agenda) = p;
    }
    else
    {
        no q = (*Agenda), r;
        while(q && !(Verifica_DataHora(q->data, data)))
        {
            r = q;
            q = q->prox;
        }
        p->prox = q;
        r->prox = p;
    }
}
int Verifica_DataHora (DataHora dAgen, DataHora dUsu)
{
    if(dAgen.ano < dUsu.ano){
        return 0;
    }
    else if(dAgen.ano == dUsu.ano){
        if(dAgen.mes < dUsu.mes){
            return 0;
        }
        else if (dAgen.mes == dUsu.mes){
            if(dAgen.dia < dUsu.dia){
                return 0;
            }
            else if(dAgen.dia == dUsu.dia){
                if(dAgen.hora < dUsu.hora){
                    return 0;
                }
                else if(dAgen.hora == dUsu.hora){
                    if(dAgen.minutos < dUsu.minutos){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
int VerificaData(DataHora dAgen, DataHora dUsu)
{
    if((dAgen.ano == dUsu.ano) && (dAgen.mes == dUsu.mes) && (dAgen.dia == dUsu.dia))
        return 1;
    else
        return 0;
}

//Remover -> Determinada Data
int Remover_Data (no *Agenda, DataHora data)
{
    moveXY(3,5, "Data Solicitada: ");
    printf("%d/%d/%d", data.dia, data.mes, data.ano);

    int i = 7, verifica=0;
    no p = (*Agenda);
    char opcao_remover;

    while(p)
    {
        if(VerificaData(p->data, data))
        {
            moveXY(3,i, "");
            printf("%d/%d/%d - %d:%d - %s", (p->data).dia, (p->data).mes, (p->data).ano, (p->data).hora, (p->data).minutos, p->compromisso);
            i++;
            verifica=1;
        }
        p = p->prox;
    }
    if(!verifica)
    {
        moveXY(3,8, "Não existe(m) compromisso(s) nesta data.");
        moveXY(3,11, "");
        system("pause");
        return 0;
    }
    else
    {
        do
        {
            moveXY(3,i+2, "Deseja realmente remover todos os compromissos desta data?");
            moveXY(3,i+3, "Tecle 'S' para Sim ou 'N' para Não: ");
            opcao_remover = toupper(getch());
        }while(opcao_remover != 'N' && opcao_remover != 'S');
        if(opcao_remover == 'S')
        {
                system("cls");
                moveXY(40,2, ":::REMOVER COMPROMISSO(S) - DATA:::");

                if(VerificaData((*Agenda)->data, data))
                {
                    while((*Agenda) && VerificaData((*Agenda)->data, data))
                    {
                        p = (*Agenda);
                        (*Agenda) = (*Agenda)->prox;
                        free(p);
                    }
                }
                else
                {
                    p = (*Agenda);
                    no q, r;
                    while(p)
                    {
                        if(VerificaData(p->data, data))
                        {
                            q->prox = p->prox;
                            r = p;
                            p = p->prox;
                            free(r);
                        }
                        else
                        {
                            q = p;
                            p = p->prox;
                        }
                    }
                }
                return 1;
            }
        else
        {
            return 0;
        }
    }
}

//Remover -> Determinado Compromisso Desejado
int Remover_Desejado (no *Agenda, char *compromisso)
{
    moveXY(3,5, "Palavra Solicitada: ");
    printf("%s", compromisso);

    int i = 7, verifica=0;
    no p = (*Agenda);
    char compromisso_final[max], *aux;
    while(p)
    {
        aux = strstr(p->compromisso, compromisso);
        if(aux)
        {
            moveXY(3,i, "");
            printf("%d/%d/%d - %d:%d - %s", (p->data).dia, (p->data).mes, (p->data).ano, (p->data).hora, (p->data).minutos, p->compromisso);
            i++;
            verifica=1;
        }
        p = p->prox;
    }
    if(!verifica)
    {
        moveXY(3,8, "Não existe(m) compromisso(s) que contenha(m) essa palavra.");
        moveXY(3,11, "");
        system("pause");
        return 0;
    }
    else
    {
        fflush(stdin);
        moveXY(3,i+3, "Digite o compromisso a ser removido (deixe em branco para cancelar): ");
        //scanf("%s", &compromisso_final);
        gets(compromisso_final);

        //Verifica se o que foi digitado não está em branco
        if(strlen(compromisso_final)>0)
        {
            p = (*Agenda);
            //Se estiver na primeira
            if(!stricmp((*Agenda)->compromisso, compromisso_final))
            {
                (*Agenda) = (*Agenda)->prox;
                free(p);
            }
            else
            {
                no q;
                //Se estiver no meio/final
                while(p)
                {
                    q = p;
                    p = p->prox;
                    if(!stricmp(p->compromisso, compromisso_final))
                    {
                        q->prox = p->prox;
                        free(p);
                        break;
                    }
                }
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }

}

//Consultar -> Determinada Data
void Consulta_Total (no Agenda, DataHora data)
{
    moveXY(3,5, "Data Solicitada: ");
    printf("%d/%d/%d", data.dia, data.mes, data.ano);
    int i = 7, verifica=0;
    no p = Agenda;
    //DataHora aux;

    while(p)
    {
        if(VerificaData(p->data, data))
        {
            moveXY(3,i, "");
            printf("%d/%d/%d - %d:%d - %s", (p->data).dia, (p->data).mes, (p->data).ano, (p->data).hora, (p->data).minutos, p->compromisso);
            i++;
            verifica=1;
        }
        p = p->prox;
    }
    if(!verifica)
    {
        moveXY(3,8, "Não existe(m) compromisso(s) para a data solicitada.");
        moveXY(3,11, "");
        system("pause");
    }
    else
    {
        moveXY(3,i+3, "");
        system("pause");
    }

}

//Consultar -> Determinado Compromisso Desejado
void Consulta_Desejado (no Agenda, char *compromisso)
{
    moveXY(3,5, "Palavra Pesquisada: ");
    printf("%s", compromisso);
    int i = 7, verifica=0;
    no p = Agenda;
    char *aux;

    while(p)
    {
        aux = strstr(p->compromisso, compromisso);
        if(aux)
        {
            moveXY(3,i, "");
            printf("%d/%d/%d - %d:%d - %s", (p->data).dia, (p->data).mes, (p->data).ano, (p->data).hora, (p->data).minutos, p->compromisso);
            i++;
            verifica=1;
        }
        p = p->prox;
    }
    if(!verifica)
    {
        moveXY(3,8, "Não existe(m) compromisso(s) que contenha(m) essa palavra.");
        moveXY(3,11, "");
        system("pause");
    }
    else
    {
        moveXY(3,i+3, "");
        system("pause");
    }
}

//Alterar -> Determinada Data e Horário
int Alterar_DataHora (no *Agenda, DataHora data)
{
    moveXY(3,5, "Data Solicitada: ");
    printf("%d/%d/%d", data.dia, data.mes, data.ano);
    moveXY(3,6, "Hora Solicitada: ");
    printf("%d:%d", data.hora, data.minutos);
    int i = 8, verifica=0;
    no p = (*Agenda);
    char compromisso_novo[max], compromisso_final[max];
    while(p)
    {
        if(((p->data).dia == data.dia) && ((p->data).mes == data.mes) && ((p->data).ano == data.ano) && ((p->data).hora == data.hora) && ((p->data).minutos == data.minutos))
        {
            moveXY(3,i, "");
            printf("%d/%d/%d - %d:%d - %s", (p->data).dia, (p->data).mes, (p->data).ano, (p->data).hora, (p->data).minutos, p->compromisso);
            i++;
            verifica=1;
        }
        p = p->prox;
    }
    if(!verifica)
    {
        moveXY(3,8, "Não existe(m) compromisso(s) para a data e hora solicitadas.");
        moveXY(3,11, "");
        system("pause");
    }
    else
    {
        fflush(stdin);
        moveXY(3,i+3, "Digite o compromisso a ser alterado (deixe em branco para cancelar): ");
        //scanf("%s", &compromisso_final);
        gets(compromisso_final);

        //Verifica se o que foi digitado não está em branco
        if(strlen(compromisso_final)>0)
        {
            system("cls");
            moveXY(38,2, ":::ALTERAR COMPROMISSO(S) - DATA/HORA:::");
            moveXY(3,5, "Digite o novo nome para o compromisso ");
            printf("'%s': ", compromisso_final);
            scanf(" %[^\n]s", &compromisso_novo);

            moveXY(3,8, "Alterando. Por favor, aguarde..");
            p = (*Agenda);

            //Se estiver na primeira
            if(!stricmp((*Agenda)->compromisso, compromisso_final))
            {
                strcpy((*Agenda)->compromisso, compromisso_novo);
            }
            else
            {
                //Se estiver no meio/final
                while(p)
                {
                    p = p->prox;
                    if(!stricmp(p->compromisso, compromisso_final))
                    {
                        strcpy(p->compromisso, compromisso_novo);
                        break;
                    }
                }
            }
            Sleep(3000);
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
//Alterar -> Determinada Palavra
int Alterar_Palavra (no *Agenda, char *compromisso)
{
    moveXY(3,5, "Palavra Solicitada: ");
    printf("%s", compromisso);

    int i = 7, verifica=0;
    no p = (*Agenda);
    char compromisso_novo[max], compromisso_final[max], *aux;
    while(p)
    {
        aux = strstr(p->compromisso, compromisso);
        if(aux)
        {
            moveXY(3,i, "");
            printf("%d/%d/%d - %d:%d - %s", (p->data).dia, (p->data).mes, (p->data).ano, (p->data).hora, (p->data).minutos, p->compromisso);
            i++;
            verifica=1;
        }
        p = p->prox;
    }
    if(!verifica)
    {
        moveXY(3,8, "Não existe(m) compromisso(s) que contenha(m) essa palavra.");
        moveXY(3,11, "");
        system("pause");
        return 0;
    }
    else
    {
        fflush(stdin);
        moveXY(3,i+3, "Digite o compromisso a ser alterado (deixe em branco para cancelar): ");
        //scanf("%s", &compromisso_final);
        gets(compromisso_final);

        //if(!stricmp(compromisso, compromisso_final))
        //Verifica se o que foi digitado não está em branco
        if(strlen(compromisso_final)>0)
        {
            system("cls");
            moveXY(42,2, ":::ALTERAR COMPROMISSO - BUSCA:::");
            moveXY(3,5, "Digite o novo nome do compromisso ");
            printf("'%s': ", compromisso_final);
            scanf(" %[^\n]s", &compromisso_novo);

            moveXY(3,8, "Alterando. Por favor, aguarde..");
            p = (*Agenda);

            //Se estiver na primeira
            if(!stricmp((*Agenda)->compromisso, compromisso_final))
            {
                strcpy((*Agenda)->compromisso, compromisso_novo);
            }
            else
            {
                //Se estiver no meio/final
                while(p)
                {
                    p = p->prox;
                    if(!stricmp(p->compromisso, compromisso_final))
                    {
                        strcpy(p->compromisso, compromisso_novo);
                        break;
                    }
                }
            }
            Sleep(3000);
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

//Backup -> Salvar em Arquivo Texto (agenda.txt)
int Backup_SalvarArqTxt (no Agenda)
{
    FILE *arq;
    if(!(arq = fopen ("agenda.txt", "w+")))
    {
        moveXY(3,5, "Erro ao criar arquivo texto. Por favor, tente novamente.");
        return 0;
    }
    no p = Agenda;
    while(p)
    {
        fprintf(arq, "%d/%d/%d - %d:%d - %s", (p->data).dia, (p->data).mes, (p->data).ano, (p->data).hora, (p->data).minutos, p->compromisso);
        fprintf(arq, "\n");
        p = p->prox;
    }
    fclose(arq);
    return 1;

}
//Backup -> Ler/Recuperar a partir do Arquivo Texto (agenda.txt)
int Backup_LerArqTxt (no *Agenda)
{
    FILE *arq;
    if(!(arq = fopen ("agenda.txt", "r")))
    {
        moveXY(3,5, "Erro ao abrir arquivo texto. Por favor, tente novamente.");
        return 0;
    }
    DataHora aux;
    char compromisso[max];
    char c;
    c = getc(arq); /* Lê o primeiro caracter */
    if (!feof(arq)){/* Verifica se o caracter lido é o fim de arquivo */
        while ((*Agenda)){ //Apaga a Agenda do sistema atual
            	no p = (*Agenda);
            	*Agenda = (*Agenda)->prox;
            	free(p);
                if((*Agenda)->prox == NULL)
                {
                    free((*Agenda));
                    (*Agenda) = NULL;
                    break;
                }
            }
        fseek(arq, 0, SEEK_SET);
        while((fscanf(arq, "%d/%d/%d - %d:%d - %s\n", &aux.dia, &aux.mes, &aux.ano, &aux.hora, &aux.minutos, &compromisso)) != EOF)
        {
            Inserir_Compromisso(&(*Agenda), &compromisso, aux);
        }
        fclose(arq);
    }
    else{
        moveXY(3,5, "Não há nenhum elemento neste arquivo");
        fclose(arq);
        return 0;
    }
    return 1;
}
//Mostrar Agenda (utilizada no Backup)
void Mostra_Agenda (no Agenda, int *i)
{
    //int i = 7;
    moveXY(3,5, "::AGENDA ATUAL::");
    if(!Agenda)
    {
        (*i)++;
        moveXY(3,(*i),"Não existe(m) compromisso(s) na sua agenda.");
        (*i)++;
    }
    else
    {
        while(Agenda)
        {
            moveXY(3,(*i), "");
            printf("%d/%d/%d - %d:%d - %s", (Agenda->data).dia, (Agenda->data).mes, (Agenda->data).ano, (Agenda->data).hora, (Agenda->data).minutos, Agenda->compromisso);
            (*i)++;
            Agenda = Agenda->prox;
        }
    }

}
