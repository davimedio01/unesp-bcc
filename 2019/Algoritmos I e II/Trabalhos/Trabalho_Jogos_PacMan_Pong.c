#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <dos.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <strings.h>

#define max_tela 20


//PAC-MAN: Funcões
char** Contrucao_Mapa(int dim_mapa);
void Contrucao_Obtaculo(char **Mapa);
void Controlar_PacMan(char **Mapa, int *Pac_PosX, int *Pac_PosY, char controle, int *placar);
void Controlar_Fantasma(char **Mapa, char *Pos_Ant_Fant, int *Pac_PosX, int *Pac_PosY, int *Fant_PosX, int *Fant_PosY, int *Vida_Pac);
void Imprimir_Mapa (char **Mapa, int dimen_mapa, int *Placar, int Pac_PosX_Ini, int Pac_PoxY_Ini, int Fant_PosX_Ini, int Fant_PosY_Ini, int *Vida_Pac);

//PING-PONG: Funções
void Pong_AtualizaTela(int Jog_Pos, int CPU_Pos, int Bola_PosX, int Bola_PosY, int Bola_Cima, int Bola_Baixo, int Bola_Direita, int Bola_Esquerda, int DecrescY, int SomaY, int DecrescX, int SomaX, int Placar_Jog, int Placar_CPU);
//Variaveis Globais para o Placar no PING-PONG
int Placar_Jog=0, Placar_CPU=0;


//Menu do Jogo
int Menu(int *opcao)
{
    do{
    printf("\n\n              D A V I Z A U M   G A M E S\n\n");
    printf("                CRIADO POR DAVI AUGUSTO\n");
    printf("                TRABALHO - ALGORITMOS I\n\n\n");
    printf("                    1 - PAC-MAN\n");
    printf("                    2 - PING-PONG\n");
    printf("                    3 - INSTRUCOES\n");
    printf("                    4 - SAIR\n\n");
    printf("   ATENCAO: TERMINO DO PING-PONG NAO VOLTA PRO MENU\n");
    printf("                  VERSAO 1.0 - BETA\n\n\n");
    printf("                    SUA OPCAO: ");
    scanf("%d",&*opcao);
    printf("\n\n");
    system("cls");
    if(*opcao==1||*opcao==2||*opcao==3||*opcao==4)
        break;
    }while(1);
    return *opcao;
}

//Tela de Instruções do Jogo
void Instrucoes()
{
    printf("\n                                  I N S T R U C O E S\n\n\n");
    printf("-------------------------------------------------------------------------------------------\n");
    printf("                                     P A C - M A N\n\n");
    printf("Use as teclas 'W'A'S'D' para controlar o Pac-Man e comer todas as bolinhas!\nMas cuidado: neste lugar existe um fantasma terrivel que tentara pega-lo!\nFuja dele se for capaz!\n\nJogo feito para um jogador.\n");
    printf("-------------------------------------------------------------------------------------------\n");
    printf("                                   P I N G - P O N G\n\n");
    printf("Use as teclas 'W' e 'S' (ou 'E' e 'D' para ir mais rapidamente)\npara controlar a barra da esquerda (Jogador 1) e rebater a bolinha contra a barra\nda direita (Jogador 2) que usa as teclas 'U' e 'J' (ou 'I' e 'K' para ir mais rapidamente).\nGanha quem somar 10 pontos! Atencao: a saida da bolinha vale por 2 pontos\n\nJogo feito para dois jogadores.\n");
    printf("-------------------------------------------------------------------------------------------\n");
    system("PAUSE");
    system("cls");
}
//Função para calculo da distancia entre pontos (usado no Pac-Man)
int Distancia_Pontos(int x2, int y2, int x1, int y1)
{
    return sqrt(pow(x2-x1,2)+ pow(y2-y1,2));
}

int main()
{
    int opcao_menu=0;
    while(opcao_menu!=4)
    {
        Menu(&opcao_menu);
        if(opcao_menu==3) //Tela de Instrucoes
            Instrucoes();
        else if(opcao_menu==1) //Pac-Man Game
        {
            char **Mapa;
            int dimen_mapa = max_tela;
            int Placar_Max = 167;
            int Vida_Pac = 1;
            int Placar=0;
            int Pac_PosX=1,Pac_PosY=1; //Posição Inicial do Pac-Man
            int Fant_PosX=9,Fant_PosY=10; //Posição Inicial do Fantasma
            char Pos_Ant_Fant=' ';
            char controle;
            Mapa=Contrucao_Mapa(dimen_mapa);
            Contrucao_Obtaculo(Mapa);
            Imprimir_Mapa(Mapa,dimen_mapa,&Placar,Pac_PosX,Pac_PosY,Fant_PosX,Fant_PosY,&Vida_Pac);
            while(Vida_Pac==1 && Placar!=Placar_Max)
            {
                controle=getch();
                if(controle=='w'||controle=='a'||controle=='s'||controle=='d')
                {
                    Controlar_PacMan(Mapa,&Pac_PosX,&Pac_PosY,controle,&Placar);
                    Controlar_Fantasma(Mapa,&Pos_Ant_Fant,&Pac_PosX,&Pac_PosY,&Fant_PosX,&Fant_PosY,&Vida_Pac);
                    Imprimir_Mapa(Mapa,dimen_mapa,&Placar,Pac_PosX,Pac_PosY,Fant_PosX,Fant_PosY,&Vida_Pac);
                }
            }
            if(Placar==Placar_Max)
            {
                Beep(550,300);
                Beep(650,300);
                Beep(700,300);
                Beep(750,300);
                Beep(780,280);
                Beep(830,280);
                Beep(900,750);
                printf("\nPARABENS!! VOCE VENCEU O JOGO E AJUDOU O PAC-MAN A COMER TUDO!");
            }

            else
            {
                Beep(760,270);
                Beep(700,300);
                Beep(650,300);
                Beep(500,300);
                Beep(450,300);
                Beep(350,300);
                Beep(300,300);
                Beep(200,300);
                Beep(180,300);
                printf("\nQUE PENA, O FANTASMA PEGOU O PAC-MAN. BOA SORTE DA PROXIMA VEZ!");
            }
            printf("\n------------------------------------------------\n");
            system("PAUSE");
            }
        else if(opcao_menu==2)//Ping-Pong Game
        {
            int Jog_Pos=13, CPU_Pos=13;
            int Bola_PosX=16, Bola_PosY=26;
            int Bola_Cima=1, Bola_Baixo=0, Bola_Esquerda=1, Bola_Direita=0;
            int DecrescY=1, DecrescX=1, SomaY=1, SomaX=1;

            Pong_AtualizaTela(Jog_Pos,CPU_Pos,Bola_PosX,Bola_PosY,Bola_Cima,Bola_Baixo,Bola_Direita,Bola_Esquerda,DecrescY,SomaY,DecrescX,SomaX,Placar_Jog,Placar_CPU);
			
            system("PAUSE");
        }
        system("cls");
    }
    return 0;
}

//PAC-MAN
//Construção do Mapa (matriz string) com alocação dinâmica na memória por conta da atualização dinâmica em si
char** Contrucao_Mapa(int dimen_mapa)
{
    int i,j;
    char **Mapa;
    Mapa=(char**)malloc(dimen_mapa *sizeof(char*)); //Aloca uma dimensão X da sala
    for(i=0;i<dimen_mapa;i++)
    {
        Mapa[i] = (char*)malloc(dimen_mapa *sizeof(char)); //Aloca a outra dimensão Y da sala
        for(j=0;j<dimen_mapa;j++)
        {
            if(i==0||i==(dimen_mapa-1)||j==0||j==(dimen_mapa-1))
                Mapa[i][j]='I';
            else
                Mapa[i][j]='.';
        }
    }
    return Mapa;
}
//Aqui estão as construções dos obstáculos dentro do mapa do jogo (modo manual)
void Contrucao_Obtaculo(char **Mapa)
{
    //Bloco 1: Superior Esquerdo
    Mapa[2][2]='I';
    Mapa[2][3]='I';
    Mapa[2][4]='I';
    Mapa[3][2]='I';
    Mapa[3][3]=' ';
    Mapa[3][4]='I';
    Mapa[4][2]='I';
    Mapa[4][3]=' ';
    Mapa[4][4]='I';
    Mapa[5][2]='I';
    Mapa[5][3]='I';
    Mapa[5][4]='I';
    //Bloco 2: Superior Centro-Esquerdo
    Mapa[2][6]='I';
    Mapa[3][6]='I';
    Mapa[4][6]='I';
    Mapa[5][6]='I';
    Mapa[2][7]='I';
    Mapa[3][7]='I';
    Mapa[4][7]='I';
    Mapa[5][7]='I';
    //Bloco 3: Superior Centro-Direito
    Mapa[2][12]='I';
    Mapa[3][12]='I';
    Mapa[4][12]='I';
    Mapa[5][12]='I';
    Mapa[2][13]='I';
    Mapa[3][13]='I';
    Mapa[4][13]='I';
    Mapa[5][13]='I';
    //Bloco 4: Superior Direito
    Mapa[2][15]='I';
    Mapa[2][16]='I';
    Mapa[2][17]='I';
    Mapa[3][15]='I';
    Mapa[3][16]=' ';
    Mapa[3][17]='I';
    Mapa[4][15]='I';
    Mapa[4][16]=' ';
    Mapa[4][17]='I';
    Mapa[5][15]='I';
    Mapa[5][16]='I';
    Mapa[5][17]='I';
    //Bloco 5: Superior Central
    Mapa[1][9]='I';
    Mapa[2][9]='I';
    Mapa[3][9]='I';
    Mapa[4][9]='I';
    Mapa[5][9]='I';
    Mapa[1][10]='I';
    Mapa[2][10]='I';
    Mapa[3][10]='I';
    Mapa[4][10]='I';
    Mapa[5][10]='I';
    //Bloco 6: Extremo Centro-Esquerdo
    Mapa[7][1]='I';
    Mapa[7][2]='I';
    Mapa[7][3]='I';
    Mapa[8][1]='I';
    Mapa[9][3]='I';
    Mapa[10][2]='I';
    Mapa[10][3]='I';
    Mapa[11][3]='I';
    Mapa[12][1]='I';
    Mapa[13][1]='I';
    Mapa[13][2]='I';
    Mapa[13][3]='I';
    //Bloco 7: Extremo Centro-Direito
    Mapa[7][16]='I';
    Mapa[7][17]='I';
    Mapa[7][18]='I';
    Mapa[8][18]='I';
    Mapa[9][16]='I';
    Mapa[10][16]='I';
    Mapa[10][17]='I';
    Mapa[11][16]='I';
    Mapa[12][18]='I';
    Mapa[13][18]='I';
    Mapa[13][17]='I';
    Mapa[13][16]='I';
    //Bloco 8: Centro-Esquerdo
    Mapa[7][5]='I';
    Mapa[8][5]='I';
    Mapa[9][5]='I';
    Mapa[10][5]='I';
    Mapa[11][5]='I';
    Mapa[12][5]='I';
    Mapa[9][6]='I';
    Mapa[9][7]='I';
    Mapa[10][6]='I';
    Mapa[10][7]='I';
    //Bloco 9: Centro-Direito
    Mapa[7][14]='I';
    Mapa[8][14]='I';
    Mapa[9][14]='I';
    Mapa[10][14]='I';
    Mapa[11][14]='I';
    Mapa[12][14]='I';
    Mapa[9][13]='I';
    Mapa[9][12]='I';
    Mapa[10][13]='I';
    Mapa[10][12]='I';
    //Bloco 10: Centro-Superior
    Mapa[7][7]='I';
    Mapa[7][8]='I';
    Mapa[7][9]='I';
    Mapa[7][10]='I';
    Mapa[7][11]='I';
    Mapa[7][12]='I';
    Mapa[8][9]='I';
    Mapa[8][10]='I';
    Mapa[9][9]='I';
    Mapa[9][10]='I';
    //Bloco 11: Centro-Inferior
    Mapa[14][7]='I';
    Mapa[14][8]='I';
    Mapa[14][9]='I';
    Mapa[14][10]='I';
    Mapa[14][11]='I';
    Mapa[14][12]='I';
    Mapa[13][9]='I';
    Mapa[13][10]='I';
    Mapa[12][9]='I';
    Mapa[12][10]='I';
    //Bloco 12: Central (Fantasma)
    Mapa[10][9]=' ';
    Mapa[10][10]=' ';
    Mapa[11][9]=' ';
    Mapa[11][10]=' ';
    //Bloco 13: Centrais (Outros)
    Mapa[12][7]='I';
    Mapa[12][12]='I';
    //Bloco 14: Inferior Extremo-Direito
    Mapa[15][15]='I';
    Mapa[15][16]='I';
    Mapa[15][17]='I';
    Mapa[16][15]=' ';
    Mapa[16][16]=' ';
    Mapa[16][17]='I';
    Mapa[17][15]='I';
    Mapa[17][16]='I';
    Mapa[17][17]='I';
    Mapa[14][14]='I';
    Mapa[15][14]='I';
    Mapa[16][14]='I';
    Mapa[17][14]='I';
    //Bloco 15: Inferior Extremo-Esquerdo
    Mapa[15][2]='I';
    Mapa[15][3]='I';
    Mapa[15][4]='I';
    Mapa[16][2]='I';
    Mapa[16][3]=' ';
    Mapa[16][4]=' ';
    Mapa[17][2]='I';
    Mapa[17][3]='I';
    Mapa[17][4]='I';
    Mapa[14][5]='I';
    Mapa[15][5]='I';
    Mapa[16][5]='I';
    Mapa[17][5]='I';
    //Bloco 16: Inferior Centro-Direito
    Mapa[16][12]='I';
    Mapa[17][12]='I';
    //Bloco 17: Inferior Centro-Esquerdo
    Mapa[16][7]='I';
    Mapa[17][7]='I';
    //Bloco 18: Inferior Central
    Mapa[16][9]='I';
    Mapa[17][9]='I';
    Mapa[18][9]='I';
    Mapa[16][10]='I';
    Mapa[17][10]='I';
    Mapa[18][10]='I';
}

//Função do Pac-Man relacionando o mapa (posições x e y), os botoes 'WASD' e uma auxiliar para somar os pontos conquistados
void Controlar_PacMan(char **Mapa, int *Pac_PosX, int *Pac_PosY, char controle, int *Placar)
{
    //Cada botão vai deixar em branco onde o Pac-Man passar; vai analisar a proxima posicao dele (com base na que ele se encontra atualmente) e vai colocar ele la se nao for uma parede
    //Botao W
    if(controle=='w')
    {
        if(Mapa[(*Pac_PosY)-1][(*Pac_PosX)]=='I')
        {}
        else
        {
            if(Mapa[(*Pac_PosY)-1][(*Pac_PosX)]=='.')
            {
                (*Placar)++;
                Beep(550,150);
            }

            Mapa[(*Pac_PosY)][(*Pac_PosX)]=' ';
            (*Pac_PosY)--;
            Mapa[(*Pac_PosY)][(*Pac_PosX)]='C';
        }
    }
    //Botao S
    if(controle=='s')
    {
        if(Mapa[(*Pac_PosY)+1][(*Pac_PosX)]=='I')
        {}
        else
        {
            if(Mapa[(*Pac_PosY)+1][(*Pac_PosX)]=='.')
            {
                (*Placar)++;
                Beep(550,150);
            }
            Mapa[(*Pac_PosY)][(*Pac_PosX)]=' ';
            (*Pac_PosY)++;
            Mapa[(*Pac_PosY)][(*Pac_PosX)]='C';
        }
    }
    //Botao A
    if(controle=='a')
    {
        if(Mapa[(*Pac_PosY)][(*Pac_PosX)-1]=='I')
        {}
        else
        {
            if(Mapa[(*Pac_PosY)][(*Pac_PosX)-1]=='.')
            {
                (*Placar)++;
                Beep(550,150);
            }
            Mapa[(*Pac_PosY)][(*Pac_PosX)]=' ';
            (*Pac_PosX)--;
            Mapa[(*Pac_PosY)][(*Pac_PosX)]='C';
        }
    }
    //Botao D
    if(controle=='d')
    {
        if(Mapa[(*Pac_PosY)][(*Pac_PosX)+1]=='I')
        {}
        else
        {
            if(Mapa[(*Pac_PosY)][(*Pac_PosX+1)]=='.')
            {
                (*Placar)++;
                Beep(550,150);
            }
            Mapa[(*Pac_PosY)][(*Pac_PosX)]=' ';
            (*Pac_PosX)++;
            Mapa[(*Pac_PosY)][(*Pac_PosX)]='C';
        }
    }
}

//Função para o controle automático do Fantasma. Com base na distancia entre as coordenadas, ele vai pelo melhor caminho. Se encostar no Pac-Man, o jogo termina (1 vida apenas)
void Controlar_Fantasma(char **Mapa, char *Pos_Ant_Fant, int *Pac_PosX, int *Pac_PosY, int *Fant_PosX, int *Fant_PosY, int *Vida_Pac)
{
    int Menor_Dist, Fant_PosX_Menor, Fant_PosY_Menor;

    //Calculo da menor distancia entre o fantasma e o Pac-Man
    Menor_Dist = Distancia_Pontos((*Fant_PosX),(*Fant_PosY),(*Pac_PosX),(*Pac_PosY));
    Fant_PosX_Menor = (*Fant_PosX);
    Fant_PosY_Menor = (*Fant_PosY);
    //Uso dos conceitos da geometria pombalina/taxi, por conta da distancia entre coordenadas ser dada por meio de linhas verticais e horizontais
    //Agora o algoritmo vai verificar as posições validas do fantasma e salvar a menor delas (com relação ao mov. do Pac-Man)
    if((Mapa[(*Fant_PosY)][(*Fant_PosX)-1]!='I')&&(Distancia_Pontos(((*Fant_PosX)-1),(*Fant_PosY),(*Pac_PosX),(*Pac_PosY))<Menor_Dist))
    {
        Fant_PosX_Menor = ((*Fant_PosX)-1);
        Fant_PosY_Menor = (*Fant_PosY);
    }
    if((Mapa[(*Fant_PosY)][(*Fant_PosX)+1]!='I')&&(Distancia_Pontos(((*Fant_PosX)+1),(*Fant_PosY),(*Pac_PosX),(*Pac_PosY))<Menor_Dist))
    {
        Fant_PosX_Menor = ((*Fant_PosX)+1);
        Fant_PosY_Menor = (*Fant_PosY);
    }
    if((Mapa[(*Fant_PosY-1)][(*Fant_PosX)]!='I')&&(Distancia_Pontos((*Fant_PosX),((*Fant_PosY)-1),(*Pac_PosX),(*Pac_PosY))<Menor_Dist))
    {
        Fant_PosX_Menor = (*Fant_PosX);
        Fant_PosY_Menor = ((*Fant_PosY)-1);
    }
    if((Mapa[(*Fant_PosY)+1][(*Fant_PosX)]!='I')&&(Distancia_Pontos((*Fant_PosX),((*Fant_PosY)+1),(*Pac_PosX),(*Pac_PosY))<Menor_Dist))
    {
        Fant_PosX_Menor = (*Fant_PosX);
        Fant_PosY_Menor = ((*Fant_PosY)+1);
    }
    //Agora o algoritmo vai verificar a questão das paredes e forçar o fantasma a andar para a coluna/linha mais proxima
    if(((*Fant_PosX)==Fant_PosX_Menor) && ((*Fant_PosY)==Fant_PosY_Menor))
    {
        if(pow(((*Fant_PosX)-1)-(*Pac_PosX),2) < pow(((*Fant_PosX)-(*Pac_PosX)),2) && Mapa[(*Fant_PosY)][(*Fant_PosX)-1]!='I')
            Fant_PosX_Menor = (*Fant_PosX)-1;
        else if (pow(((*Fant_PosX)+1)-(*Pac_PosX),2) < pow(((*Fant_PosX)-(*Pac_PosX)),2) && Mapa[(*Fant_PosY)][(*Fant_PosX+1)]!='I')
            Fant_PosX_Menor = (*Fant_PosX)+1;
        if(pow(((*Fant_PosY)-1)-(*Pac_PosY),2) < pow(((*Fant_PosY)-(*Pac_PosY)),2) && Mapa[(*Fant_PosY)-1][(*Fant_PosX)]!='I')
            Fant_PosY_Menor = (*Fant_PosY)-1;
        else if (pow(((*Fant_PosY)+1)-(*Pac_PosY),2) < pow(((*Fant_PosY)-(*Pac_PosY)),2) && Mapa[(*Fant_PosY)+1][(*Fant_PosX)]!='I')
            Fant_PosY_Menor = (*Fant_PosY)+1;
    }
    //Assim, tendo encontrado as menores posições para ir atras do Pac-Man, o fantasma ira se mover (igual o Pac-Man)
    if((*Pos_Ant_Fant)==' ')
        Mapa[(*Fant_PosY)][(*Fant_PosX)] = ' ';
    if((*Pos_Ant_Fant)=='.')
        Mapa[(*Fant_PosY)][(*Fant_PosX)] = '.';
    if((*Pos_Ant_Fant)=='I')
        Mapa[(*Fant_PosY)][(*Fant_PosX)] = 'I';
    (*Fant_PosX) = Fant_PosX_Menor;
    (*Fant_PosY) = Fant_PosY_Menor;
    (*Pos_Ant_Fant) = Mapa[(*Fant_PosY)][(*Fant_PosX)];
    //Se o fantasma encostar no Pac-Man, o contador de vida diminui e o jogo termina com isso
    if((*Fant_PosY)==(*Pac_PosY)&&(*Fant_PosX)==(*Pac_PosX))
        (*Vida_Pac)=0;
}

//Funcao que imprime o Mapa
void Imprimir_Mapa (char **Mapa, int dimen_mapa, int *Placar, int Pac_PosX_Ini, int Pac_PoxY_Ini, int Fant_PosX_Ini, int Fant_PosY_Ini, int *Vida_Pac)
{
    int i,j;
    Mapa[Pac_PoxY_Ini][Pac_PosX_Ini] = 'C';
    Mapa[Fant_PosY_Ini][Fant_PosX_Ini] = 'F';
    system("cls");
    printf("              P A C - M A N\n\n");
    for(i=0;i<dimen_mapa;i++)
    {
        printf("\n");
        for(j=0;j<dimen_mapa;j++)
            printf(" %c",Mapa[i][j]);
    }
    printf("\n\nPONTUACAO: %d\n",(*Placar));
    printf("VIDA DO PAC-MAN: %d\n",(*Vida_Pac));
    printf("DIGITE SEU MOVIMENTO: ");
}


//PING-PONG
//Diferente do Pac-Man, o Pong necessita de uma constante atualização na tela (ou seja, a bolinha n pode ficar parada so quando o jogador resolver pressionar a tecla)
//Para isso, é necessário uma função de Atualiza_Tela
void Pong_AtualizaTela(int Jog_Pos, int CPU_Pos, int Bola_PosX, int Bola_PosY, int Bola_Cima, int Bola_Baixo, int Bola_Direita, int Bola_Esquerda, int DecrescY, int SomaY, int DecrescX, int SomaX, int Placar_Jog, int Placar_CPU)
{
    if(Placar_Jog<10 && Placar_CPU<10)
    {
    usleep(1000000); //Suspender a execução por um intervalo. Fundamental para atualizar a tela com certa velocidade
    int i,j;

    system("cls");

    for(i=0;i<=31;i++)
    {
        for(j=0;j<=70;j++)
        {
            //Barra do Jogador (esquerda)
            if(i==Jog_Pos-2 || i==Jog_Pos-1 || i==Jog_Pos || i==Jog_Pos+1 || i==Jog_Pos+2)
            {
                if(j==0)
                    printf("|");
            }
             //Checar se a barra da CPU (direita) está na msm posição da bola
            if(i!=Bola_PosY)
            {
                if(i==CPU_Pos-2 || i==CPU_Pos-1 || i==CPU_Pos || i==CPU_Pos+1 || i==CPU_Pos+2)
                {
                    if(j==65)
                        printf("|");
                    else
                        printf(" ");
                    if(i==Jog_Pos-2 || i==Jog_Pos-1 || i==Jog_Pos || i==Jog_Pos+1 || i==Jog_Pos+2)
                    {
                        if(j==2)
                            printf("\b"); //realiza uma 'limpeza' com relação a barra da CPU
                    }
                }
            }
            else if(i==Bola_PosY)
            {
                if(i==CPU_Pos-2 || i==CPU_Pos-1 || i==CPU_Pos || i==CPU_Pos+1 || i==CPU_Pos+2)
                {
                    if(j<Bola_PosX)
                        printf(" ");
                    else if(j>Bola_PosX)
                    {
                        if(j<65)
                            printf(" ");
                        else if(j==65)
                            printf("|");
                    }
                    else if(j==Bola_PosX)
                        printf("*");
                    if(i==Jog_Pos-2 || i==Jog_Pos-1 || i==Jog_Pos || i==Jog_Pos+1 || i==Jog_Pos+2)
                    {
                        if(j==Bola_PosX+1)
                            printf("\b");
                    }
                }
                else
                {
                    if(j==Bola_PosX)
                        printf("*");
                    else
                        printf(" ");
                }
            }

            if(i==31){
                printf("-");
            }
        }
        printf("\n");
    }

    if(Bola_PosX==-1)
        Placar_CPU++;
    else if(Bola_PosX==66)
        Placar_Jog++;

    printf("                             PONTUACAO\n");
    printf("JOGADOR 1: %d PTS                                       JOGADOR 2: %d PTS\n",Placar_Jog,Placar_CPU);

    //Movimentação da Bola
    if(Bola_Cima)
        Bola_PosY=Bola_PosY-DecrescY;
    else if(Bola_Baixo)
        Bola_PosY=Bola_PosY+SomaY;
    if(Bola_Direita)
        Bola_PosX=Bola_PosX+SomaX;
    else if(Bola_Esquerda)
        Bola_PosX=Bola_PosX-DecrescX;
    //Movimentos da Bola relacionados a coluna max e min (bater na parede e voltar)
    if(Bola_PosY==0 || Bola_PosY==1)
    {
        Bola_Cima=0;
        Bola_Baixo=1;
    }
    else if(Bola_PosY==28 || Bola_PosY == 29)
    {
        Bola_Cima=1;
        Bola_Baixo=0;
    }
    //Movimentos da Bola relacionados a linha min e max (bater no jogador/CPU e ir pro outro lado)
    if(Bola_PosX<=2 && (Jog_Pos==Bola_PosY-2 || Jog_Pos==Bola_PosY-1 || Jog_Pos==Bola_PosY || Jog_Pos==Bola_PosY+1 || Jog_Pos==Bola_PosY+2))
    {
        Bola_Esquerda = 0;
        Bola_Direita = 1;
        if(Jog_Pos==Bola_PosY-2)
        {
            DecrescY = 2;
            SomaY = 2;

            Bola_Cima = 0;
            Bola_Baixo = 1;
        }
        else if(Jog_Pos==Bola_PosY-1)
        {
            DecrescY = 1;
            SomaY = 1;

            Bola_Cima = 0;
            Bola_Baixo = 1;
        }
        else if(Jog_Pos==Bola_PosY)
        {
            DecrescY = 0;
            SomaY = 0;

            Bola_Cima = 0;
            Bola_Baixo = 0;
        }
        else if(Jog_Pos==Bola_PosY+1)
        {
            DecrescY = 1;
            SomaY = 1;

            Bola_Cima = 1;
            Bola_Baixo = 0;
        }
        else if(Jog_Pos==Bola_PosY+2)
        {
            DecrescY = 2;
            SomaY = 2;

            Bola_Cima = 1;
            Bola_Baixo = 0;
        }
    }
    if(Bola_PosX>=62 && (CPU_Pos==Bola_PosY-2 || CPU_Pos==Bola_PosY-1 || CPU_Pos==Bola_PosY || CPU_Pos==Bola_PosY+1 || CPU_Pos==Bola_PosY+2))
    {
        Bola_Esquerda = 1;
        Bola_Direita = 0;
        if(CPU_Pos==Bola_PosY-2)
        {
            DecrescY = 2;
            SomaY = 2;

            Bola_Cima = 0;
            Bola_Baixo = 1;
        }
        else if(CPU_Pos==Bola_PosY-1)
        {
            DecrescY = 1;
            SomaY = 1;

            Bola_Cima = 0;
            Bola_Baixo = 1;
        }
        else if(CPU_Pos==Bola_PosY)
        {
            DecrescY = 0;
            SomaY = 0;

            Bola_Cima = 0;
            Bola_Baixo = 0;
        }
        else if(CPU_Pos==Bola_PosY+1)
        {
            DecrescY = 1;
            SomaY = 1;

            Bola_Cima = 1;
            Bola_Baixo = 0;
        }
        else if(CPU_Pos==Bola_PosY+2)
        {
            DecrescY = 2;
            SomaY = 2;

            Bola_Cima = 1;
            Bola_Baixo = 0;
        }
    }

    //Repetidor para Atualizar a Tela (jogo dinâmico) (uso da função kbhit para pegar a tecla do usuario)
    while(!kbhit())
    {
        Pong_AtualizaTela(Jog_Pos, CPU_Pos, Bola_PosX, Bola_PosY, Bola_Cima, Bola_Baixo, Bola_Direita, Bola_Esquerda, DecrescY, SomaY, DecrescX, SomaX, Placar_Jog, Placar_CPU);
    }

    //Controlador do Jogador 1
    int controle = getch();
    //Subir = Lento
    if(controle==119)
    {
        if(Jog_Pos>2)
            Jog_Pos-=1;

    }
    //Subir = Rapido
    else if(controle==101)
    {
        if(Jog_Pos>2)
            Jog_Pos-=2;
    }
    //Descer = Lento
    else if(controle==115)
    {
        if(Jog_Pos<27)
            Jog_Pos+=1;
    }
    //Descer = Rapido
    else if(controle==100)
    {
        if(Jog_Pos<27)
            Jog_Pos+=2;
    }

    //Controlador do Jogador 2
    //Subir = Lento
    if(controle==117)
    {
        if(CPU_Pos>2)
            CPU_Pos-=1;
    }
    //Subir = Rapido
    else if(controle==105)
    {
        if(CPU_Pos>2)
            CPU_Pos-=2;
    }
    //Descer = Lento
    else if(controle==106)
    {
        if(CPU_Pos<27)
            CPU_Pos+=1;
    }
    //Descer = Rapido
    else if(controle==107)
    {
        if(CPU_Pos<27)
            CPU_Pos+=2;
    }

        Pong_AtualizaTela(Jog_Pos, CPU_Pos, Bola_PosX, Bola_PosY, Bola_Cima, Bola_Baixo, Bola_Direita, Bola_Esquerda, DecrescY, SomaY, DecrescX, SomaX, Placar_Jog, Placar_CPU);

    }
    else
    {
        printf("\n-----------------------------------------------------------------------\n");
        if(Placar_CPU==10)
        {
            Beep(550,300);
            Beep(650,300);
            Beep(700,300);
            Beep(750,300);
            Beep(780,280);
            Beep(830,280);
            Beep(900,750);
            printf("\nPARABENS PARA O JOGADOR 2! VITORIA POR: %d X %d\n",Placar_Jog, Placar_CPU);
            printf("\n-----------------------------------------------------------------------\n");
        }
        else if(Placar_Jog==10)
        {
            Beep(550,300);
            Beep(650,300);
            Beep(700,300);
            Beep(750,300);
            Beep(780,280);
            Beep(830,280);
            Beep(900,750);
            printf("\nPARABENS PARA O JOGADOR 1! VITORIA POR: %d X %d\n",Placar_Jog, Placar_CPU);
            printf("\n----------------------------------------------------------------------\n");
        }
        system("PAUSE");
        system("cls");
        //goto main();
    }

}
