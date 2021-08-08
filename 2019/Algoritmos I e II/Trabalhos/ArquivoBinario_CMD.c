//Trabalho 3 - Algoritmos II~~
//Alunos: Davi Augusto e Luiz Sementille
//Curso: BCC
//Data de Entrega: 09/09/2019
//Compilar com TDM-GCC 64bit

//Tamanho da Janela do Console: 120x30 (LxA)

//Funções Primárias: Cadastro; Alteração; Exclusão (Lógica e Física); Consulta (Númerica e String)
//Funções Secundárias: Consulta de Arquivo por Pasta; Trocar Nome do Arquivo; Remover Arquivo; Criar e Alternar Nome de Pastas; Mudar Arquivo de Pasta
//Alterar Data e Horário do Sistema;
//Ainda, fazer uma tela de ajuda do tipo texto e criptografada (F1)

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <windows.h>

//Teclas em ASCII
#define CIMA 72
#define BAIXO 80
#define DIREITA 77
#define ESQUERDA 75
#define ESC 27
#define AJUDA 59 //F1 (tecla especial: 0 e 59 ao mesmo tempo)
#define ENTER 13
#define BACKSPACE 8

#define MAX 100
#define MAX_ARQ 20

//Campos de Preenchimento
typedef struct{
    char nome[MAX]; //Nome do jogador
    int numCamisa, idade, excluido; //Número da camisa,
    char time[MAX], pos[MAX]; //Nome do time e posição
}Time_Futebol;

//Funções
//Funções dos Menus
void moveXY (int x, int y, char t[]);
void Menu_Principal();
int Tela_Ajuda(char opcao_first);

//Funções Primárias
void Cadastro(Time_Futebol);
void Alterar(Time_Futebol);
void Consultas(Time_Futebol);
void Exclusao_Logica_Fisica(Time_Futebol);

//Funções Secundárias
void Consulta_Arquivo_Pasta();
void Renomear_Arquivo();
void Remover_Arquivo();
void Criar_Pasta();
void Renomear_Pasta();
void Alterar_Data();
void Alterar_Hora();

int main()
{
    setlocale(LC_ALL, "Portuguese");
	system("COLOR 09");


	/*system("date /t");
	system("time /t");*/

	Time_Futebol user;
	//Variáveis de Manipulação e Troca dos Menus
	char opcao_menu=0, opcao_first;
	short posX=11, posY=6;
	short posX_sub1=14, posY_sub1=9;
	short posX_sub2=70, posY_sub2=9;
	short posX_subsub=17, posY_subsub=20;
	int funcao[3], ajuda=0;

    funcao[0]=0;
    Menu_Principal();

    while(opcao_menu!=ESC)
    {
        //Executar Menu_Principal -> Opções de Manipulação
        if(funcao[0]==0 && ajuda==0)
        {
            moveXY(posX, posY, "->");
            opcao_menu = toupper(getch());

            switch(opcao_menu)
            {
                case DIREITA:
                    if(posX<67)
                    {
                        moveXY(posX,posY, "  ");
                        posX+=56;
                        moveXY(posX,posY, "->");
                        Beep(450,100);
                    }
                    break;
                case ESQUERDA:
                    if(posX>11)
                    {
                        moveXY(posX,posY, "  ");
                        posX-=56;
                        moveXY(posX,posY, "->");
                        Beep(450,100);
                    }
                    break;
                case ENTER:
                    if(posX==11)
                    {
                        moveXY(posX,posY, "  ");
                        funcao[0]=1;
                        funcao[1]=0;
                    }
                    else if(posX==67)
                    {
                        moveXY(posX,posY, "  ");
                        funcao[0]=2;
                        funcao[1]=0;
                    }
                    break;
                case (AJUDA && 0):
                    ajuda=1;
                    system("cls");
                    break;
                case ESC:
                    system("cls");
                    break;
            }
        }

        //Funções de Manipulação de Dados
        else if(funcao[0]==1 && funcao[1]==0 && ajuda==0)
        {
            moveXY(posX_sub1,posY_sub1, "->");
            opcao_first = toupper(getch());
            switch(opcao_first)
            {
                case CIMA:
                    if(posY_sub1>9)
                    {
                        moveXY(posX_sub1,posY_sub1,"  ");
                        posY_sub1-=3;
                        moveXY(posX_sub1,posY_sub1,"->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY_sub1<18)
                    {
                        moveXY(posX_sub1,posY_sub1,"  ");
                        posY_sub1+=3;
                        moveXY(posX_sub1,posY_sub1,"->");
                        Beep(450,100);
                    }
                    break;
                case (AJUDA && 0):
                    ajuda=1;
                    system("cls");
                    break;
                case ENTER:
                    if(posY_sub1==9)
                        funcao[1]=1;
                    else if(posY_sub1==12)
                        funcao[1]=2;
                    else if(posY_sub1==15)
                        funcao[1]=3;
                    else if(posY_sub1==18)
                        funcao[1]=4;
                    break;
                case ESC:
                    funcao[0]=0;
                    moveXY(posX_sub1,posY_sub1, "  ");
                    posY_sub1=9;
                    break;
            }
        }
        //Cadastro
        else if(funcao[0]==1 && funcao[1]==1)
        {
            Cadastro(user);
            Menu_Principal();
            funcao[1]=0;
        }
        //Alterações
        else if(funcao[0]==1 && funcao[1]==2)
        {
            Alterar(user);
            Menu_Principal();
            funcao[1]=0;
        }
        //Consultas
        else if(funcao[0]==1 && funcao[1]==3)
        {
            Consultas(user);
            Menu_Principal();
            funcao[1]=0;
        }

        //Exclusões Lógica-Física
        else if(funcao[0]==1 && funcao[1]==4)
        {
            Exclusao_Logica_Fisica(user);
            Menu_Principal();
            funcao[1]=0;
        }

        //Funções de Manipulação de Arquivos e Outros
        else if(funcao[0]==2 && funcao[1]==0 && ajuda==0)
        {
            moveXY(posX_sub2,posY_sub2, "->");
            opcao_first = toupper(getch());
            switch(opcao_first)
            {
                case CIMA:
                    if(posY_sub2>9)
                    {
                        moveXY(posX_sub2,posY_sub2,"  ");
                        posY_sub2-=2;
                        moveXY(posX_sub2,posY_sub2,"->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY_sub2<21)
                    {
                        moveXY(posX_sub2,posY_sub2,"  ");
                        posY_sub2+=2;
                        moveXY(posX_sub2,posY_sub2,"->");
                        Beep(450,100);
                    }
                    break;
                case (AJUDA && 0):
                    ajuda=1;
                    system("cls");
                    break;
                case ENTER:
                    if(posY_sub2==9)
                        funcao[1]=1;
                    else if(posY_sub2==11)
                        funcao[1]=2;
                    else if(posY_sub2==13)
                        funcao[1]=3;
                    else if(posY_sub2==15)
                        funcao[1]=4;
                    else if(posY_sub2==17)
                        funcao[1]=5;
                    else if(posY_sub2==19)
                        funcao[1]=6;
                    else if(posY_sub2==21)
                        funcao[1]=7;
                    break;
                case ESC:
                    funcao[0]=0;
                    moveXY(posX_sub2,posY_sub2, "  ");
                    posX_sub2=70;
                    posY_sub2=9;
                    break;
            }
        }
        //Consulta de Arquivos em uma Pasta
        else if(funcao[0]==2 && funcao[1]==1)
        {
            Consulta_Arquivo_Pasta();
            Menu_Principal();
            funcao[1]=0;
        }
        //Renomear Arquivo
        else if(funcao[0]==2 && funcao[1]==2)
        {
            Renomear_Arquivo();
            Menu_Principal();
            funcao[1]=0;
        }
        //Remover Arquivo
        else if(funcao[0]==2 && funcao[1]==3)
        {
            Remover_Arquivo();
            Menu_Principal();
            funcao[1]=0;
        }
        //Criar Pasta
        else if(funcao[0]==2 && funcao[1]==4)
        {
            Criar_Pasta();
            Menu_Principal();
            funcao[1]=0;
        }
        //Renomear Pasta
        else if(funcao[0]==2 && funcao[1]==5)
        {
            Renomear_Pasta();
            Menu_Principal();
            funcao[1]=0;
        }


        //Alterar Data do Sistema
        else if(funcao[0]==2 && funcao[1]==6)
        {
            Alterar_Data();
            Menu_Principal();
            funcao[1]=0;
        }
        //Alterar Hora do Sistema
        else if(funcao[0]==2 && funcao[1]==7)
        {
            Alterar_Hora();
            Menu_Principal();
            funcao[1]=0;
        }

        //Menu de Ajuda (Criptografado) DESCOMENTAR DEPOIS
        else if(ajuda==1)
        {
            if(Tela_Ajuda(opcao_first))
            {
                Menu_Principal();
                ajuda=0;
            }
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
    moveXY(45,2, "DAVELOUIS DREAMTEAM");

    //Data e Hora Atuais do Sistema
    moveXY(3,3, "Data: ");
    system("date /t");
    //printf("%s",__DATE__);
    moveXY(95,3, "Horário: ");
    system("time /t");
    //printf("%s",__TIME__);

    for(i=3;i<=108;i++)
        moveXY(i,4, "-");
    moveXY(14,6, "MANIPULAÇÃO DE DADOS");
    moveXY(17,9, "CADASTRO");
    moveXY(17,12, "ALTERAÇÕES");
    moveXY(17,15, "CONSULTAS");
    moveXY(17,18, "EXCLUSÃO");

    moveXY(70,6, "MANIPULAÇÃO DE ARQUIVOS E OUTROS");
    moveXY(73,9, "CONSULTA DE ARQUIVOS EM UMA PASTA");
    moveXY(73,11, "RENOMEAR ARQUIVO");
    moveXY(73,13, "REMOVER ARQUIVO");
    moveXY(73,15, "CRIAR PASTA");
    moveXY(73,17, "RENOMEAR PASTA");
    moveXY(73,19, "ALTERAR DATA DO SISTEMA");
    moveXY(73,21, "ALTERAR HORA DO SISTEMA");

    for(i=5; i<=24;i++)
        moveXY(56,i,"|");
    for(i=3;i<=108;i++)
        moveXY(i,24,"-");

    moveXY(83,25, "F1: AJUDA");
	moveXY(83,26, "ENTER: SELECIONAR");
	moveXY(83,27, "ESC: SAIR DO PROGRAMA/MENU");
	moveXY(3,26, "CRÉDITOS: DAVI AUGUSTO E LUIZ SEMENTILLE");
	moveXY(3,27, "TRABALHO III - ALGORITMOS II");
	moveXY(25,29, "OBS: USE AS SETAS DO TECLADO PARA ESCOLHER A FUNCAO DESEJADA");
}

//Funções Primárias
//Cadastro
void Cadastro(Time_Futebol user)
{
    system("cls");

    Time_Futebol aux;

    char arq_nome[MAX_ARQ];
    int numCamisas[MAX], okay = 0, cont=0, i, novo = 0, id;
    moveXY(50,2, "::: CADASTRO :::");

    char diretorio[MAX]="";
    moveXY(4,4, "");
    printf("Digite o diretório que contenha a pasta para criação de arquivo (use \\ para separar os diretórios) ");
    moveXY(4,5, "OBS: deixe em branco caso deseje utilizar o diretório atual para criação de arquivo.");
    moveXY(4,6, "OBS²: lembre-se de colocar \\ no final do diretório desejado.");
    moveXY(4,8, "");
    gets(diretorio);

    do
    {
        moveXY(4,11, "");
        printf("Digite o nome do arquivo para cadastro (com extensão): ");
        gets(arq_nome);
    }while(strlen(arq_nome)==0);

    FILE *arq;
    char resp;
    char diretorio_2[MAX];
    strcpy(diretorio_2,diretorio);
    strcat(diretorio,arq_nome);
    if((arq = fopen(diretorio, "r+b")) == NULL)
	{
		do
		{
		    system("cls");
		    moveXY(50,2, "::: CADASTRO :::");
		    moveXY(4,5,"");
			printf("Esse arquivo não existe!");
			moveXY(4,7,"");
			printf("Deseja criar um arquivo novo?(S/N)");
			moveXY(4,9,"");
			resp = toupper(getch());
		}while(resp!='N' && resp!='S');
		if(resp == 'S')
		{
		    fclose(arq);
            strcat(diretorio_2,arq_nome);
			if((arq = fopen(diretorio_2, "w+b")) == NULL)
			{
			    system("cls");
			    moveXY(50,2, "::: CADASTRO :::");
			    moveXY(4,5,"");
				printf("Erro de abertura de arquivo!");
				moveXY(4,6,"");
				printf("Tente a operação novamente.");
				moveXY(4,8,"");
				system("pause");
                system("cls");
                fclose(arq);
				return;
			}
			else
            {
                system("cls");
			    moveXY(50,2, "::: CADASTRO :::");
			    moveXY(4,5,"");
				printf("Arquivo criado com sucesso!");
				moveXY(4,8,"");
				system("pause");
                system("cls");
                okay = 1;
                //return;
            }
		}
		else
		{
			system("cls");
			fclose(arq);
			return;
		}
	}
	do
    {
        if(okay == 1)
        {
            user.numCamisa = 1;
            okay = 0;
        }
        else
        {
            rewind(arq);
            while(fread(&aux, sizeof(Time_Futebol), 1, arq) == 1)
            {
                user.numCamisa = aux.numCamisa + 1;
            }


        }

        system("cls");
        moveXY(45,2, "::: CADASTRO DE JOGADORES :::");
        fflush(stdin);
        moveXY(4, 4, "::: INFORMAÇÕES PESSOAIS :::");
        do {
            moveXY(9, 8, "                        ");
            moveXY(4, 8, "Nome do jogador: ");
            gets(user.nome);
        } while(strlen(user.nome) == 0);
        fflush(stdin);
        do {
            moveXY(8, 10, "              ");
            moveXY(4, 10, "Idade (5 a 50): ");
            scanf("%d", &user.idade);
        } while(user.idade <=5 || user.idade >=50);
        fflush(stdin);

        // Informações do jogador no time
        moveXY(4, 12, "::: INFORMAÇÕES DO TIME :::");

        //Nome do time
        do {
            moveXY(8, 14, "              ");
            moveXY(4, 14, "Nome do time: ");
            gets(user.time);
        } while(strlen(user.time)==0);

        fflush(stdin);

        //Posicao
        do {
            moveXY(8, 16, "              ");
            moveXY(4, 16, "Posicao: ");
            gets(user.pos);
        } while(strlen(user.pos)==0);

        moveXY(4, 18, "");
		printf("Número da Camisa: %d", user.numCamisa);
        //Numero da camisa

        user.excluido = 0;

        //Como foi lido os numeros de camisa, então para que não sobrescreva:
        fseek(arq, 0, SEEK_END);

        //Salva o registro

        fwrite(&user, sizeof(user), 1, arq);
        fflush(arq);

        fflush(stdin);
        moveXY(4,22,"Deseja realizar outro cadastro no arquivo? (S/N) ");
        do
        {
            resp = toupper(getch());
        }while(resp!='S' && resp!='N');

        system("cls");
    }while(resp == 'S');

    fclose(arq);
}
//Alterações
void Alterar(Time_Futebol user)
{
    system("cls");
    char arq_nome[MAX_ARQ];
    //Variáveis auxiliares para salvar os dados antigos do registro escolhido

    int numCamisas, okay;
    char aux[MAX], time[MAX];

    moveXY(45,2, "::: ALTERAÇÕES :::");

    char diretorio[MAX], op;
    moveXY(4,4, "");
    printf("Digite o diretório que contenha a pasta para alteração de arquivo (use \\ para separar os diretórios) ");
    moveXY(4,5, "OBS: deixe em branco caso deseje utilizar o diretório atual para alteração de arquivo.");
    moveXY(4,6, "OBS²: lembre-se de colocar \\ no final do diretório desejado.");
    moveXY(4,8, "");
    gets(diretorio);


    do
    {
        moveXY(4,11, "");
        printf("Digite o nome do arquivo para alterações (com extensão): ");
        gets(arq_nome);
    }while(strlen(arq_nome)==0);

    FILE *arq;
    if((arq = fopen(strcat(diretorio,arq_nome), "r+b")) == NULL)
	{
	    system("cls");
	    moveXY(45,2, "::: ALTERAÇÕES :::");
        moveXY(4,6,"Esse arquivo não existe!");
        moveXY(4,7,"Crie um novo na função 'Cadastro'");
        moveXY(4,9,"");
        system("pause");
        system("cls");
        fclose(arq);
        return;
	}
	else
    {
        fseek(arq,0,SEEK_SET);
        system("cls");
    }

    moveXY(45,2, "::: ALTERAÇÃO DE JOGADOR :::");
    do {
        fflush(stdin);
        moveXY(76,5, "                       ");
        moveXY(30,5,"Qual o numero da camisa do jogador que deseja alterar? ");
        scanf("%d", &numCamisas);
    } while(numCamisas <= 0);

    system("cls");

    okay = 0;
    while (fread(&user, sizeof(user), 1, arq) == 1) {
        if(user.numCamisa == numCamisas && user.excluido == 0)
        {
            moveXY(45,2, "::: ALTERAÇÃO DE JOGADOR :::");
            moveXY(50,5, "::: JOGADOR :::");
            moveXY(20, 9, "::: INFORMAÇÕES PESSOAIS :::");

            fflush(stdin);

            moveXY(22, 12, "");printf("Nome: %s", user.nome);
            moveXY(28, 12, "");gets(aux);
            //Se ele digitou alguma coisa, troca
            if(strlen(aux) > 0)
                strcpy(user.nome, aux);
            fflush(stdin);

            moveXY(22, 15, "");printf("Idade: %d", user.idade);
            moveXY(29, 15, "");gets(aux);

            if(strlen(aux) > 0)
                user.idade = atoi(aux);
            fflush(stdin);

            moveXY(72, 9, "::: INFORMAÇÕES DO TIME :::");

            moveXY(74, 12, "");printf("Time: %s", user.time);
            moveXY(80, 12, "");gets(aux);

            if(strlen(aux) > 0)
                strcpy(user.time, aux);
            fflush(stdin);

            moveXY(74, 15, "");printf("Posição: %s", user.pos);
            moveXY(83, 15, "");gets(aux);

            if(strlen(aux) > 0)
                strcpy(user.pos, aux);
            fflush(stdin);

            moveXY(74, 18, "");printf("Número da Camisa: %d", user.numCamisa);

            moveXY(23, 26, "Confirma alterações do jogador? Se sim, digite 's', senão digite 'n': ");

            do {
                op = toupper(getch());
            } while(op!='N' && op!='S');

            if(op=='S')
            {
                system("cls");
                moveXY(45,2, "::: ALTERANDO JOGADOR :::");
                moveXY(50,5, "::: JOGADOR :::");
                moveXY(48, 10, "Alterando...");
                Sleep(2000);
                fseek(arq, -sizeof(user), SEEK_CUR);
        	  	fwrite(&user, sizeof(user), 1, arq);
                fflush(arq);
                moveXY(42, 10, "Registro alterado com sucesso...");
                moveXY(27, 26, "Deseja alterar outro registro? Se sim, digite 's', senão digite 'n': ");
                do {
                    op = toupper(getch());
                } while(op!='N' && op!='S');
                system("cls");
                if(op=='N')
                {
                    fclose(arq);
                    return;
                }
                Alterar(user);
            }
            system("cls");
            fclose(arq);
            return;
        }
    }
    if(okay == 0)
    {
        moveXY(45,5, "::: JOGADORES :::");
        moveXY(32, 11, "");
		printf("Não existem jogadores com o número de camisa %d!", numCamisas);
        moveXY(45, 26, "Pressione alguma tecla para continuar...");
        getch();
        system("cls");
        fclose(arq);
    }

}
//Consultas
void Consultas(Time_Futebol user)
{
    system("cls");
    char arq_nome[MAX_ARQ];
    char nome[MAX], time[MAX], pos[MAX], aux[MAX];
    int idade, numCamisas, id, okay;
    moveXY(45,2, "::: CONSULTAS :::");

    char diretorio[MAX];
    moveXY(4,4, "");
    printf("Digite o diretório que contenha a pasta para consulta de arquivo (use \\ para separar os diretórios) ");
    moveXY(4,5, "OBS: deixe em branco caso deseje utilizar o diretório atual para consulta de arquivo.");
    moveXY(4,6, "OBS²: lembre-se de colocar \\ no final do diretório desejado.");
    moveXY(4,8, "");
    gets(diretorio);


    do
    {
        moveXY(4,11, "");
        printf("Digite o nome do arquivo para consultas (com extensão): ");
        gets(arq_nome);
    }while(strlen(arq_nome)==0);

    FILE *arq;
    if((arq = fopen(strcat(diretorio,arq_nome), "rb")) == NULL)
	{
	    system("cls");
	    moveXY(45,2, "::: CONSULTAS :::");
        moveXY(4,6,"Erro de abertura de arquivo!");
        moveXY(4,7,"Crie um novo na função 'Cadastro'");
        moveXY(4,9,"");
        system("pause");
        system("cls");
        fclose(arq);
        return;
	}
	else
    {
        fseek(arq,0,SEEK_SET);
        system("cls");
    }

    char resp;
    do
    {
        moveXY(45,2, "::: CONSULTAS :::");
        moveXY(38,5,"O que deseja consultar no arquivo?");
        moveXY(47,8,"1 - Geral");
        moveXY(47,10,"2 - Número da Camisa");
        moveXY(47,12,"3 - Nome de Jogador");
        moveXY(47,14,"4 - Idade");
        moveXY(47,16,"5 - Nome de Time");
        moveXY(47,18,"6 - Posição");
        moveXY(80,23,"ESC: Voltar para o Menu");
        moveXY(47,23,"Sua Escolha: ");
        resp = toupper(getch());
        fflush(stdin);
        switch(resp)
        {
            case '1':
            //condições
                moveXY(4,24,"");
                system("cls");
                fseek(arq, 0, SEEK_SET);
                okay = 0;
                while (fread(&user, sizeof(user), 1, arq) == 1) {
                    if(user.excluido == 0)
                    {
                        okay=1;
                        moveXY(48,2, "::: CONSULTA GERAL :::");
                        moveXY(50,5, "::: JOGADORES :::");
                        moveXY(20, 9, "::: INFORMAÇÕES PESSOAIS :::");
                        moveXY(22, 12, "");printf("Nome: %s", user.nome);
                        moveXY(22, 15, "");printf("Idade: %d", user.idade);
                        moveXY(72, 9, "::: INFORMAÇÕES DO TIME :::");
                        moveXY(74, 12, "");printf("Time: %s", user.time);
                        moveXY(74, 15, "");printf("Posição: %s", user.pos);
                        moveXY(74, 18, "");printf("Número da Camisa: %d", user.numCamisa);
                        moveXY(43, 26, "Pressione alguma tecla para continuar...");
                        getch();
                        system("cls");
                    }
                }
                moveXY(50,4, "::: JOGADORES :::");
                if(okay == 1){
                    moveXY(38, 11, "");printf("Não existem mais jogadores para mostrar!");
                }
                else
                {
                    moveXY(38, 11, "");printf("Não existe nenhum jogador no sistema!");
                }
                moveXY(34, 21, "Pressione alguma tecla para continuar...");
                getch();
                system("cls");
                break;
            case '2':
                moveXY(4,24,"");
                system("cls");
                moveXY(45,2, "::: CONSULTA POR NÚMERO DE CAMISA :::");
                do {
                    fflush(stdin);
                    moveXY(82,5, "                       ");
                    moveXY(38,5,"Qual o número da camisa que deseja pesquisar? ");
                    scanf("%d", &numCamisas);
                } while(numCamisas <= 0);

                system("cls");
                fseek(arq, 0, SEEK_SET);

                okay=0;
                while (fread(&user, sizeof(user), 1, arq) == 1) {
                    if(user.numCamisa == numCamisas && user.excluido == 0)
                    {
                        moveXY(45,2, "::: CONSULTA NÚMERO DE CAMISA :::");
                        moveXY(50,5, "::: JOGADORES :::");
                        moveXY(20, 9, "::: INFORMAÇÕES PESSOAIS :::");
                        moveXY(22, 12, "");printf("Nome: %s", user.nome);
                        moveXY(22, 15, "");printf("Idade: %d", user.idade);
                        moveXY(72, 9, "::: INFORMAÇÕES DO TIME :::");
                        moveXY(74, 12, "");printf("Time: %s", user.time);
                        moveXY(74, 15, "");printf("Posição: %s", user.pos);
                        moveXY(74, 18, "");printf("Número da Camisa: %d", user.numCamisa);
                        moveXY(45, 26, "Pressione alguma tecla para continuar...");
                        getch();
                        system("cls");
                        okay=1;
                    }
                }
                moveXY(50,4, "::: JOGADORES :::");
                if(okay == 1)
                {
                    moveXY(38, 11, "");printf("Não existem mais jogadores para mostrar!");
                }
                else{
                    moveXY(38, 11, "");printf("Não existe nenhum jogador no sistema com o número de camisa %d", numCamisas);
                }

                moveXY(34, 21, "Pressione alguma tecla para continuar...");
                getch();
                system("cls");
                break;
            case '3':
            //condições
                moveXY(4,24,"");
                system("cls");
                moveXY(45,2, "::: CONSULTA NOME DE JOGADOR :::");
                do {
                    fflush(stdin);
                    moveXY(38,5,"Qual o nome do jogador que deseja pesquisar? ");
                } while(strlen(gets(nome))==0);
                system("cls");
                fseek(arq, 0, SEEK_SET);
                okay=0;
                while (fread(&user, sizeof(user), 1, arq) == 1) {
                    strcpy(aux, user.nome);
                    if(strcmp(strlwr(aux), strlwr(nome)) == 0 && user.excluido == 0)
                    {
                        moveXY(45,2, "::: CONSULTA POR NOME DO JOGADOR:::");
                        moveXY(50,5, "::: JOGADORES :::");
                        moveXY(20, 9, "::: INFORMAÇÕES PESSOAIS :::");
                        moveXY(22, 12, "");printf("Nome: %s", user.nome);
                        moveXY(22, 15, "");printf("Idade: %d", user.idade);
                        moveXY(72, 9, "::: INFORMAÇÕES DO TIME :::");
                        moveXY(74, 12, "");printf("Time: %s", user.time);
                        moveXY(74, 15, "");printf("Posição: %s", user.pos);
                        moveXY(74, 18, "");printf("Número da Camisa: %d", user.numCamisa);
                        moveXY(45, 26, "Pressione alguma tecla para continuar...");
                        getch();
                        system("cls");
                        okay=1;
                    }
                }
                moveXY(50,4, "::: JOGADORES :::");
                if(okay == 1)
                {
                    moveXY(38, 11, "");printf("Não existem mais jogadores para mostrar!");
                }
                else
                {
                    moveXY(38, 11, "");printf("Não existe nenhum jogador no sistema com o nome %s!", nome);
                }

                moveXY(34, 21, "Pressione alguma tecla para continuar...");
                getch();
                system("cls");
                break;
            case '4':
            //condições
                moveXY(4,24,"");
                system("cls");
                moveXY(45,2, "::: CONSULTA POR IDADE :::");
                do {
                    fflush(stdin);
                    moveXY(85,5, "                       ");
                    moveXY(30,5,"Qual a idade do jogador que deseja pesquisar (máx 50)? ");
                    scanf("%d", &idade);
                } while(idade<=0 || idade>50);
                system("cls");
                fseek(arq, 0, SEEK_SET);
                okay = 0;
                while (fread(&user, sizeof(user), 1, arq) == 1) {
                    if(user.idade == idade && user.excluido == 0)
                    {
                        moveXY(45,2, "::: CONSULTA POR IDADE DE JOGADOR :::");
                        moveXY(50,5, "::: JOGADORES :::");
                        moveXY(20, 9, "::: INFORMAÇÕES PESSOAIS :::");
                        moveXY(22, 12, "");printf("Nome: %s", user.nome);
                        moveXY(22, 15, "");printf("Idade: %d", user.idade);
                        moveXY(72, 9, "::: INFORMAÇÕES DO TIME :::");
                        moveXY(74, 12, "");printf("Time: %s", user.time);
                        moveXY(74, 15, "");printf("Posição: %s", user.pos);
                        moveXY(74, 18, "");printf("Número da Camisa: %d", user.numCamisa);
                        moveXY(45, 26, "Pressione alguma tecla para continuar...");
                        getch();
                        system("cls");
                        okay=1;
                    }
                }
                moveXY(50,4, "::: JOGADORES :::");
                if(okay == 1)
                {
                    moveXY(38, 11, "");printf("Não existem mais jogadores para mostrar!");
                }
                else
				{
                    moveXY(38, 11, "");printf("Não existem mais jogadores no sistema com a idade de %d anos!", idade);
                }
                moveXY(34, 21, "Pressione alguma tecla para continuar...");
                getch();
                system("cls");
                break;
            case '5':
            //condições
                moveXY(4,24,"");
                system("cls");
                moveXY(45,2, "::: CONSULTA POR TIME :::");
                do {
                    moveXY(38,5,"Qual o nome do time que deseja pesquisar? ");
                } while(strlen(gets(time))==0);
                system("cls");
                fseek(arq, 0, SEEK_SET);
                okay = 0;
                while (fread(&user, sizeof(user), 1, arq) == 1) {
                    strcpy(aux, user.time);
                    if(strcmp(strlwr(aux), strlwr(time)) == 0 && user.excluido == 0)
                    {
                        moveXY(45,2, "::: CONSULTA POR TIME :::");
                        moveXY(50,5, "::: JOGADORES :::");
                        moveXY(20, 9, "::: INFORMAÇÕES PESSOAIS :::");
                        moveXY(22, 12, "");printf("Nome: %s", user.nome);
                        moveXY(22, 15, "");printf("Idade: %d", user.idade);
                        moveXY(72, 9, "::: INFORMAÇÕES DO TIME :::");
                        moveXY(74, 12, "");printf("Time: %s", user.time);
                        moveXY(74, 15, "");printf("Posição: %s", user.pos);
                        moveXY(74, 18, "");printf("Número da Camisa: %d", user.numCamisa);
                        moveXY(45, 26, "Pressione alguma tecla para continuar...");
                        getch();
                        system("cls");
                        okay = 1;
                    }
                }
                moveXY(50,4, "::: JOGADORES :::");
                if(okay == 1)
                {
                    moveXY(38, 11, "");printf("Não existem mais jogadores para mostrar!");
                }
                else
				{
                    moveXY(38, 11, "");printf("Não existem mais jogadores no sistema que pertençam ao time %s!", time);
                }
                moveXY(34, 21, "Pressione alguma tecla para continuar...");
                getch();
                system("cls");
                break;

            case '6':
            //condições
                moveXY(4,24,"");
                system("cls");
                moveXY(45,2, "::: CONSULTA POSIÇÃO DE JOGADOR :::");
                do {
                    moveXY(38,5,"Qual a posicao que jogador que deseja pesquisar joga? ");
                } while(strlen(gets(pos))==0);
                system("cls");
                fseek(arq, 0, SEEK_SET);
                okay = 0;
                while (fread(&user, sizeof(user), 1, arq) == 1) {
                    strcpy(aux, user.pos);
                    if(strcmp(strlwr(aux), strlwr(pos)) == 0 && user.excluido == 0)
                    {
                        moveXY(45,2, "::: CONSULTA POSIÇÃO DE JOGADOR :::");
                        moveXY(50,5, "::: JOGADORES :::");
                        moveXY(20, 9, "::: INFORMAÇÕES PESSOAIS :::");
                        moveXY(22, 12, "");printf("Nome: %s", user.nome);
                        moveXY(22, 15, "");printf("Idade: %d", user.idade);
                        moveXY(72, 9, "::: INFORMAÇÕES DO TIME :::");
                        moveXY(74, 12, "");printf("Time: %s", user.time);
                        moveXY(74, 15, "");printf("Posição: %s", user.pos);
                        moveXY(74, 18, "");printf("Número da Camisa: %d", user.numCamisa);
                        moveXY(45, 26, "Pressione alguma tecla para continuar...");
                        getch();
                        system("cls");
                        okay = 1;
                    }
                }
                moveXY(50,4, "::: JOGADORES :::");
                if (okay == 1) {
                    moveXY(38, 11, "");printf("Não existem mais jogadores para mostrar!");
                } else {
                    moveXY(38, 11, "");printf("Não existem mais jogadores no sistema que joguem na posição de %s!", pos);
                }
                moveXY(34, 21, "Pressione alguma tecla para continuar...");
                getch();
                system("cls");
                break;

            case ESC:
                system("cls");
                return;
                break;
        }
        fflush(arq);
    }while(resp != ESC);

    fclose(arq);
}
//Exclusão Lógica-Física
void Exclusao_Logica_Fisica(Time_Futebol user)
{
    system("cls");
    char arq_nome[MAX_ARQ];
    char op;
    int id, okay;
    moveXY(45,2, "::: EXCLUSÃO LÓGICA :::");

    char diretorio[MAX], dir[MAX];
    moveXY(4,4, "");
    printf("Digite o diretório que contenha a pasta para exclusão lógica de arquivo (use \\ para separar os diretórios) ");
    moveXY(4,5, "OBS: deixe em branco caso deseje utilizar o diretório atual para exclusão lógica de arquivo.");
    moveXY(4,6, "OBS²: lembre-se de colocar \\ no final do diretório desejado.");
    moveXY(4,8, "");
    fflush(stdin);
    gets(diretorio);

    do
    {
        moveXY(4,11, "");
        printf("Digite o nome do arquivo para exclusão lógica (com extensão): ");
        gets(arq_nome);
    }while(strlen(arq_nome)==0);

    FILE *arq;

    strcpy(dir, diretorio); //arquivo com os registros exlcuídos
    strcat(diretorio,arq_nome);

    if((arq = fopen(diretorio, "r+b")) == NULL)
	{
	    system("cls");
	    moveXY(45,2, "::: EXCLUSÃO LÓGICA :::");
        moveXY(4,6,"Erro de abertura de arquivo!");
        moveXY(4,7,"Crie um novo na função 'Cadastro'");
        moveXY(4,9,"");
        system("pause");
        system("cls");
        fclose(arq);
        return;
	}
    moveXY(4,24,"");
    system("cls");
    moveXY(40,2, "::: EXCLUSÃO DE JOGADOR :::");

    do {
        moveXY(35,4, "              ");
        moveXY(4,4,"Qual o numero da camisa do jogador que deseja excluir? ");
        scanf("%d", &id);
    } while(id<=0);
    system("cls");
    fseek(arq, 0, SEEK_SET);
    okay = 0;
    while (fread(&user, sizeof(user), 1, arq) == 1) {
        if(user.numCamisa == id && user.excluido == 0)
        {
            okay = 1;
            moveXY(45,2, "::: EXCLUI JOGADOR :::");
            moveXY(50,5, "::: JOGADOR :::");
            moveXY(20, 9, "::: INFORMAÇÕES PESSOAIS :::");
            moveXY(22, 12, "");printf("Nome: %s", user.nome);
            moveXY(22, 15, "");printf("Idade: %d", user.idade);
            moveXY(72, 9, "::: INFORMAÇÕES DO TIME :::");
            moveXY(74, 12, "");printf("Time: %s", user.time);
            moveXY(74, 15, "");printf("Posição: %s", user.pos);
            moveXY(74, 18, "");printf("Número da Camisa: %d", user.numCamisa);
            moveXY(28, 26, "Excluir jogador? Se sim, digite 's', senão digite 'n': ");
            do {
                op = toupper(getch());
            } while(op!='N' && op!='S');
            if(op=='S')
            {
                system("cls");
                moveXY(45,2, "::: EXCLUI JOGADOR :::");
                moveXY(50,5, "::: JOGADOR :::");
                moveXY(40, 10, "Excluindo...");
                Sleep(2000);
                user.excluido = 1;
                fseek(arq, -sizeof(Time_Futebol), SEEK_CUR);
        	  	fwrite(&user, sizeof(Time_Futebol), 1, arq);
                fflush(arq);
                fclose(arq);

                if((arq = fopen(diretorio, "rb")) == NULL)
            	{
            	    system("cls");
                    fclose(arq);
                    return;
            	}
                FILE *arq2;
                strcat(dir, "copia.txt");
                if((arq2 = fopen(dir, "wb")) == NULL)
                {
                    system("cls");
                    fclose(arq2);
                    return;
                }
                while(fread(&user, sizeof(user), 1, arq) == 1)
                {
                    if(user.excluido == 0)
                        fwrite(&user, sizeof(user), 1, arq2);
                }
                fclose(arq);
                remove(diretorio);
                fclose(arq2);
                rename(dir, diretorio);
				moveXY(40, 10, "     ");
                moveXY(45, 10, "Registro excluído com sucesso...");
                moveXY(25, 26, "Deseja excluir outro registro? Se sim, digite 's', senão digite 'n': ");
                do {
                    op = toupper(getch());
                } while(op!='N' && op!='S');
                if(op=='N')
                {
                    fclose(arq);
                    system("cls");
                    return;
                }
                system("cls");
                Exclusao_Logica_Fisica(user);
            }
            system("cls");
            fclose(arq);
            return;
        }
    }
    /*moveXY(48,5, "::: JOGADORES :::");
    if(okay == 0){
        moveXY(38, 11, "");printf("Não existem jogadores para mostrar");
    }
    moveXY(45, 21, "Pressione alguma tecla para continuar...");
    getch();
    system("cls");
    fclose(arq);*/

}


//Funções Secundárias
//Consulta de Arquivos numa Pasta
void Consulta_Arquivo_Pasta()
{
    system("cls");
    moveXY(38,2, "::: CONSULTAR ARQUIVOS DE UMA PASTA :::");
    fflush(stdin);

    char nome_pasta[MAX];
    moveXY(4,4, "Digite o nome do diretório consultar os arquivos (use \\ para separar os diretórios) ");
    moveXY(4,5, "OBS: deixe em branco caso deseje utilizar a pasta atual para renomeação de arquivo.");
    moveXY(4,6, "OBS²: lembre-se de colocar \\ no final do diretório desejado.");
    moveXY(4,8, "");
    gets(nome_pasta);

    system("cls");
    moveXY(38,2, "::: CONSULTAR ARQUIVOS DE UMA PASTA :::");

    char consulta[MAX] = "dir /b ";
    //moveXY(4,6,"Arquivos dentro da pasta:");
    moveXY(0,6,"");
    if(!system(strcat(consulta,nome_pasta)))
        moveXY(4,20, "Pasta consultada com sucesso!");
    else
        moveXY(4,20, "Erro na consulta de pasta. Tente novamente.");

    moveXY(4,24,"");
	system("pause");
	system("cls");
}
//Renomear Arquivo
void Renomear_Arquivo()
{
    system("cls");
    moveXY(45,2, "::: RENOMEAR ARQUIVO :::");
    fflush(stdin);

    char diretorio[MAX];
    moveXY(4,4, "");
    printf("Digite o diretório que contenha o arquivo para renomeação (use \\ para separar os diretórios) ");
    moveXY(4,5, "OBS: deixe em branco caso deseje utilizar a pasta atual para renomeação de arquivo.");
    moveXY(4,6, "OBS²: lembre-se de colocar \\ no final do diretório desejado.");
    moveXY(4,8, "");
    gets(diretorio);

    char arq_atual[MAX_ARQ], arq_novo[MAX_ARQ];
    do
    {
        moveXY(4,11, "Digite o nome do arquivo atual para renomeação (com extensão): ");
        gets(arq_atual);
    }while(strlen(arq_atual)==0);

    do
    {
        moveXY(4,13, "Agora, digite o novo nome do arquivo (com extensão): ");
        gets(arq_novo);
    }while(strlen(arq_novo)==0);

	/*Testar se o arquivo existe
	FILE *arq;
    if((arq = fopen(arq_atual, "rb")) == NULL)
	{
	    system("cls");
	    moveXY(45,2, "::: RENOMEAR ARQUIVO :::");
        moveXY(4,6,"Erro de abertura de arquivo!");
        moveXY(4,7,"Crie um novo na função 'Cadastro'");
        moveXY(4,9,"");
        system("pause");
        system("cls");
        return;
	}
	fclose(arq);*/
	system("cls");

	char diretorio_2[MAX];
    strcpy(diretorio_2,diretorio);

	moveXY(45,2, "::: RENOMEAR ARQUIVO :::");
	if(rename(strcat(diretorio,arq_atual),strcat(diretorio_2,arq_novo))==0)
		moveXY(4,4,"Arquivo renomeado com sucesso!");
    else
        moveXY(4,4,"Erro na renomeação! Tente novamente.");
    moveXY(4,24,"");
	system("pause");
	system("cls");
}

//Remover Arquivo
void Remover_Arquivo() //PODE EDITAR COM DIRETORIO PERSONALIZADO SE QUISER
{
    system("cls");
    char arq_nome[MAX_ARQ];
    moveXY(45,2, "::: REMOVER ARQUIVO :::");
    fflush(stdin);

    char diretorio[MAX];
    moveXY(4,4, "");
    printf("Digite o diretório que contenha o arquivo para remoção (use \\ para separar os diretórios) ");
    moveXY(4,5, "OBS: deixe em branco caso deseje utilizar a pasta atual para remoção de arquivo.");
    moveXY(4,6, "OBS²: lembre-se de colocar \\ no final do diretório desejado.");
    moveXY(4,8, "");
    gets(diretorio);

    do
	{
		moveXY(4,11, "");
        printf("Digite o nome do arquivo para remover (com extensão): ");
        gets(arq_nome);
	}while(strlen(arq_nome)==0);

	/*Testar se o arquivo existe
	FILE *arq;
    if((arq = fopen(arq_nome, "rb")) == NULL)
	{
	    system("cls");
	    moveXY(45,2, "::: REMOVER ARQUIVO :::");
        moveXY(4,6,"Erro de abertura de arquivo!");
        moveXY(4,7,"Crie um novo na função 'Cadastro'");
        moveXY(4,9,"");
        system("pause");
        system("cls");
        return;
	}
	fclose(arq);*/

	system("cls");
	moveXY(45,2, "::: REMOVER ARQUIVO :::");
	if(remove(strcat(diretorio,arq_nome))==0)
		moveXY(4,4,"Arquivo removido com sucesso!");
    else
        moveXY(4,4,"Erro na remoção de arquivo! Tente novamente.");
    moveXY(4,24,"");
	system("pause");
	system("cls");
}
//Criar Pasta
void Criar_Pasta()
{
    system("cls");
    moveXY(45,2, "::: CRIAR PASTA :::");
    fflush(stdin);

    char diretorio[MAX];
    moveXY(4,4, "");
    printf("Digite o diretório desejado para criar uma pasta (use \\ para separar os diretórios) ");
    moveXY(4,5, "OBS: deixe em branco caso deseje utilizar a pasta atual para criar uma pasta.");
    moveXY(4,6, "OBS²: lembre-se de colocar \\ no final do diretório desejado.");
    moveXY(4,8, "");
    gets(diretorio);

    char nome_pasta[MAX];
    do
	{
		moveXY(4,11, "");
        printf("Agora, digite o nome da pasta para criar nesse diretório: ");
        gets(nome_pasta);
	}while(strlen(nome_pasta)==0);

    system("cls");
    moveXY(45,2, "::: CRIAR PASTA :::");

    char criar[MAX] = "mkdir ";
    moveXY(4,6,"");
    if(!system(strcat(criar,strcat(diretorio,nome_pasta))))
        moveXY(4,4, "Pasta criada com sucesso!");
    else
        moveXY(4,4, "Erro na criação de pasta. Tente novamente.");

    moveXY(4,24,"");
	system("pause");
	system("cls");
}
//Renomear Pasta
void Renomear_Pasta()
{
    system("cls");
    moveXY(45,2, "::: RENOMEAR PASTA :::");
    fflush(stdin);

    char diretorio[MAX];
    moveXY(4,4, "");
    printf("Digite o diretório que contenha a pasta para renomeação (use \\ para separar os diretórios) ");
    moveXY(4,5, "OBS: deixe em branco caso deseje utilizar o diretório atual para renomeação de pasta.");
    moveXY(4,6, "OBS²: lembre-se de colocar \\ no final do diretório desejado.");
    moveXY(4,8, "");
    gets(diretorio);

	char nome_pasta[MAX];
    do
	{
		moveXY(4,11, "");
        printf("Digite o nome da pasta desejada contida nesse diretório: ");
        gets(nome_pasta);
	}while(strlen(nome_pasta)==0);

	char novo_nome_pasta[MAX];
	do
	{
		moveXY(4,13, "");
        printf("Agora, digite o novo nome que deseja para a pasta: ");
        gets(novo_nome_pasta);
	}while(strlen(novo_nome_pasta)==0);
    system("cls");
    moveXY(45,2, "::: RENOMEAR PASTA :::");


    char diretorio_2[MAX];
    strcpy(diretorio_2,diretorio);
    if(rename(strcat(diretorio,nome_pasta),strcat(diretorio_2,novo_nome_pasta))==0)
		moveXY(4,4,"Pasta renomeada com sucesso!");
    else
        moveXY(4,4,"Erro na renomeação! Tente novamente.");

    /*char renomear[MAX];
    strcat(renomear,nome_pasta);
    strcat(renomear," ");
    moveXY(0,6,"");
    if(!system(strcat(renomear,novo_nome_pasta)))
        moveXY(4,20, "Pasta renomeada com sucesso!");
    else
        moveXY(4,20, "Erro na renomeação de pasta. Tente novamente.");*/

    moveXY(4,24,"");
	system("pause");
	system("cls");
}


//Alterar Data do Sistema
void Alterar_Data()
{
    system("cls");
    char resp;
    moveXY(45,2, "::: ALTERAR DATA DO SISTEMA :::");
    moveXY(4,4, "OBS: Requer privilégios administrativos do usuário! (execute como administrador)");

    moveXY(4,6, "Data atual: ");
    system("date /t");
    //printf("%s",__DATE__);

    int teste=0, i;
    do
    {
        moveXY(4,8, "Deseja realmente alterar a data do sistema? (S/N)");
        moveXY(4,9, "");
        resp = toupper(getch());
        if(resp=='S')
            teste=1;
    }while(resp!='S' && resp!='N');

    if(teste)
    {
        moveXY(0,12,"");
        if(!system("date"))
            moveXY(4,20, "Data alterada com sucesso!");
        else
            moveXY(4,20, "Erro na alteração da data! Tente novamente.");
    }
    moveXY(4,24,"");
	system("pause");
	system("cls");
}

//Alterar Hora do Sistema
void Alterar_Hora()
{
    system("cls");
    char resp;
    moveXY(45,2, "::: ALTERAR HORA DO SISTEMA :::");
    moveXY(4,4, "OBS: Requer privilégios administrativos do usuário! (execute como administrador)");

    moveXY(4,6, "Hora atual: ");
    system("time /t");
    //printf("%s",__TIME__);

    int teste=0, i;
    do
    {
        moveXY(4,8, "Deseja realmente alterar a hora do sistema? (S/N)");
        moveXY(4,9, "");
        resp = toupper(getch());
        if(resp=='S')
            teste=1;
    }while(resp!='S' && resp!='N');

    if(teste)
    {
        moveXY(0,12,"");
        if(!system("time"))
            moveXY(4,20, "Hora alterada com sucesso!");
        else
            moveXY(4,20, "Erro na alteração da hora! Tente novamente.");
    }
    moveXY(4,24,"");
	system("pause");
	system("cls");
}

void geraArqMenu() {
    FILE *arq;
    if ((arq = fopen("ajuda.txt", "w"))==NULL) {

    }
    fputs("::: MENU DE AJUDA :::" , arq);
    putc('\n', arq);
    fputs("-> O Menu é dividido em SubMenus, então, quando acessar o sistema deverá escolher, utilizando as setas esquerda e ", arq);
    fputs("direita, entre 'Manipulação de Dados' e 'Manipulação de Arquivos e outros'. Pressione <ENTER> para acessar a opção", arq);
    putc('\n', arq);
    fputs("-> Ao escolher entre os dois possíveis Menus, será direcionado ao SubMenu para navegar correspondente onde poderá decidir, ", arq);
    fputs("utilizando as setas para cima e para baixo, entre as diferentes funcionalidades do sistema. De forma aná-loga, utilize o ", arq);
    fputs("<ENTER> para acessar a função desejada. Cada função terá explicações de seu funcionamento ao aces-sá-la.", arq);
    putc('\n', arq);
    fputs("-> Se você está num SubMenu e deseja voltar à decidir entre os Menus acima citados, então pressione <ESC> uma vez. Pressione <ESC> mais uma vez se deseja encerrar o sistema.", arq);
    putc('\n', arq);
    putc('\n', arq);
    fputs("Nós, Davi e Luiz, desenvolvedores do sistema, agradecemos desde já sua preferência!", arq);

    fclose(arq);

}

void cripto() {
    FILE *arq, *arq1;
    char aux[MAX], op;
    int i;
    system("cls");
    if ((arq = fopen("ajuda.txt", "r"))==NULL){
        printf("Alguma coisa deu errado na abertura do arquivo\n" );
        exit(1);
    }
    if((arq1 = fopen("cripto.txt", "w"))==NULL)
    {
        printf("Alguma coisa deu errado na abertura do arquivo\n" );
        exit(1);
    }
    while (fgets(aux, 80, arq)!=NULL) {
        for (i = 0; i < strlen(aux); i++) {
                aux[i] = aux[i]+17;
        }
        fputs(aux, arq1);
    }
    fclose(arq);
    fclose(arq1);
}

void descripto()
{
    FILE *arq, *arq1;
    char aux[MAX], cripto[MAX]={""}, op;
    int i;
    system("cls");
    if ((arq = fopen("cripto.txt", "r"))==NULL){
        printf("Alguma coisa deu errado na abertura do arquivo\n" );
        exit(1);
    }
    if((arq1 = fopen("descripto.txt", "w"))==NULL)
    {
        printf("Alguma coisa deu errado na abertura do arquivo\n" );
        exit(1);
    }
    while (fgets(aux, 80, arq)!=NULL) {
        for (i = 0; i < strlen(aux); i++) {
                aux[i] = aux[i]-17;
        }
        fputs(aux, arq1);
    }
    fclose(arq);
    fclose(arq1);
}

void imprimeDescripto() {
    FILE *arq;
    char aux[120], op, cont=0, posY = 5;
    int i;
    system("cls");
    if ((arq = fopen("descripto.txt", "r"))==NULL){
        printf("Alguma coisa deu errado na abertura do arquivo\n" );
        exit(1);
    }
    while (fgets(aux, 115, arq)!=NULL) {
        if(!cont){
            moveXY(52,2, aux);
            cont++;
            continue;
        }
        moveXY(4, posY, aux);
        posY+=2;
    }
    fclose(arq);
}

//Ajuda (Criptografada)
int Tela_Ajuda(char opcao_first)
{
    system("cls");

    geraArqMenu();
    cripto();
    descripto();
    imprimeDescripto();

    moveXY(45, 28, "Pressione <ESC> para voltar para o Menu...");

    do
    {
        opcao_first = toupper(getch());
        if(opcao_first==ESC)
        {
            system("cls");
            return 1;
        }
    }while(opcao_first!=ESC);
}
