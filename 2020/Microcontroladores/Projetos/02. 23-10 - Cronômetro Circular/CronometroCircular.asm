;*************************************************************
; Cronômetro Circular na PORTB								 *
;															 *
; Autor: Davi Augusto Neves Leite			     			 *			 
; RA: 191027383						     				     *					 
; Data: 30/10/2020					     					 *					 
;*************************************************************

#include <p16f628a.inc>
;-------------------------------------------------------------
; Configuração dos Bits
__CONFIG _BODEN_ON & _CP_OFF & _PWRTE_ON & _WDT_OFF & _LVP_OFF & _MCLRE_ON & _XT_OSC
;-------------------------------------------------------------
;Configuração do endereço 0x20 para ser o contador de dígitos do display
		COUNT_DISPLAY		EQU		0x20
;-------------------------------------------------------------
;Configuração do endereço 0x22 para ser uma auxiliar do Timer
		NUMBER_OF_TIMER 	EQU 	0x22
;-------------------------------------------------------------
;-------------------------------------------------------------
			ORG 0x0000
			GOTO INICIO	   ;Vai para o bloco INICIO (main)
;-------------------------------------------------------------
;-------------------------------------------------------------
;Bloco da Rotina de Interrupção do TMR0
			ORG 0x0004
			
			;Nesta primeira etapa, reseta a flag do TMR0 e compara o valor do TMR0 com uma auxiliar que conta quantas vezes o PIC acionou a interrupção
			BANKSEL INTCON
			BCF INTCON, T0IF
			
			BANKSEL TMR0
			MOVLW D'131'
			MOVWF TMR0
			DECFSZ NUMBER_OF_TIMER, 1	;Subtrai o valor de F (TMR0) da auxiliar que conta quantas vezes o PIC acionou a interrupção (esperar até 1s)
			GOTO FIM_T0					;Retorna para o início
			
			CALL VERIFICA_RA1	;Chama a sub-rotina para verificar se o botão RA1 está pressionado (contador crescente ou decrescente)
			CALL COUNT_CHANGE 	;Chama a sub-rotina para mudar o dígito do display após realizar a verificação com a RA1
			
			;Reinicia a variável auxiliar que conta quantas vezes o PIC acionou a interrupção
			MOVLW D'125'
			MOVWF NUMBER_OF_TIMER

FIM_T0: RETFIE
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina para mudar o contador e mostrar o respectivo número no display
COUNT_CHANGE:	
			;-------------------------------------------------------------
			;Deixa selecionado o banco do PORTB para alteração dos números no display (RBx)
			BANKSEL PORTB
			;-------------------------------------------------
			; Abaixo, realiza-se uma subtração e verifica se o resultado obtido foi 0 (a partir da flag Z)
			;-------------------------------------------------
			; Número 0
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'0'			  ;Decresce em 0 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER0  ;Caso tenha sido, coloca o número 0 no display
			NOP
			;-------------------------------------------------
			; Número 1
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'1'			  ;Decresce em 1 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER1  ;Caso tenha sido, coloca o número 1 no display
			NOP
			;-------------------------------------------------
			; Número 2
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'2'			  ;Decresce em 2 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER2  ;Caso tenha sido, coloca o número 2 no display
			NOP
			;-------------------------------------------------
			; Número 3
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'3'			  ;Decresce em 3 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER3  ;Caso tenha sido, coloca o número 3 no display
			NOP
			;-------------------------------------------------
			; Número 4
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'4'			  ;Decresce em 4 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER4  ;Caso tenha sido, coloca o número 4 no display
			NOP
			;-------------------------------------------------
			; Número 5
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'5'			  ;Decresce em 5 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER5  ;Caso tenha sido, coloca o número 5 no display
			NOP
			;-------------------------------------------------
			; Número 6
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'6'			  ;Decresce em 6 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER6  ;Caso tenha sido, coloca o número 6 no display
			NOP
			;-------------------------------------------------
			; Número 7
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'7'			  ;Decresce em 7 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER7  ;Caso tenha sido, coloca o número 7 no display
			NOP
			;-------------------------------------------------
			; Número 8
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'8'			  ;Decresce em 8 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER8  ;Caso tenha sido, coloca o número 8 no display
			NOP
			;-------------------------------------------------
			; Número 9
			MOVF COUNT_DISPLAY, W ;Move o valor do contador pro registrador W
			SUBLW D'9'			  ;Decresce em 9 unidade(s)
			BTFSC STATUS, Z		  ;Verifica se o resultado foi 0
			GOTO DISPLAY_NUMBER9  ;Caso tenha sido, coloca o número 9 no display
			NOP
			
			RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Abaixo, ficam as funções para ativar cada número do display de 7 segmentos (config. RBx)
;-------------------------------------------------------------
; Número 0
DISPLAY_NUMBER0:
			 MOVLW B'11111110'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 1
DISPLAY_NUMBER1:
			 MOVLW B'00111000'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 2
DISPLAY_NUMBER2:
			 MOVLW B'11011101'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 3
DISPLAY_NUMBER3:
			 MOVLW B'01111101'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 4
DISPLAY_NUMBER4:
			 MOVLW B'00111011'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 5
DISPLAY_NUMBER5:
			 MOVLW B'01110111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 6
DISPLAY_NUMBER6:
			 MOVLW B'11110011'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 7
DISPLAY_NUMBER7:
			 MOVLW B'00111100'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 8
DISPLAY_NUMBER8:
			 MOVLW B'11111111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
;-------------------------------------------------------------
; Número 9
DISPLAY_NUMBER9:
			 MOVLW B'00111111'
			 MOVWF PORTB
			 GOTO FIM_DISPLAY_NUMBER
			 
FIM_DISPLAY_NUMBER:	RETURN	
;-------------------------------------------------------------
;-------------------------------------------------------------
; Rotina para verificar se o RA1 está pressionado (a fim de se realizar as devidas operações de crescer ou decrescer o contador)
VERIFICA_RA1:
			;Aqui está a condição (if) que diz se o botão RA1 foi pressionado ou não, e chama as funções de controle do contador
			BTFSC PORTA, 1
			GOTO COUNT_CRESC 	;Caso NÃO esteja pressionado, chama a função crescente!
			GOTO COUNT_DECRESC	;Caso esteja pressionado, chama a função decrescente!
;-------------------------------------------------------------
; Rotina para incrementar o contador (crescente)
COUNT_CRESC:
			INCF COUNT_DISPLAY, 1 ;Aumenta o contador em 1 -> COUNT_DISPLAY = COUNT_DISPLAY + 1	
			GOTO FIM_VERIFICA_RA1
;-------------------------------------------------------------
; Rotina para decrementar o contador (decrescente)
COUNT_DECRESC:
			DECF COUNT_DISPLAY, 1 ;Diminui o contador em 1 -> COUNT_DISPLAY = COUNT_DISPLAY - 1
			
FIM_VERIFICA_RA1: RETURN		  ;Marca o fim da verificação
;-------------------------------------------------------------
;-------------------------------------------------------------
;Rotina que verifica se há necessidade de setar o contador para 0 se ele passou de 9 (houve carry na soma), antes verificando se o botão RA1 está pressionado...
VERIFICA_COUNT:
			BANKSEL PORTA				;Seleciona o banco do reg. PORTA
			BTFSC PORTA, 1				;Analisando se o botão RA1 está pressionado
			GOTO VERIFICA_SETAR_CRESC	;Caso NÃO esteja, ele vai analisar se é preciso setar o contador do display para 0 (passar de 9 -> crescente)
			GOTO VERIFICA_SETAR_DECRESC	;Caso esteja, ele vai analisar se é preciso setar o contador do display para 9 ("passar" de 0 -> decrescente)
;-------------------------------------------------------------
;Verifica se é necessário setar o contador do display para 0 (Crescente)
VERIFICA_SETAR_CRESC:
			MOVF COUNT_DISPLAY, W 	;Move o valor do contador do display para W
			SUBLW D'10' 		  	;Realiza a subtração de 10 para verificar o carry
			BTFSC STATUS, Z		  	;Setar para 0 se a flag Z estiver com 0
			GOTO SETAR_CRESC		;Chama a sub-rotina para setar o contador do display para 0
			GOTO FIM_VERIFICA_COUNT ;Retorna em caso de nenhuma alteração
;-------------------------------------------------------------
;Verifica se é necessário setar o contador do display para 9 (Decrescente)
VERIFICA_SETAR_DECRESC:
			MOVF COUNT_DISPLAY, W 	;Move o valor do contador do display para W
			SUBLW D'255' 		  	;Realiza a subtração de 255 ("-1") para verificar o carry
			BTFSC STATUS, Z		  	;Setar para 0 se a flag Z estiver com 0
			GOTO SETAR_DECRESC	;Chama a sub-rotina para setar o contador do display para 9
			GOTO FIM_VERIFICA_COUNT ;Retorna em caso de nenhuma alteração
;-------------------------------------------------------------
;Seta o contador do display para 0 (após verificação)
SETAR_CRESC:
			MOVLW D'0'				;Setando o contador do display para 0
			MOVWF COUNT_DISPLAY
			CALL DISPLAY_NUMBER0	;Chama a sub-rotina para setar o dígito 0 no display
			GOTO FIM_VERIFICA_COUNT ;Retorna em caso de nenhuma alteração
;-------------------------------------------------------------
;Seta o contador do display para 9 (após verificação)
SETAR_DECRESC:
			MOVLW D'9'				;Setando o contador do display para 9
			MOVWF COUNT_DISPLAY
			CALL DISPLAY_NUMBER9	;Chama a sub-rotina para setar o dígito 9 no display
			GOTO FIM_VERIFICA_COUNT ;Retorna em caso de nenhuma alteração

FIM_VERIFICA_COUNT: RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração do registrador OPTION_REG
CONFIG_OPTIONREG:
			 BANKSEL OPTION_REG
			 MOVLW B'10000101'
			 MOVWF OPTION_REG
			 RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração do registrador INTCON
CONFIG_INTCON:
			 BANKSEL INTCON
			 MOVLW B'10100000'
			 MOVWF INTCON
			 RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração do registrador TRISA (PORTA)
CONFIG_TRISA:
			 BANKSEL TRISA
			 MOVLW B'00000010' ;Colocando o RA1 como input
			 MOVWF TRISA
			 RETURN
;-------------------------------------------------------------
; Configuração do registrador TRISB (PORTB)
CONFIG_TRISB:
			 BANKSEL TRISB
			 MOVLW B'00000000' ;Definindo todos RBx como output (display)
			 MOVWF TRISB
			 RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração inicial da PORTA
CONFIG_PORTA:
			 BANKSEL PORTA
			 CLRF PORTA
			 MOVLW D'7'
			 MOVWF CMCON
			 RETURN		 
;-------------------------------------------------------------
; Configuração inicial da PORTB
CONFIG_PORTB:
			 BANKSEL PORTB
			 MOVLW B'11111110'
			 MOVWF PORTB
			 RETURN
;-------------------------------------------------------------
;-------------------------------------------------------------
; Configuração do registrador TMR0 (Timer0)
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
;Para isso, basta analisar a flag Z do registrador de status após operações básicas
LOOP:	
		CALL VERIFICA_COUNT ;Chama a sub-rotina de verificar o contador do display
		
		GOTO LOOP	
END
;-------------------------------------------------------------
;-------------------------------------------------------------