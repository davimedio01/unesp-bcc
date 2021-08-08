;*************************************************************
; Comunica��o Serial										 *
;															 *
; Autor: Davi Augusto Neves Leite			     			 *			 
; RA: 191027383						     				     *					 
; Data: 01/11/2020					     					 *					 
;*************************************************************

#include <p16f628a.inc>
;-------------------------------------------------------------
; Configura��o dos Bits
__CONFIG _BODEN_ON & _CP_OFF & _PWRTE_ON & _WDT_OFF & _LVP_OFF & _MCLRE_ON & _HS_OSC
;-------------------------------------------------------------
;-------------------------------------------------------------
;Configura��o do endere�o 0x20 para ser o contador de d�gitos do display
		COUNT_DISPLAY		EQU		0x20
;-------------------------------------------------------------
;-------------------------------------------------------------
		ORG 0x0000
		GOTO INICIO ;Vai para o bloco INICIO
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina para mudar o contador e mostrar o respectivo n�mero no display
;-------------------------------------------------------------
COUNT_CHANGE:
			;-------------------------------------------------------------
			;Deixa selecionado o banco do PORTB para altera��o dos n�meros no display (RBx)
			;-------------------------------------------------------------
			BANKSEL PORTB
			
			;-------------------------------------------------
			; Abaixo, realiza-se uma subtra��o e verifica se o resultado obtido foi 0 (a partir da flag Z)
			;-------------------------------------------------
			; N�mero 0
			;-------------------------------------------------
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'0'			  ;Decresce em 0 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER0  ;Caso tenha sido, coloca o n�mero 0 no display
			NOP
			
			;-------------------------------------------------
			; N�mero 1
			;-------------------------------------------------
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'1'			  ;Decresce em 1 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER1  ;Caso tenha sido, coloca o n�mero 1 no display
			NOP
			
			;-------------------------------------------------
			; N�mero 2
			;-------------------------------------------------
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'2'			  ;Decresce em 2 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER2  ;Caso tenha sido, coloca o n�mero 2 no display
			NOP
			
			;-------------------------------------------------
			; N�mero 3
			;-------------------------------------------------
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'3'			  ;Decresce em 3 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER3  ;Caso tenha sido, coloca o n�mero 3 no display
			NOP
			
			;-------------------------------------------------
			; N�mero 4
			;-------------------------------------------------
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'4'			  ;Decresce em 4 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER4  ;Caso tenha sido, coloca o n�mero 4 no display
			NOP
			
			;-------------------------------------------------
			; N�mero 5
			;-------------------------------------------------
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'5'			  ;Decresce em 5 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER5  ;Caso tenha sido, coloca o n�mero 5 no display
			NOP
			
			;-------------------------------------------------
			; N�mero 6
			;-------------------------------------------------
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'6'			  ;Decresce em 6 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER6  ;Caso tenha sido, coloca o n�mero 6 no display
			NOP
			
			;-------------------------------------------------
			; N�mero 7
			;-------------------------------------------------
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'7'			  ;Decresce em 7 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER7  ;Caso tenha sido, coloca o n�mero 7 no display
			NOP
			
			;-------------------------------------------------
			; N�mero 8
			;-------------------------------------------------
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'8'			  ;Decresce em 8 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER8  ;Caso tenha sido, coloca o n�mero 8 no display
			NOP
			
			;-------------------------------------------------
			; N�mero 9
			;-------------------------------------------------
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'9'			  ;Decresce em 9 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER9  ;Caso tenha sido, coloca o n�mero 9 no display
			NOP
			
			;-------------------------------------------------
			; Quando o n�mero enviado n�o est� entre 0 e 9, inclusivo
			;-------------------------------------------------
			MOVLW D'255' 		  ;Move o valor 255 para o registrador W
SEND_DATA:
			BANKSEL TXSTA
			BTFSS TXSTA, TRMT 	  ;Verifica se o buffer de transmiss�o est� vazio
			GOTO SEND_DATA 		  ;Caso N�O esteja, verifica novamente (at� conseguir enviar)
			NOP
			BANKSEL TXREG		  ;Ativa o banco do registrador TXREG
			MOVWF TXREG 		  ;Caso esteja, envia o valor para o Buffer de Transmiss�o
			
			GOTO RECEIVE_DATA 	  ;Retorna para a fun��o de recebimento de dados
;-------------------------------------------------------------
;-------------------------------------------------------------
; Abaixo, ficam as fun��es para ativar cada n�mero do display de 7 segmentos (config. RBx)
; Cada uma move um valor espec�fico (MOVLW), em bin�rio, para a PORTB
;-------------------------------------------------------------
; N�mero 0
;-------------------------------------------------------------
DISPLAY_NUMBER0:
			 MOVLW B'11111110'
			 MOVWF PORTB
			 MOVF COUNT_DISPLAY, W
			 GOTO SEND_DATA		 ;Manda o valor para o programa
;-------------------------------------------------------------
; N�mero 1
;-------------------------------------------------------------
DISPLAY_NUMBER1:
			 MOVLW B'00111000'
			 MOVWF PORTB
			 MOVF COUNT_DISPLAY, W
			 GOTO SEND_DATA		 ;Manda o valor para o programa
;-------------------------------------------------------------
; N�mero 2
;-------------------------------------------------------------
DISPLAY_NUMBER2:
			 MOVLW B'11011101'
			 MOVWF PORTB
			 MOVF COUNT_DISPLAY, W
			 GOTO SEND_DATA		 ;Manda o valor para o programa
;-------------------------------------------------------------
; N�mero 3
;-------------------------------------------------------------
DISPLAY_NUMBER3:
			 MOVLW B'01111101'
			 MOVWF PORTB
			 MOVF COUNT_DISPLAY, W
			 GOTO SEND_DATA		 ;Manda o valor para o programa
;-------------------------------------------------------------
; N�mero 4
;-------------------------------------------------------------
DISPLAY_NUMBER4:
			 MOVLW B'00111011'
			 MOVWF PORTB
			 MOVF COUNT_DISPLAY, W
			 GOTO SEND_DATA		 ;Manda o valor para o programa
;-------------------------------------------------------------
; N�mero 5
;-------------------------------------------------------------
DISPLAY_NUMBER5:
			 MOVLW B'01110111'
			 MOVWF PORTB
			 MOVF COUNT_DISPLAY, W
			 GOTO SEND_DATA		 ;Manda o valor para o programa
;-------------------------------------------------------------
; N�mero 6
;-------------------------------------------------------------
DISPLAY_NUMBER6:
			 MOVLW B'11110011'
			 MOVWF PORTB
			 MOVF COUNT_DISPLAY, W
			 GOTO SEND_DATA		 ;Manda o valor para o programa
;-------------------------------------------------------------
; N�mero 7
;-------------------------------------------------------------
DISPLAY_NUMBER7:
			 MOVLW B'00111100'
			 MOVWF PORTB
			 MOVF COUNT_DISPLAY, W
			 GOTO SEND_DATA		 ;Manda o valor para o programa
;-------------------------------------------------------------
; N�mero 8
;-------------------------------------------------------------
DISPLAY_NUMBER8:
			 MOVLW B'11111111'
			 MOVWF PORTB
			 MOVF COUNT_DISPLAY, W
			 GOTO SEND_DATA		 ;Manda o valor para o programa
;-------------------------------------------------------------
; N�mero 9
;-------------------------------------------------------------
DISPLAY_NUMBER9:
			 MOVLW B'00111111'
			 MOVWF PORTB
			 MOVF COUNT_DISPLAY, W
			 GOTO SEND_DATA		 ;Manda o valor para o programa
			 
FIM_DISPLAY_NUMBER:	RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Sub-rotinas de Configura��es Iniciais
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configura��o do registrador INTCON
;-------------------------------------------------------------
CONFIG_INTCON:
			 BANKSEL INTCON
			 MOVLW B'10100000'
			 MOVWF INTCON
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador TXSTA para Comunica��o Serial (Transmiss�o de Dados)
;-------------------------------------------------------------
CONFIG_TXSTA:
			 BANKSEL TXSTA
			 MOVLW B'00100110' ;Configura��o do TXSTA para comunica��o serial ass�ncrona de 8 bits
			 MOVWF TXSTA
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador RCSTA para Comunica��o Serial (Recep��o de Dados)
;-------------------------------------------------------------
CONFIG_RCSTA:
			 BANKSEL RCSTA
			 MOVLW B'10010000' ;Configura��o do RCSTA para comunica��o serial ass�ncrona de 8 bits
			 MOVWF RCSTA
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador SPBRSG para Comunica��o Serial (Taxa de Transmiss�o)
;-------------------------------------------------------------
; Clock: 20MHz // BPS: 9600bps // BRGH = 1 -> SPBRGH = 129,2083
;-------------------------------------------------------------
CONFIG_SPBRG:
			 BANKSEL SPBRG
			 MOVLW D'129' 		;Configura��o do SPBRS para taxa de alta velocidade (TXSTA)
			 MOVWF SPBRG
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador PIE1 para Comunica��o Serial
;-------------------------------------------------------------
CONFIG_PIE1:
			 BANKSEL PIE1
			 MOVLW B'00110000'
			 MOVWF PIE1
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador PIR1 para Comunica��o Serial
;-------------------------------------------------------------
CONFIG_PIR1:
			 BANKSEL PIR1
			 MOVLW B'00000000'
			 MOVWF PIR1
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador TRISB (PORTB) para Comunica��o Serial
;-------------------------------------------------------------
CONFIG_TRISB_SERIAL:
			 BANKSEL TRISB
			 MOVLW B'00000110' ;Definindo RB1 e RB2 como Input para Comunica��o Serial
			 MOVWF TRISB
			 RETURN
;-------------------------------------------------------------
; Configura��o do registrador TRISB (PORTB) para Display
;-------------------------------------------------------------
CONFIG_TRISB_DISPLAY:
			 BANKSEL TRISB
			 MOVLW B'00000000' ;Definindo todos RBx como output (display)
			 MOVWF TRISB
			 RETURN
;-------------------------------------------------------------
; Configura��o inicial da PORTB (Display) e do Contador
;-------------------------------------------------------------
CONFIG_PORTB:
			 BANKSEL PORTB
			 MOVLW B'11111110'
			 MOVWF PORTB
			 
			 CLRF COUNT_DISPLAY		;Zera o contador do display
			 RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
INICIO:
		CALL CONFIG_TRISB_DISPLAY	;Chama a sub-rotina de programar o TRISB para Display (Inicial)
		CALL CONFIG_PORTB	   		;Chama a sub-rotina de programar o PORTB (Display)
		
		CALL CONFIG_INTCON			;Chama a sub-rotina de programar o INTCON
		CALL CONFIG_TRISB_SERIAL	;Chama a sub-rotina de programar o TRISB para Comunica��o Serial
		CALL CONFIG_TXSTA			;Chama a sub-rotina de programar o TXSTA para Comunica��o Serial (Transmiss�o)
		CALL CONFIG_RCSTA			;Chama a sub-rotina de programar o RCSTA para Comunica��o Serial (Recep��o)
		CALL CONFIG_SPBRG			;Chama a sub-rotina de programar o SPBRG para Comunica��o Serial (Taxa de Transmiss�o)
		CALL CONFIG_PIE1			;Chama a sub-rotina de programar o PIE1 para Comunica��o Serial (Interrup��o)
		CALL CONFIG_PIR1			;Chama a sub-rotina de programar o PIR1 para Comunica��o Serial
		
RECEIVE_DATA:
		BANKSEL PIR1
		BTFSS PIR1, RCIF 			;Verifica se chegou algum byte pela serial
		GOTO RECEIVE_DATA 			;Caso N�O tenha, volta o loop at� chegar
		NOP
		
		;Caso tenha chegado algum dado...
		BANKSEL RCREG
		MOVF RCREG, W			 	;Move o byte do buffer de recep��o e coloca registrador W
		MOVWF COUNT_DISPLAY			;Move o valor de W para o contador do display
		GOTO COUNT_CHANGE			;Vai para a rotina para mudar o valor do display

END
;-------------------------------------------------------------
;-------------------------------------------------------------