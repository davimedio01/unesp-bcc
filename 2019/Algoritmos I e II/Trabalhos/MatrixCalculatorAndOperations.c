//Trabalho 1 - Algoritmos II~~
//Aluno: Davi Augusto
//Curso: BCC
//Data de Entrega: 12/08/2019

//Compilar com o GCC 64-bit para evitar conflitos na matriz
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

//Teclas em ASCII (*usar o getch)
#define CIMA 72
#define BAIXO 80
#define DIREITA 77
#define ESQUERDA 75
#define ESC 27
#define AJUDA 59 //F1 (tecla especial: 0 e 59 ao mesmo tempo)
#define ENTER 13
#define LIN_MAX 10
#define COL_MAX 10

//Variáveis Globais
int i, j, lin, col, col2, n;//, menu_sub=0, menu_subsub=0;

//Funções do Menu
void moveXY (int x, int y, char t[]);
void Menu_Principal ();
void Menu_First ();
void Menu_Second ();
void Menu_Third ();
void Menu_Fourth ();

void Help_MenuFirst ();
void HelpExe_MenuFirst ();
void Help_MenuSecond ();
void HelpExe_MenuSecond();
void Help_MenuThird ();
void HelpExe_MenuThird();
void Help_MenuFourth ();
void HelpExe_MenuFourth ();

void Menu_First_Func1 ();
void Menu_First_Func2 ();
void Menu_First_Func3 ();
void Menu_First_Func4 ();

void Menu_Second_Func1 ();
void Menu_Second_Func2 ();
void Menu_Second_Func3 ();

void Menu_Third_Func1 ();
void Menu_Third_Func2 ();
void Menu_Third_Func3 ();
void Menu_Third_Func4 ();
void Menu_Third_Func5 ();

void Menu_Fourth_Func1 ();
void Menu_Fourth_Func2 ();

//Função para Repetir Funções
void Repita_Func (char *opcao_func, int *menu);

//Funções das Matrizes
void Lin_Col (int *lin, int *col);
void Lin_Col_Equal (int *n);
void Lin_Col_Multiplica (int *lin1, int *col1, int *col2);
void Leia_MatrizNormal (int *lin, int *col, int matriz_nor[][COL_MAX]);
void Mostra_Matriz (int *lin, int *col, int matriz[][COL_MAX]);
void Leia_MatrizTriInf (int *n, int matriz_triinf[][COL_MAX]);
void Leia_MatrizTriSup (int *n, int matriz_trisup[][COL_MAX]);
void Transpor_Matriz (int *lin, int *col, int matriz1[][COL_MAX], int matriz_trans[][COL_MAX]);

void Soma_Matriz (int *lin, int *col, int matriz1[][COL_MAX], int matriz2[][COL_MAX], int matrizsoma[][COL_MAX]);
void Subtrair_Matriz (int *lin, int *col, int matriz1[][COL_MAX], int matriz2[][COL_MAX], int matrizsubtracao[][COL_MAX]);
void Multiplica_Matriz (int *lin1, int *col1, int *col2, int matriz1[][COL_MAX], int matriz2[][COL_MAX], int matrizmultiplica[][COL_MAX]);

int Verifica_MatrizNula (int *lin, int *col, int matriz[][COL_MAX]);
int Verifica_MatrizSimetrica (int *n, int matriz[][COL_MAX]);
int Verifica_MatrizPermuta (int *n, int matriz[][COL_MAX]);
int Verifica_MatrizQuadMagic (int *n, int matriz[][COL_MAX]);
int Verifica_MatrizQuadLatino (int *n, int matriz[][COL_MAX]);

void Mostra_Vetor (int *n, int vet[]);
void Mostra_Indep (int *n, int term_indep[]);
void Sist_Line_TriInf (int *n, int matriz_triinf[][COL_MAX], int xi[], int term_indep[]);
void Sist_Line_TriSup (int *n, int matriz_trisup[][COL_MAX], int xi[], int term_indep[]);

int main()
{
	system("COLOR 09");

	//Manipulação do Menu Principal
	char opcao_menu=0, opcao_first, resp;
	short posX=30, posY=6, posY_outro=6, posY_menulinear=8;
	short posX_sub=33, posY_sub=8;
	int menu_pri=0, menu_ajuda=0, menu_sub=0, menu_subsub=0;
	//moveXY(30,6,"->");

	while(opcao_menu!=ESC)
	{
	    //Condição para executar o Menu Principal
	    if(menu_pri==0)
        {
            Menu_Principal();
            moveXY(posX,posY,"->");
            opcao_menu = toupper(getch());

            switch(opcao_menu)
            {
                //Manipulação da Seta no Menu Principal
                case CIMA:
                    if(posY>6)
                    {
                        moveXY(30,posY,"  ");
                        posY-=3;
                        moveXY(30,posY,"->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY<15)
                    {
                        moveXY(30,posY,"  ");
                        posY+=3;
                        moveXY(30,posY,"->");
                        Beep(450,100);
                    }
                    break;

                //Usuário apertar o ENTER
                case ENTER:
                    if(posY==6)
                        menu_pri=1;
                    else if(posY==9)
                        menu_pri=2;
                    else if(posY==12)
                        menu_pri=3;
                    else if(posY==15)
                        menu_pri=4;
				break;

                //Saída do Menu Principal
                case ESC:
                    opcao_menu=ESC;
				break;
            }
            system("cls");
		}

		//Condição para executar a 1°Opção: Operações Simples
		else if(menu_pri==1 && menu_sub==0 && menu_subsub==0 && menu_ajuda==0)
        {
            Menu_First();
            moveXY(posX,posY,"->");
            opcao_first = toupper(getch());

            switch(opcao_first)
            {
                //Manipulação da Seta
                case CIMA:
                    if(posY>6)
                    {
                        moveXY(30,posY,"  ");
                        posY-=9;
                        moveXY(30,posY,"->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY<15)
                    {
                        moveXY(30,posY,"  ");
                        posY+=9;
                        moveXY(30,posY,"->");
                        Beep(450,100);
                    }
                    break;

                case (AJUDA && 0):
                    menu_ajuda=1;
                    break;

                case ENTER:
                    if(posY==6)
                        menu_sub=1;
                    else if(posY==15)
                        menu_sub=2;
                    break;

                case ESC:
                    menu_pri=0;
                    posY=6;
                    break;
            }
            system("cls");
        }
        //Condição para executar a Ajuda-Sobre da 1°Opção: Operações Simples
        else if(menu_pri==1 && (menu_sub==0||menu_sub==1) && menu_subsub==0  && menu_ajuda==1)
        {
            Help_MenuFirst();
            opcao_first = toupper(getch());
            switch (opcao_first)
            {
                case DIREITA:
                    menu_ajuda=2;
                    break;

                case ESC:
                    menu_ajuda=0;
                    break;
            }
            system("cls");
        }
        //Condição para executar a Ajuda-Exemplos da 1°Opção: Operações Simples
        else if(menu_pri==1 && (menu_sub==0||menu_sub==1) && menu_subsub==0 && menu_ajuda==2)
        {
            HelpExe_MenuFirst();
            opcao_first = toupper(getch());
            switch (opcao_first)
            {
                case ESQUERDA:
                    menu_ajuda=1;
                    break;

                case ESC:
                    menu_ajuda=0;
                    break;
            }
            system("cls");
        }
        //Condição para executar a 1°Opção: Operações Simples -> Sub-Menu 1: Leitura e Impressão
		else if(menu_pri==1 && menu_sub==1 && menu_subsub==0 && menu_ajuda==0)
        {
            Menu_First();
            moveXY(posX_sub,posY_sub,"->");
            opcao_first = toupper(getch());

            switch(opcao_first)
            {
                //Manipulação da Seta
                case CIMA:
                    if(posY_sub>8)
                    {
                        moveXY(33,posY_sub,"  ");
                        posY_sub-=2;
                        moveXY(33,posY_sub,"->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY_sub<12)
                    {
                        moveXY(33,posY_sub,"  ");
                        posY_sub+=2;
                        moveXY(33,posY_sub,"->");
                        Beep(450,100);
                    }
                    break;

                case ENTER:
                    if(posY_sub==8)
                        menu_subsub=1;
                    else if(posY_sub==10)
                        menu_subsub=2;
                    else if(posY_sub==12)
                        menu_subsub=3;
                    break;

                case (AJUDA && 0):
                    menu_ajuda=1;
                    break;

                case ESC:
                    menu_pri=1;
                    menu_sub=0;
                    posY_sub=8;
                    break;
            }
            system("cls");
        }
        //Condição para executar a 1°Opção: Operações Simples -> Sub-Menu 1: Leitura e Impressão -> Função: Matriz Comum
        else if(menu_pri==1 && menu_sub==1 && menu_subsub==1)
        {
            Menu_First_Func1();
            printf("\n\n\n");
            Lin_Col(&lin, &col);
            printf("\nPor ultimo, digite a Matriz abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            int matriz_nor[lin][col];
            Leia_MatrizNormal(&lin, &col, matriz_nor);
            system("cls");
            Menu_First_Func1();
            printf("\n\n\nA Matriz digitada eh:\n");
            Mostra_Matriz(&lin, &col, matriz_nor);
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_subsub);

            system("cls");
        }
        //Condição para executar a 1°Opção: Operações Simples -> Sub-Menu 1: Leitura e Impressão -> Função: Matriz Triangular Inferior
        else if(menu_pri==1 && menu_sub==1 && menu_subsub==2)
        {
            Menu_First_Func2();
            printf("\n\n\n");
            Lin_Col_Equal(&n);
            printf("\nAgora, digite a Matriz abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            int matriz_triinf[n][n];
            Leia_MatrizTriInf(&n,matriz_triinf);
            system("cls");
            Menu_First_Func2();
            printf("\n\n\nA Matriz Triangular Inferior digitada eh:\n");
            Mostra_Matriz(&n,&n,matriz_triinf);
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_subsub);

            system("cls");
        }
        //Condição para executar a 1°Opção: Operações Simples -> Sub-Menu 1: Leitura e Impressão -> Função: Matriz Triangular Superior
        else if(menu_pri==1 && menu_sub==1 && menu_subsub==3)
        {
            Menu_First_Func3();
            printf("\n\n\n");
            Lin_Col_Equal(&n);
            printf("\nAgora, digite a Matriz abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            int matriz_trisup[n][n];
            Leia_MatrizTriSup(&n,matriz_trisup);
            system("cls");
            Menu_First_Func3();
            printf("\n\n\nA Matriz Triangular Superior digitada eh:\n");
            Mostra_Matriz(&n,&n,matriz_trisup);
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_subsub);

            system("cls");
        }
        //Condição para executar a 1°Opção: Operações Simples -> Sub-Menu 2/Função: Determinação da Matriz Transposta
        else if(menu_pri==1 && menu_sub==2 && menu_subsub==0)
        {
            Menu_First_Func4();
            printf("\n\n\n");
            Lin_Col(&lin, &col);
            printf("\nAgora, digite a Matriz abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            int matriz_nor[lin][col], matriz_trans[col][lin];
            Leia_MatrizNormal(&lin,&col,matriz_nor);
            system("cls");
            Menu_First_Func4();
            printf("\n\n\nA Matriz digitada eh:\n");
            Mostra_Matriz(&lin,&col,matriz_nor);
            printf("\nSua Transposta eh:\n");
            Transpor_Matriz(&lin,&col,matriz_nor,matriz_trans);
            Mostra_Matriz(&col,&lin,matriz_trans);
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_sub);

            system("cls");
        }


        //Condição para executar a 2°Opção: Operações Aritméticas
        else if(menu_pri==2 && menu_sub==0 && menu_ajuda==0)
        {

            Menu_Second();
            moveXY(posX,posY_outro,"->");
            opcao_first = toupper(getch());
            switch(opcao_first)
            {
                //Manipulação da Seta
                case CIMA:
                    if(posY_outro>6)
                    {
                        moveXY(30,posY_outro,"  ");
                        posY_outro-=3;
                        moveXY(30,posY_outro,"->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY_outro<12)
                    {
                        moveXY(30,posY_outro,"  ");
                        posY_outro+=3;
                        moveXY(30,posY_outro,"->");
                        Beep(450,100);
                    }
                    break;

                case ENTER:
                    if(posY_outro==6)
                        menu_sub=1;
                    else if(posY_outro==9)
                        menu_sub=2;
                    else if(posY_outro==12)
                        menu_sub=3;
                    break;

                case (AJUDA && 0):
                    menu_ajuda=1;
                    break;

                case ESC:
                    menu_pri=0;
                    posY_outro=6;
                    break;
            }
            system("cls");
        }
        //Condição para executar a Ajuda da 2°Opção: Operações Aritméticas
        else if(menu_pri==2  && menu_sub==0 && menu_ajuda==1)
        {
            Help_MenuSecond();
            opcao_first = toupper(getch());
            switch (opcao_first)
            {
                case DIREITA:
                    menu_ajuda=2;
                    break;
                case ESC:
                    menu_ajuda=0;
                    break;
            }
            system("cls");

        }
        //Condição para executar a Ajuda-Exemplos da 2°Opção: Operações Aritméticas
        else if(menu_pri==2  && menu_sub==0 && menu_ajuda==2)
        {
            HelpExe_MenuSecond();
            opcao_first = toupper(getch());
            switch (opcao_first)
            {
                case ESQUERDA:
                    menu_ajuda=1;
                    break;

                case ESC:
                    menu_ajuda=0;
                    break;
            }
            system("cls");
        }
        //Condição para executar a 2°Opção: Operações Aritméticas -> Sub-Menu 1/Função: Soma
        else if(menu_pri==2 && menu_sub==1 && menu_subsub==0)
        {
            Menu_Second_Func1();
            printf("\n\n\n");
            Lin_Col(&lin,&col);
            printf("\nAgora, digite a Matriz A abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            int matriz1[lin][col], matriz2[lin][col], matrizsoma[lin][col];
            Leia_MatrizNormal(&lin,&col,matriz1);
            printf("\nPor fim, digite a Matriz B abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            Leia_MatrizNormal(&lin,&col,matriz2);
            system("cls");
            Menu_Second_Func1();
            printf("\n\n\nA Matriz A digitada eh:\n");
            Mostra_Matriz(&lin,&col,matriz1);
            printf("\nA Matriz B digitada eh:\n");
            Mostra_Matriz(&lin,&col,matriz2);
            printf("\nA Matriz Soma eh:\n");
            Soma_Matriz(&lin,&col,matriz1,matriz2,matrizsoma);
            Mostra_Matriz(&lin,&col,matrizsoma);
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_sub);


            system("cls");
        }
        //Condição para executar a 2°Opção: Operações Aritméticas -> Sub-Menu 2/Função: Subtração
        else if(menu_pri==2 && menu_sub==2 && menu_subsub==0)
        {
            Menu_Second_Func2();
            printf("\n\n\n");
            Lin_Col(&lin, &col);
            printf("\nAgora, digite a Matriz A abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            int matriz1[lin][col],matriz2[lin][col], matrizsubtracao[lin][col];
            Leia_MatrizNormal(&lin,&col,matriz1);
            printf("\nPor fim, digite a Matriz B abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            Leia_MatrizNormal(&lin,&col,matriz2);
            system("cls");
            Menu_Second_Func2();
            printf("\n\n\nA Matriz A digitada eh:\n");
            Mostra_Matriz(&lin,&col,matriz1);
            printf("\nA Matriz B digitada eh:\n");
            Mostra_Matriz(&lin,&col,matriz2);
            printf("\nA Matriz Subtracao eh:\n");
            Subtrair_Matriz(&lin, &col, matriz1, matriz2, matrizsubtracao);
            Mostra_Matriz(&lin,&col,matrizsubtracao);
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_sub);

            system("cls");
        }
        //Condição para executar a 2°Opção: Operações Aritméticas -> Sub-Menu 3/Função: Multiplicação
        else if(menu_pri==2 && menu_sub==3 && menu_subsub==0)
        {
            Menu_Second_Func3();
            printf("\n\n\n");
            Lin_Col_Multiplica(&lin,&col,&col2);
            printf("\nAgora, digite a Matriz A abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            int matriz1[lin][col], matriz2[col][col2];
            int matrizmultiplica[lin][col2];
            Leia_MatrizNormal(&lin,&col,matriz1);
            printf("\nPor fim, digite a Matriz B abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            Leia_MatrizNormal(&col,&col2,matriz2);
            system("cls");
            Menu_Second_Func3();
            printf("\n\n\nA Matriz A digitada eh:\n");
            Mostra_Matriz(&lin,&col,matriz1);
            printf("\nA Matriz B digitada eh:\n");
            Mostra_Matriz(&col,&col2,matriz2);
            printf("\nA Matriz Multiplicacao eh:\n");
            Multiplica_Matriz(&lin, &col, &col2, matriz1, matriz2, matrizmultiplica);
            Mostra_Matriz(&lin, &col2, matrizmultiplica);
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_sub);

            system("cls");
        }


        //Condição para executar a 3°Opção: Verificações
        else if(menu_pri==3 && menu_sub==0 && menu_ajuda==0)
        {

            Menu_Third();
            moveXY(posX,posY_outro,"->");
            opcao_first = toupper(getch());

            switch(opcao_first)
            {
                //Manipulação da Seta
                case CIMA:
                    if(posY_outro>6)
                    {
                        moveXY(30,posY_outro,"  ");
                        posY_outro-=3;
                        moveXY(30,posY_outro,"->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY_outro<18)
                    {
                        moveXY(30,posY_outro,"  ");
                        posY_outro+=3;
                        moveXY(30,posY_outro,"->");
                        Beep(450,100);
                    }
                    break;

                case ENTER:
                    if(posY_outro==6)
                        menu_sub=1;
                    else if(posY_outro==9)
                        menu_sub=2;
                    else if(posY_outro==12)
                        menu_sub=3;
                    else if(posY_outro==15)
                        menu_sub=4;
                    else if(posY_outro==18)
                        menu_sub=5;
                    break;

                case (AJUDA && 0):
                    menu_ajuda=1;
                    break;

                case ESC:
                    menu_pri=0;
                    posY_outro=6;
                    break;
            }
            system("cls");
        }
        //Condição para executar a Ajuda da 3°Opção: Verificações
        else if(menu_pri==3  && menu_sub==0 && menu_ajuda==1)
        {
            Help_MenuThird();
            opcao_first = toupper(getch());
            switch (opcao_first)
            {
                case DIREITA:
                    menu_ajuda=2;
                    break;
                case ESC:
                    menu_ajuda=0;
                    break;
            }
            system("cls");

        }
        //Condição para executar a Ajuda-Exemplos da 3°Opção: Verificações
        else if(menu_pri==3  && menu_sub==0 && menu_ajuda==2)
        {
            HelpExe_MenuThird();
            opcao_first = toupper(getch());
            switch (opcao_first)
            {
                case ESQUERDA:
                    menu_ajuda=1;
                    break;

                case ESC:
                    menu_ajuda=0;
                    break;
            }
            system("cls");
        }
        //Condição para executar a 3°Opção: Verificações -> Sub-Menu 1/Função: Matriz Nula
        else if(menu_pri==3 && menu_sub==1 && menu_subsub==0)
        {
            Menu_Third_Func1();
            printf("\n\n\n");
            Lin_Col(&lin,&col);
            int matriz[lin][col];
            printf("\nAgora, digite a Matriz abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            Leia_MatrizNormal(&lin,&col,matriz);
            system("cls");
            Menu_Third_Func1();
            printf("\n\n\nA Matriz digitada eh:\n");
            Mostra_Matriz(&lin,&col,matriz);
            if(Verifica_MatrizNula(&lin, &col, matriz))
                printf("\n\nEssa Matriz eh nula.\n\n");
            else
                printf("\n\nEssa Matriz nao eh nula.\n\n");
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_sub);

            system("cls");
        }
        //Condição para executar a 3°Opção: Verificações -> Sub-Menu 2/Função: Matriz Simétrica
        else if(menu_pri==3 && menu_sub==2 && menu_subsub==0)
        {
            Menu_Third_Func2();
            printf("\n\n\n");
            Lin_Col_Equal(&n);
            int matriz[n][n],matriz_trans[n][n];
            printf("\nAgora, digite a Matriz abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            Leia_MatrizNormal(&n,&n,matriz);
            system("cls");
            Menu_Third_Func2();
            printf("\n\nA Matriz digitada eh:\n");
            Mostra_Matriz(&n,&n,matriz);
            Transpor_Matriz(&n,&n,matriz,matriz_trans);
            printf("\n\nSua Transposta eh:\n");
            Mostra_Matriz(&n,&n,matriz_trans);
            if(Verifica_MatrizSimetrica(&n,matriz))
                printf("\n\nEssa Matriz eh simetrica.\n\n");
            else
                printf("\n\nEssa Matriz nao eh simetrica.\n\n");
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_sub);

            system("cls");
        }
        //Condição para executar a 3°Opção: Verificações -> Sub-Menu 3/Função: Matriz Quadrado Mágico
        else if(menu_pri==3 && menu_sub==3 && menu_subsub==0)
        {
            Menu_Third_Func3();
            printf("\n\n\n");
            Lin_Col_Equal(&n);
            int matriz[n][n];
            printf("\nAgora, digite a Matriz abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            Leia_MatrizNormal(&n,&n,matriz);
            system("cls");
            Menu_Third_Func3();
            printf("\n\n\nA Matriz digitada eh:\n");
            Mostra_Matriz(&n,&n,matriz);
            if(Verifica_MatrizQuadMagic(&n, matriz))
                printf("\n\nEssa Matriz eh um quadrado magico.\n\n");
            else
                printf("\n\nEssa Matriz nao eh um quadrado magico.\n\n");
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_sub);

            system("cls");
        }
        //Condição para executar a 3°Opção: Verificações -> Sub-Menu 4/Função: Matriz Quadrado Latino
        else if(menu_pri==3 && menu_sub==4 && menu_subsub==0)
        {
            Menu_Third_Func4();
            printf("\n\n\n");
            Lin_Col_Equal(&n);
            int matriz[n][n];
            printf("\nAgora, digite a Matriz abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            Leia_MatrizNormal(&n,&n,matriz);
            system("cls");
            Menu_Third_Func4();
            printf("\n\n\nA Matriz digitada eh:\n");
            Mostra_Matriz(&n,&n,matriz);
            if(Verifica_MatrizQuadLatino(&n, matriz))
                printf("\n\nEssa Matriz eh um quadrado latino.\n\n");
            else
                printf("\n\nEssa Matriz nao eh um quadrado latino.\n\n");
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_sub);

            system("cls");
        }
        //Condição para executar a 3°Opção: Verificações -> Sub-Menu 5/Função: Matriz de Permutação
        else if(menu_pri==3 && menu_sub==5 && menu_subsub==0)
        {
            Menu_Third_Func5();
            printf("\n\n\n");
            Lin_Col_Equal(&n);
            int matriz[n][n];
            printf("\nAgora, digite a Matriz abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            Leia_MatrizNormal(&n,&n,matriz);
            system("cls");
            Menu_Third_Func5();
            printf("\n\n\nA Matriz digitada eh:\n");
            Mostra_Matriz(&n,&n,matriz);
            if(Verifica_MatrizPermuta(&n, matriz))
                printf("\n\nEssa Matriz eh de permutacao.\n\n");
            else
                printf("\n\nEssa Matriz nao eh de permutacao.\n\n");
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_sub);

            system("cls");
        }


        //Condição para executar a 4°Opção: Resolução de Sistema Linear
        else if(menu_pri==4 && menu_sub==0 && menu_ajuda==0)
        {

            Menu_Fourth();
            moveXY(posX,posY_menulinear,"->");
            opcao_first = toupper(getch());

            posY=15;
            switch(opcao_first)
            {
                //Manipulação da Seta
                case CIMA:
                    if(posY_menulinear>8)
                    {
                        moveXY(30,posY_menulinear,"  ");
                        posY_menulinear-=4;
                        moveXY(30,posY_menulinear,"->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY_menulinear<12)
                    {
                        moveXY(30,posY_menulinear,"  ");
                        posY_menulinear+=4;
                        moveXY(30,posY_menulinear,"->");
                        Beep(450,100);
                    }
                    break;

                case ENTER:
                    if(posY_menulinear==8)
                        menu_sub=1;
                    else if(posY_menulinear==12)
                        menu_sub=2;
                    break;

                case (AJUDA && 0):
                    menu_ajuda=1;
                    break;

                case ESC:
                    menu_pri=0;
                    posY_menulinear=8;
                    break;
            }
            system("cls");
        }
        //Condição para executar a Ajuda da 4°Opção: Resolução de Sistema Linear
        else if(menu_pri==4 && menu_ajuda==1)
        {
            Help_MenuFourth();
            opcao_first = toupper(getch());
            switch (opcao_first)
            {
                case DIREITA:
                    menu_ajuda=2;
                    break;
                case ESC:
                    menu_ajuda=0;
                    break;
            }
            system("cls");

        }
        //Condição para executar a Ajuda-Exemplos da 4°Opção: Resolução de Sistema Linear
        else if(menu_pri==4 && menu_ajuda==2)
        {
            HelpExe_MenuFourth();
            opcao_first = toupper(getch());
            switch (opcao_first)
            {
                case ESQUERDA:
                    menu_ajuda=1;
                    break;

                case ESC:
                    menu_ajuda=0;
                    break;
            }
            system("cls");
        }
        //Condição para executar a 4°Opção: Resolução de Sistema Linear -> Sub-Menu 1/Função: Matriz Triangular Inferior
        else if(menu_pri==4 && menu_sub==1 && menu_subsub==0)
        {
            Menu_Fourth_Func1();
            printf("\n\n\n");
            Lin_Col_Equal(&n);
            printf("\nAgora, digite a Matriz Triangular Inferior abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            int matriz_triinf[n][n];
            Leia_MatrizTriInf(&n,matriz_triinf);
            printf("\n\n");
            int xi[n];
            int term_indep[n];
            Sist_Line_TriInf(&n, matriz_triinf, xi, term_indep);
            system("cls");
            Menu_Fourth_Func1();
            printf("\n\n\nA Matriz Triangular Inferior digitada eh:\n");
            Mostra_Matriz(&n,&n, matriz_triinf);
            Mostra_Indep(&n, term_indep);
            Mostra_Vetor(&n, xi);
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_sub);
            posY_menulinear=8;

            system("cls");
        }
        //Condição para executar a 4°Opção: Resolução de Sistema Linear -> Sub-Menu 2/Função: Matriz Triangular Superior
        else if(menu_pri==4 && menu_sub==2 && menu_subsub==0)
        {
            Menu_Fourth_Func2();
            printf("\n\n\n");
            Lin_Col_Equal(&n);
            printf("\nAgora, digite a Matriz Triangular Superior abaixo no esquema de linha 1, coluna 1 -> linha 1, coluna 2...\n");
            int matriz_trisup[n][n];
            Leia_MatrizTriSup(&n,matriz_trisup);
            printf("\n\n");
            int xi[n];
            int term_indep[n];
            Sist_Line_TriSup(&n, matriz_trisup, xi, term_indep);
            system("cls");
            Menu_Fourth_Func2();
            printf("\n\n\nA Matriz Triangular Superior digitada eh:\n");
            Mostra_Matriz(&n,&n, matriz_trisup);
            Mostra_Indep(&n, term_indep);
            Mostra_Vetor(&n, xi);
            printf("\n");
            system("pause");

            //Realiza a repetição da função caso o usuário deseje isso
            Repita_Func(&resp,&menu_sub);
            posY_menulinear=12;
            //posY=15;
            system("cls");
        }

	}
	Beep(300,650); //Tchau. Obrigado por usar o programa

    return 0;
}

//Repetir Funções
void Repita_Func (char *opcao_func, int *menu)
{
    while(1)
    {
        printf("\n\nDeseja executar a funcao novamente?\n\nENTER: Sim\nESC: Volta para o Menu Anterior\n");
        if(*menu==1)
        {
            *opcao_func = toupper(getch());
            switch(*opcao_func)
            {
                case ESC:
                    *menu=0;
                    break;
                case ENTER:
                    *menu=1;
                    break;
            }
        }
        else if(*menu==2)
        {
            *opcao_func = toupper(getch());
            switch(*opcao_func)
            {
                case ESC:
                    *menu=0;
                    break;
                case ENTER:
                    *menu=2;
                    break;
            }
        }
        else if(*menu==3)
        {
            *opcao_func = toupper(getch());
            switch(*opcao_func)
            {
                case ESC:
                    *menu=0;
                    break;
                case ENTER:
                    *menu=3;
                    break;
            }
        }
        else if(*menu==4)
        {
            *opcao_func = toupper(getch());
            switch(*opcao_func)
            {
                case ESC:
                    *menu=0;
                    break;
                case ENTER:
                    *menu=4;
                    break;
            }
        }
        else if(*menu==5)
        {
            *opcao_func = toupper(getch());
            switch(*opcao_func)
            {
                case ESC:
                    *menu=0;
                    break;
                case ENTER:
                    *menu=5;
                    break;
            }
        }

        if(*menu>=0 && *menu<=5)
            break;
    }
}

//Funções para os Menus

//Função MoveXY (do windows.h) para controle do Menu por meio de coordenadas
void moveXY (int x, int y, char t[])
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {x,y};
	SetConsoleCursorPosition(hStdout,position);
	printf("%s",t);
}

//Função do Menu Principal
void Menu_Principal ()
{
	moveXY(32,1, "::: MATRIZAO DO DAVIZAUM :::");
	moveXY(31,2, ":: TRABALHO - ALGORITMOS II ::");
	moveXY(30,3, "::: CRIADO POR: DAVI AUGUSTO :::");
	moveXY(33,6, "1- OPERACOES SIMPLES");
	moveXY(33,9, "2- OPERACOES ARITMETICAS");
	moveXY(33,12, "3- VERIFICACOES");
	moveXY(33,15, "4- RESOLUCAO DE SISTEMA LINEAR");
	moveXY(55,18, "ENTER: SELECIONAR");
	moveXY(55,19, "ESC: SAIR");
	moveXY(38,22, "VERSAO: 1.05 BETA");

}

//Menu 1: Operações Simples
void Menu_First ()
{
	moveXY(32,2, "::: OPERACOES SIMPLES :::");
	moveXY(33,6, "1- LEITURA E IMPRESSAO");
	moveXY(36,8, "* MATRIZ COMUM");
	moveXY(36,10, "* MATRIZ TRIANGULAR INFERIOR");
	moveXY(36,12, "* MATRIZ TRIANGULAR SUPERIOR");
	moveXY(33,15, "2- DETERMINACAO DA MATRIZ TRANSPOSTA");
	moveXY(55,18, "F1: AJUDA");
	moveXY(55,20, "ENTER: SELECIONAR");
	moveXY(55,21, "ESC: VOLTAR ");
}
//Ajuda do Menu 1
void Help_MenuFirst ()
{
    moveXY(45,2, "::::: AJUDA :::::");
    moveXY(2,5, "::: OPERACOES SIMPLES :::");
    moveXY(2,8, "O menu de operacoes simples possui dois tipos de funcoes:");
    moveXY(2,10, "1- Leitura e Impressao: realiza a leitura de um *tipo de matriz* e exibe o resultado na tela.");
    moveXY(2,12, "2- Determinacao da Matriz Transposta: determina a matriz transposta de qualquer tipo de matriz.");
    moveXY(2,16, "*TIPOS DE MATRIZ:");
    moveXY(6,18, "- Comum: qualquer numero de linhas e colunas.");
    moveXY(15,19, "Ex: Matriz 4x2 (4 linhas e 2 colunas)");
    moveXY(6,21, "- Triangular Inferior: um mesmo numero de linhas e colunas,");
    moveXY(8,22, "em que ha elementos com valor nulo quando o numero da linha eh inferior ao numero da coluna");
    moveXY(6,24, "- Triangular Superior: um mesmo numero de linhas e colunas,");
    moveXY(8,25, "em que ha elementos com valor nulo quando o numero da linha eh superior ao numero da coluna");
    moveXY(2,28, "ESC: VOLTAR PARA O MENU");
    moveXY(82,27, "------");
    moveXY(82,28, "|--->| - EXEMPLOS");
    moveXY(82,29, "------");
}
//Ajuda-Exemplos do Menu 1
void HelpExe_MenuFirst ()
{
    moveXY(50,2, "::::: AJUDA :::::");
    moveXY(2,5, "::: EXEMPLOS :::");
    moveXY(2,8, "-----------------------------------------------------");
    moveXY(20,9, "- MATRIZ COMUM -");
    moveXY(2,10, "-----------------------------------------------------");
    moveXY(4,11, "-----------");
    moveXY(6,12, "2 4 8 9");
    moveXY(6,13, "1 1 5 1");
    moveXY(4,15, "MATRIZ (2x4)");
    moveXY(4,16, "- 2 LINHAS");
    moveXY(4,17, "- 4 COLUNAS");
    moveXY(4,18, "-----------");
    moveXY(4,19, "-----------");
    moveXY(7,20, "10 20");
    moveXY(7,21, "-2 -7");
    moveXY(7,22, "5  5 ");
    moveXY(4,24, "MATRIZ (3x2)");
    moveXY(4,25, "- 3 LINHAS");
    moveXY(4,26, "- 2 COLUNAS");
    moveXY(23,11, "--------------------------------");
    moveXY(23,12, "2  4  8  9  8   1  2  3  4    10");
    moveXY(23,13, "8  5  1  10 28  3  4  5  6    8");
    moveXY(23,14, "1  1  1  1  354 4  7  7  77   6");
    moveXY(23,15, "10 20 30 0  0   5  5  50 7    0");
    moveXY(23,16, "2  2  2  6  66  7  8  9  0    0");
    moveXY(23,17, "-2 -5 2  2  40  42 41 36 7    9");
    moveXY(23,18, "-8 1  -7 1  0   0  1  2  3   -10");
    moveXY(23,19, "16 5  12 8  7   4  14 12 6   -9");
    moveXY(23,20, "66 69 24 7  8   0  1  5  -6  -4");
    moveXY(23,21, "-1 -2 14 11 28  33 94 8  100 70");
    moveXY(23,22, "--------------------------------");
    moveXY(33,24, "MATRIZ (10x10)");
    moveXY(33,25, "- 10 LINHAS");
    moveXY(33,26, "- 10 COLUNAS");
    moveXY(60,8, "---------------------------------------------------");
    moveXY(71,9,"- MATRIZ TRIANGULAR INFERIOR -");
    moveXY(60,10, "---------------------------------------------------");
    moveXY(66,11, "-------");
    moveXY(66,12, "2 0 0 0");
    moveXY(66,13, "5 7 0 0");
    moveXY(66,14, "1 6 4 0");
    moveXY(66,15, "3 8 7 1");
    moveXY(66,16, "-------");
    moveXY(60,17, "MATRIZ DE ORDEM 4 (4x4)");
    moveXY(96,12, "------");
    moveXY(96,13, "3  0 0");
    moveXY(96,14, "10 9 0");
    moveXY(96,15, "9 20 9");
    moveXY(96,16, "------");
    moveXY(88,17, "MATRIZ DE ORDEM 3 (3x3)");
    moveXY(60,18, "---------------------------------------------------");
    moveXY(71,19, "- MATRIZ TRIANGULAR SUPERIOR -");
    moveXY(60,20, "---------------------------------------------------");
    moveXY(66,21, "---------");
    moveXY(66,22, "2 5 10 60");
    moveXY(66,23, "0 3 9  8");
    moveXY(66,24, "0 0 4  6");
    moveXY(66,25, "0 0 0  1");
    moveXY(66,26, "---------");
    moveXY(60,27, "MATRIZ DE ORDEM 4 (4x4)");
    moveXY(96,22, "------");
    moveXY(96,23, "10 3 5");
    moveXY(96,24, "0  9 7");
    moveXY(96,25, "0  0 9");
    moveXY(96,26, "------");
    moveXY(88,27, "MATRIZ DE ORDEM 3 (3x3)");

    moveXY(2,28, "------");
    moveXY(2,29, "|<---| - OPERACOES SIMPLES");
    moveXY(2,30, "------");
    moveXY(88,29, "ESC: VOLTAR PARA O MENU");

}
//Menu 1: Operações Simples -> Função 1: Leitura e Impressão de Matriz Comum
void Menu_First_Func1 ()
{
    moveXY(40,2, "::::: LEITURA E IMPRESSAO :::::");
    moveXY(43,3, "::::: MATRIZ COMUM :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}
//Menu 2: Operações Simples -> Função 1: Leitura e Impressão de Matriz Triagonal Inferior
void Menu_First_Func2 ()
{
    moveXY(40,2, "::::: LEITURA E IMPRESSAO :::::");
    moveXY(37,3, "::::: MATRIZ TRIAGONAL INFERIOR :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}
//Menu 3: Operações Simples -> Função 1: Leitura e Impressão de Matriz Triagonal Superior
void Menu_First_Func3 ()
{
    moveXY(40,2, "::::: LEITURA E IMPRESSAO :::::");
    moveXY(37,3, "::::: MATRIZ TRIAGONAL SUPERIOR :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}
//Menu 4: Operações Simples -> Função 2: Determinação da Matriz Transposta
void Menu_First_Func4 ()
{
    moveXY(42,2, "::::: OPERACOES SIMPLES :::::");
    moveXY(34,3, "::::: DETERMINACAO DA MATRIZ TRANSPOSTA :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}


//Menu 2: Operações Aritméticas
void Menu_Second ()
{
	moveXY(28,2, "::: OPERACOES ARITMETICAS :::");
	moveXY(33,6, "1- SOMA (+)");
	moveXY(33,9, "2- SUBTRACAO (-)");
	moveXY(33,12, "3- MULTIPLICACAO (x)");
	moveXY(55,16, "F1: AJUDA");
	moveXY(55,18, "ENTER: SELECIONAR");
	moveXY(55,19, "ESC: VOLTAR ");
}
//Ajuda do Menu 2
void Help_MenuSecond ()
{
    moveXY(50,2, "::::: AJUDA :::::");
    moveXY(2,5, "::: OPERACOES ARITMETICAS :::");
    moveXY(2,8, "O menu de operacoes aritmeticas possui tres tipos de funcoes:");
    moveXY(2,10, "1- Soma*: realiza a soma entre duas matrizes e mostra a matriz resultante na tela.");
    moveXY(2,12, "2- Subtracao*: realiza a subtracao entre duas matrizes e mostra a matriz resultante na tela.");
    moveXY(2,14, "3- Multiplicacao**: realiza a multiplicacao entre duas matrizes e mostra a matriz resultante na tela.");
    moveXY(2,18, "ATENCAO:");
    moveXY(2,20, "*: para realizar as operacoes de soma e subtracao, o numero de linhas e colunas");
    moveXY(5,21, "entre as matrizes devem ser iguais (linha|coluna +- linha|coluna).");
    moveXY(5,22, "Ex: Matriz A (4x2) e Matriz B (4x2) podem ser somadas ou subtraidas.");
    moveXY(9,23, "Matriz A (4x2) e Matriz B (2x4) nao podem ser somadas ou subtraidas.");
    moveXY(2,25, "**: para realizar a operacao de multiplicacao, o numero das colunas da primeira matriz");
    moveXY(6,26, "deve ser igual ao numero das linhas da segunda matriz (linha * coluna).");
    moveXY(6,27, "Ex: Matriz A (5x2) e Matriz B (2x4) podem ser multiplicadas, resultando na Matriz C (5x4).");
    moveXY(10,28, "Matriz A (4x2) e Matriz B (4x3) nao podem ser multiplicadas.");
    moveXY(2,30, "ESC: VOLTAR PARA O MENU");
    moveXY(99,29, "------");
    moveXY(99,30, "|--->| - EXEMPLOS");
    moveXY(99,31, "------");
}
//Ajuda-Exemplos do Menu 2
void HelpExe_MenuSecond ()
{
    moveXY(50,2, "::::: AJUDA :::::");
    moveXY(2,5, "::: EXEMPLOS :::");
    moveXY(15,8, "- SOMA -");
    moveXY(6,11, "------");
    moveXY(6,12, "2 5 60");
    moveXY(6,13, "4 8  4");
    moveXY(6,14, "8 4 10");
    moveXY(6,15, "------");
    moveXY(2,17, "MATRIZ A (3x3)");
    moveXY(18,13, "+");
    moveXY(25,11, "------");
    moveXY(25,12, "10 8 9");
    moveXY(25,13, "8 20 7");
    moveXY(25,14, "7 50 1");
    moveXY(25,15, "------");
    moveXY(21,17, "MATRIZ B (3x3)");
    moveXY(18,19, "=");
    moveXY(14,21, "--------");
    moveXY(14,22, "12 13 69");
    moveXY(14,23, "12 28 11");
    moveXY(14,24, "15 54 11");
    moveXY(14,25, "--------");
    moveXY(10,27, "MATRIZ SOMA (3x3)");
    moveXY(50,8, "- SUBTRACAO -");
    moveXY(43,11, "--------");
    moveXY(43,12, "20 5 6 4");
    moveXY(43,13, "4 80 8 6");
    moveXY(43,14, "8 60 1 7");
    moveXY(43,15, "--------");
    moveXY(40,17, "MATRIZ A (3x4)");
    moveXY(56,13, "-");
    moveXY(62,11, "--------");
    moveXY(62,12, "10 8 9 4");
    moveXY(62,13, "8 20 7 2");
    moveXY(62,14, "7 50 1 8");
    moveXY(62,15, "--------");
    moveXY(60,17, "MATRIZ B (3x4)");
    moveXY(56,19, "=");
    moveXY(51,21, "-----------");
    moveXY(51,22, "10 -3 -3  0");
    moveXY(51,23, "-4 60  1  4");
    moveXY(51,24, "1  10  0 -1");
    moveXY(51,25, "-----------");
    moveXY(46,27, "MATRIZ SUBTRACAO (3x4)");
    moveXY(88,8, "- MULTIPLICACAO -");
    moveXY(84,10, "------>");
    moveXY(84,11, "----");
    moveXY(84,12, "10 5");
    moveXY(84,13, "14 2");
    moveXY(84,14, "8 60");
    moveXY(84,15, "----");
    moveXY(79,17, "MATRIZ A (3x2)");
    moveXY(96,13, "*");
    moveXY(111,11, "|");
    moveXY(111,12, "|");
    moveXY(111,13, "|");
    moveXY(111,14, "|");
    moveXY(111,15, "V");
    moveXY(102,12, "--------");
    moveXY(102,13, "10 8 9 4");
    moveXY(102,14, "8 20 7 2");
    moveXY(102,15, "--------");
    moveXY(100,17, "MATRIZ B (2x4)");
    moveXY(96,19, "=");
    moveXY(88,21, "----------------");
    moveXY(88,22, "86  96   77  32");
    moveXY(88,23, "156 152  140 60");
    moveXY(88,24, "560 1264 492 152");
    moveXY(88,25, "----------------");
    moveXY(85,27, "MATRIZ MULTIPLICA (3x4)");
    moveXY(2,29, "------");
    moveXY(2,30, "|<---| - OPERACOES ARITMETICAS");
    moveXY(2,31, "------");
    moveXY(91,30, "ESC: VOLTAR PARA O MENU");
}
//Menu 2: Operações Aritméticas -> Função 1: Soma
void Menu_Second_Func1 ()
{
    moveXY(40,2, "::::: OPERACOES ARITMETICAS :::::");
    moveXY(48,3, "::::: SOMA :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}
//Menu 2: Operações Aritméticas -> Função 2: Subtração
void Menu_Second_Func2 ()
{
    moveXY(40,2, "::::: OPERACOES ARITMETICAS :::::");
    moveXY(46,3, "::::: SUBTRACAO :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}
//Menu 2: Operações Aritméticas -> Função 3: Multiplicação
void Menu_Second_Func3 ()
{
    moveXY(40,2, "::::: OPERACOES ARITMETICAS :::::");
    moveXY(44,3, "::::: MULTIPLICACAO :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}


//Menu 3: Verificações
void Menu_Third ()
{
	moveXY(32,2, "::: VERIFICACOES :::");
	moveXY(33,6, "1- NULA");
	moveXY(33,9, "2- SIMETRICA");
	moveXY(33,12, "3- QUADRADO MAGICO");
	moveXY(33,15, "4- QUADRADO LATINO");
	moveXY(33,18, "5- MATRIZ DE PERMUTACAO");
	moveXY(55,22, "F1: AJUDA");
	moveXY(55,24, "ENTER: SELECIONAR");
	moveXY(55,25, "ESC: VOLTAR ");
}
//Ajuda do Menu 3
void Help_MenuThird ()
{
    moveXY(50,2, "::::: AJUDA :::::");
    moveXY(2,5, "::: VERIFICACOES :::");
    moveXY(2,8, "O menu de verificacoes possui cinco tipos de funcoes para verificacao de matrizes, sendo elas:");
    moveXY(2,10, "1- Nulo*: verifica se a matriz eh do tipo nula.");
    moveXY(5,11, "-> Quando todos os elementos valem 0 (nulos).");
    moveXY(2,13, "2- Simetrica: verifica se a matriz eh simetrica.");
    moveXY(5,14, "-> Quando a matriz eh igual a sua transposta (A=At).");
    moveXY(2,16, "3- Quadrado Magico: verifica se a matriz eh um quadrado magico");
    moveXY(5,17, "-> Quando a soma dos elementos de cada linha, cada coluna e das diagonais forem iguais.");
    moveXY(2,19, "4- Quadrado Latino: verifica se a matriz eh um quadrado latino.");
    moveXY(5,20, "-> Quando cada linha e cada coluna aparecem todos os inteiros 1,2,3,...,n (com 'n' sendo a ordem a matriz).");
    moveXY(2,22, "5- Matriz de Permutacao: verifica se a matriz eh de permutacao.");
    moveXY(5,23, "-> Quando cada linha e cada coluna houver 'n-1' elementos nulos e um elemento valendo '1'.");
    moveXY(2,26, "ATENCAO:");
    moveXY(2,27, "*: essa verificacao indepente de um numero igual ('n') de linhas com colunas, ao contrario de todas as outras.");
    moveXY(2,30, "ESC: VOLTAR PARA O MENU");
    moveXY(94,29, "------");
    moveXY(94,30, "|--->| - EXEMPLOS");
    moveXY(94,31, "------");
}
//Ajuda-Exemplos do Menu 3
void HelpExe_MenuThird ()
{
    moveXY(50,2, "::::: AJUDA :::::");
    moveXY(2,5, "::: EXEMPLOS :::");
    moveXY(2,7, "------------------------------------------------------------------------------------------------------------");
    moveXY(6,8, "- NULO -");
    moveXY(6,10, "-------");
    moveXY(6,11, "0 0 0 0");
    moveXY(6,12, "0 0 0 0");
    moveXY(6,13, "0 0 0 0");
    moveXY(6,14, "-------");
    moveXY(5,16, "MATRIZ (3x4)");
    moveXY(45,8, "- SIMETRICA -");
    moveXY(35,10, "-----");
    moveXY(35,11, "1 2 3");
    moveXY(35,12, "2 3 1");
    moveXY(35,13, "3 1 2");
    moveXY(35,14, "-----");
    moveXY(33,16, "MATRIZ (3x3)");
    moveXY(49,12, "<=>");
    moveXY(62,10, "-----");
    moveXY(62,11, "1 2 3");
    moveXY(62,12, "2 3 1");
    moveXY(62,13, "3 1 2");
    moveXY(62,14, "-----");
    moveXY(56,16, "M. TRANSPOSTA (3x3)");
    moveXY(85,8, "- QUADRADO MAGICO -");
    moveXY(80,11, "-------");
    moveXY(80,12, "2  7  6");
    moveXY(80,13, "9  5  1");
    moveXY(80,14, "4  3  8");
    moveXY(80,15, "-------");
    moveXY(98,16, "MATRIZ (3X3)");
    moveXY(88,12, "| = 15 L1");
    moveXY(88,13, "| = 15 L2");
    moveXY(88,14, "| = 15 L3");
    moveXY(80,16, "|");
    moveXY(80,17, "15");
    moveXY(80,18, "C1");
    moveXY(83,16, "|");
    moveXY(83,17, "15");
    moveXY(83,18, "C2");
    moveXY(86,16, "|");
    moveXY(86,17, "15");
    moveXY(86,18, "C3");
    moveXY(98,17, "L = Linha");
    moveXY(98,18, "C = Coluna");
    moveXY(80,20, "Diagonal Principal:  2+5+8=15");
    moveXY(80,21, "Diagonal Secundaria: 6+5+4=15");
    moveXY(80,22, "------------------------------");
    moveXY(78,19, "/");
    moveXY(78,20, "/");
    moveXY(78,21, "/");
    moveXY(78,22, "/");
    moveXY(2,18, "-----------------------------------------------------------------------------");
    moveXY(11,19, "- QUADRADO LATINO -");
    moveXY(6,21, "-------");
    moveXY(6,22, "1 2 3 4");
    moveXY(6,23, "2 3 4 1");
    moveXY(6,24, "4 1 2 3");
    moveXY(6,25, "3 4 1 2");
    moveXY(6,26, "-------");
    moveXY(16,22, "MATRIZ DE ORDEM 4");
    moveXY(22,23, "(4x4)");
    moveXY(16,24, "TERMOS NAS LINHAS");
    moveXY(16,25, "E COLUNAS: 1,2,3,4");
    moveXY(46,19, "- MATRIZ DE PERMUTACAO -");
    moveXY(42,21, "-------");
    moveXY(42,22, "0 1 0 0");
    moveXY(42,23, "0 0 1 0");
    moveXY(42,24, "1 0 0 0");
    moveXY(42,25, "0 0 0 1");
    moveXY(42,26, "-------");
    moveXY(55,22, "MATRIZ DE ORDEM 4");
    moveXY(61,23, "(4x4)");
    moveXY(55,24, "TERMOS NULOS: 3");
    moveXY(55,25, "-> CADA LINHA E COLUNA");
    moveXY(2,29, "------");
    moveXY(2,30, "|<---| - VERIFICACOES");
    moveXY(2,31, "------");
    moveXY(87,30, "ESC: VOLTAR PARA O MENU");
}
//Menu 3: Verificações -> Função 1: Matriz Nula
void Menu_Third_Func1 ()
{
    moveXY(40,2, "::::: VERIFICACOES :::::");
    moveXY(44,3, "::::: NULO :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}
//Menu 3: Verificações -> Função 2: Matriz Simétrica
void Menu_Third_Func2 ()
{
    moveXY(40,2, "::::: VERIFICACOES :::::");
    moveXY(41,3, "::::: SIMETRICA :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}
//Menu 3: Verificações -> Função 3: Matriz Quadrado Mágico
void Menu_Third_Func3 ()
{
    moveXY(40,2, "::::: VERIFICACOES :::::");
    moveXY(38,3, "::::: QUADRADO MAGICO :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}
//Menu 3: Verificações -> Função 4: Matriz Quadrado Latino
void Menu_Third_Func4 ()
{
    moveXY(40,2, "::::: VERIFICACOES :::::");
    moveXY(39,3, "::::: QUADRADO LATINO :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}
//Menu 3: Verificações -> Função 5: Matriz de Permutação
void Menu_Third_Func5 ()
{
    moveXY(40,2, "::::: VERIFICACOES :::::");
    moveXY(36,3, "::::: MATRIZ DE PERMUTACAO :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}


//Menu 4: Resolução de Sistema Linear
void Menu_Fourth ()
{
	moveXY(29,2, "::: RESOLUCAO DE SISTEMA LINEAR :::");
	moveXY(33,8, "1- MATRIZ TRIANGULAR INFERIOR");
	moveXY(33,12, "2- MATRIZ TRIANGULAR SUPERIOR");
	moveXY(55,16, "F1: AJUDA");
	moveXY(55,18, "ENTER: SELECIONAR");
	moveXY(55,19, "ESC: VOLTAR ");
}
//Ajuda do Menu 4
void Help_MenuFourth ()
{
    moveXY(35,2, "::::: AJUDA :::::");
    moveXY(2,5, "::: RESOLUCAO DE SISTEMA LINEAR :::");
    moveXY(2,8, "O menu de resolucao de sistema linear possui duas funcoes para tal, sendo elas:");
    moveXY(2,10, "1- Matriz Triangular Inferior: dado a matriz desse tipo e os termos independentes,");
    moveXY(5,11, "retorna todas as solucoes possiveis.");
    moveXY(2,13, "2- Matriz Triangular Superior: dado a matriz desse tipo e os termos independentes,");
    moveXY(5,14, "retorna todas as solucoes possiveis.");
    moveXY(2,17, "ATENCAO: os dois tipos de matriz acima utilizam do numero de ordem 'n', ou seja,");
    moveXY(11,18, "para um numero x de linhas, sera obrigatorio o mesmo numero x de colunas.");
    moveXY(2,21, "ESC: VOLTAR PARA O MENU");
    moveXY(66,20, "------");
    moveXY(66,21, "|--->| - EXEMPLOS");
    moveXY(66,22, "------");
}
//Ajuda-Exemplos do Menu 4
void HelpExe_MenuFourth ()
{
    moveXY(50,2, "::::: AJUDA :::::");
    moveXY(2,5, "::: EXEMPLOS :::");
    moveXY(6,8, "- SISTEMA TRIANGULAR INFERIOR -");
    moveXY(2,10, "-----");
    moveXY(2,11, "2 0 0");
    moveXY(2,12, "3 2 0");
    moveXY(2,13, "1 4 2");
    moveXY(2,14, "-----");
    moveXY(2,16, "M.T.I.");
    moveXY(3,17, "(3x3)");
    moveXY(13,12, "=>");
    moveXY(20,11, "|2*X1               = B1");
    moveXY(20,12, "|3*X1 + 2*X2        = B2");
    moveXY(20,13, "|1*X1 + 4*X2 + 2*X3 = B3");
    moveXY(78,8, "- SISTEMA TRIANGULAR SUPERIOR -");
    moveXY(66,10, "--------");
    moveXY(66,11, "2 3 6 8");
    moveXY(66,12, "0 5 7 12");
    moveXY(66,13, "0 0 3 7");
    moveXY(66,14, "0 0 0 11");
    moveXY(66,15, "--------");
    moveXY(68,17, "M.T.S.");
    moveXY(69,18, "(4x4)");
    moveXY(80,12, "=>");
    moveXY(86,11, "|2*X4 + 3*X3 + 6*X2 +  8*X1 = B4");
    moveXY(86,12, "|       5*X3 + 7*X2 + 12*X1 = B3");
    moveXY(86,13, "|              3*X2 +  7*X1 = B2");
    moveXY(86,14, "|                     11*X1 = B1");
    moveXY(43,23, "Xi = SOLUCOES DO SISTEMA");
    moveXY(43,24, "Bi = TERMOS INDEPENDENTES");
    moveXY(48,25, "com 'i' sendo o indice do termo.");
    moveXY(2,26, "------");
    moveXY(2,27, "|<---| - RESOLUCAO DE SISTEMA LINEAR");
    moveXY(2,28, "------");
    moveXY(95,27, "ESC: VOLTAR PARA O MENU");
}
//Menu 4: Resolução de Sistema Linear -> Função 1: Matriz Triangular Inferior
void Menu_Fourth_Func1 ()
{
    moveXY(37,2, "::::: RESOLUCAO DE SISTEMA LINEAR :::::");
    moveXY(37,3, "::::: MATRIZ TRIANGULAR INFERIOR :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}
//Menu 4: Resolução de Sistema Linear -> Função 2: Matriz Triangular Superior
void Menu_Fourth_Func2 ()
{
    moveXY(37,2, "::::: RESOLUCAO DE SISTEMA LINEAR :::::");
    moveXY(37,3, "::::: MATRIZ TRIANGULAR SUPERIOR :::::");
    moveXY(2,6, "*VALOR MAXIMO DE LINHAS/COLUNAS SUPORTADO PELO PROGRAMA: 10");
    moveXY(80,6, "ENTER: CONFIRMAR");
}


//Funções para Matrizes

//Função para Definir o Número de Linhas e Colunas
void Lin_Col (int *lin, int *col)
{
	do
	{
		printf("Digite o numero desejado de linhas para essa(s) matriz(es): ");
		scanf("%d",&*lin);
	}while(*lin<1||*lin>LIN_MAX);
    printf("\n");
	do
	{
		printf("Agora, digite o numero desejado de colunas para essa(s) matriz(es): ");
		scanf("%d",&*col);
	}while(*col<1||*col>COL_MAX);
}

//Função para Definir o Número de Linhas e Colunas (Iguais)
void Lin_Col_Equal (int *n)
{
	do
	{
		printf("Digite o numero de ordem para essa matriz (linhas e colunas iguais): ");
		scanf("%d",&*n);
	}while(*n<1||*n>COL_MAX);
    printf("\n");
}

//Função para Definir o Numero de Linhas e Colunas para a Função de Multiplicação (3 valores)
void Lin_Col_Multiplica (int *lin1, int *col1, int *col2)
{
    do
	{
		printf("Digite o numero desejado de linhas para a primeira matriz: ");
		scanf("%d",&*lin1);
	}while(*lin1<1||*lin1>LIN_MAX);
    printf("\n");
	do
	{
		printf("Agora, digite o numero desejado de colunas para a primeira matriz (o mesmo de linhas da segunda matriz): ");
		scanf("%d",&*col1);
	}while(*col1<1||*col1>COL_MAX);
	printf("\n");
	do
	{
		printf("Por ultimo, digite o numero desejado de colunas para a segunda matriz: ");
		scanf("%d",&*col2);
	}while(*col2<1||*col2>COL_MAX);
}

//Função para Mostrar Matriz
void Mostra_Matriz (int *lin, int *col, int matriz[][COL_MAX])
{
    printf ("\n");
    for (i=0; i<*lin; i++) {
        for (j=0;j<*col; j++)
            printf("%d ",matriz[i][j]);
        printf ("\n");
    }
}


//Função para Ler Matriz (Normal)
void Leia_MatrizNormal (int *lin, int *col, int matriz_nor[][COL_MAX])
{
    printf("\n");
    for (i=0;i<*lin; i++)
        for (j=0;j<*col; j++)
            scanf("%d",&matriz_nor[i][j]);
}

//Função para Ler Matriz (Triangular Inferior)
void Leia_MatrizTriInf (int *n, int matriz_triinf[][COL_MAX])
{
    printf("\n");
    for (i=0;i<*n;i++)
    {
    	for (j=0;j<*n;j++)
    	{
    		if(i<j)
    			matriz_triinf[i][j]=0;
    		else
    			scanf("%d", &matriz_triinf[i][j]);
		}
	}
}

//Função para Ler Matriz (Triangular Superior)
void Leia_MatrizTriSup (int *n, int matriz_trisup[][COL_MAX])
{
    printf("\n");
    for (i=0;i<*n;i++)
    {
    	for (j=0;j<*n;j++)
    	{
    		if(i>j)
    			matriz_trisup[i][j]=0;
    		else
    			scanf("%d", &matriz_trisup[i][j]);
		}
	}
}

//Função para Transpor Matriz
void Transpor_Matriz (int *lin, int *col, int matriz1[][COL_MAX], int matriz_trans[][COL_MAX])
{
	for(i=0;i<*lin;i++)
		for(j=0;j<*col;j++)
			matriz_trans[j][i] = matriz1[i][j];

}

//Função para Somar Duas Matrizes
void Soma_Matriz (int *lin, int *col, int matriz1[][COL_MAX], int matriz2[][COL_MAX], int matrizsoma[][COL_MAX])
{
	for(i=0;i< *lin;i++)
		for(j=0;j< *col;j++)
			matrizsoma[i][j] = (matriz1[i][j] + matriz2[i][j]);
}

//Função para Subtrarir Duas Matrizes
void Subtrair_Matriz (int *lin, int *col, int matriz1[][COL_MAX], int matriz2[][COL_MAX], int matrizsubtracao[][COL_MAX])
{
	for(i=0;i<*lin;i++)
		for(j=0;j<*col;j++)
			matrizsubtracao[i][j] = (matriz1[i][j] - matriz2[i][j]);
}

//Função para Multiplicar Duas Matrizes
void Multiplica_Matriz (int *lin1, int *col1, int *col2, int matriz1[][COL_MAX], int matriz2[][COL_MAX], int matrizmultiplica[][COL_MAX])
{
	int k;
	for(i=0;i<*lin1;i++)
	{
		for(j=0;j<*col2;j++)
		{
			matrizmultiplica[i][j]=0;
			for(k=0;k<*col1;k++)
				matrizmultiplica[i][j] += (matriz1[i][k] * matriz2[k][j]);
		}
	}
}

//Função para Verificar Matriz Nula
int Verifica_MatrizNula (int *lin, int *col, int matriz[][COL_MAX])
{

	for(i=0;i<*lin;i++)
	{
		for(j=0;j<*col;j++)
		{
			if(matriz[i][j]!=0)
				return 0;
		}
	}
	return 1;
}

//Função para Verificar Matriz Simétrica (A=At)
int Verifica_MatrizSimetrica (int *n, int matriz[][COL_MAX])
{
	for(i=0;i<*n;i++)
	{
		for(j=0;j<*n;j++)
		{
			if(matriz[i][j] != matriz[j][i])
				return 0;
		}
	}
	return 1;
}

//Função para Verificar Matriz de Permutação
int Verifica_MatrizPermuta (int *n, int matriz[][COL_MAX])
{
	int cont0, cont1;
	//Linhas
	for(i=0;i<*n;i++)
	{
		cont0=cont1=0;
		for(j=0;j<*n;j++)
		{
			if(matriz[i][j]==0)
				cont0++;
			else if (matriz[i][j]==1)
				cont1++;
		}
		if (cont0 != *n-1|| cont1 != 1)
			return 0;
	}
	//Colunas
	for(i=0;i<*n;i++)
	{
		cont0=cont1=0;
		for(j=0;j<*n;j++)
		{
			if(matriz[j][i]==0)
				cont0++;
			else if (matriz[j][i]==1)
				cont1++;
		}
		if (cont0 != *n-1|| cont1 != 1)
			return 0;
	}
	return 1;
}

//Função para Verificar Matriz Quadrado Mágico
int Verifica_MatrizQuadMagic (int *n, int matriz[][COL_MAX])
{
	int soma_linhas[*n];
	//Somando as Linhas
	printf("\nSoma de cada linha: ");
	for(i=0;i<*n;i++)
    {
        soma_linhas[i]=0;
        for(j=0;j<*n;j++)
            soma_linhas[i] += matriz[i][j];
    }
    for(i=0;i<*n;i++)
        printf("%d ",soma_linhas[i]);

	int soma_colunas[*n];
	//Somando as Colunas
	printf("\nSoma de cada coluna: ");
	for(i=0;i<*n;i++)
	{
		soma_colunas[i]=0;
		for(j=0;j<*n;j++)
			soma_colunas[i] += matriz[j][i];
	}
	for(i=0;i<*n;i++)
        printf("%d ",soma_colunas[i]);

	int soma_DP=0, soma_DS=0;
	//Somando a diagonal principal
	for(i=0;i<*n;i++)
		soma_DP += matriz[i][i];
	//Somando a diagonal secundária
	for(i=0;i<*n;i++)
		soma_DS += matriz[i][*n -i-1];
    printf("\nSoma da diagonal principal: %d",soma_DP);
    printf("\nSoma da diagonal secundaria: %d",soma_DS);

    //Testar as linhas e colunas com contadores
    int teste_linha=1,teste_coluna=1;
    for(i=1;i<*n;i++)
    {
        if(soma_linhas[i] != soma_linhas[i-1])
        {
            teste_linha=0;
            break;
        }
        else if(soma_colunas[i] != soma_colunas[i-1])
        {
            teste_coluna=0;
            break;
        }
    }

    //Verificação do Quadrado Magico
    if((teste_linha && teste_coluna) && (soma_DP == soma_DS) && (soma_DP == soma_linhas[0]))
        return 1;
    else
        return 0;
}

//Função para Verificar Matriz Quadrado Latino
int Verifica_MatrizQuadLatino (int *n, int matriz[][COL_MAX])
{
	int k;

	//Linhas
	for(i=0;i<*n;i++)
	{
		for(j=0;j<*n;j++)
		{
			for(k=0;k<*n;k++)
			{
				if(((j!=k) && (matriz[i][j] == matriz[i][k])) || (matriz[i][j]==0) || (matriz[i][k]==0))
					return 0;
			}
		}
	}

	//Colunas
	for(i=0;i<*n;i++)
	{
		for(j=0;j<*n;j++)
		{
			for(k=0;k<*n;k++)
			{
				if(((j!=k) && (matriz[j][i] == matriz[k][i])) || (matriz[j][i]==0) || (matriz[k][i]==0))
					return 0;
			}
		}
	}

	return 1;
}


//Sistemas Lineares Triangulares (tipo float)
//Função para Mostrar Vetor (Soluções do Sistema)
void Mostra_Vetor (int *n, int vet[])
{
    printf("\n\nAs solucoes mais proximas do sistema sao:\n\n");
    for (i=0; i<*n; i++) {
        printf("X%d: %d", i+1, vet[i]);
        printf ("\n");
    }
}
//Função para Mostrar Vetor (Termos Independentes)
void Mostra_Indep (int *n, int term_indep[])
{
    printf("\n\nTermos Independentes:\n\n");
    for (i=0; i<*n; i++) {
        printf("B%d: %d", i+1, term_indep[i]);
        printf ("\n");
    }
}
//Função para Resolução de um Sistema Linear Triangular Inferior
void Sist_Line_TriInf (int *n, int matriz_triinf[][COL_MAX], int xi[], int term_indep[])
{
	//Vetor para armazenar os termos independentes
	//int term_indep[*n];
	for(i=0;i<*n;i++)
	{
		printf("Digite o valor do termo independente (B%d) da linha %d da matriz: ", i+1, i+1);
		scanf("%d",&term_indep[i]);
		printf("\n");
	}

	//Primeira Solução Possível (X1 = B1/M11)
	xi[0] = (term_indep[0]/matriz_triinf[0][0]);
	//Outras Soluções
	int soma;
	for(i=1;i<*n;i++)
	{
		soma=0;
		for(j=0;j<i;j++)
			soma += (matriz_triinf[i][j] * xi[j]);
		xi[i] = (term_indep[i] - soma)/matriz_triinf[i][i];
	}
}
//Função para Resolução de um Sistema Linear Triangular Superior
void Sist_Line_TriSup (int *n, int matriz_trisup[][COL_MAX], int xi[], int term_indep[])
{
	//Vetor para armazenar os termos independentes
	//int term_indep[*n];
	int count;
	for(i=0,count=*n;i<*n,count>0;i++,count--)
	{
		printf("Digite o valor do termo independente (B%d) da linha %d da matriz: ", i+1, count);
		scanf("%d",&term_indep[i]);
		printf("\n");
	}

	//Primeira Solução Possível (Xn = Bn/Mnn)
	xi[*n-1] = term_indep[*n-1]/matriz_trisup[*n-1][*n-1];

	//Outras Soluções
	int soma;
	for(i=*n-1;i>=0;i--)
	{
		soma=0;
		for(j=i;j<*n;j++)
			soma += (matriz_trisup[i][j] * xi[j]);
		xi[i] = (term_indep[i] - soma)/matriz_trisup[i][i];
	}

}
