;*************************************************************
; Cron�metro Circular na PORTB								 *
;															 *
; Autor: Davi Augusto Neves Leite			     			 *			 
; RA: 191027383						     				     *					 
; Data: 30/10/2020					     					 *					 
;*************************************************************

#include <p16f628a.inc>
;-------------------------------------------------------------
; Configura��o dos Bits
__CONFIG _BODEN_ON & _CP_OFF & _PWRTE_ON & _WDT_OFF & _LVP_OFF & _MCLRE_ON & _XT_OSC
;-------------------------------------------------------------
;Configura��o do endere�o 0x20 para ser o contador de d�gitos do display
		COUNT_DISPLAY		EQU		0x20
;-------------------------------------------------------------
;Configura��o do endere�o 0x22 para ser uma auxiliar do Timer
		NUMBER_OF_TIMER 	EQU 	0x22
;-------------------------------------------------------------
;-------------------------------------------------------------
			ORG 0x0000
			GOTO INICIO	   ;Vai para o bloco INICIO (main)
;-------------------------------------------------------------
;-------------------------------------------------------------
;Bloco da Rotina de Interrup��o do TMR0
			ORG 0x0004
			
			;Nesta primeira etapa, reseta a flag do TMR0 e compara o valor do TMR0 com uma auxiliar que conta quantas vezes o PIC acionou a interrup��o
			BANKSEL INTCON
			BCF INTCON, T0IF
			
			BANKSEL TMR0
			MOVLW D'131'
			MOVWF TMR0
			DECFSZ NUMBER_OF_TIMER, 1	;Subtrai o valor de F (TMR0) da auxiliar que conta quantas vezes o PIC acionou a interrup��o (esperar at� 1s)
			GOTO FIM_T0					;Retorna para o in�cio
			
			CALL VERIFICA_RA1	;Chama a sub-rotina para verificar se o bot�o RA1 est� pressionado (contador crescente ou decrescente)
			CALL COUNT_CHANGE 	;Chama a sub-rotina para mudar o d�gito do display ap�s realizar a verifica��o com a RA1
			
			;Reinicia a vari�vel auxiliar que conta quantas vezes o PIC acionou a interrup��o
			MOVLW D'125'
			MOVWF NUMBER_OF_TIMER

FIM_T0: RETFIE
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina para mudar o contador e mostrar o respectivo n�mero no display
COUNT_CHANGE:	
			;-------------------------------------------------------------
			;Deixa selecionado o banco do PORTB para altera��o dos n�meros no display (RBx)
			BANKSEL PORTB
			;-------------------------------------------------
			; Abaixo, realiza-se uma subtra��o e verifica se o resultado obtido foi 0 (a partir da flag Z)
			;-------------------------------------------------
			; N�mero 0
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'0'			  ;Decresce em 0 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER0  ;Caso tenha sido, coloca o n�mero 0 no display
			NOP
			;-------------------------------------------------
			; N�mero 1
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'1'			  ;Decresce em 1 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER1  ;Caso tenha sido, coloca o n�mero 1 no display
			NOP
			;-------------------------------------------------
			; N�mero 2
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'2'			  ;Decresce em 2 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER2  ;Caso tenha sido, coloca o n�mero 2 no display
			NOP
			;-------------------------------------------------
			; N�mero 3
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'3'			  ;Decresce em 3 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER3  ;Caso tenha sido, coloca o n�mero 3 no display
			NOP
			;-------------------------------------------------
			; N�mero 4
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'4'			  ;Decresce em 4 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER4  ;Caso tenha sido, coloca o n�mero 4 no display
			NOP
			;-------------------------------------------------
			; N�mero 5
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'5'			  ;Decresce em 5 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER5  ;Caso tenha sido, coloca o n�mero 5 no display
			NOP
			;-------------------------------------------------
			; N�mero 6
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'6'			  ;Decresce em 6 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER6  ;Caso tenha sido, coloca o n�mero 6 no display
			NOP
			;-------------------------------------------------
			; N�mero 7
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'7'			  ;Decresce em 7 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER7  ;Caso tenha sido, coloca o n�mero 7 no display
			NOP
			;-------------------------------------------------
			; N�mero 8
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'8'			  ;Decresce em 8 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER8  ;Caso tenha sido, coloca o n�mero 8 no display
			NOP
			;-------------------------------------------------
			; N�mero 9
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'9'			  ;Decresce em 9 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER9  ;Caso tenha sido, coloca o n�mero 9 no display
			NOP
			
			RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Abaixo, ficam as fun��es para ativar cada n�mero do display de 7 segmentos (config. RBx)
;-------------------------------------------------------------
; N�mero 0
DISPLAY_NUMBER0:
			 MOVLW B'11111110'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; N�mero 1
DISPLAY_NUMBER1:
			 MOVLW B'00111000'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; N�mero 2
DISPLAY_NUMBER2:
			 MOVLW B'11011101'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; N�mero 3
DISPLAY_NUMBER3:
			 MOVLW B'01111101'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; N�mero 4
DISPLAY_NUMBER4:
			 MOVLW B'00111011'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; N�mero 5
DISPLAY_NUMBER5:
			 MOVLW B'01110111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; N�mero 6
DISPLAY_NUMBER6:
			 MOVLW B'11110011'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; N�mero 7
DISPLAY_NUMBER7:
			 MOVLW B'00111100'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; N�mero 8
DISPLAY_NUMBER8:
			 MOVLW B'11111111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; N�mero 9
DISPLAY_NUMBER9:
			 MOVLW B'00111111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
			 
FIM_DISPLAY_NUMBER:	RETURN	
;-------------------------------------------------------------
;-------------------------------------------------------------
; Rotina para verificar se o RA1 est� pressionado (a fim de se realizar as devidas opera��es de crescer ou decrescer o contador)
VERIFICA_RA1:
			;Aqui est� a condi��o (if) que diz se o bot�o RA1 foi pressionado ou n�o, e chama as fun��es de controle do contador
			BTFSC PORTA, 1
			GOTO COUNT_CRESC 	;Caso N�O esteja pressionado, chama a fun��o crescente!
			GOTO COUNT_DECRESC	;Caso esteja pressionado, chama a fun��o decrescente!
;-------------------------------------------------------------
; Rotina para incrementar o contador (crescente)
COUNT_CRESC:
			INCF COUNT_DISPLAY, 1 ;Aumenta o contador em 1 -> COUNT_DISPLAY = COUNT_DISPLAY + 1	
			GOTO FIM_VERIFICA_RA1
;-------------------------------------------------------------
; Rotina para decrementar o contador (decrescente)
COUNT_DECRESC:
			DECF COUNT_DISPLAY, 1 ;Diminui o contador em 1 -> COUNT_DISPLAY = COUNT_DISPLAY - 1
			
FIM_VERIFICA_RA1: RETURN		  ;Marca o fim da verifica��o
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina que verifica se h� necessidade de setar o contador para 0 se ele passou de 9 (houve carry na soma), antes verificando se o bot�o RA1 est� pressionado...
VERIFICA_COUNT:
			BANKSEL PORTA				;Seleciona o banco do reg. PORTA
			BTFSC PORTA, 1				;Analisando se o bot�o RA1 est� pressionado
			GOTO VERIFICA_SETAR_CRESC	;Caso N�O esteja, ele vai analisar se � preciso setar o contador do display para 0 (passar de 9 -> crescente)
			GOTO VERIFICA_SETAR_DECRESC	;Caso esteja, ele vai analisar se � preciso setar o contador do display para 9 ("passar" de 0 -> decrescente)
;-------------------------------------------------------------
;Verifica se � necess�rio setar o contador do display para 0 (Crescente)
VERIFICA_SETAR_CRESC:
			MOVF COUNT_DISPLAY, W 	;Move o valor do contador do display para W
			SUBLW D'10' 		  	;Realiza a subtra��o de 10 para verificar o carry
			BTFSC STATUS, Z		  	;Setar para 0 se a flag Z estiver com 0
			GOTO SETAR_CRESC		;Chama a sub-rotina para setar o contador do display para 0
			GOTO FIM_VERIFICA_COUNT ;Retorna em caso de nenhuma altera��o
;-------------------------------------------------------------
;Verifica se � necess�rio setar o contador do display para 9 (Decrescente)
VERIFICA_SETAR_DECRESC:
			MOVF COUNT_DISPLAY, W 	;Move o valor do contador do display para W
			SUBLW D'255' 		  	;Realiza a subtra��o de 255 ("-1") para verificar o carry
			BTFSC STATUS, Z		  	;Setar para 0 se a flag Z estiver com 0
			GOTO SETAR_DECRESC	;Chama a sub-rotina para setar o contador do display para 9
			GOTO FIM_VERIFICA_COUNT ;Retorna em caso de nenhuma altera��o
;-------------------------------------------------------------
;Seta o contador do display para 0 (ap�s verifica��o)
SETAR_CRESC:
			MOVLW D'0'				;Setando o contador do display para 0
			MOVWF COUNT_DISPLAY
			CALL DISPLAY_NUMBER0	;Chama a sub-rotina para setar o d�gito 0 no display
			GOTO FIM_VERIFICA_COUNT ;Retorna em caso de nenhuma altera��o
;-------------------------------------------------------------
;Seta o contador do display para 9 (ap�s verifica��o)
SETAR_DECRESC:
			MOVLW D'9'				;Setando o contador do display para 9
			MOVWF COUNT_DISPLAY
			CALL DISPLAY_NUMBER9	;Chama a sub-rotina para setar o d�gito 9 no display
			GOTO FIM_VERIFICA_COUNT ;Retorna em caso de nenhuma altera��o

FIM_VERIFICA_COUNT: RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configura��o do registrador OPTION_REG
CONFIG_OPTIONREG:
			 BANKSEL OPTION_REG
			 MOVLW B'10000101'
			 MOVWF OPTION_REG
			 RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configura��o do registrador INTCON
CONFIG_INTCON:
			 BANKSEL INTCON
			 MOVLW B'10100000'
			 MOVWF INTCON
			 RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configura��o do registrador TRISA (PORTA)
CONFIG_TRISA:
			 BANKSEL TRISA
			 MOVLW B'00000010' ;Colocando o RA1 como input
			 MOVWF TRISA
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador TRISB (PORTB)
CONFIG_TRISB:
			 BANKSEL TRISB
			 MOVLW B'00000000' ;Definindo todos RBx como output (display)
			 MOVWF TRISB
			 RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configura��o inicial da PORTA
CONFIG_PORTA:
			 BANKSEL PORTA
			 CLRF PORTA
			 MOVLW D'7'
			 MOVWF CMCON
			 RETURN		 
;-------------------------------------------------------------
; Configura��o inicial da PORTB
CONFIG_PORTB:
			 BANKSEL PORTB
			 MOVLW B'11111110'
			 MOVWF PORTB
			 RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configura��o do registrador TMR0 (Timer0)
CONFIG_TMR0:
			 BANKSEL TMR0
			 MOVLW D'131'
			 MOVWF TMR0
			 
			 MOVLW D'125'
			 MOVWF NUMBER_OF_TIMER
			 
			 MOVLW D'0'
			 MOVWF COUNT_DISPLAY
			 
			 RETURN		
;-------------------------------------------------------------
;-------------------------------------------------------------
INICIO:
		CALL CONFIG_OPTIONREG  ;Chama a sub-rotina de programar o OPTION_REG
		CALL CONFIG_INTCON	   ;Chama a sub-rotina de programar o INTCON
		
		CALL CONFIG_TRISA	   ;Chama a sub-rotina de programar o TRISA
		CALL CONFIG_TRISB	   ;Chama a sub-rotina de programar o TRISB
		CALL CONFIG_PORTA	   ;Chama a sub-rotina de programar o PORTA
		CALL CONFIG_PORTB	   ;Chama a sub-rotina de programar o PORTB
		
		CALL CONFIG_TMR0	   ;Chama a sub-rotina de programar o TMR0
;-------------------------------------------------------------
;Rotina de LOOP que verifica se o contador passou de 9 (e voltar pra 0) ou passou de 0 (e voltar pra 9)
;Para isso, basta analisar a flag Z do registrador de status ap�s opera��es b�sicas
LOOP:	
		CALL VERIFICA_COUNT ;Chama a sub-rotina de verificar o contador do display
		
		GOTO LOOP	
END
;-------------------------------------------------------------
;-------------------------------------------------------------