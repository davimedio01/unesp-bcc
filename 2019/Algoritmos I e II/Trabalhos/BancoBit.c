//Trabalho 2 - Algoritmos II~~
//Alunos: Davi Augusto e Luiz Sementille
//Curso: BCC
//Data de Entrega: 02/09/2019
//Compilar com TDM-GCC 64bit

//Funções Necessarias: Login/Cadastro(Local), Deposito, Saque, Preenchimento de Cheques
//Limite: B$999.999.999,99
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>

//Teclas em ASCII (*usar o getch)
#define CIMA 72
#define BAIXO 80
#define DIREITA 77
#define ESQUERDA 75
#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define AJUDA 65 //A
#define max_cheque 20

typedef struct{
    char nome[50], login_cad[15], senha_cad[15], login_log[15], senha_log[15];
    int num_conta;
    double saldo_atual;
}Usuario;

//Funções dos Menus
void moveXY (int x, int y, char t[]);
void Menu_Cadastro (Usuario *user_conta);
void Menu_Login (Usuario *user_conta);
void Menu_Superior(Usuario user_conta);
void Menu_Principal();
void Menu_Ajuda();

//Funções do Banco
int Deposito (Usuario *user_conta);
int Saque (Usuario *user_conta, int cont_nota[], int cont_moeda[]);

void Converte_Cheque(char cheque[], char notas[], char moedas[]);
int concatDezenaeUni(char cheque[], int d, int u, int op);
void colocaUni(char cheque[], int i, int c, int d, int u);
void concatChequeMoedas(char notas[], char cheque[], int i);
int concatChequeNotas(char notas[], char cheque[], int i, int zerado);
void Preenche_Cheque(char notas[], char moedas[]);

//Função para Repetir Funções (--NÃO UTILIZADO--)
//void Repita_Func (char *opcao_func, int *menu);

int main()
{
    system("COLOR 09");
    //Colocar a linguagem em português para acentuação
    setlocale(LC_ALL,"Portuguese");

    //Declaração, Criação e Login da Conta do Usuario
    Usuario user_conta;
    Menu_Cadastro(&user_conta);
    Menu_Login(&user_conta);
    user_conta.saldo_atual = 0.00;
    //Criar numero da conta aleatoriamente
    srand(time(NULL));
    user_conta.num_conta = rand()%100000;

    //Declaração das variáveis para manipulação dos menus e troca dos mesmos
    char opcao_menu=0, opcao_first;
    short posX=37, posY=12; //Seta de escolha das Funções
    int funcao=0, ajuda=0;

    while(opcao_menu!=ESC)
    {
        Menu_Superior(user_conta);
        if(funcao==0 && ajuda==0)
        {
            Menu_Principal();
            moveXY(posX, posY, "->");
            opcao_menu = toupper(getch());

            //Manipulação da Seta do Menu Principal
            switch(opcao_menu)
            {
                case CIMA:
                    if(posY>12)
                    {
                        moveXY(posX,posY,"  ");
                        posY-=3;
                        moveXY(posX,posY,"->");
                        Beep(450,100);
                    }
                    break;
                case BAIXO:
                    if(posY<18)
                    {
                        moveXY(posX,posY,"  ");
                        posY+=3;
                        moveXY(posX,posY,"->");
                        Beep(450,100);
                    }
                    break;
                case AJUDA:
                    ajuda=1;
                    system("cls");
                    break;
                case ENTER:
                    if(posY==12)
                        funcao=1;
                    else if(posY==15)
                        funcao=2;
                    else if(posY==18)
                        funcao=3;
                    system("cls");
                    break;
                case ESC:
                    opcao_menu=ESC;
                    system("cls");
                    break;
            }
        }
        //Menu de Ajuda (F1)
        else if(funcao==0 && ajuda==1)
        {
            Menu_Ajuda();
            opcao_first = toupper(getch());
            switch(opcao_first)
            {
                case ESC:
                    ajuda=0;
                    system("cls");
                    break;
            }
        }
        //Depósito
        else if (funcao==1)
        {
            moveXY(43,8,"::: DEPÓSITO :::");
            if(user_conta.saldo_atual<999999999.99)
            {
                if(Deposito(&user_conta))
                {
                    system("cls");
                    Menu_Superior(user_conta);
                    moveXY(43,8,"::: DEPÓSITO :::");
                    moveXY(35,15, "DEPÓSITO REALIZADO COM SUCESSO.");
                }
                else
                {
                    system("cls");
                    Menu_Superior(user_conta);
                    moveXY(43,8,"::: DEPÓSITO :::");
                    moveXY(20,15, "UM DEPÓSITO DESSE VALOR SUPERA O LIMITE PERMITIDO!!");
                    moveXY(20,17, "POR FAVOR, REALIZE UM SAQUE E/OU TENTE A OPERAÇÃO NOVAMENTE.");
                }
            }
            else
                moveXY(20,15, "SALDO NO LIMITE!! POR FAVOR, REALIZE UM SAQUE E TENTE NOVAMENTE.");
            moveXY(30,25,"");
            system("pause");
            funcao=0;
            system("cls");
        }
        //Saque
        else if (funcao==2)
        {
            moveXY(45,8,"::: SAQUE :::");
            if(user_conta.saldo_atual>0)
            {
                float notas[] = {2.00,5.00,10.00,20.00,50.00,100.00};
                float moedas[] = {0.01,0.10,0.25,0.50,1.00};
                int cont_nota[6], cont_moeda[5];
                int i;
                if(Saque(&user_conta,cont_nota,cont_moeda))
                {
                    system("cls");
                    Menu_Superior(user_conta);
                    moveXY(45,8,"::: SAQUE :::");
                    moveXY(35,10,"TOTAL DE NOTAS E MOEDAS A RECEBER");
                    moveXY(40,12,"");
                    short posY_saque = 12;

                    //Verificação das Notas
                    for(i=5;i>=0;i--)
                    {
                       if(cont_nota[i]>0)
                       {
                           printf("%d nota(s) de B$ %.2f\n",cont_nota[i],notas[i]);
                           posY_saque++;
                           moveXY(40,posY_saque,"");
                       }
                    }
                    //Verificação das Moedas
                    for(i=4;i>=0;i--)
                    {
                       if(cont_moeda[i]>0)
                       {
                           printf("%d moeda(s) de B$ %.2f\n",cont_moeda[i],moedas[i]);
                           posY_saque++;
                           moveXY(40,posY_saque,"");
                       }
                    }
                    moveXY(38,26, "SAQUE REALIZADO COM SUCESSO.");
                }
                else
                {
                    system("cls");
                    Menu_Superior(user_conta);
                    moveXY(45,8,"::: SAQUE :::");
                    moveXY(20,15, "UM SAQUE DESSE VALOR SUPERA O SALDO ATUAL QUE VOCÊ POSSUI!!");
                    moveXY(20,17, "POR FAVOR, REALIZE UM DEPÓSITO E/OU TENTE A OPERAÇÃO NOVAMENTE.");
                }
            }
            else
                moveXY(13,15, "SALDO INSUFICIENTE PARA SAQUE!! POR FAVOR, REALIZE UM DEPÓSITO E TENTE NOVAMENTE.");
            moveXY(30,28,"");
            system("pause");
            funcao=0;
            system("cls");
        }
        //Preenchimento de Cheque
        else if (funcao==3)
        {
            moveXY(35,8,"::: PREENCHIMENTO DE CHEQUE :::");
            double num_cheque=0;
            char data[50], valor[13], notas[10], moedas[3];
            int i;
            do
            {
            	fflush(stdin);
                moveXY(35,10,"DIGITE O VALOR DO CHEQUE (COM DUAS CASAS DECIMAIS)");
                moveXY(35,12,"B$");
                moveXY(37,12," ");
                gets(valor);
            }while(strlen(valor)==0 && strlen(valor)>=1000000000);
            fflush(stdin);
            do
            {
            	moveXY(35,15,"AGORA, DIGITE O VALOR DA DATA");
            	moveXY(37,16,"EM 'DIA' de 'MES' de 'ANO'");
            	moveXY(35,18,"DATA:");
           		moveXY(40,18," ");
           		gets(data);
			}while(strlen(data)==0);
            Converte_Cheque(valor, notas, moedas);
            system("cls");
            Menu_Superior(user_conta);
            moveXY(35,8, "::: PREENCHIMENTO DE CHEQUE :::");
            for(i=12;i<=90;i++)
            {
            	moveXY(i,10,"-");
            	moveXY(i,26,"-");
			}
          	for(i=11;i<=25;i++)
            {
            	moveXY(11,i,"|");
            	moveXY(91,i,"|");
			}
            moveXY(45,11, "C H E Q U E");
            moveXY(13,24, " B A N C O  B I T");
            moveXY(58,24, "ASS: ");
            printf("%s",user_conta.nome);
            moveXY(67,19, "Ilhas Weblands,");
            moveXY(67,21, "");
            printf("%s",data);
            
            Preenche_Cheque(notas,moedas);

            moveXY(30,28,"");
            system("pause");
            funcao=0;
            system("cls");
        }
    }
    Beep(300,650); //Tchau. Obrigado por usar o programa.

    return 0;
}

/*void Repita_Func (char *opcao_func, int *funcao)
{
    do
    {
        //printf("\n\nDeseja executar a funcao novamente?\n\nENTER: Sim\nESC: Volta para o Menu Anterior\n");
        do
        {
            *opcao_func = toupper(getch());
            switch(*opcao_func)
            {
                case ESC:
                    *funcao=0;
                    break;
                case ENTER:
                    break;
            }
        }while((*opcao_func != ESC)||(*opcao_func != ENTER));

        //if(*funcao>=0 && *funcao<=3)
        //    break;
    }while((*funcao < 0)&&(*funcao > 3));
}*/

//Funções dos Menus
//Função MoveXY (do windows.h) para controle do Menu por meio de coordenadas
void moveXY (int x, int y, char t[])
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {x,y};
	SetConsoleCursorPosition(hStdout,position);
	printf("%s",t);
}
//Menu de Cadastro
void Menu_Cadastro (Usuario *user_conta)
{
    char asterisco;
    int i=0;
    moveXY(32,1, "::: BANCOBIT DAS ILHAS WEBLANDS :::");
    moveXY(39,3, ":: TELA DE CADASTRO ::");
    moveXY(17,7, "POR FAVOR, REALIZE O CADASTRO ABAIXO PARA TER SUA SENHA SUPER SECRETA.");
    moveXY(28,13, "NOME:");
    moveXY(28,15, "LOGIN:");
    moveXY(28,17, "SENHA:");
    moveXY(65,22, "ENTER: CONFIRMAR");
    moveXY(45,25, "VERSAO: 1.05");
    fflush(stdin);
    do
    {
    	moveXY(35,13, "");
    	gets((*user_conta).nome);
	}while(strlen((*user_conta).nome)==0);
    do
    {
    	moveXY(35,15, "");
    	gets((*user_conta).login_cad);
	}while(strlen((*user_conta).login_cad)==0);
	do
	{
		moveXY(35,17, "");
		gets((*user_conta).senha_cad);
	}while(strlen((*user_conta).senha_cad)==0);
    /*Colocar asterisco na senha
    do
    {
        asterisco = toupper(getch());
        //isprint = Analisa se o valor é imprimivel
        if(isprint(asterisco))
        {
            (*user_conta).senha_cad[i] = asterisco;
            i++;
            printf("*");
        }
        //Analisa se o usuario apertou o backspace e verifica de o contador é diferente de 0 (para apagar)
        else if (asterisco == BACKSPACE && i)
        {
            (*user_conta).senha_cad[i] = '\0';
            i--;
            printf("\b \b");
        }
    }while(asterisco!=ENTER);*/
    system("cls");
}
//Menu de Login
void Menu_Login (Usuario *user_conta)
{
    char asterisco;
    int i=0, j, verifica;
    while(1)
    {
        moveXY(32,1, "::: BANCOBIT DAS ILHAS WEBLANDS :::");
        moveXY(40,3, ":: TELA DE LOGIN ::");
        moveXY(19,7, "POR FAVOR, REALIZE O LOGIN ABAIXO COM SUA SENHA SUPER SECRETA.");
        moveXY(28,13, "LOGIN:");
        moveXY(28,15, "SENHA:");
        moveXY(65,22, "ENTER: CONFIRMAR");
        moveXY(45,25, "VERSAO: 1.05");
        fflush(stdin);
        moveXY(35,13, "");
        gets((*user_conta).login_log);
        moveXY(35,15, "");
        gets((*user_conta).senha_log);
        /*Colocar asterisco na senha
        do
        {
            asterisco = toupper(getch());
            //isprint = Analisa se o valor é imprimivel
            if(isprint(asterisco))
            {
                (*user_conta).senha_log[i] = asterisco;
                i++;
                printf("*");
            }
            //Analisa se o usuario apertou o backspace e verifica de o contador é diferente de 0 (para apagar)
            else if (asterisco == BACKSPACE && i)
            {
                (*user_conta).senha_log[i] = '\0';
                i--;
                printf("\b \b");
            }
        }while(asterisco!=ENTER);
        system("cls");
        i=0;
        for(j=0;j<strlen((*user_conta).senha_log);j++)
        	if((*user_conta).senha_cad[j] == (*user_conta).senha_log[j])
        		verifica=1;
        	else
        		verifica=0;
        */
        system("cls");
        if((strcmp((*user_conta).login_log,(*user_conta).login_cad)==0) && (strcmp((*user_conta).senha_log,(*user_conta).senha_cad)==0))
            break;
    }
}
void Menu_Superior(Usuario user_conta)
{
    moveXY(5,1,"VOCÊ ESTÁ LOGADO NO BANCOBIT.");
    moveXY(5,4,"NOME:");
    moveXY(5,5,"NÚMERO DA CONTA -");
    moveXY(70,5,"SALDO ATUAL - B$");
    moveXY(10,4," ");
    printf("%s",user_conta.nome);
    moveXY(22,5, " ");
    printf("%d",user_conta.num_conta);
    moveXY(86,5, " ");
    printf("%.2lf",user_conta.saldo_atual);
    moveXY(2,6,"-------------------------------------------------------------------------------------------------");
}
//Menu Principal
void Menu_Principal()
{
    moveXY(40,12,"DEPÓSITO");
    moveXY(40,15, "SAQUE");
    moveXY(40,18, "PREENCHIMENTO DE CHEQUES");
    moveXY(80,22, "A: AJUDA");
	moveXY(80,24, "ENTER: SELECIONAR");
	moveXY(80,25, "ESC: SAIR DO PROGRAMA");
	moveXY(5,22, "CRÉDITOS: DAVI AUGUSTO E LUIZ SEMENTILLE");
	moveXY(5,23, "TRABALHO II - ALGORITMOS II");
	moveXY(5,25, "SALDO/CHEQUE LIMITE - B$ 999.999.999,99");
	moveXY(25,28, "OBS: USE AS SETAS DO TECLADO PARA ESCOLHER A FUNCAO DESEJADA");
}
//Menu de Ajuda
void Menu_Ajuda()
{
    moveXY(40,8, "::::: AJUDA :::::");
    moveXY(2,10, "::: DEPÓSITO :::");
    moveXY(2,12, "A função de depósito realiza o envio de dinheiro para a conta atual conectada,");
    moveXY(2,13, "sendo armazenado no sistema.");
    moveXY(2,15, "::: SAQUE :::");
    moveXY(2,17, "A função de saque realiza a retirada de dinheiro da conta atual conectada,");
    moveXY(2,18, "sendo mostrado o total de notas e moedas mínimas para tal.");
    moveXY(2,20, "::: PREENCHIMENTO DE CHEQUES :::");
    moveXY(2,22, "A função de preenchimento de cheques realiza o preenchimento automático de cheques");
    moveXY(2,23, "com base em uma data específica e no valor total da conta atual conectada.");
    moveXY(2,28, "*USE A NOTAÇÃO DA MOEDA EM VÍRGULA (EX: B$ 12,71)");
    moveXY(70,28, "ESC: VOLTAR PARA O MENU");
}

//Funções do Banco
//Depósito
int Deposito (Usuario *user_conta)
{
    double deposito;
    do
    {
        moveXY(35,10,"DIGITE O VALOR A SER DEPOSITADO");
        moveXY(35,12,"B$");
        moveXY(37,12," ");
        scanf("%lf",&deposito);
        moveXY(37,12,"                                       ");
        printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    }while(deposito<=0.00 || deposito>999999999.99);

    double verifica = (*user_conta).saldo_atual + deposito;
    if(verifica<=999999999.99)
    {
        (*user_conta).saldo_atual += deposito;
        return 1;
    }
    else
        return 0;
}

int Saque (Usuario *user_conta, int cont_nota[], int cont_moeda[])
{
    double saque;
    do
    {
        moveXY(35,10,"DIGITE O VALOR A SER SACADO");
        moveXY(35,12,"B$");
        moveXY(37,12," ");
        scanf("%lf",&saque);
        moveXY(37,12,"                                       ");
        printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    }while(saque<=0.00 || saque>999999999.99);

    if((*user_conta).saldo_atual >= saque)
    {
        //Separar parte inteira da decimal para facilitar a contagem
        long int saque_nota = saque;
        long int saque_moeda = ceil((saque - saque_nota)*100);
        
        //Definir todos contadores inicialmente
        int i;
        for(i=0;i<6;i++)
            cont_nota[i]=0;
        for(i=0;i<5;i++)
            cont_moeda[i]=0;

        //Loops para Notas e Moeda de B$1,00
        do
        {
            if(saque_nota>=100)
            {
                cont_nota[5] = saque_nota/100;
                saque_nota %= 100;
            }
            else if(saque_nota>=50)
            {
            	cont_nota[4] = saque_nota/50;
                saque_nota %= 50;
                
            }
            else if(saque_nota>=20)
            {
                cont_nota[3] = saque_nota/20;
            	saque_nota %= 20;
			}
            else if(saque_nota>=10)
            {
                cont_nota[2] = saque_nota/10;
            	saque_nota %= 10;
			}
            else if(saque_nota>=5)
            {
                cont_nota[1] = saque_nota/5;
            	saque_nota %= 5;
			}
            else if(saque_nota>=2)
            {
                cont_nota[0] = saque_nota/2;
            	saque_nota %= 2;
            }
            else if(saque_nota>=1)
            {
                cont_moeda[4] = saque_nota/1;
                saque_nota %= 1;
            }
        }while(saque_nota!=0);

        //Loops para Moedas
        do
        {
            if(saque_moeda>=50)
            {
                cont_moeda[3] = saque_moeda/50;
                saque_moeda %= 50;
            }
            else if(saque_moeda>=25)
            {
                cont_moeda[2] = saque_moeda/25;
				saque_moeda %= 25;            
			}
            else if(saque_moeda>=10)
            {
                cont_moeda[1] = saque_moeda/10;
                saque_moeda %= 10;
            }
            else if(saque_moeda>=1)
            {
                cont_moeda[0] = saque_moeda/1;
                saque_moeda %= 1;
            }
        }while(saque_moeda!=0);
        (*user_conta).saldo_atual -= saque;
        return 1;
    }
    else
        return 0;

}

//Preencher Cheques (Numeros por Extenso)
void Converte_Cheque(char cheque[], char notas[], char moedas[]) //<1.000.000.000,00 (menor que um bilhão)
{
	
	double val;
	char *pch;
	pch = strtok(cheque, ",");
	int cont=0,i;
  	while (pch != NULL)
  	{	
  		if(!cont)
  		{
  			strcpy(notas, pch);
  			cont++;
		}
    	else
    	{
    		strcpy(moedas, pch);
    		pch = strtok (NULL,",");
		}
    		
  	}
  		strrev(notas);
  		for(i=strlen(notas); i<9; i++)
  			notas[i] = '0';
  	strrev(notas);
}

int concatDezenaeUni(char cheque[], int d, int u, int op)
{
	char unidade[max_cheque][max_cheque] = {"Um", "Dois", "Três", "Quatro", "Cinco", "Seis", "Sete", "Oito", "Nove"};
    char dezena[max_cheque][max_cheque] = {"Dez","Vinte","Trinta", "Quarenta", "Cinquenta", "Sessenta", "Setenta", "Oitenta", "Noventa"};
	char especiais[max_cheque][max_cheque] = {"Onze","Doze", "Treze", "Quatorze", "Quinze", "Dezesseis", "Dezessete", "Dezoito", "Dezenove"};
	
	int op2 = 1;
	
	if(d+u == 0)
	{
		return (op2 = 0);
	}
	if(op)
		strcat(cheque, " E ");
	if(d!=0)
	{
		if(d==1 && u!=0)
			strcat(cheque, especiais[u-1]);
		else if(d==1 && u==0)
			strcat(cheque, dezena[0]);
		else if(d!= 1)
		{
			strcat(cheque, dezena[d-1]);
			if(u!=0)
			{
				strcat(cheque, " E ");
				strcat(cheque, unidade[u-1]);
			}
		}	
	}
	else if(u!=0)
		strcat(cheque, unidade[u-1]);
	
	return op2;
		
}
void colocaUni(char cheque[], int i, int c, int d, int u)
{
	int tam = strlen(cheque);
	switch(i)
	{
		case 0: if(c+d == 0 && u)
					strcat(cheque, " Milhão");
				else
					strcat(cheque, " Milhões");
				break;
				
		case 3: strcat(cheque, " Mil");
				break;	
	}
}
void concatChequeMoedas(char notas[], char cheque[], int i){
	
	int d, u, aux, op;
	
	aux = atoi(notas);
	d = aux/10;
    aux = aux%10;
    u = aux/1;
    
    if(strlen(cheque) == 0)
    	op = concatDezenaeUni(cheque, d, u, 0);
    else
    	op = concatDezenaeUni(cheque, d, u, 1);
    if(!op)
    	return;
    strcat(cheque, " CentBits");
    		
}
int concatChequeNotas(char notas[], char cheque[], int i, int zerado)
{
	
    char centena[max_cheque][max_cheque] = {"Cem","Cento","Duzentos","Trezentos","Quatrocentos","Quinhentos","Seiscentos","Setecentos","Oitocentos","Novecentos"}; 
    
    int c, d, u, tam, aux, op, e;

	c = atoi(notas)/100;
	aux = atoi(notas)%100;
    d = aux/10;
    aux = aux%10;
    u = aux/1;
    
    if((c+d+u) == 0)
    	return 0;
    if((i==3 || i==6) && zerado)
    	strcat(cheque, " E ");
    if(!c)
    {
    	op = concatDezenaeUni(cheque, d, u, 0);
    	if(!op)
    		return;
    	colocaUni(cheque, i, c, d, u);
	}
    else if(c == 1){
    	if(d+u != 0)
    	{
			strcat(cheque, centena[1]);
			op = concatDezenaeUni(cheque, d, u, 1); 
			colocaUni(cheque, i, c, d, u);   		
		}
		else
		{
			strcat(cheque, centena[0]);	
			colocaUni(cheque, i, c, d, u);
		}
			
	}	
	else if(c!=1 && c!=0){
		strcat(cheque, centena[c]);
		op = concatDezenaeUni(cheque, d, u, 1);
		colocaUni(cheque, i, c, d, u);
	}	
	return 1;
	
}
void Preenche_Cheque(char notas[], char moedas[])
{
    int i,j,k;
    //Coordenadas iniciais do preenchimento
    short posY_nota = 14, posY_moeda = 16;
    //Auxiliares
    char cheque[120] = {""};
    int u,d,c,especial=0, zerado;
    for(i=0; i<strlen(notas); i+=3)
    {
    	char aux[4] = {notas[i], notas[i+1], notas[i+2]};
    	zerado = concatChequeNotas(aux, cheque, i, zerado); 	
	}
	if(strlen(cheque)!= 0)
		strcat(cheque, " Bits");
	i=0;
	char aux[3] = {moedas[i],moedas[i+1]};
	concatChequeMoedas(aux, cheque, i);
	fflush(stdin);
	moveXY(14, 14, "");
	for(i=0; i<strlen(cheque); i++)
	{
		putchar(cheque[i]);
		if(i==73)
			moveXY(13, 15, "");
	}
	
}

